/*
 * Copyright (C) 2011
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * Copyright (C) 2010 TechNexion Ltd.
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
 * Foundation, Inc.
 */

#ifndef _BPP3_H_
#define _BPP3_H_

const omap3_sysinfo sysinfo = {
	DDR_DISCRETE,
	"BPP3",
	"NAND",
};

#define XR16L2751_GPMC_CONFIG1	0x00000000
#define XR16L2751_GPMC_CONFIG2	0x001e1e01
#define XR16L2751_GPMC_CONFIG3	0x00080300
#define XR16L2751_GPMC_CONFIG4	0x1c091c09
#define XR16L2751_GPMC_CONFIG5	0x04181f1f
#define XR16L2751_GPMC_CONFIG6	0x00000FCF

#define XR16L2751_UART1_BASE	0x21000000
#define XR16L2751_UART2_BASE	0x23000000

/*
 * IEN  - Input Enable
 * IDIS - Input Disable
 * PTD  - Pull type Down
 * PTU  - Pull type Up
 * DIS  - Pull type selection is inactive
 * EN	- Pull type selection is active
 * M0	- Mode 0
 */
#define MUX_BPP3_UART1						\
	MUX_VAL(CP(UART1_TX),		M0 | IDIS)		\
	MUX_VAL(CP(UART1_RX),		M0 | IEN | DIS)		\

#define MUX_BPP3_POWER						\
	/* gpio_99, power instantly off */			\
	MUX_VAL(CP(CCDC_DATA0),		M4 | IEN | EN | PTD)	\
	/* gpio_101 and gpio_104, controls the power supply */	\
	MUX_VAL(CP(CCDC_DATA2),		M4 | IEN | EN | PTD)	\
	MUX_VAL(CP(CCDC_DATA5),		M4 | IEN | EN | PTU)	\

#define MUX_BPP3_GPIO						\
	/* ETK_D12, gpio_26, f1 button */			\
	MUX_VAL(CP(ETK_D12_ES2),	M4 | IEN | DIS) 	\
	/* ETK_D15, gpio_29, left button */			\
	MUX_VAL(CP(ETK_D15_ES2),	M4 | IEN | DIS) 	\
	/* gpio 35, buzzer */					\
	MUX_VAL(CP(GPMC_A2),		M4 | IEN | EN | PTD)	\
	/* gpio_182, pin 90, relay, pull down */		\
	MUX_VAL(CP(MCSPI2_CS1),		M4 | IEN | EN | PTD)	\
	/* gpio_153, mcbsp4_dr, vebus power, 0 forced on */	\
	MUX_VAL(CP(MCBSP4_DR),		M4 | IEN | EN | PTU)	\
	/* gpio_155, mcbsp4_fsx, mk2 power, 0 off, 1 on */	\
	MUX_VAL(CP(MCBSP4_FSX),		M4 | IEN | EN | PTD)	\

#define MUX_BPP3_MMC2_DISABLE					\
	MUX_VAL(CP(MMC2_CLK),		M7)			\
	MUX_VAL(CP(MMC2_CMD),		M7)			\
	MUX_VAL(CP(MMC2_DAT0),		M7)			\
	MUX_VAL(CP(MMC2_DAT1),		M7)			\
	MUX_VAL(CP(MMC2_DAT2),		M7)			\
	MUX_VAL(CP(MMC2_DAT3),		M7)			\
	MUX_VAL(CP(MMC2_DAT4),		M7)			\
	MUX_VAL(CP(MMC2_DAT5),		M7)			\
	/* used as gpio */					\
	/* MUX_VAL(CP(MMC2_DAT6),	M7) */			\
	/* MUX_VAL(CP(MMC2_DAT7),	M7) */			\

#define MUX_TAM3517_DSS						\
	MUX_VAL(CP(DSS_PCLK),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_HSYNC),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_VSYNC),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_ACBIAS),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA0),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA1),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA2),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA3),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA4),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA5),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA6),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA7),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA8),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA9),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA10),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA11),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA12),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA13),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA14),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA15),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA16),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA17),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA18),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA19),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA20),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA21),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA22),		M0 | IDIS)		\
	MUX_VAL(CP(DSS_DATA23),		M0 | IDIS)		\
	/* gpio_139, pin 70, display on (LCD_PON / DSP_PON) */	\
	MUX_VAL(CP(MMC2_DAT7),		M4 | IEN | EN | PTD)	\
	/* gpio_53, pin 144, LCD backlight on */		\
	MUX_VAL(CP(GPMC_NCS2),		M4 | IEN | EN | PTD)	\
	/* gpio_42, pin 153, LCD backlight off */	\
	MUX_VAL(CP(GPMC_A9),		M4 | IEN | EN | PTU)	\

#define MUX_TAM3517_MMC1					\
	MUX_VAL(CP(MMC1_CLK),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(MMC1_CMD),		M0 | IEN | DIS)		\
	MUX_VAL(CP(MMC1_DAT0),		M0 | IEN | DIS)		\
	MUX_VAL(CP(MMC1_DAT1),		M0 | IEN | DIS)		\
	MUX_VAL(CP(MMC1_DAT2),		M0 | IEN | DIS)		\
	MUX_VAL(CP(MMC1_DAT3),		M0 | IEN | DIS)		\
	/* CardDetect */					\
	MUX_VAL(CP(MMC1_DAT4),		M4 | IEN | EN | PTU)	\

#define MUX_TAM3517_RMII 					\
	MUX_VAL(CP(RMII_MDIO_DATA),	M0 | IEN | DIS)		\
	MUX_VAL(CP(RMII_MDIO_CLK),	M0 | IDIS)		\
	MUX_VAL(CP(RMII_RXD0)	,	M0 | IEN | DIS)		\
	MUX_VAL(CP(RMII_RXD1),		M0 | IEN | DIS)		\
	MUX_VAL(CP(RMII_CRS_DV),	M0 | IEN | DIS)		\
	MUX_VAL(CP(RMII_RXER),		M0 | IEN | DIS)		\
	MUX_VAL(CP(RMII_TXD0),		M0 | IDIS)		\
	MUX_VAL(CP(RMII_TXD1),		M0 | IDIS)		\
	MUX_VAL(CP(RMII_TXEN),		M0 | IDIS)		\
	MUX_VAL(CP(RMII_50MHZ_CLK),	M0 | IEN | EN | PTD)	\

#define MUX_TAM3517_SDRC					\
	MUX_VAL(CP(SDRC_D0),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D1),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D2),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D3),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D4),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D5),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D6),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D7),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D8),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D9),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D10),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D11),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D12),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D13),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D14),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D15),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D16),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D17),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D18),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D19),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D20),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D21),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D22),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D23),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D24),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D25),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D26),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D27),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D28),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D29),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D30),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_D31),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_CLK),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_DQS0),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_DQS1),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_DQS2),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_DQS3),		M0 | IEN | DIS)		\
	MUX_VAL(CP(SDRC_DQS0N),		M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(SDRC_DQS1N),		M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(SDRC_DQS2N),		M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(SDRC_DQS3N),		M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(SDRC_CKE0),		M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(SDRC_CKE1),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(STRBEN_DLY0),	M0 | IEN | EN | PTD)	\
	MUX_VAL(CP(STRBEN_DLY1),	M0 | IEN | EN | PTD)	\

#define MUX_TAM3517_INTERNAL					\
	/* gpio_57, unknown function, but crucial */		\
	MUX_VAL(CP(GPMC_NCS6),		M4 | IDIS) 		\

#define MUX_TAM3517_HSUSB1					\
	/* hsusb1_stp */					\
	MUX_VAL(CP(ETK_CLK_ES2),	M3 | IDIS)		\
	/* hsusb1_clk */					\
	MUX_VAL(CP(ETK_CTL_ES2),	M3 | IDIS)		\
	/* hsusb1_data[0..7] */					\
	MUX_VAL(CP(ETK_D0_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D1_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D2_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D3_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D4_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D5_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D6_ES2),		M3 | IEN | EN | PTU)	\
	MUX_VAL(CP(ETK_D7_ES2),		M3 | IEN | EN | PTU)	\
	/* hsusb1_dir */					\
	MUX_VAL(CP(ETK_D8_ES2),		M3 | IEN | EN | PTD)	\
	/* hsusb1_nxt */					\
	MUX_VAL(CP(ETK_D9_ES2),		M3 | IEN | EN | PTD)	\
	MUX_VAL(CP(USB0_DRVBUS),	M0 | IEN | EN | PTD)	\
	/* USB NRESET */					\
	MUX_VAL(CP(ETK_D11_ES2),	M4 | IDIS)		\

/* tam3517: do not multiplex these signals */
#define MUX_BPP3_GPMC \
	MUX_VAL(CP(GPMC_D0),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D1),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D2),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D3),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D4),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D5),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D6),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D7),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D8),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D9),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D10),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D11),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D12),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D13),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D14),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_D15),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(GPMC_NCS0),		M0 | IDIS)		\

#define MUX_TAM3517_CONTROL_DEBUG				\
	MUX_VAL(CP(SYS_32K),		M0 | IEN | DIS )	\
	MUX_VAL(CP(SYS_CLKREQ),		M0 | IEN | DIS )	\
	MUX_VAL(CP(SYS_NIRQ),		M0 | IEN | EN | PTU)	\
	MUX_VAL(CP(SYS_NRESWARM),	M4 | IDIS)		\

#define MUX_BPP3()			\
	MUX_TAM3517_CONTROL_DEBUG	\
	MUX_TAM3517_DSS			\
	MUX_TAM3517_HSUSB1		\
	MUX_TAM3517_INTERNAL		\
	MUX_TAM3517_MMC1		\
	MUX_TAM3517_RMII		\
	MUX_TAM3517_SDRC		\
	MUX_BPP3_GPIO			\
	MUX_BPP3_GPMC			\
	MUX_BPP3_MMC2_DISABLE		\
	MUX_BPP3_POWER			\
	MUX_BPP3_UART1

#endif
