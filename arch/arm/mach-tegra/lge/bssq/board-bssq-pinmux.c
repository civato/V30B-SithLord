/*
 * arch/arm/mach-tegra/board-bssq-pinmux.c
 *
 * Copyright (C) 2010-2011 NVIDIA Corporation
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <mach/pinmux.h>

#if defined(CONFIG_LU6500)	//                                                          
#include <linux/lge_hw_rev.h>
#endif

#include <lge/board-bssq.h>
#include <mach-tegra/gpio-names.h>

/* Setting the drive strength of pins
 * hsm: Enable High speed mode (ENABLE/DISABLE)
 * Schimit: Enable/disable schimit (ENABLE/DISABLE)
 * drive: low power mode (DIV_1, DIV_2, DIV_4, DIV_8)
 * pulldn_drive - drive down (falling edge) - Driver Output Pull-Down drive
 *                strength code. Value from 0 to 31.
 * pullup_drive - drive up (rising edge)  - Driver Output Pull-Up drive
 *                strength code. Value from 0 to 31.
 * pulldn_slew -  Driver Output Pull-Up slew control code  - 2bit code
 *                code 11 is least slewing of signal. code 00 is highest
 *                slewing of the signal.
 *                Value - FASTEST, FAST, SLOW, SLOWEST
 * pullup_slew -  Driver Output Pull-Down slew control code -
 *                code 11 is least slewing of signal. code 00 is highest
 *                slewing of the signal.
 *                Value - FASTEST, FAST, SLOW, SLOWEST
 */
#define SET_DRIVE(_name, _hsm, _schmitt, _drive, _pulldn_drive, _pullup_drive, _pulldn_slew, _pullup_slew) \
	{                                               \
		.pingroup = TEGRA_DRIVE_PINGROUP_##_name,   \
		.hsm = TEGRA_HSM_##_hsm,                    \
		.schmitt = TEGRA_SCHMITT_##_schmitt,        \
		.drive = TEGRA_DRIVE_##_drive,              \
		.pull_down = TEGRA_PULL_##_pulldn_drive,    \
		.pull_up = TEGRA_PULL_##_pullup_drive,		\
		.slew_rising = TEGRA_SLEW_##_pulldn_slew,   \
		.slew_falling = TEGRA_SLEW_##_pullup_slew,	\
	}

#define DEFAULT_DRIVE(_name)					\
	{							\
		.pingroup = TEGRA_DRIVE_PINGROUP_##_name,	\
		.hsm = TEGRA_HSM_DISABLE,			\
		.schmitt = TEGRA_SCHMITT_ENABLE,		\
		.drive = TEGRA_DRIVE_DIV_1,			\
		.pull_down = TEGRA_PULL_31,			\
		.pull_up = TEGRA_PULL_31,			\
		.slew_rising = TEGRA_SLEW_SLOWEST,		\
		.slew_falling = TEGRA_SLEW_SLOWEST,		\
	}


static __initdata struct tegra_drive_pingroup_config bssq_drive_pinmux[] = {
	DEFAULT_DRIVE(VI1),
	DEFAULT_DRIVE(SDIO1),
	SET_DRIVE(DAP2, DISABLE, ENABLE, DIV_1, 46, 46, SLOWEST, SLOWEST),
	SET_DRIVE(DAP3, DISABLE, ENABLE, DIV_1, 46, 46, SLOWEST, SLOWEST),
	SET_DRIVE(DBG, DISABLE, ENABLE, DIV_1, 31, 31, FASTEST, FASTEST),  /* I2C1 */
	SET_DRIVE(DDC, DISABLE, ENABLE, DIV_1, 31, 31, FASTEST, FASTEST),  /* I2C2-1 */
	SET_DRIVE(AT1, DISABLE, ENABLE, DIV_1, 31, 31, FASTEST, FASTEST),  /* I2C2-2 */
	SET_DRIVE(VI2, DISABLE, ENABLE, DIV_1, 31, 31, FASTEST, FASTEST),  /* I2C3 */
	SET_DRIVE(AO1, DISABLE, ENABLE, DIV_1, 31, 31, FASTEST, FASTEST),  /* DVC */
};

static __initdata struct tegra_pingroup_config bssq_pinmux[] = {
#if defined (CONFIG_LU6500)
#include <lge/pinmux_lu6500.h>
#elif defined (CONFIG_SU880) || defined (CONFIG_KU8800)
#include <lge/pinmux_sku880.h>
#elif defined (CONFIG_KS1103)
#include <lge/pinmux_ks1103.h>
#else
	{TEGRA_PINGROUP_ATA,   TEGRA_MUX_RSVD,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_ATB,   TEGRA_MUX_SDIO4,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// microsd det, mmc clk, mmc cmd
	{TEGRA_PINGROUP_ATC,   TEGRA_MUX_GMI,         	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// gpio
	{TEGRA_PINGROUP_ATD,   TEGRA_MUX_GMI,         	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_ATE,   TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC, pull dn(strapping)
	{TEGRA_PINGROUP_CDEV1, TEGRA_MUX_PLLA_OUT,      TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// audio mclk2(static)
	{TEGRA_PINGROUP_CDEV2, TEGRA_MUX_PLLP_OUT4,     TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// audio mclk(set dynamically)
	{TEGRA_PINGROUP_CRTP,  TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_CSUS,  TEGRA_MUX_VI_SENSOR_CLK, TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// CAM_MCLK
	{TEGRA_PINGROUP_DAP1,  TEGRA_MUX_DAP1,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// dap1(static)
	{TEGRA_PINGROUP_DAP2,  TEGRA_MUX_DAP2,          TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_TRISTATE},	// dap2(set dynamically)
	{TEGRA_PINGROUP_DAP3,  TEGRA_MUX_DAP3,          TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_TRISTATE},	// dap3(set dynamically)
	{TEGRA_PINGROUP_DAP4,  TEGRA_MUX_DAP4,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// dap4(static)
 	{TEGRA_PINGROUP_DDC,   TEGRA_MUX_RSVD,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_DTA,   TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// 8M CAM VCM en, VT CAM pwdn
	{TEGRA_PINGROUP_DTB,   TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// flash LED
	{TEGRA_PINGROUP_DTC,   TEGRA_MUX_VI,            TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// VT hsync, vsync
	{TEGRA_PINGROUP_DTD,   TEGRA_MUX_VI,            TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// VT pclk
	{TEGRA_PINGROUP_DTE,   TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// VT/8M reset n, flash en
	{TEGRA_PINGROUP_DTF,   TEGRA_MUX_I2C3,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// CAM I2C
	{TEGRA_PINGROUP_GMA,   TEGRA_MUX_SDIO4,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// mmc dat[0..3]
	{TEGRA_PINGROUP_GMB,   TEGRA_MUX_GMI,			TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_TRISTATE},	// BT host wake up
	{TEGRA_PINGROUP_GMC,   TEGRA_MUX_UARTD,         TEGRA_PUPD_PULL_UP, 	TEGRA_TRI_NORMAL},	// GPS UART4, kangsic.ham
	{TEGRA_PINGROUP_GMD,   TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_GME,   TEGRA_MUX_SDIO4,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// mmc dat[4..7]
	{TEGRA_PINGROUP_GPU,   TEGRA_MUX_PWM,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// muic int, uart sw, vib pwm, vib en, ipc srdy
	{TEGRA_PINGROUP_GPU7,  TEGRA_MUX_RTCK,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// jtag rtck
	{TEGRA_PINGROUP_GPV,   TEGRA_MUX_PCIE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_HDINT, TEGRA_MUX_HDMI,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_TRISTATE},
	{TEGRA_PINGROUP_I2CP,  TEGRA_MUX_I2C,           TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// power i2c sda, slc
	{TEGRA_PINGROUP_IRRX,  TEGRA_MUX_GMI,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// ipc mrdy1
	{TEGRA_PINGROUP_IRTX,  TEGRA_MUX_GMI,       	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
#if defined(CONFIG_LU6500)
	{TEGRA_PINGROUP_KBCA,  TEGRA_MUX_KBC,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// KEYBOARD
	{TEGRA_PINGROUP_KBCB,  TEGRA_MUX_KBC,         	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// KEYBOARD, wlan host wakeup
	{TEGRA_PINGROUP_KBCC,  TEGRA_MUX_KBC,           TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// KEYBOARD
	{TEGRA_PINGROUP_KBCD,  TEGRA_MUX_KBC,         	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// KEYBOARD
	{TEGRA_PINGROUP_KBCE,  TEGRA_MUX_KBC,           TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// ??
	{TEGRA_PINGROUP_KBCF,  TEGRA_MUX_KBC,           TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// KEYBOARD
#else
	{TEGRA_PINGROUP_KBCA,  TEGRA_MUX_KBC,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// GPIO
	{TEGRA_PINGROUP_KBCB,  TEGRA_MUX_KBC,         	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// wlan host wakeup
	{TEGRA_PINGROUP_KBCC,  TEGRA_MUX_KBC,           TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// GPIO
	{TEGRA_PINGROUP_KBCD,  TEGRA_MUX_KBC,         	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// GPIO
	{TEGRA_PINGROUP_KBCE,  TEGRA_MUX_KBC,           TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// ??
	{TEGRA_PINGROUP_KBCF,  TEGRA_MUX_KBC,           TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// GPIO
#endif
	{TEGRA_PINGROUP_LCSN,  TEGRA_MUX_DISPLAYA,     	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// lcd cs
	{TEGRA_PINGROUP_LD9,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// mdm usb vbus en
	{TEGRA_PINGROUP_LD0,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LD1,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// gen2 i2c switch
	{TEGRA_PINGROUP_LD10,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// lp8720(CAM PMIC)en/1seg 1.2v en
	{TEGRA_PINGROUP_LD11,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// DMB en/1seg en
	{TEGRA_PINGROUP_LD12,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// motion int
	{TEGRA_PINGROUP_LD13,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_NORMAL},	// kangsic.ham for GPS
	{TEGRA_PINGROUP_LD14,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_NORMAL},	// kangsic.ham for GPS
	{TEGRA_PINGROUP_LD15,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// WM ldo en
	{TEGRA_PINGROUP_LD16,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_PULL_DOWN,	TEGRA_TRI_NORMAL},	// kangsic.ham for GPS
	{TEGRA_PINGROUP_LD17,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LD2,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// audio int
	{TEGRA_PINGROUP_LD3,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// bd6084(lcd cp) en(resetb)
	{TEGRA_PINGROUP_LD4,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// X2 DMB_RESET
	{TEGRA_PINGROUP_LD5,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// X2 DMB_INT
	{TEGRA_PINGROUP_LD6,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// X2 DMB_EN, bd2802(key led) reset
	{TEGRA_PINGROUP_LD7,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// lcd reset (KS1001 in rev_C)
	{TEGRA_PINGROUP_LD8,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// compass_int
	{TEGRA_PINGROUP_LDC,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LDI,   TEGRA_MUX_RSVD,			TEGRA_PUPD_PULL_DOWN,		TEGRA_TRI_NORMAL},	// CP_STATE
	{TEGRA_PINGROUP_LHP0,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},	// AP_STATE
	{TEGRA_PINGROUP_LHP1,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// BT en
	{TEGRA_PINGROUP_LHP2,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// wlan en
	{TEGRA_PINGROUP_LHS,   TEGRA_MUX_RSVD,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_LM0,   TEGRA_MUX_SPI3,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// DMB spi3 cs
	{TEGRA_PINGROUP_LM1,   TEGRA_MUX_RSVD,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_TRISTATE},
	{TEGRA_PINGROUP_LPP,   TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LPW0,  TEGRA_MUX_SPI3,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// DMB/1seg spi3 sdi
	{TEGRA_PINGROUP_LPW1,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// CHG PGB N/NC
	{TEGRA_PINGROUP_LPW2,  TEGRA_MUX_SPI3,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// DMB spi3 sdo
	{TEGRA_PINGROUP_LSC0,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},	// GYRO_INT
	{TEGRA_PINGROUP_LSC1,  TEGRA_MUX_SPI3,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// DBM spi3 clk
	{TEGRA_PINGROUP_LSCK,  TEGRA_MUX_DISPLAYA,      TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LSDA,  TEGRA_MUX_DISPLAYA,      TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_LSDI,  TEGRA_MUX_DISPLAYA,      TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
#ifndef CONFIG_TEGRA_DSI
	{TEGRA_PINGROUP_LSPI,  TEGRA_MUX_DISPLAYA,		TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_LVP0,  TEGRA_MUX_DISPLAYA,      TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},
#else
	{TEGRA_PINGROUP_LSPI,  TEGRA_MUX_DISPLAYA,      TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// lcd te
	{TEGRA_PINGROUP_LVP0,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
#endif
	{TEGRA_PINGROUP_LVP1,  TEGRA_MUX_RSVD,      	TEGRA_PUPD_NORMAL, 		TEGRA_TRI_TRISTATE},	// lcd maker id
	{TEGRA_PINGROUP_LVS,   TEGRA_MUX_RSVD,			TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// bl_dcdc sda
	{TEGRA_PINGROUP_OWC,   TEGRA_MUX_OWR,           TEGRA_PUPD_PULL_UP,		TEGRA_TRI_TRISTATE},	// test point
	{TEGRA_PINGROUP_PMC,   TEGRA_MUX_PWR_ON,        TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// power
 	{TEGRA_PINGROUP_PTA,   TEGRA_MUX_I2C2,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// ddc audio gen2 i2c scl, sda
	{TEGRA_PINGROUP_RM,    TEGRA_MUX_I2C,           TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// touch gen1 i2c scl, sda
	{TEGRA_PINGROUP_SDB,   TEGRA_MUX_SDIO3,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// micro sd
	{TEGRA_PINGROUP_SDC,   TEGRA_MUX_SDIO3,         TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// micro sd
	{TEGRA_PINGROUP_SDD,   TEGRA_MUX_SDIO3,         TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// micro sd
	{TEGRA_PINGROUP_SDIO1, TEGRA_MUX_SDIO1,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// wlan
	{TEGRA_PINGROUP_SLXA,  TEGRA_MUX_SDIO3,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_SLXC,  TEGRA_MUX_SDIO3,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_SLXD,  TEGRA_MUX_SDIO3,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_SLXK,  TEGRA_MUX_SDIO3,         TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// micro sd
	{TEGRA_PINGROUP_SPDI,  TEGRA_MUX_RSVD,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_TRISTATE},	// NC
	{TEGRA_PINGROUP_SPDO,  TEGRA_MUX_RSVD,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// hdmi reg
	{TEGRA_PINGROUP_SPIA,  TEGRA_MUX_SPI2,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// spi2 ipc
	{TEGRA_PINGROUP_SPIB,  TEGRA_MUX_SPI2,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// spi2 ipc
	{TEGRA_PINGROUP_SPIC,  TEGRA_MUX_SPI2,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// spi2 ipc
	{TEGRA_PINGROUP_SPID,  TEGRA_MUX_GMI,     	 	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// BT wake up
	{TEGRA_PINGROUP_SPIE,  TEGRA_MUX_GMI,      		TEGRA_PUPD_PULL_UP,		TEGRA_TRI_TRISTATE},	// touch int, prox out
	{TEGRA_PINGROUP_SPIF,  TEGRA_MUX_RSVD,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// ear bias en
	{TEGRA_PINGROUP_SPIG,  TEGRA_MUX_SPI2_ALT,     	TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// hook_det
	{TEGRA_PINGROUP_SPIH,  TEGRA_MUX_SPI2_ALT,      TEGRA_PUPD_PULL_UP,		TEGRA_TRI_TRISTATE},	// batt low int
	{TEGRA_PINGROUP_UAA,   TEGRA_MUX_UARTA,         TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// ipc rx,tx,cts,rtx uart1
	{TEGRA_PINGROUP_UAB,   TEGRA_MUX_UARTA,        	TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// ipc srdy2, DMB int, DMB reset, ipc mrdy2
	{TEGRA_PINGROUP_UAC,   TEGRA_MUX_RSVD,			TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// mdm resest, mdm pwer on, ap pwr on, mdm reset flag
	{TEGRA_PINGROUP_UAD,   TEGRA_MUX_IRDA,          TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// ap20 uart2
	{TEGRA_PINGROUP_UCA,   TEGRA_MUX_UARTC,         TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// bt uart3
	{TEGRA_PINGROUP_UCB,   TEGRA_MUX_UARTC,         TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},		// bt uart3
	{TEGRA_PINGROUP_UDA,   TEGRA_MUX_SPI1,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},		// ipc spi1
	{TEGRA_PINGROUP_CK32,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_DDRC,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_PMCA,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_PMCB,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_PMCC,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_PMCD,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_PMCE,  TEGRA_MUX_NONE,          TEGRA_PUPD_PULL_UP,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_XM2C,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL,		TEGRA_TRI_NORMAL},
	{TEGRA_PINGROUP_XM2D,  TEGRA_MUX_NONE,          TEGRA_PUPD_NORMAL, 		TEGRA_TRI_NORMAL},
#endif
};

static struct tegra_gpio_table gpio_table[] = {
	{ .gpio = TEGRA_GPIO_HP_DET,		.enable = true	},
//                                                                                           
#if !defined(CONFIG_MACH_BSSQ)
	{ .gpio = TEGRA_GPIO_SPKR_EN,		.enable = true	},
#endif
//                                               
};

int __init bssq_pinmux_init(void)
{
#if defined(CONFIG_LU6500)	//                                                          
	int i;
	if((get_lge_pcb_revision() > REV_D))
		for(i=0; i<=ARRAY_SIZE(bssq_pinmux); i++)
			if(bssq_pinmux[i].pingroup == TEGRA_PINGROUP_LD7)
				bssq_pinmux[i].tristate = TEGRA_TRI_NORMAL;
#endif

	tegra_pinmux_config_table(bssq_pinmux, ARRAY_SIZE(bssq_pinmux));
	tegra_drive_pinmux_config_table(bssq_drive_pinmux,
					ARRAY_SIZE(bssq_drive_pinmux));

	tegra_gpio_config(gpio_table, ARRAY_SIZE(gpio_table));
	return 0;
}
