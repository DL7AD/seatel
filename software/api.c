#include "ch.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/netif.h"
#include "chprintf.h"

#include "main.h"
#include "api.h"
#include "imu.h"
#include "mde.h"
#include "ctrl.h"
#include "debug.h"

//static char separator = '.';
static bool connected = false;

static bool extract_numbers(char *msg, float *az, float *el)
{
    // P 180.00 45.00_
    // 012345678901234
    uint8_t l = strlen(msg);
    uint8_t i = 2;

    char* n1 = &msg[2];

    while(i<l && msg[i] != '.' && msg[i] != ',') i++;

    //if(msg[i] == '.' || msg[i] == ',')
    //    separator = msg[i];

    msg[i] = '_';
    char* n2 = &msg[++i];

    while(i<l && msg[i] != ' ') i++;
    msg[i] = '_';
    char* n3 = &msg[++i];

    while(i<l && msg[i] != '.' && msg[i] != ',') i++;
    msg[i] = '_';
    char* n4 = &msg[++i];

    *az = atoi(n1) + atoi(n2)/100.0;
    *el = atoi(n3) + atoi(n4)/100.0;

    return i != l;
}

static void server_serve(struct netconn *conn) {
    struct netbuf *inbuf;

    uint8_t *data;
    uint16_t len;
    char buf[128];
    float az,el,last_az,last_el;
    systime_t last_cmd = chVTGetSystemTimeX();
    err_t err;

    // Switch connected-LED
    palSetLine(LINE_CONNECTED);
    connected = true;

    // Serve request
    while ((err = netconn_recv(conn, &inbuf)) == ERR_OK)
    {
        bool quit_conn = false;
        do
        {
            netbuf_data(inbuf, (void*)&data, &len);

            if(!len)
                continue;

            memset(buf, 0, sizeof(buf));
            memcpy(buf, data, len < sizeof(buf) ? len : sizeof(buf));

            switch(data[0])
            {
                case 'p':
                    // Get position of rotator
                    az = mde_get_az_enc_pos() / 182.044;
                    el = imu_get_el_pos()     / 182.044;
                    chsnprintf(buf, sizeof(buf), "%.2f\n%.2f\n", az, el);
                    netconn_write(conn, buf, strlen(buf), NETCONN_COPY);
                    break;
                case 'P':
                    // Set position of rotator
                    if(!extract_numbers(buf, &az, &el)) {
                        break; // Error
                    }

                    az_set_tgt_pos(az*182.044);
                    el_set_tgt_pos(el*182.044);
                    if(TIME_I2MS(chVTGetSystemTimeX()-last_cmd) < 3000)
                    {
                        int16_t az_spd = (az-last_az)*182.044 / (TIME_I2MS(chVTGetSystemTimeX()-last_cmd)/1000.0);
                        int16_t el_spd = (el-last_el)*182.044 / (TIME_I2MS(chVTGetSystemTimeX()-last_cmd)/1000.0);
                        if(abs(az_spd) < 5*182 && abs(el_spd) < 5*182)
                        {
                            //az_set_tgt_pos_spd(az_spd);
                            //el_set_tgt_pos_spd(el_spd);
                            az_set_tgt_pos_spd(0);
                            el_set_tgt_pos_spd(0);
                        }
                    }

                    last_az = az;
                    last_el = el;
                    last_cmd = chVTGetSystemTimeX();

                    netconn_write(conn, "ack\n", 4, NETCONN_COPY);


                    break;
                case 'S':
                    // Stop rotator
                    az_set_tgt_pos(mde_get_az_enc_pos());
                    el_set_tgt_pos(imu_get_el_pos());
                    az_set_tgt_pos_spd(0);
                    el_set_tgt_pos_spd(0);

                    netconn_write(conn, "S\n", 2, NETCONN_COPY);

                    break;
                case 'q':
                    // Quit connection
                    quit_conn = true;
                    break;
            }

        } while(!quit_conn && netbuf_next(inbuf) >= 0);
        netbuf_delete(inbuf);
    }

    // Close the connection (server closes)
    netconn_close(conn);

    // Delete the buffer (netconn_recv gives us ownership, so we have to make sure to deallocate the buffer)
    netbuf_delete(inbuf);

    // Switch connected-LED
    palClearLine(LINE_CONNECTED);
    connected = false;
}


THD_WORKING_AREA(wa_api, API_THREAD_STACK_SIZE);
THD_FUNCTION(apiserver, p) {
    (void)p;

    struct netconn *conn, *newconn;
    err_t err;

    // Create a new TCP connection handle
    conn = netconn_new(NETCONN_TCP);
    LWIP_ERROR("server: invalid conn", (conn != NULL), chThdExit(MSG_RESET););

    // Bind to port
    netconn_bind(conn, NULL, API_THREAD_PORT);

    // Put the connection into LISTEN state
    netconn_listen(conn);

    // Goes to the final priority after initialization
    chThdSetPriority(API_THREAD_PRIORITY);

    while (true) {
        err = netconn_accept(conn, &newconn);
        if (err != ERR_OK)
            continue;
        server_serve(newconn);
        netconn_delete(newconn);
    }
}

void api_init(void)
{
    chThdCreateStatic(wa_api, sizeof(wa_api), API_THREAD_PRIORITY, apiserver, NULL);
}

bool api_is_connected(void)
{
    return connected;
}
