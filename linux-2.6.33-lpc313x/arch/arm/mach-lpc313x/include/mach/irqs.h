/* linux/arch/arm/mach-lpc313x/include/mach/irqs.h
 *
 *  Author:	Durgesh Pattamatta
 *  Copyright (C) 2009 NXP semiconductors
 *
 *  IRQ defines for LPC313x and LPC315x SoCs.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H



# define IRQ_EVT_ROUTER0  1        /*interrupts from Event router 0*/
# define IRQ_EVT_ROUTER1  2        /*interrupts from Event router 1*/
# define IRQ_EVT_ROUTER2  3        /*interrupts from Event router 2*/
# define IRQ_EVT_ROUTER3  4        /*interrupts from Event router 3*/
# define IRQ_TIMER0       5        /*Timer 0 IRQ */
# define IRQ_TIMER1       6        /*Timer 1 IRQ */
# define IRQ_TIMER2       7        /*Timer 2 IRQ */
# define IRQ_TIMER3       8        /*Timer 3 IRQ */
# define IRQ_ADC          9        /*10bit ADC irq*/
# define IRQ_UART         10       /*UART irq */
# define IRQ_I2C0         11       /*I2C 0 IRQ */
# define IRQ_I2C1         12       /*I2C 1 IRQ */
# define IRQ_I2S0_OUT     13       /*I2S 0 out IRQ */
# define IRQ_I2S1_OUT     14       /*I2S 1 out IRQ */
# define IRQ_I2S0_IN      15       /*I2S 0 IN IRQ */
# define IRQ_I2S1_IN      16       /*I2S 1 IN IRQ */
# define IRQ_LCD          18       /*LCD irq */
# define IRQ_SPI_SMS      19       /*SPI SMS IRQ */
# define IRQ_SPI_TX       20       /*SPI Transmit IRQ */
# define IRQ_SPI_RX       21       /*SPI Receive IRQ */
# define IRQ_SPI_OVR      22       /*SPI overrun IRQ */
# define IRQ_SPI          23       /*SPI interrupt IRQ */
# define IRQ_DMA          24       /*DMA irq */
# define IRQ_NAND_FLASH   25       /*NAND flash irq */
# define IRQ_MCI          26       /*MCI irq */
# define IRQ_USB          27       /*USB irq */
# define IRQ_ISRAM0       28       /*ISRAM0 irq */
# define IRQ_ISRAM1       29       /*ISRAM1 irq */


# define NR_IRQ_CPU	  30	/* IRQs directly recognized by CPU */

#define IRQ_EVT_START   NR_IRQ_CPU

/* System specific IRQs */
#include "event_router.h"

/* Other chip IRQs routed through event router.
 * These IRQs should be treated as board IRQs but they are
 * common for all boards.
 *
 * No define all other possible event router events as interrupts
 */
#define IRQ_mLCD_DB_0	30
#define IRQ_mLCD_DB_1	31
#define IRQ_mLCD_DB_2	32
#define IRQ_mLCD_DB_3	33
#define IRQ_mLCD_DB_4	34
#define IRQ_mLCD_DB_5	35
#define IRQ_mLCD_DB_6	36
#define IRQ_mLCD_DB_7	37
#define IRQ_mLCD_DB_8	38
#define IRQ_mLCD_DB_9	39
#define IRQ_mLCD_DB_10	40
#define IRQ_mLCD_DB_11	41
#define IRQ_mLCD_DB_12	42
#define IRQ_mLCD_DB_13	43
#define IRQ_mLCD_DB_14	44
#define IRQ_mLCD_DB_15	45
#define IRQ_mLCD_RS		46
#define IRQ_mLCD_CSB	47
#define IRQ_mLCD_E_RD	48
#define IRQ_mLCD_RW_WR	49
#define IRQ_mNAND_RYBN0	50
#define IRQ_mNAND_RYBN1	51
#define IRQ_mNAND_RYBN2	52
#define IRQ_mNAND_RYBN3	53
#define IRQ_EBI_D_0		54
#define IRQ_EBI_D_1		55
#define IRQ_EBI_D_2		56
#define IRQ_EBI_D_3		57
#define IRQ_EBI_D_4		58
#define IRQ_EBI_D_5		59
#define IRQ_EBI_D_6		60
#define IRQ_EBI_D_7		61
#define IRQ_EBI_D_8		62
#define IRQ_EBI_D_9		63
#define IRQ_EBI_D_10	64
#define IRQ_EBI_D_11	65
#define IRQ_EBI_D_12	66
#define IRQ_EBI_D_13	67
#define IRQ_EBI_D_14	68
#define IRQ_EBI_D_15	69
#define IRQ_EBI_NWE		70
#define IRQ_EBI_A_0_ALE	71
#define IRQ_EBI_A_1_CLE	72
#define IRQ_EBI_DQM_0_NOE		73
#define IRQ_EBI_NCAS_BLOUT_0 	74
#define IRQ_EBI_NRAS_BLOUT_1	75
#define IRQ_GPIO1		76
#define IRQ_GPIO0		77
#define IRQ_GPIO2		78
#define IRQ_GPIO3		79
#define IRQ_GPIO4		80
#define IRQ_mGPIO5		81
#define IRQ_mGPIO6		82
#define IRQ_mGPIO7		83
#define IRQ_mGPIO8		84
#define IRQ_mGPIO9		85
#define IRQ_mGPIO10		86
#define IRQ_GPIO11		87
#define IRQ_GPIO12		88
#define IRQ_GPIO13		89
#define IRQ_GPIO14		90
#define IRQ_GPIO15		91
#define IRQ_GPIO16		92
#define IRQ_GPIO17		93
#define IRQ_GPIO18		94
#define IRQ_NAND_NCS_0	95
#define IRQ_NAND_NCS_1	96
#define IRQ_NAND_NCS_2	97
#define IRQ_NAND_NCS_3	98
#define IRQ_SPI_MISO	99
#define IRQ_SPI_MOSI	100
#define IRQ_SPI_CS_IN	101
#define IRQ_SPI_SCK		102
#define IRQ_SPI_CS_OUT0	103
#define IRQ_UART_RXD	104
#define IRQ_UART_TXD	105
#define IRQ_mUART_CTS_N	106
#define IRQ_mUART_RTS_N	107
#define IRQ_mI2STX_CLK0	108
#define IRQ_mI2STX_BCK0	109
#define IRQ_mI2STX_DATA0	110
#define IRQ_mI2STX_WS0	111
#define IRQ_I2SRX_BCK0	112
#define IRQ_I2SRX_DATA0	113
#define IRQ_I2SRX_WS0	114
#define IRQ_I2SRX_DATA1	115
#define IRQ_I2SRX_BCK1	116
#define IRQ_I2SRX_WS1	117
#define IRQ_I2STX_DATA1	118
#define IRQ_I2STX_BCK1	119
#define IRQ_I2STX_WS1	120
#define IRQ_CLK_256FS_O	121
#define IRQ_I2C_SDA1	122
#define IRQ_I2C_SCL1	123
#define IRQ_PWM_DATA	124
#define IRQ_AD_NINT_I	125
#define IRQ_PLAY_DET_I	126
#define IRQ_timer0_intct1	127
#define IRQ_timer1_intct1	128
#define IRQ_timer2_intct1	129
#define IRQ_timer3_intct1	130
#define IRQ_adc_int		131
#define IRQ_wdog_m0		132				/* Watchdog interrupt */
#define IRQ_uart_rxd	133
#define IRQ_i2c0_scl_n	134
#define IRQ_i2c1_scl_n	135
#define IRQ_arm926_nfiq	136
#define IRQ_arm926_nirq	137
#define IRQ_MCI_DAT_0	138
#define IRQ_MCI_DAT_1	139
#define IRQ_MCI_DAT_2	140
#define IRQ_MCI_DAT_3	141
#define IRQ_MCI_DAT_4	142
#define IRQ_MCI_DAT_5	143
#define IRQ_MCI_DAT_6	144
#define IRQ_MCI_DAT_7	145
#define IRQ_MCI_CMD		146
#define IRQ_MCI_CLK		147
#define IRQ_USB_VBUS	148				/* VBUS power enable */
#define IRQ_usb_otg_ahb_needclk	149
#define IRQ_usb_atx_pll_lock	150
#define IRQ_usb_otg_vbus_pwr_en	151		/* Detect VBUS over current - Host mode */
#define IRQ_USB_ID				152		/* Detect ID pin change - OTG */
/* Do not define the following not needed pins
#define IRQ_isram0_mrc_finished 153
#define IRQ_isram1_mrc_finished	154
*/
#define LAST_IRQ				153


#define NR_STARTUP_BOARD_IRQS 		6
#define _INTERNAL_IRQ_EVENT_MAP	\
	{IRQ_mLCD_DB_0, EVT_mLCD_DB_0, EVT_STARTUP}, \
	{IRQ_mLCD_DB_1, EVT_mLCD_DB_1, EVT_STARTUP}, \
	{IRQ_mLCD_DB_2, EVT_mLCD_DB_2, EVT_STARTUP}, \
	{IRQ_mLCD_DB_3, EVT_mLCD_DB_3, EVT_STARTUP}, \
	{IRQ_mLCD_DB_4, EVT_mLCD_DB_4, EVT_STARTUP}, \
	{IRQ_mLCD_DB_5, EVT_mLCD_DB_5, EVT_STARTUP}, \
	{IRQ_mLCD_DB_6, EVT_mLCD_DB_6, EVT_STARTUP}, \
	{IRQ_mLCD_DB_7, EVT_mLCD_DB_7, EVT_STARTUP}, \
	{IRQ_mLCD_DB_8, EVT_mLCD_DB_8, EVT_STARTUP}, \
	{IRQ_mLCD_DB_9, EVT_mLCD_DB_9, EVT_STARTUP}, \
	{IRQ_mLCD_DB_10, EVT_mLCD_DB_10, EVT_STARTUP}, \
	{IRQ_mLCD_DB_11, EVT_mLCD_DB_11, EVT_STARTUP}, \
	{IRQ_mLCD_DB_12, EVT_mLCD_DB_12, EVT_STARTUP}, \
	{IRQ_mLCD_DB_13, EVT_mLCD_DB_13, EVT_STARTUP}, \
	{IRQ_mLCD_DB_14, EVT_mLCD_DB_14, EVT_STARTUP}, \
	{IRQ_mLCD_DB_15, EVT_mLCD_DB_15, EVT_STARTUP}, \
	{IRQ_mLCD_RS, EVT_mLCD_RS, EVT_STARTUP}, \
	{IRQ_mLCD_CSB, EVT_mLCD_CSB, EVT_STARTUP}, \
	{IRQ_mLCD_E_RD, EVT_mLCD_E_RD, EVT_STARTUP}, \
	{IRQ_mLCD_RW_WR, EVT_mLCD_RW_WR, EVT_STARTUP}, \
	{IRQ_mNAND_RYBN0, EVT_mNAND_RYBN0, EVT_STARTUP}, \
	{IRQ_mNAND_RYBN1, EVT_mNAND_RYBN1, EVT_STARTUP}, \
	{IRQ_mNAND_RYBN2, EVT_mNAND_RYBN2, EVT_STARTUP}, \
	{IRQ_mNAND_RYBN3, EVT_mNAND_RYBN3, EVT_STARTUP}, \
	{IRQ_EBI_D_0, EVT_EBI_D_0, EVT_STARTUP}, \
	{IRQ_EBI_D_1, EVT_EBI_D_1, EVT_STARTUP}, \
	{IRQ_EBI_D_2, EVT_EBI_D_2, EVT_STARTUP}, \
	{IRQ_EBI_D_3, EVT_EBI_D_3, EVT_STARTUP}, \
	{IRQ_EBI_D_4, EVT_EBI_D_4, EVT_STARTUP}, \
	{IRQ_EBI_D_5, EVT_EBI_D_5, EVT_STARTUP}, \
	{IRQ_EBI_D_6, EVT_EBI_D_6, EVT_STARTUP}, \
	{IRQ_EBI_D_7, EVT_EBI_D_7, EVT_STARTUP}, \
	{IRQ_EBI_D_8, EVT_EBI_D_8, EVT_STARTUP}, \
	{IRQ_EBI_D_9, EVT_EBI_D_9, EVT_STARTUP}, \
	{IRQ_EBI_D_10, EVT_EBI_D_10, EVT_STARTUP}, \
	{IRQ_EBI_D_11, EVT_EBI_D_11, EVT_STARTUP}, \
	{IRQ_EBI_D_12, EVT_EBI_D_12, EVT_STARTUP}, \
	{IRQ_EBI_D_13, EVT_EBI_D_13, EVT_STARTUP}, \
	{IRQ_EBI_D_14, EVT_EBI_D_14, EVT_STARTUP}, \
	{IRQ_EBI_D_15, EVT_EBI_D_15, EVT_STARTUP}, \
	{IRQ_EBI_NWE, EVT_EBI_NWE, EVT_STARTUP}, \
	{IRQ_EBI_A_0_ALE, EVT_EBI_A_0_ALE, EVT_STARTUP}, \
	{IRQ_EBI_A_1_CLE, EVT_EBI_A_1_CLE, EVT_STARTUP}, \
	{IRQ_EBI_DQM_0_NOE, EVT_EBI_DQM_0_NOE, EVT_STARTUP}, \
	{IRQ_EBI_NCAS_BLOUT_0, EVT_EBI_NCAS_BLOUT_0, EVT_STARTUP}, \
	{IRQ_EBI_NRAS_BLOUT_1, EVT_EBI_NRAS_BLOUT_1, EVT_STARTUP}, \
	{IRQ_GPIO1, EVT_GPIO1, EVT_STARTUP}, \
	{IRQ_GPIO0, EVT_GPIO0, EVT_STARTUP}, \
	{IRQ_GPIO2, EVT_GPIO2, EVT_STARTUP}, \
	{IRQ_GPIO3, EVT_GPIO3, EVT_STARTUP}, \
	{IRQ_GPIO4, EVT_GPIO4, EVT_STARTUP}, \
	{IRQ_mGPIO5, EVT_mGPIO5, EVT_STARTUP}, \
	{IRQ_mGPIO6, EVT_mGPIO6, EVT_STARTUP}, \
	{IRQ_mGPIO7, EVT_mGPIO7, EVT_STARTUP}, \
	{IRQ_mGPIO8, EVT_mGPIO8, EVT_STARTUP}, \
	{IRQ_mGPIO9, EVT_mGPIO9, EVT_STARTUP}, \
	{IRQ_mGPIO10, EVT_mGPIO10, EVT_STARTUP}, \
	{IRQ_GPIO11, EVT_GPIO11, EVT_STARTUP}, \
	{IRQ_GPIO12, EVT_GPIO12, EVT_STARTUP}, \
	{IRQ_GPIO13, EVT_GPIO13, EVT_STARTUP}, \
	{IRQ_GPIO14, EVT_GPIO14, EVT_STARTUP}, \
	{IRQ_GPIO15, EVT_GPIO15, EVT_STARTUP}, \
	{IRQ_GPIO16, EVT_GPIO16, EVT_STARTUP}, \
	{IRQ_GPIO17, EVT_GPIO17, EVT_STARTUP}, \
	{IRQ_GPIO18, EVT_GPIO18, EVT_STARTUP}, \
	{IRQ_NAND_NCS_0, EVT_NAND_NCS_0, EVT_STARTUP}, \
	{IRQ_NAND_NCS_1, EVT_NAND_NCS_1, EVT_STARTUP}, \
	{IRQ_NAND_NCS_2, EVT_NAND_NCS_2, EVT_STARTUP}, \
	{IRQ_NAND_NCS_3, EVT_NAND_NCS_3, EVT_STARTUP}, \
	{IRQ_SPI_MISO, EVT_SPI_MISO, EVT_STARTUP}, \
	{IRQ_SPI_MOSI, EVT_SPI_MOSI, EVT_STARTUP}, \
	{IRQ_SPI_CS_IN, EVT_SPI_CS_IN, EVT_STARTUP}, \
	{IRQ_SPI_SCK, EVT_SPI_SCK, EVT_STARTUP}, \
	{IRQ_SPI_CS_OUT0, EVT_SPI_CS_OUT0, EVT_STARTUP}, \
	{IRQ_UART_RXD, EVT_UART_RXD, EVT_STARTUP}, \
	{IRQ_UART_TXD, EVT_UART_TXD, EVT_STARTUP}, \
	{IRQ_mUART_CTS_N, EVT_mUART_CTS_N, EVT_STARTUP}, \
	{IRQ_mUART_RTS_N, EVT_mUART_RTS_N, EVT_STARTUP}, \
	{IRQ_mI2STX_CLK0, EVT_mI2STX_CLK0, EVT_STARTUP}, \
	{IRQ_mI2STX_BCK0, EVT_mI2STX_BCK0, EVT_STARTUP}, \
	{IRQ_mI2STX_DATA0, EVT_mI2STX_DATA0, EVT_STARTUP}, \
	{IRQ_mI2STX_WS0, EVT_mI2STX_WS0, EVT_STARTUP}, \
	{IRQ_I2SRX_BCK0, EVT_I2SRX_BCK0, EVT_STARTUP}, \
	{IRQ_I2SRX_DATA0, EVT_I2SRX_DATA0, EVT_STARTUP}, \
	{IRQ_I2SRX_WS0, EVT_I2SRX_WS0, EVT_STARTUP}, \
	{IRQ_I2SRX_DATA1, EVT_I2SRX_DATA1, EVT_STARTUP}, \
	{IRQ_I2STX_BCK1, EVT_I2STX_BCK1, EVT_STARTUP}, \
	{IRQ_I2STX_WS1, EVT_I2STX_WS1, EVT_STARTUP}, \
	{IRQ_CLK_256FS_O, EVT_CLK_256FS_O, EVT_STARTUP}, \
	{IRQ_I2C_SDA1, EVT_I2C_SDA1, EVT_STARTUP}, \
	{IRQ_I2C_SCL1, EVT_I2C_SCL1, EVT_STARTUP}, \
	{IRQ_PWM_DATA, EVT_PWM_DATA, EVT_STARTUP}, \
	{IRQ_AD_NINT_I, EVT_AD_NINT_I, EVT_STARTUP}, \
	{IRQ_PLAY_DET_I, EVT_PLAY_DET_I, EVT_STARTUP}, \
	{IRQ_timer0_intct1, EVT_timer0_intct1, EVT_STARTUP}, \
	{IRQ_timer1_intct1, EVT_timer1_intct1, EVT_STARTUP}, \
	{IRQ_timer2_intct1, EVT_timer2_intct1, EVT_STARTUP}, \
	{IRQ_timer3_intct1, EVT_timer3_intct1, EVT_STARTUP}, \
	{IRQ_adc_int, EVT_adc_int, EVT_STARTUP}, \
	{IRQ_wdog_m0, EVT_wdog_m0, EVT_RISING_EDGE}, \
	{IRQ_uart_rxd, EVT_uart_rxd, EVT_STARTUP}, \
	{IRQ_i2c0_scl_n, EVT_i2c0_scl_n, EVT_STARTUP}, \
	{IRQ_i2c1_scl_n, EVT_i2c1_scl_n, EVT_STARTUP}, \
	{IRQ_arm926_nfiq, EVT_arm926_nfiq, EVT_STARTUP}, \
	{IRQ_arm926_nirq, EVT_arm926_nirq, EVT_STARTUP}, \
	{IRQ_MCI_DAT_0, EVT_MCI_DAT_0, EVT_STARTUP}, \
	{IRQ_MCI_DAT_1, EVT_MCI_DAT_1, EVT_STARTUP}, \
	{IRQ_MCI_DAT_2, EVT_MCI_DAT_2, EVT_STARTUP}, \
	{IRQ_MCI_DAT_3, EVT_MCI_DAT_3, EVT_STARTUP}, \
	{IRQ_MCI_DAT_4, EVT_MCI_DAT_4, EVT_STARTUP}, \
	{IRQ_MCI_DAT_5, EVT_MCI_DAT_5, EVT_STARTUP}, \
	{IRQ_MCI_DAT_6, EVT_MCI_DAT_6, EVT_STARTUP}, \
	{IRQ_MCI_DAT_7, EVT_MCI_DAT_7, EVT_STARTUP}, \
	{IRQ_MCI_CMD, EVT_MCI_CMD, EVT_STARTUP}, \
	{IRQ_MCI_CLK, EVT_MCI_CLK, EVT_STARTUP}, \
	{IRQ_USB_VBUS, EVT_USB_VBUS, EVT_FALLING_EDGE}, \
	{IRQ_usb_otg_ahb_needclk, EVT_usb_otg_ahb_needclk, EVT_STARTUP}, \
	{IRQ_usb_atx_pll_lock, EVT_usb_atx_pll_lock, EVT_STARTUP}, \
	{IRQ_usb_otg_vbus_pwr_en, EVT_usb_otg_vbus_pwr_en, EVT_FALLING_EDGE}, \
	{IRQ_USB_ID, EVT_USB_ID, EVT_ACTIVE_LOW}, \

#if defined(CONFIG_LPC3152_AD)
/* For chips with analog die there are some more AD events routed
 * through event router.
 */
#define IRQ_RTC	        34
#define IRQ_PLAY        35
#define NR_IRQ_CHIP_EVT	NR_STARTUP_BOARD_IRQS

#define AD_IRQ_EVENT_MAP	\
	{IRQ_RTC, EVT_AD_NINT_I, EVT_ACTIVE_LOW}, \
	{IRQ_PLAY, EVT_PLAY_DET_I, EVT_ACTIVE_HIGH}, \

#define CHIP_IRQ_EVENT_MAP   _INTERNAL_IRQ_EVENT_MAP \
	AD_IRQ_EVENT_MAP 

#else
#define CHIP_IRQ_EVENT_MAP   _INTERNAL_IRQ_EVENT_MAP
#define NR_IRQ_CHIP_EVT	     (( IRQ_USB_ID - NR_IRQ_CPU) - 2 )
#endif

/* now compute the board start IRQ number */
#define IRQ_BOARD_START   (NR_IRQ_CPU + NR_IRQ_CHIP_EVT)

/* Route all internal chip events to IRQ_EVT_ROUTER0 */
#define IRQ_EVTR0_START        IRQ_EVT_START
#define IRQ_EVTR0_END          (IRQ_BOARD_START - 1)


#if defined (CONFIG_MACH_VAL3153) 

# define IRQ_CS8900_ETH_INT  IRQ_BOARD_START	/* Ethernet chip */
# define IRQ_SDMMC_CD0       (IRQ_BOARD_START + 1)	/* SD card detect */
# define IRQ_SDMMC_CD1       (IRQ_BOARD_START + 2)	/* SD card detect */
# define NR_IRQ_BOARD        3

/* now define board irq to event pin map */
#define BOARD_IRQ_EVENT_MAP	{ \
	CHIP_IRQ_EVENT_MAP \
	{IRQ_CS8900_ETH_INT, EVT_GPIO16, EVT_ACTIVE_HIGH}, \
	{IRQ_SDMMC_CD0, EVT_GPIO12, EVT_ACTIVE_HIGH}, \
	{IRQ_SDMMC_CD1, EVT_GPIO13, EVT_ACTIVE_HIGH}, \
	}
/* Following defines group the board IRQs into 4 IRQ_EVNTR groups.
   IRQ_EVT_ROUTERx IRQ is generated when event in the corresponding 
   group triggers.
*/
#define IRQ_EVTR1_START        IRQ_CS8900_ETH_INT
#define IRQ_EVTR1_END          IRQ_CS8900_ETH_INT
#define IRQ_EVTR2_START        IRQ_SDMMC_CD0
#define IRQ_EVTR2_END          IRQ_SDMMC_CD0
#define IRQ_EVTR3_START        IRQ_SDMMC_CD1
#define IRQ_EVTR3_END          IRQ_SDMMC_CD1


#elif defined (CONFIG_MACH_EA313X) || defined(CONFIG_MACH_EA3152)
# define IRQ_DM9000_ETH_INT   IRQ_BOARD_START	/* Ethernet chip */
# define IRQ_SDMMC_CD         (IRQ_BOARD_START + 1)	/* SD card detect */
# define IRQ_EA_VBUS_OVRC     (IRQ_BOARD_START + 2)	/* Over current indicator */
# define NR_IRQ_BOARD         3

/* now define board irq to event pin map */
#define BOARD_IRQ_EVENT_MAP	{ \
	CHIP_IRQ_EVENT_MAP \
	{IRQ_DM9000_ETH_INT, EVT_mNAND_RYBN3, EVT_ACTIVE_HIGH}, \
  {IRQ_SDMMC_CD, EVT_mNAND_RYBN2, EVT_ACTIVE_LOW}, \
	{IRQ_EA_VBUS_OVRC, EVT_I2SRX_WS0, EVT_ACTIVE_LOW}, \
	}
  //{IRQ_SDMMC_CD, EVT_mI2STX_BCK0, EVT_ACTIVE_LOW}, --hh


/* Following defines group the board IRQs into 4 IRQ_EVNTR groups.
   IRQ_EVT_ROUTERx IRQ is generated when event in the corresponding 
   group triggers.
*/
#define IRQ_EVTR1_START        IRQ_DM9000_ETH_INT
#define IRQ_EVTR1_END          IRQ_DM9000_ETH_INT
#define IRQ_EVTR2_START        IRQ_SDMMC_CD
#define IRQ_EVTR2_END          IRQ_SDMMC_CD
#define IRQ_EVTR3_START        IRQ_EA_VBUS_OVRC
#define IRQ_EVTR3_END          IRQ_EA_VBUS_OVRC

#elif defined (CONFIG_MACH_VAL3154)
# define IRQ_SDMMC_CD	 IRQ_BOARD_START 	/* SD card detect */
# define NR_IRQ_BOARD	 1

/* now define board irq to event pin map */
#define BOARD_IRQ_EVENT_MAP	{ \
	CHIP_IRQ_EVENT_MAP \
	{IRQ_SDMMC_CD, EVT_mI2STX_BCK0, EVT_ACTIVE_LOW}, \
	}
/* Following defines group the board IRQs into 4 IRQ_EVNTR groups.
   IRQ_EVT_ROUTERx IRQ is generated when event in the corresponding 
   group triggers.
*/
#define IRQ_EVTR1_START        IRQ_SDMMC_CD
#define IRQ_EVTR1_END          IRQ_SDMMC_CD
#define IRQ_EVTR2_START        0
#define IRQ_EVTR2_END          0
#define IRQ_EVTR3_START        0
#define IRQ_EVTR3_END          0

#else
# define NR_IRQ_BOARD          0
#define IRQ_EVTR0_START        0
#define IRQ_EVTR0_END          0
#define IRQ_EVTR1_START        0
#define IRQ_EVTR1_END          0
#define IRQ_EVTR2_START        0
#define IRQ_EVTR2_END          0
#define IRQ_EVTR3_START        0
#define IRQ_EVTR3_END          0

#endif


#define NR_IRQS		(NR_IRQ_CPU + NR_IRQ_CHIP_EVT + NR_IRQ_BOARD)


#endif
