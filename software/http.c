#include "ch.h"

#include <stdlib.h>
#include <string.h>

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/netif.h"
#include "chprintf.h"

#include "http.h"
#include "config.h"
#include "jquery.h"
#include "favicon.h"
#include "ctrl.h"
#include "mde.h"
#include "imu.h"
#include "api.h"
#include "debug.h"
#include "ina3221.h"
#include "ocxo.h"
#include "gps.h"

#define HTTP_PRINT(str) { \
    netconn_write(conn, (str), strlen((str)), NETCONN_NOCOPY); \
    netconn_write(conn, "\n", 1, NETCONN_NOCOPY); \
}
#define HTTP_PRINT_COPY(str) { \
    netconn_write(conn, (str), strlen((str)), NETCONN_COPY); \
    netconn_write(conn, "\n", 1, NETCONN_NOCOPY); \
}

static void print_ack(struct netconn *conn)
{
    HTTP_PRINT("HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\nOK");
}

static void print_debug(struct netconn *conn)
{
    char str[DEBUG_BUCKET_SIZE];
    debug_emty_bucket(str);
    HTTP_PRINT("HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n");
    HTTP_PRINT_COPY(str);
}

static void print_page(struct netconn *conn)
{
    char buf[1024];

    HTTP_PRINT(
        "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n\n\
        <!DOCTYPE html>\n\
        <html>\n\
        <head>\n\
        <meta content='text/html;charset=utf-8' http-equiv='Content-Type'>\n\
        <meta content='utf-8' http-equiv='encoding'>\n\
        <title>Sea Tel Antenna</title>\n\
        <style type='text/css'>\n\
        html {\n\
            font-family: Monospace;\n\
        }\n\
        input {\n\
            border: solid 1px #888888;\n\
            font-family: Monospace;\n\
        }\n\
        td {\n\
            border: solid 1px #888888;\n\
            padding: 3px;\n\
            height: 22px;\n\
        }\n\
        a {\n\
            text-decoration:none;\n\
        }\n\
        a:hover {\n\
            text-decoration:underline;\n\
        }\n\
        .container {\n\
            float: left;\n\
            margin: 3px;\n\
            padding: 5px;\n\
            border: 1px solid #888888;\n\
        }\n\
        #deviation {\n\
            width: 301px;\n\
            height: 301px;\n\
            background-size: 30px 30px;\n\
            border: 0;\n\
            margin: 0;\n\
            padding: 0;\n\
            background-image:\n\
            linear-gradient(to right, gray 1px, transparent 1px),\n\
            linear-gradient(to bottom, gray 1px, transparent 1px);\n\
        }\n\
        #pointing {\n\
            width: 301px;\n\
            height: 301px;\n\
            margin: 25px 30px;\n\
            padding: 0;\n\
            float: left;\n\
            background-size: 151px 151px;\n\
            background-image:\n\
            linear-gradient(to right, transparent 150px, gray 1px),\n\
            linear-gradient(to bottom, transparent 150px, gray 1px);\n\
            font-size: 16px;\n\
        }\n\
        #pointing .legend {\n\
            font-size: 12px;\n\
            margin-top: 280px;\n\
            margin-left: -15px;\n\
        }\n\
        #pointing .title {\n\
            font-size: 12px;\n\
            margin-top: -19px;\n\
            margin-left: -15px;\n\
        }\n\
        #pointing span {\n\
            position: absolute;\n\
            padding: 0;\n\
        }\n\
        #pointing_n {\n\
            margin-top: -19px;\n\
            margin-left: 145px;\n\
        }\n\
        #pointing_s {\n\
            margin-top: 303px;\n\
            margin-left: 145px;\n\
        }\n\
        #pointing_w {\n\
            margin-top: 142px;\n\
            margin-left: -15px;\n\
        }\n\
        #pointing_e {\n\
            margin-top: 142px;\n\
            margin-left: 305px;\n\
        }\n\
        #pointing #pointing_circle0,#pointing #pointing_circle30,#pointing #pointing_circle60 {\n\
            position: absolute;\n\
            padding: 0;\n\
            border-radius: 100%;\n\
            border: 1px solid gray;\n\
        }\n\
        #pointing_circle0 {\n\
            width: 100px;\n\
            height: 100px;\n\
            margin-top: 100px;\n\
            margin-left: 100px;\n\
        }\n\
        #pointing_circle30 {\n\
            width: 200px;\n\
            height: 200px;\n\
            margin-top: 50px;\n\
            margin-left: 50px;\n\
        }\n\
        #pointing_circle60 {\n\
            width: 300px;\n\
            height: 300px;\n\
            margin: 0;\n\
        }\n\
        .cross {\n\
            position: absolute;\n\
            border: 0;\n\
            padding: 5px;\n\
            width: 15px;\n\
            height: 15px;\n\
            background-size: 14px 14px;\n\
            margin-top: 138px;\n\
            margin-left: 138px;\n\
        }\n\
        #cross_pointing {\n\
            background-image:\n\
            linear-gradient(to right, transparent 11px, red 1px),\n\
            linear-gradient(to bottom, transparent 11px, red 1px);\n\
        }\n\
        #cross_deviation {\n\
            background-image:\n\
            linear-gradient(to right, transparent 11px, gray 1px),\n\
            linear-gradient(to bottom, transparent 11px, gray 1px);\n\
        }\n\
        .circle {\n\
            position: absolute;\n\
            padding: 0;\n\
            border-radius: 100%;\n\
            border: 1px solid red;\n\
            width: 17px;\n\
            height: 17px;\n\
            margin-top: 141px;\n\
            margin-left: 141px;\n\
        }\n\
        h1 {\n\
            margin: 5px 0;\n\
        }\n\
        #debug {\n\
            overflow: scroll;\n\
            height: 360px;\n\
        }\n\
        </style>\n\
        <script type='text/javascript'>\n\
        const zeroPad = (num, places) => String(num).padStart(places, '0');\n\
        var az_tgt,el_tgt,sk_tgt,az_off,el_off = 0;\n\
        var req = function() {\n\
            $.ajax({\n\
                dataType: \"json\",\n\
                url: \"/state.json\",\n\
                success: function(data) {\n\
                    //$('#time').text('Time: ' + (val/100000));\n\
                    $('#motor_az').text(data['mde']['mot'][0]);\n\
                    $('#motor_el').text(data['mde']['mot'][1]);\n\
                    $('#motor_sk').text(data['mde']['mot'][2]);\n\
                    $('#motor_state_az').text(data['ctrl']['state'][0]);\n\
                    $('#motor_state_el').text(data['ctrl']['state'][1]);\n\
                    $('#motor_state_sk').text(data['ctrl']['state'][2]);\n\
                    $('#tgt_az').text(data['ctrl']['state'][0].localeCompare('TARGET_POSITION') ? 'MANUAL' : (data['ctrl']['tgt'][0]*360/65536).toFixed(2)+'°');\n\
                    $('#tgt_el').text(data['ctrl']['state'][1].localeCompare('TARGET_POSITION') ? 'MANUAL' : (data['ctrl']['tgt'][1]*360/65536).toFixed(2)+'°');\n\
                    az_tgt = data['ctrl']['tgt'][0];\n\
                    el_tgt = data['ctrl']['tgt'][1];\n\
                    sk_tgt = data['ctrl']['tgt'][2];\n\
                    $('#enc').text(data['mde']['enc']['pos']);\n\
                    $('#enc_dec').text((data['mde']['enc']['pos']*360/65536).toFixed(2)+'°');\n\
                    $('#off_az').text((data['mde']['enc']['off']*360/65536).toFixed(2)+'°');\n\
                    az_off = data['mde']['enc']['off'];\n\
                    $('#pos_and_off_az').text(((data['mde']['enc']['pos']+data['mde']['enc']['off'])*360/65536).toFixed(2)+'°');\n\
                    $('#enc_spd').text(data['mde']['enc']['spd']);\n\
                    $('#enc_spd_dec').text((data['mde']['enc']['spd']*360/65536).toFixed(2)+'°/sec');\n\
                    $('#imu_accel_x').text(data['imu']['accel'][0]);\n\
                    $('#imu_accel_x_dec').text((data['imu']['accel'][0]/4096).toFixed(3)+'g');\n\
                    $('#imu_accel_y').text(data['imu']['accel'][1]);\n\
                    $('#imu_accel_y_dec').text((data['imu']['accel'][1]/4096).toFixed(3)+'g');\n\
                    $('#imu_accel_z').text(data['imu']['accel'][2]);\n\
                    $('#imu_accel_z_dec').text((data['imu']['accel'][2]/4096).toFixed(3)+'g');\n\
                    $('#imu_rot_x').text(data['imu']['rot'][0]);\n\
                    $('#imu_rot_y').text(data['imu']['rot'][1]);\n\
                    $('#imu_rot_z').text(data['imu']['rot'][2]);\n\
                    $('#imu_el_pos').text(data['imu']['el']['pos']);\n\
                    $('#imu_el_pos_dec').text((data['imu']['el']['pos']*360/65536).toFixed(2)+'°');\n\
                    $('#imu_el_spd').text(data['imu']['el']['spd']);\n\
                    $('#imu_el_spd_dec').text((data['imu']['el']['spd']*360/65536).toFixed(2)+'°');\n\
                    var az = data['mde']['enc']['pos'] + data['mde']['enc']['off'];\n\
                    var el = data['imu']['el']['pos'];\n\
                    var left = 141-(az-data['ctrl']['tgt'][0])*360/65536*60;\n\
                    var top  = 141+(el-data['ctrl']['tgt'][1])*360/65536*60;\n\
                    if(top >  292) top  = 292;\n\
                    if(top <   -8) top  = -8;\n\
                    if(left > 292) left = 292;\n\
                    if(left <  -8) left = -8;\n\
                    $('#circle_deviation').css({'margin-left': left, 'margin-top': top});\n\
                    left = 138+Math.sin(az*2*Math.PI/65536)*150*(16384-el)/16384;\n\
                    top  = 138-Math.cos(az*2*Math.PI/65536)*150*(16384-el)/16384;\n\
                    $('#cross_pointing').css({'margin-left': left, 'margin-top': top});\n\
                    if(data['ctrl']['state'][0].localeCompare('TARGET_POSITION')) {\n\
                        $('#circle_target').css('visibility', 'hidden');\n\
                    } else {\n\
                        el = (16384-data['ctrl']['tgt'][1])/16384;\n\
                        left = 141+Math.sin(data['ctrl']['tgt'][0]*2*Math.PI/65536)*150*el;\n\
                        top  = 141-Math.cos(data['ctrl']['tgt'][0]*2*Math.PI/65536)*150*el;\n\
                        $('#circle_target').css({'margin-left': left, 'margin-top': top});\n\
                        $('#circle_target').css('visibility', 'visible');\n\
                    }\n\
                    $('#api_connected').html(data['api_connected'] ? 'CONNECTED &#x1F7E2;' : 'DISCONNECTED &#x1F534;');\n\
                    $('#pwr_lna1_v').text((data['pwr']['lna1'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_lna1_p').text((data['pwr']['lna1'][1]/1000).toFixed(2)+' W');\n\
                    $('#pwr_lna2_v').text((data['pwr']['lna2'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_lna2_p').text((data['pwr']['lna2'][1]/1000).toFixed(2)+' W');\n\
                    $('#pwr_ocxo_v').text((data['pwr']['ocxo'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_ocxo_p').text((data['pwr']['ocxo'][1]/1000).toFixed(2)+' W');\n\
                    $('#pwr_ext5_v').text((data['pwr']['ext5'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_ext5_p').text((data['pwr']['ext5'][1]/1000).toFixed(2)+' W');\n\
                    $('#pwr_ext24_v').text((data['pwr']['ext24'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_ext24_p').text((data['pwr']['ext24'][1]/1000).toFixed(2)+' W');\n\
                    $('#pwr_mde_v').text((data['pwr']['mde'][0]/1000).toFixed(2)+' V');\n\
                    $('#pwr_mde_p').text((data['pwr']['mde'][1]/1000).toFixed(2)+' W');\n\
                    $('#time').html('20'+\n\
                        zeroPad(data['gps']['date']%100,2)+'-'+\n\
                        zeroPad(Math.round(data['gps']['date']/100)%100,2)+'-'+\n\
                        zeroPad(Math.round(data['gps']['date']/10000),2)+' '+\n\
                        zeroPad(Math.round(data['gps']['time']/10000),2)+':'+\n\
                        zeroPad(Math.round(data['gps']['time']/100)%100,2)+':'+\n\
                        zeroPad(data['gps']['time']%100,2)+\n\
                        (data['gps']['pulse'] ? ' &#x1F7E2;' : ''));\n\
                    $('#lat').text((data['gps']['lat']).toFixed(5)+'°');\n\
                    $('#lon').text((data['gps']['lon']).toFixed(5)+'°');\n\
                    $('#alt').text((data['gps']['alt']).toFixed(1)+'m');\n\
                    $('#sats').text(data['gps']['sats_sol']+'/x');\n\
                    $('#ocxo').text(data['ocxo']['cntr']+' / '+data['ocxo']['dac']);\n\
                },\n\
                timeout: 1000\n\
            });\n\
        }\n\
        var deb = function() {\n\
            $.ajax({\n\
                dataType: \"text\",\n\
                url: \"/debug\",\n\
                success: function( data ) {\n\
                    if(data.trim() != '') {\n\
                        var scrolled_bottom = $('#debug').scrollTop()+$('#debug').height() == $('#debug').prop('scrollHeight');\n\
                        $('#debug').append(data.trim().replaceAll(\"\\n\",\"<br />\")+'<br />');\n\
                        if(scrolled_bottom) {\n\
                            $('#debug').scrollTop($('#debug').prop('scrollHeight'));\n\
                        }\n\
                    }\n\
                },\n\
                timeout: 1000\n\
            });\n\
        }\n\
        var start_req = function() {\n\
            window.setInterval(req, 100);\n\
            window.setInterval(deb, 100);\n\
        }\n\
        var load = function() {\n\
            window.setTimeout(start_req, 500);\n\
            var script = document.createElement('script');\n\
            script.src = 'jquery.js';\n\
            document.getElementsByTagName('head')[0].appendChild(script);\n\
        }\n\
        var set_motor = function(motor, torque) {\n\
            $.get('/set/trq/'+motor+'/'+torque);\n\
        }\n\
        var calibrate = function() {\n\
            $.get('/calibrate');\n\
        }\n\
        var set_az_tgt = function(az) {\n\
            if(az != 0) { $.get('/set/tar/az/'+Math.round(az_tgt+az*182.04));\n\
            } else {      $.get('/set/tar/az/'+Math.round($('#az_tgt_in').val()*182.04)); }\n\
        }\n\
        var set_el_tgt = function(el) {\n\
            if(el != 0) { $.get('/set/tar/el/'+Math.round(el_tgt+el*182.04));\n\
            } else {      $.get('/set/tar/el/'+Math.round($('#el_tgt_in').val()*182.04)); }\n\
        }\n\
        var set_sk_tgt = function(sk) {\n\
            if(sk != 0) { $.get('/set/tar/sk/'+Math.round(sk_tgt+sk*182.04));\n\
            } else {      $.get('/set/tar/sk/'+Math.round($('#sk_tgt_in').val()*182.04)); }\n\
        }\n\
        var set_az_off = function(az) {\n\
            if(az != 0) { $.get('/set/off/az/'+Math.round(az_off+az*182.04));\n\
            } else {      $.get('/set/off/az/'+Math.round($('#az_off_in').val()*182.04)); }\n\
        }\n\
        var set_el_off = function(el) {\n\
            if(el != 0) { $.get('/set/tar/el/'+Math.round(el_off+el*182.04));\n\
            } else {      $.get('/set/tar/el/'+Math.round($('#el_off_in').val()*182.04)); }\n\
        }\n\
        var sw = function(tar, state) {\n\
            $.get('/sw/'+tar+'/'+state);\n\
        }\n\
        </script>\n\
        <body onload='window.setTimeout(load, 500)'>\n\
        <div class='container'>\n\
        <h1>Motors</h1>\n\
        <hr />\n\
        <table>\n\
        <tr>\n\
        <td width='80'>Motor</td>\n\
        <td width='120'>State</td>\n\
        <td width='60'>Torque</td>\n\
        <td>Manual Control</td>\n\
        </tr>\n\
    ");

    const char name[3][13] = {"Azimuth", "Elevation", "Skew"};
    const char abbrevation[3][3] = {"az", "el", "sk"};

    for(uint8_t i=0; i<3; i++)
    {
        HTTP_PRINT("<tr>");
        chsnprintf(buf, sizeof(buf), "<td>%s</td>", name[i]);
        HTTP_PRINT_COPY(buf);
        chsnprintf(buf, sizeof(buf), "<td id='motor_state_%s'></td>", abbrevation[i]);
        HTTP_PRINT_COPY(buf);
        chsnprintf(buf, sizeof(buf), "<td id='motor_%s'></td>", abbrevation[i]);
        HTTP_PRINT_COPY(buf);
        HTTP_PRINT("<td>");
        for(int8_t torque=-60; torque<=60; torque+=5)
        {
            if(torque) {
                chsnprintf(buf, sizeof(buf), "<input type='button' value='%+03d' onclick='set_motor(\"%s\",%d)' />", torque, abbrevation[i], torque);
            } else {
                chsnprintf(buf, sizeof(buf), "&nbsp;<input type='button' value='STOP' onclick='set_motor(\"%s\",0)' />&nbsp;", abbrevation[i]);
            }
            HTTP_PRINT_COPY(buf);
        }
        HTTP_PRINT("</td>");
        HTTP_PRINT("</tr>");
    }

    HTTP_PRINT(
        "</table>\n\
        </div>\n\
        <div class='container' style='width:1349px;height:500px;'>\n\
        <h1>Sensors</h1>\n\
        <hr />\n\
        <table style='float:left;'>\n\
        <tr>\n\
        <td width='200'>Sensor</td>\n\
        <td width='100'>Raw</td>\n\
        <td width='100'>Decoded</td>\n\
        <td width='80'>Offset</td>\n\
        <td width='120'>Set Offset</td>\n\
        <td width='80'>Corrected</td>\n\
        </tr>\n\
        <tr>\n\
        <td rowspan='2'>Azimuth Encoder</td>\n\
        <td rowspan='2' id='enc'></td>\n\
        <td rowspan='2' id='enc_dec'></td>\n\
        <td id='off_az'></td>\n\
        <td><input id='az_off_in' size='6' />° <input type='button' onclick='set_az_off(0)' value='Set' /></td>\n\
        <td rowspan='2' align='center' id='pos_and_off_az'></td>\n\
        </tr>\n\
        <tr>\n\
        <td colspan='2'>\n\
        <input type='button' onclick='set_az_off(-10)' value='---' />\n\
        <input type='button' onclick='set_az_off(-1)' value='--' />\n\
        <input type='button' onclick='set_az_off(-0.1)' value='-' />\n\
        <input type='button' onclick='set_az_off(0.1)' value='+' />\n\
        <input type='button' onclick='set_az_off(1)' value='++' />\n\
        <input type='button' onclick='set_az_off(10)' value='+++' />\n\
        </td>\n\
        </tr>\n\
        <tr>\n\
        <td>Azimuth Encoder Speed</td>\n\
        <td id='enc_spd'></td>\n\
        <td id='enc_spd_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Acceleration X</td>\n\
        <td id='imu_accel_x'></td>\n\
        <td id='imu_accel_x_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Acceleration Y</td>\n\
        <td id='imu_accel_y'></td>\n\
        <td id='imu_accel_y_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Acceleration Z</td>\n\
        <td id='imu_accel_z'></td>\n\
        <td id='imu_accel_z_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Rotation X</td>\n\
        <td id='imu_rot_x'></td>\n\
        <td id='imu_rot_x_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Rotation Y</td>\n\
        <td id='imu_rot_y'></td>\n\
        <td id='imu_rot_y_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>IMU Rotation Z</td>\n\
        <td id='imu_rot_z'></td>\n\
        <td id='imu_rot_z_dec'></td>\n\
        </tr>\n\
        <tr>\n\
        <td rowspan='2'>Elevation</td>\n\
        <td rowspan='2' id='imu_el_pos'></td>\n\
        <td rowspan='2' id='imu_el_pos_dec'></td>\n\
        <td id='off_el'>XXX</td>\n\
        <td><input id='el_off_in' size='6' />° <input type='button' onclick='set_el_off(0)' value='Set' /></td>\n\
        <td rowspan='2' align='center' id='tgt_and_off_el'>XXX</td>\n\
        </tr>\n\
        <tr>\n\
        <td colspan='2'>\n\
        <input type='button' onclick='set_el_off(-10)' value='---' />\n\
        <input type='button' onclick='set_el_off(-1)' value='--' />\n\
        <input type='button' onclick='set_el_off(-0.1)' value='-' />\n\
        <input type='button' onclick='set_el_off(0.1)' value='+' />\n\
        <input type='button' onclick='set_el_off(1)' value='++' />\n\
        <input type='button' onclick='set_el_off(10)' value='+++' />\n\
        </td>\n\
        </tr>\n\
        <tr>\n\
        <td>Elevation Speed</td>\n\
        <td id='imu_el_spd'></td>\n\
        <td id='imu_el_spd_dec'></td>\n\
        </tr>\n\
        </table>\n\
        <div stlye='float:left;'>\n\
        <div id='pointing'>\n\
        <span class='title'>Pointing diagram</span>\n\
        <span id='pointing_n'>N</span>\n\
        <span id='pointing_w'>W</span>\n\
        <span id='pointing_e'>E</span>\n\
        <span id='pointing_s'>S</span>\n\
        <div id='pointing_circle0'></div>\n\
        <div id='pointing_circle30'></div>\n\
        <div id='pointing_circle60'></div>\n\
        <div class='cross' id='cross_pointing'></div>\n\
        <div id='circle_target' class='circle'></div>\n\
        <span class='legend'>\n\
        30°/div<br />\n\
        circle: target<br />\n\
        cross: pointing\n\
        </span>\n\
        </div>\n\
        </div>\n\
        </div>\n\
        <div class='container' style='width:531px;height:276px;'>\n\
        <h1>Power</h1>\n\
        <hr />\n\
        <table style='float:left;'>\n\
        <tr>\n\
        <td width='100'>Bus</td>\n\
        <td width='80'></td>\n\
        <td width='80'>Voltage</td>\n\
        <td width='80'>Power</td>\n\
        </tr>\n\
        <tr>\n\
        <td>MDE</td>\n\
        <td><input type='button' value='On' onclick='sw(\"mde\", 1)'> <input type='button' value='Off' onclick='sw(\"mde\", 0)'></td>\n\
        <td id='pwr_mde_v'></td>\n\
        <td id='pwr_mde_p'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>External 5V</td>\n\
        <td><input type='button' value='On' onclick='sw(\"ext5\", 1)'> <input type='button' value='Off' onclick='sw(\"ext5\", 0)'></td>\n\
        <td id='pwr_ext5_v'></td>\n\
        <td id='pwr_ext5_p'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>External 24V</td>\n\
        <td><input type='button' value='On' onclick='sw(\"ext24\", 1)'> <input type='button' value='Off' onclick='sw(\"ext24\", 0)'></td>\n\
        <td id='pwr_ext24_v'></td>\n\
        <td id='pwr_ext24_p'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>LNA 1</td>\n\
        <td rowspan='2'><input type='button' value='On' onclick='sw(\"lna\", 1)'> <input type='button' value='Off' onclick='sw(\"lna\", 0)'></td>\n\
        <td id='pwr_lna1_v'></td>\n\
        <td id='pwr_lna1_p'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>LNA 2</td>\n\
        <td id='pwr_lna2_v'></td>\n\
        <td id='pwr_lna2_p'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>OCXO</td>\n\
        <td></td>\n\
        <td id='pwr_ocxo_v'></td>\n\
        <td id='pwr_ocxo_p'></td>\n\
        </tr>\n\
        </table>\n\
        </div>\n\
        <div class='container' style='width:531px;height:116px;'>\n\
        <h1>GPS</h1>\n\
        <hr />\n\
        <table style='float:left;'>\n\
        <tr>\n\
        <td width='70'>Time</td>\n\
        <td width='175' id='time'></td>\n\
        <td width='0' style='border:0;'></td>\n\
        <td width='40'>Lat</td>\n\
        <td width='70' id='lat'></td>\n\
        <td width='0' style='border:0;'></td>\n\
        <td width='35'>Alt</td>\n\
        <td width='60' id='alt'></td>\n\
        </tr>\n\
        <tr>\n\
        <td>OCXO/DAC</td>\n\
        <td id='ocxo'></td>\n\
        <td style='border:0;'></td>\n\
        <td>Lon</td>\n\
        <td id='lon'></td>\n\
        <td style='border:0;'></td>\n\
        <td>Sats</td>\n\
        <td id='sats'></td>\n\
        </tr>\n\
        </table>\n\
        </div>\n\
        <div class='container' style='width:1349px;height:410px;'>\n\
        <h1>Automation <input type='button' onclick='calibrate()' value='Calibrate Azimuth'></h1>\n\
        <hr />\n\
        <table style='float:left;'>\n\
        <tr>\n\
        <td width='80'></td>\n\
        <td width='70'>Target</td>\n\
        <td width='120'>Set Target</td>\n\
        </tr>\n\
    ");

    for(uint8_t i=0; i<2; i++)
    {
        chsnprintf(buf, sizeof(buf),
            "<tr>\n\
            <td rowspan='2'>%s</td>\n\
            <td id='tgt_%s'></td>\n\
            <td><input id='%s_tgt_in' size='6' />° <input type='button' onclick='set_%s_tgt(0)' value='Set' /></td>\n\
            </tr>\n\
            <tr>\n\
            <td colspan='2'>\n\
            <input type='button' onclick='set_%s_tgt(-10)' value='---' />\n\
            <input type='button' onclick='set_%s_tgt(-1)' value='--' />\n\
            <input type='button' onclick='set_%s_tgt(-0.1)' value='-' />\n\
            <input type='button' onclick='set_%s_tgt(0.1)' value='+' />\n\
            <input type='button' onclick='set_%s_tgt(1)' value='++' />\n\
            <input type='button' onclick='set_%s_tgt(10)' value='+++' />\n\
            </td>\n\
            </tr>", name[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i], abbrevation[i]);
        HTTP_PRINT_COPY(buf);

    }

    HTTP_PRINT(
        "<tr height='5'></tr>\n\
        <tr>\n\
        <td>API</td>\n\
        <td colspan='2' id='api_connected'></td>\n\
        </tr>\n\
        </table>\n\
        <div style='float:left;margin-left:20px;'>\n\
        Deviation diagram<br />\n\
        <div id='deviation'>\n\
        <div class='cross' id='cross_deviation'></div>\n\
        <div id='circle_deviation' class='circle'></div></div>\n\
        0.5°/div, red: target, center: pointing\n\
        </div>\n\
        </div>\n\
        <div class='container' style='width:630px;height:410px;'>\n\
        <h1>Debug</h1>\n\
        <hr />\n\
        <div id='debug'></div>\n\
        </div>\n\
        </body>\n\
        </html>\
    ");
}

static void print_json(struct netconn *conn) {
    char buf[1024];
    uint32_t len = chsnprintf(buf, sizeof(buf), "{\"mde\":{\"mot\":[%d,%d,%d],\"enc\":{\"pos\":%d,\"spd\":%d,\"off\":%d}},",
        mde_get_trq_az(), mde_get_trq_el(), mde_get_trq_sk(),
        mde_get_az_enc_pos(), mde_get_az_enc_spd(), mde_get_az_enc_off());
    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"imu\":{\"accel\":[%d,%d,%d],\"rot\":[%d,%d,%d],\"el\":{\"pos\":%d,\"spd\":%d}},",
        imu_get_accel_x(), imu_get_accel_y(), imu_get_accel_z(), imu_get_rot_x(), imu_get_rot_y(), imu_get_rot_z(), imu_get_el_pos(), imu_get_el_spd());
    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"ctrl\":{\"state\":[\"%s\",\"%s\",\"%s\"],\"tgt\":[%d,%d,%d]},",
        MOTOR_STATE(az_get_state()), MOTOR_STATE(el_get_state()), MOTOR_STATE(sk_get_state()),
        az_get_tgt_pos(), el_get_tgt_pos(), sk_get_tgt_pos());


    const mon_source_t mon_ext5_v  = {MON_PORT_1, MON_NMVOLT};
    const mon_source_t mon_ext5_p  = {MON_PORT_1, MON_NMWATT};
    const mon_source_t mon_ext24_v = {MON_PORT_2, MON_NMVOLT};
    const mon_source_t mon_ext24_p = {MON_PORT_2, MON_NMWATT};
    const mon_source_t mon_mde_v   = {MON_PORT_3, MON_NMVOLT};
    const mon_source_t mon_mde_p   = {MON_PORT_3, MON_NMWATT};
    const mon_source_t mon_lna1_v  = {MON_PORT_4, MON_NMVOLT};
    const mon_source_t mon_lna1_p  = {MON_PORT_4, MON_NMWATT};
    const mon_source_t mon_lna2_v  = {MON_PORT_5, MON_NMVOLT};
    const mon_source_t mon_lna2_p  = {MON_PORT_5, MON_NMWATT};
    const mon_source_t mon_ocxo_v  = {MON_PORT_6, MON_NMVOLT};
    const mon_source_t mon_ocxo_p  = {MON_PORT_6, MON_NMWATT};
    mon_reading_t ext5_v,ext5_p,ext24_v,ext24_p,mde_v,mde_p,ocxo_v,ocxo_p,lna1_v,lna1_p,lna2_v,lna2_p;
    ina3221_get_current_reading(&mon_ext5_v,  &ext5_v);
    ina3221_get_current_reading(&mon_ext5_p,  &ext5_p);
    ina3221_get_current_reading(&mon_ext24_v, &ext24_v);
    ina3221_get_current_reading(&mon_ext24_p, &ext24_p);
    ina3221_get_current_reading(&mon_mde_v,   &mde_v);
    ina3221_get_current_reading(&mon_mde_p,   &mde_p);
    ina3221_get_current_reading(&mon_lna1_v,  &lna1_v);
    ina3221_get_current_reading(&mon_lna1_p,  &lna1_p);
    ina3221_get_current_reading(&mon_lna2_v,  &lna2_v);
    ina3221_get_current_reading(&mon_lna2_p,  &lna2_p);
    ina3221_get_current_reading(&mon_ocxo_v,  &ocxo_v);
    ina3221_get_current_reading(&mon_ocxo_p,  &ocxo_p);

    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"pwr\":{\"ext5\":[%d,%d],\"ext24\":[%d,%d],\"mde\":[%d,%d],\"ocxo\":[%d,%d],\"lna1\":[%d,%d],\"lna2\":[%d,%d]},",
        ext5_v, ext5_p, ext24_v, ext24_p, mde_v, mde_p, ocxo_v, -ocxo_p, lna1_v, lna1_p, lna2_v, lna2_p);

    uint32_t date;
    uint32_t time;
    float lat;
    float lon;
    int16_t alt;
    uint8_t sats;
    uint8_t sats_sol;
    bool pulse;
    get_gps_data(&date, &time, &lat, &lon, &alt, &sats, &sats_sol, &pulse);

    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"gps\":{\"date\":%d,\"time\":%d,\"lat\":%.5f,\"lon\":%.5f,\"alt\":%d,\"sats\":%d,\"sats_sol\":%d,\"pulse\":%d},",
        date, time, lat, lon, alt, sats, sats_sol, pulse);

    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"ocxo\":{\"cntr\":%d,\"dac\":%d},",
        ocxo_get_cntr(), ocxo_get_dac_val());

    len += chsnprintf(&buf[len], sizeof(buf)-len, "\"api_connected\":%d,\"time\":%d}", api_is_connected(), chVTGetSystemTimeX());

    HTTP_PRINT("HTTP/1.1 200 OK\r\nContent-type: application/json\r\n\r\n");
    HTTP_PRINT_COPY(buf);
}

static void server_serve(struct netconn *conn) {
    struct netbuf *inbuf;

    uint8_t *data;
    uint16_t len;
    err_t err;

    // Serve request
    if((err = netconn_recv(conn, &inbuf)) == ERR_OK)
    {
        netbuf_data(inbuf, (void **)&data, &len);

        if(strncmp((char*)data, "GET /state.json", 15) == 0) {
            print_json(conn);
        } else if(strncmp((char*)data, "GET /favicon.ico", 16) == 0) {
            netconn_write(conn, favicon, favicon_size, NETCONN_NOCOPY);
        } else if(strncmp((char*)data, "GET /jquery.js", 14) == 0) {
            HTTP_PRINT("HTTP/1.1 200 OK\r\nContent-type: text/javascript\r\n\r\n");
            HTTP_PRINT(jquery);
        } else if(strncmp((char*)data, "GET / ", 6) == 0) {
            print_page(conn);
        } else if(strncmp((char*)data, "GET /set/trq/az/", 16) == 0) {
            az_set_const_trq(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/trq/el/", 16) == 0) {
            el_set_const_trq(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/trq/sk/", 16) == 0) {
            sk_set_const_trq(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/tar/az/", 16) == 0) {
            az_set_tgt_pos(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/tar/el/", 16) == 0) {
            el_set_tgt_pos(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/tar/sk/", 16) == 0) {
            sk_set_tgt_pos(atoi((char*)&data[16]));
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /set/off/az/", 16) == 0) {
            mde_set_az_enc_off(atoi((char*)&data[16]));
            print_ack(conn);

        } else if(strncmp((char*)data, "GET /sw/lna/", 12) == 0) {
            bool sw = atoi((char*)&data[12]);
            palWriteLine(LINE_PWR_LNA, sw);
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /sw/mde/", 12) == 0) {
            bool sw = atoi((char*)&data[12]);
            if(sw) {
                mde_power_up();
            } else {
                mde_power_down();
            }
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /sw/ext5/", 13) == 0) {
            bool sw = atoi((char*)&data[13]);
            palWriteLine(LINE_PWR_EXT_5V, sw);
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /sw/ext24/", 14) == 0) {
            bool sw = atoi((char*)&data[14]);
            palWriteLine(LINE_PWR_EXT_24V, sw);
            print_ack(conn);

        } else if(strncmp((char*)data, "GET /calibrate", 14) == 0) {
            az_calibrate();
            print_ack(conn);
        } else if(strncmp((char*)data, "GET /debug", 10) == 0) {
            print_debug(conn);
        } else {
            HTTP_PRINT("HTTP/1.1 404 Not Found\r\n");
            HTTP_PRINT("404 Not Found\r\n\r\n");
        }
    }

    // Close the connection (server closes)
    netconn_close(conn);

    // Delete the buffer (netconn_recv gives us ownership, so we have to make sure to deallocate the buffer)
    netbuf_delete(inbuf);
}


THD_WORKING_AREA(wa_httpserver, HTTP_THREAD_STACK_SIZE);
THD_FUNCTION(httpserver, p) {
    (void)p;

    struct netconn *conn, *newconn;
    err_t err;

    // Create a new TCP connection handle
    conn = netconn_new(NETCONN_TCP);
    LWIP_ERROR("server: invalid conn", (conn != NULL), chThdExit(MSG_RESET););

    // Bind to port
    netconn_bind(conn, NULL, HTTP_THREAD_PORT);

    // Put the connection into LISTEN state
    netconn_listen(conn);

    // Goes to the final priority after initialization
    chThdSetPriority(HTTP_THREAD_PRIORITY);

    while (true) {
        err = netconn_accept(conn, &newconn);
        if (err != ERR_OK)
            continue;
        server_serve(newconn);
        netconn_delete(newconn);
    }
}

void http_init(void)
{
    chThdCreateStatic(wa_httpserver, sizeof(wa_httpserver), HTTP_THREAD_PRIORITY, httpserver, NULL);
}
