/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0U
#endif

/*
 * Ethernet PHY type.
 */
#define BOARD_PHY_ID            MII_DP83848I_ID
#define BOARD_PHY_RMII

/**********************************************************
 * CONNECTION LAYOUT BETWEEN ETH PHY DP83848 AND STM32F4  *
 **********************************************************
 * PC1----------------MDC
 * PA2----------------MDIO
 * PA1----------------OSCIN
 * PA7----------------CRS
 * PC4----------------RX0
 * PC5----------------RX1
 * PB11---------------TX_EN
 * PB12---------------TX0
 * PB13---------------TX1
 */

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F407xx

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1_ETH_OSCIN        1U // ETH OSCIN
#define GPIOA_PIN2_ETH_MDIO         2U // ETH MDIO
#define GPIOA_PIN3                  3U
#define GPIOA_PIN4                  4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6                  6U
#define GPIOA_PIN7_ETH_CRS          7U // ETH CRS
#define GPIOA_PIN8                  8U
#define GPIOA_PIN9                  9U
#define GPIOA_PIN10                 10U
#define GPIOA_PIN11                 11U
#define GPIOA_PIN12                 12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                 10U
#define GPIOB_PIN11_ETH_TX_EN       11U // ETH TX EN
#define GPIOB_PIN12_ETH_TX0         12U // ETH TX0
#define GPIOB_PIN13_ETH_TX1         13U // ETH TX1
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1_MDC              1U // ETH MDC
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4_ETH_RX0          4U // ETH RX0
#define GPIOC_PIN5_ETH_RX1          5U // ETH RX1
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_INT1                  0U
#define GPIOE_INT2                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * Ethernetboard IO pins assignments.
 */
#define LINE_SPI_MOSI       PAL_LINE(GPIOC, 12)
#define LINE_SPI_MISO       PAL_LINE(GPIOC, 11)
#define LINE_SPI_SCK        PAL_LINE(GPIOC, 10)
#define LINE_SX1280_CS      PAL_LINE(GPIOA, 15)
#define LINE_SX1280_RESET   PAL_LINE(GPIOB, 4)
#define LINE_SX1280_BUSY    PAL_LINE(GPIOB, 10)
#define LINE_SX1280_IRQ1    PAL_LINE(GPIOC, 7)
#define SPI_INTERFACE       (&SPID3)


/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - BUTTON                    (input floating).
 * PA1  - PIN1                      (input pullup).
 * PA2  - PIN2                      (input pullup).
 * PA3  - PIN3                      (input pullup).
 * PA4  - LRCK                      (alternate 6).
 * PA5  - SPC                       (alternate 5).
 * PA6  - SDO                       (alternate 5).
 * PA7  - SDI                       (alternate 5).
 * PA8  - PIN8                      (input pullup).
 * PA9  - VBUS_FS                   (input floating).
 * PA10 - OTG_FS_ID                 (alternate 10).
 * PA11 - OTG_FS_DM                 (alternate 10).
 * PA12 - OTG_FS_DP                 (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_PIN0) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN1_ETH_OSCIN) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN2_ETH_MDIO) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN7_ETH_CRS) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN10) |  \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |  \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1_ETH_OSCIN) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2_ETH_MDIO) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN7_ETH_CRS) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN9) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN1_ETH_OSCIN) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN2_ETH_MDIO) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN5) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN6) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN7_ETH_CRS) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN9) |       \
                                     PIN_OSPEED_HIGH(GPIOA_PIN10) |     \
                                     PIN_OSPEED_HIGH(GPIOA_PIN11) |     \
                                     PIN_OSPEED_HIGH(GPIOA_PIN12) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOA_PIN0) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN1_ETH_OSCIN) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN2_ETH_MDIO) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN5) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN6) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN7_ETH_CRS) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN9) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN11) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN12) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW(GPIOA_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOA_PIN1_ETH_OSCIN) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN2_ETH_MDIO) |             \
                                     PIN_ODR_LOW(GPIOA_PIN3) |             \
                                     PIN_ODR_LOW(GPIOA_PIN4) |             \
                                     PIN_ODR_LOW(GPIOA_PIN5) |              \
                                     PIN_ODR_LOW(GPIOA_PIN6) |              \
                                     PIN_ODR_HIGH(GPIOA_PIN7_ETH_CRS) |              \
                                     PIN_ODR_LOW(GPIOA_PIN8) |             \
                                     PIN_ODR_LOW(GPIOA_PIN9) |          \
                                     PIN_ODR_LOW(GPIOA_PIN10) |        \
                                     PIN_ODR_LOW(GPIOA_PIN11) |        \
                                     PIN_ODR_LOW(GPIOA_PIN12) |        \
                                     PIN_ODR_LOW(GPIOA_SWDIO) |            \
                                     PIN_ODR_LOW(GPIOA_SWCLK) |            \
                                     PIN_ODR_LOW(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN1_ETH_OSCIN, 11U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN2_ETH_MDIO, 11U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN5, 0U) |           \
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |           \
                                     PIN_AFIO_AF(GPIOA_PIN7_ETH_CRS, 11U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN9, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN10, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_PIN12, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - PIN2                      (input pullup).
 * PB3  - SWO                       (alternate 0).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5                      (input pullup).
 * PB6  - SCL                       (alternate 4).
 * PB7  - PIN7                      (input pullup).
 * PB8  - PIN8                      (input pullup).
 * PB9  - SDA                       (alternate 4).
 * PB10 - CLK_IN                    (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - PIN14                     (input pullup).
 * PB15 - PIN15                     (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN3) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN9) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |         \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN11_ETH_TX_EN) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN12_ETH_TX0) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN13_ETH_TX1) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN15))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PIN8) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11_ETH_TX_EN) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN12_ETH_TX0) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13_ETH_TX1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN3) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN6) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN9) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN10) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN11_ETH_TX_EN) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN12_ETH_TX0) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN13_ETH_TX1) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN15))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN3) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN6) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN9) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN10) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11_ETH_TX_EN) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN12_ETH_TX0) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN13_ETH_TX1) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN15))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_PIN0) |             \
                                     PIN_ODR_LOW(GPIOB_PIN1) |             \
                                     PIN_ODR_LOW(GPIOB_PIN2) |             \
                                     PIN_ODR_LOW(GPIOB_PIN3) |              \
                                     PIN_ODR_LOW(GPIOB_PIN4) |             \
                                     PIN_ODR_LOW(GPIOB_PIN5) |             \
                                     PIN_ODR_LOW(GPIOB_PIN6) |              \
                                     PIN_ODR_LOW(GPIOB_PIN7) |             \
                                     PIN_ODR_LOW(GPIOB_PIN8) |             \
                                     PIN_ODR_LOW(GPIOB_PIN9) |              \
                                     PIN_ODR_LOW(GPIOB_PIN10) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN11_ETH_TX_EN) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN12_ETH_TX0) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN13_ETH_TX1) |            \
                                     PIN_ODR_LOW(GPIOB_PIN14) |            \
                                     PIN_ODR_LOW(GPIOB_PIN15))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN3, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN6, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 4U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN9, 4U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN11_ETH_TX_EN, 11U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN12_ETH_TX0, 11U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN13_ETH_TX1, 11U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0U))

/*
 * GPIOC setup:
 *
 * PC0  - OTG_FS_POWER_ON           (output pushpull maximum).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PDM_OUT                   (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC6  - PIN6                      (input pullup).
 * PC7  - MCLK                      (alternate 6).
 * PC8  - PIN8                      (input pullup).
 * PC9  - PIN9                      (input pullup).
 * PC10 - SCLK                      (alternate 6).
 * PC11 - PIN11                     (input pullup).
 * PC12 - SDIN                      (alternate 6).
 * PC13 - PIN13                     (input pullup).
 * PC14 - PIN14                     (input pullup).
 * PC15 - PIN15                     (input pullup).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |\
                                     PIN_MODE_ALTERNATE(GPIOC_PIN1_MDC) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |        \
                                     PIN_MODE_ALTERNATE(GPIOC_PIN4_ETH_RX0) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_PIN5_ETH_RX1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1_MDC) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4_ETH_RX0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5_ETH_RX1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN0) |\
                                     PIN_OSPEED_HIGH(GPIOC_PIN1_MDC) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN3) |       \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4_ETH_RX0) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5_ETH_RX1) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN10) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN12) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOC_PIN0) |\
                                     PIN_PUPDR_FLOATING(GPIOC_PIN1_MDC) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN3) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN4_ETH_RX0) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN5_ETH_RX1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN10) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN12) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_PIN0) |  \
                                     PIN_ODR_HIGH(GPIOC_PIN1_MDC) |             \
                                     PIN_ODR_LOW(GPIOC_PIN2) |             \
                                     PIN_ODR_LOW(GPIOC_PIN3) |          \
                                     PIN_ODR_HIGH(GPIOC_PIN4_ETH_RX0) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5_ETH_RX1) |             \
                                     PIN_ODR_LOW(GPIOC_PIN6) |             \
                                     PIN_ODR_LOW(GPIOC_PIN7) |             \
                                     PIN_ODR_LOW(GPIOC_PIN8) |             \
                                     PIN_ODR_LOW(GPIOC_PIN9) |             \
                                     PIN_ODR_LOW(GPIOC_PIN10) |             \
                                     PIN_ODR_LOW(GPIOC_PIN11) |            \
                                     PIN_ODR_LOW(GPIOC_PIN12) |             \
                                     PIN_ODR_LOW(GPIOC_PIN13) |            \
                                     PIN_ODR_LOW(GPIOC_PIN14) |            \
                                     PIN_ODR_LOW(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |\
                                     PIN_AFIO_AF(GPIOC_PIN1_MDC, 11U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_PIN4_ETH_RX0, 11U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN5_ETH_RX1, 11U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN10, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup).
 * PD1  - PIN1                      (input pullup).
 * PD2  - PIN2                      (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - RESET                     (output pushpull maximum).
 * PD5  - OVER_CURRENT              (input floating).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD10 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - LED4                      (output pushpull maximum).
 * PD13 - LED3                      (output pushpull maximum).
 * PD14 - LED5                      (output pushpull maximum).
 * PD15 - LED6                      (output pushpull maximum).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |         \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |  \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN4) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN5) |\
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN12) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN13) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN14) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_LOW(GPIOD_PIN0) |             \
                                     PIN_ODR_LOW(GPIOD_PIN1) |             \
                                     PIN_ODR_LOW(GPIOD_PIN2) |             \
                                     PIN_ODR_LOW(GPIOD_PIN3) |             \
                                     PIN_ODR_LOW(GPIOD_PIN4) |            \
                                     PIN_ODR_LOW(GPIOD_PIN5) |     \
                                     PIN_ODR_LOW(GPIOD_PIN6) |             \
                                     PIN_ODR_LOW(GPIOD_PIN7) |             \
                                     PIN_ODR_LOW(GPIOD_PIN8) |             \
                                     PIN_ODR_LOW(GPIOD_PIN9) |             \
                                     PIN_ODR_LOW(GPIOD_PIN10) |            \
                                     PIN_ODR_LOW(GPIOD_PIN11) |            \
                                     PIN_ODR_LOW(GPIOD_PIN12) |              \
                                     PIN_ODR_LOW(GPIOD_PIN13) |              \
                                     PIN_ODR_LOW(GPIOD_PIN14) |              \
                                     PIN_ODR_LOW(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |  \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - INT1                      (input floating).
 * PE1  - INT2                      (input floating).
 * PE2  - PIN2                      (input floating).
 * PE3  - CS_SPI                    (output pushpull maximum).
 * PE4  - PIN4                      (input floating).
 * PE5  - PIN5                      (input floating).
 * PE6  - PIN6                      (input floating).
 * PE7  - PIN7                      (input floating).
 * PE8  - PIN8                      (input floating).
 * PE9  - PIN9                      (input floating).
 * PE10 - PIN10                     (input floating).
 * PE11 - PIN11                     (input floating).
 * PE12 - PIN12                     (input floating).
 * PE13 - PIN13                     (input floating).
 * PE14 - PIN14                     (input floating).
 * PE15 - PIN15                     (input floating).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_INT1) |           \
                                     PIN_MODE_INPUT(GPIOE_INT2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |        \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_INT1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_INT2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_INT1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_INT2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |        \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOE_INT1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_INT2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN3) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN6) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN9) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN10) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN13) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN14) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_LOW(GPIOE_INT1) |             \
                                     PIN_ODR_LOW(GPIOE_INT2) |             \
                                     PIN_ODR_LOW(GPIOE_PIN2) |             \
                                     PIN_ODR_LOW(GPIOE_PIN3) |           \
                                     PIN_ODR_LOW(GPIOE_PIN4) |             \
                                     PIN_ODR_LOW(GPIOE_PIN5) |             \
                                     PIN_ODR_LOW(GPIOE_PIN6) |             \
                                     PIN_ODR_LOW(GPIOE_PIN7) |             \
                                     PIN_ODR_LOW(GPIOE_PIN8) |             \
                                     PIN_ODR_LOW(GPIOE_PIN9) |             \
                                     PIN_ODR_LOW(GPIOE_PIN10) |            \
                                     PIN_ODR_LOW(GPIOE_PIN11) |            \
                                     PIN_ODR_LOW(GPIOE_PIN12) |            \
                                     PIN_ODR_LOW(GPIOE_PIN13) |            \
                                     PIN_ODR_LOW(GPIOE_PIN14) |            \
                                     PIN_ODR_LOW(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_INT1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_INT2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |        \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input floating).
 * PF1  - PIN1                      (input floating).
 * PF2  - PIN2                      (input floating).
 * PF3  - PIN3                      (input floating).
 * PF4  - PIN4                      (input floating).
 * PF5  - PIN5                      (input floating).
 * PF6  - PIN6                      (input floating).
 * PF7  - PIN7                      (input floating).
 * PF8  - PIN8                      (input floating).
 * PF9  - PIN9                      (input floating).
 * PF10 - PIN10                     (input floating).
 * PF11 - PIN11                     (input floating).
 * PF12 - PIN12                     (input floating).
 * PF13 - PIN13                     (input floating).
 * PF14 - PIN14                     (input floating).
 * PF15 - PIN15                     (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOF_PIN0) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN3) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN6) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN9) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN10) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN13) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN14) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_LOW(GPIOF_PIN0) |             \
                                     PIN_ODR_LOW(GPIOF_PIN1) |             \
                                     PIN_ODR_LOW(GPIOF_PIN2) |             \
                                     PIN_ODR_LOW(GPIOF_PIN3) |             \
                                     PIN_ODR_LOW(GPIOF_PIN4) |             \
                                     PIN_ODR_LOW(GPIOF_PIN5) |             \
                                     PIN_ODR_LOW(GPIOF_PIN6) |             \
                                     PIN_ODR_LOW(GPIOF_PIN7) |             \
                                     PIN_ODR_LOW(GPIOF_PIN8) |             \
                                     PIN_ODR_LOW(GPIOF_PIN9) |             \
                                     PIN_ODR_LOW(GPIOF_PIN10) |            \
                                     PIN_ODR_LOW(GPIOF_PIN11) |            \
                                     PIN_ODR_LOW(GPIOF_PIN12) |            \
                                     PIN_ODR_LOW(GPIOF_PIN13) |            \
                                     PIN_ODR_LOW(GPIOF_PIN14) |            \
                                     PIN_ODR_LOW(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input floating).
 * PG1  - PIN1                      (input floating).
 * PG2  - PIN2                      (input floating).
 * PG3  - PIN3                      (input floating).
 * PG4  - PIN4                      (input floating).
 * PG5  - PIN5                      (input floating).
 * PG6  - PIN6                      (input floating).
 * PG7  - PIN7                      (input floating).
 * PG8  - PIN8                      (input floating).
 * PG9  - PIN9                      (input floating).
 * PG10 - PIN10                     (input floating).
 * PG11 - PIN11                     (input floating).
 * PG12 - PIN12                     (input floating).
 * PG13 - PIN13                     (input floating).
 * PG14 - PIN14                     (input floating).
 * PG15 - PIN15                     (input floating).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOG_PIN0) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN3) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN6) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN9) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN10) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN13) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN14) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_LOW(GPIOG_PIN0) |             \
                                     PIN_ODR_LOW(GPIOG_PIN1) |             \
                                     PIN_ODR_LOW(GPIOG_PIN2) |             \
                                     PIN_ODR_LOW(GPIOG_PIN3) |             \
                                     PIN_ODR_LOW(GPIOG_PIN4) |             \
                                     PIN_ODR_LOW(GPIOG_PIN5) |             \
                                     PIN_ODR_LOW(GPIOG_PIN6) |             \
                                     PIN_ODR_LOW(GPIOG_PIN7) |             \
                                     PIN_ODR_LOW(GPIOG_PIN8) |             \
                                     PIN_ODR_LOW(GPIOG_PIN9) |             \
                                     PIN_ODR_LOW(GPIOG_PIN10) |            \
                                     PIN_ODR_LOW(GPIOG_PIN11) |            \
                                     PIN_ODR_LOW(GPIOG_PIN12) |            \
                                     PIN_ODR_LOW(GPIOG_PIN13) |            \
                                     PIN_ODR_LOW(GPIOG_PIN14) |            \
                                     PIN_ODR_LOW(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input floating).
 * PH3  - PIN3                      (input floating).
 * PH4  - PIN4                      (input floating).
 * PH5  - PIN5                      (input floating).
 * PH6  - PIN6                      (input floating).
 * PH7  - PIN7                      (input floating).
 * PH8  - PIN8                      (input floating).
 * PH9  - PIN9                      (input floating).
 * PH10 - PIN10                     (input floating).
 * PH11 - PIN11                     (input floating).
 * PH12 - PIN12                     (input floating).
 * PH13 - PIN13                     (input floating).
 * PH14 - PIN14                     (input floating).
 * PH15 - PIN15                     (input floating).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN3) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN6) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN9) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN10) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN13) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN14) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_LOW(GPIOH_OSC_IN) |           \
                                     PIN_ODR_LOW(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_LOW(GPIOH_PIN2) |             \
                                     PIN_ODR_LOW(GPIOH_PIN3) |             \
                                     PIN_ODR_LOW(GPIOH_PIN4) |             \
                                     PIN_ODR_LOW(GPIOH_PIN5) |             \
                                     PIN_ODR_LOW(GPIOH_PIN6) |             \
                                     PIN_ODR_LOW(GPIOH_PIN7) |             \
                                     PIN_ODR_LOW(GPIOH_PIN8) |             \
                                     PIN_ODR_LOW(GPIOH_PIN9) |             \
                                     PIN_ODR_LOW(GPIOH_PIN10) |            \
                                     PIN_ODR_LOW(GPIOH_PIN11) |            \
                                     PIN_ODR_LOW(GPIOH_PIN12) |            \
                                     PIN_ODR_LOW(GPIOH_PIN13) |            \
                                     PIN_ODR_LOW(GPIOH_PIN14) |            \
                                     PIN_ODR_LOW(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input floating).
 * PI1  - PIN1                      (input floating).
 * PI2  - PIN2                      (input floating).
 * PI3  - PIN3                      (input floating).
 * PI4  - PIN4                      (input floating).
 * PI5  - PIN5                      (input floating).
 * PI6  - PIN6                      (input floating).
 * PI7  - PIN7                      (input floating).
 * PI8  - PIN8                      (input floating).
 * PI9  - PIN9                      (input floating).
 * PI10 - PIN10                     (input floating).
 * PI11 - PIN11                     (input floating).
 * PI12 - PIN12                     (input floating).
 * PI13 - PIN13                     (input floating).
 * PI14 - PIN14                     (input floating).
 * PI15 - PIN15                     (input floating).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOI_PIN0) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN3) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN6) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN9) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN10) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN13) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN14) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_LOW(GPIOI_PIN0) |             \
                                     PIN_ODR_LOW(GPIOI_PIN1) |             \
                                     PIN_ODR_LOW(GPIOI_PIN2) |             \
                                     PIN_ODR_LOW(GPIOI_PIN3) |             \
                                     PIN_ODR_LOW(GPIOI_PIN4) |             \
                                     PIN_ODR_LOW(GPIOI_PIN5) |             \
                                     PIN_ODR_LOW(GPIOI_PIN6) |             \
                                     PIN_ODR_LOW(GPIOI_PIN7) |             \
                                     PIN_ODR_LOW(GPIOI_PIN8) |             \
                                     PIN_ODR_LOW(GPIOI_PIN9) |             \
                                     PIN_ODR_LOW(GPIOI_PIN10) |            \
                                     PIN_ODR_LOW(GPIOI_PIN11) |            \
                                     PIN_ODR_LOW(GPIOI_PIN12) |            \
                                     PIN_ODR_LOW(GPIOI_PIN13) |            \
                                     PIN_ODR_LOW(GPIOI_PIN14) |            \
                                     PIN_ODR_LOW(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
