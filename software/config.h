#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ch.h"
#include "hal.h"

#define BOARD_NAME                  "Sea Tel Ctrl"
#define LWIP_NETIF_HOSTNAME_STRING  "sea_tel_ctrl"
#define IP_SUFFIX                   123


#define LWIP_IPADDR(p)              IP4_ADDR(p, 192, 168, 20,  IP_SUFFIX)
#define LWIP_GATEWAY(p)             IP4_ADDR(p, 192, 168, 20,  1        )
#define LWIP_NETMASK(p)             IP4_ADDR(p, 255, 255, 255, 0        )
#define LWIP_ETHADDR_0              0xC2
#define LWIP_ETHADDR_1              0xAF
#define LWIP_ETHADDR_2              0x51
#define LWIP_ETHADDR_3              0x03
#define LWIP_ETHADDR_4              0x14
#define LWIP_ETHADDR_5              IP_SUFFIX


#define LINE_LED_READY              PAL_LINE(GPIOE, 10)

#define LINE_PWR_LNA                PAL_LINE(GPIOE, 8)
#define LINE_PWR_EXT_5V             PAL_LINE(GPIOD, 7)
#define LINE_PWR_EXT_24V            PAL_LINE(GPIOD, 1)




#endif
