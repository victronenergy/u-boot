/*
 * Copyright (C) 2016 CANtronik Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/video.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <common.h>
#include <environment.h>
#include <fsl_esdhc.h>
#include <mmc.h>
#include <miiphy.h>
#include <netdev.h>
#include <usb.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_SIZE;

	return 0;
}

#define UART_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |		\
	PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |		\
	PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

static const iomux_v3_cfg_t uart1_pads[] = {
	MX6_PAD_GPIO1_IO04__UART1_TX	| MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_ENET2_COL__UART1_RX	| MUX_PAD_CTRL(UART_PAD_CTRL),
};

static void setup_iomux_uart(void)
{
	imx_iomux_v3_setup_multiple_pads(uart1_pads, ARRAY_SIZE(uart1_pads));
}

#ifdef CONFIG_FSL_ESDHC
#define USDHC_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |		\
	PAD_CTL_PUS_22K_UP  | PAD_CTL_SPEED_LOW |		\
	PAD_CTL_DSE_80ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define USDHC_POWER	IMX_GPIO_NR(1, 10)

static const iomux_v3_cfg_t usdhc1_pads[] = {
	MX6_PAD_SD1_CLK__USDHC1_CLK	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_CMD__USDHC1_CMD	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_DATA0__USDHC1_DATA0	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_DATA1__USDHC1_DATA1	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_DATA2__USDHC1_DATA2	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_DATA3__USDHC1_DATA3	| MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_GPIO1_IO10__GPIO1_IO_10	| MUX_PAD_CTRL(NO_PAD_CTRL),
};

static struct fsl_esdhc_cfg usdhc_cfg[1] = {
	{ USDHC1_BASE_ADDR, 0, 4 },
};

int board_mmc_getcd(struct mmc *mmc)
{
	return 1;	/* Assume boot SD always present */
}

int board_mmc_init(bd_t *bis)
{
	imx_iomux_v3_setup_multiple_pads(usdhc1_pads, ARRAY_SIZE(usdhc1_pads));

	gpio_request(USDHC_POWER, "usdhc_power");
	gpio_direction_output(USDHC_POWER, 1);

	usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);

	return fsl_esdhc_initialize(bis, &usdhc_cfg[0]);
}
#endif /* #ifdef CONFIG_FSL_ESDHC */

#ifdef CONFIG_NAND_MXS
#define GPMI_PAD_CTRL0 (PAD_CTL_PKE | PAD_CTL_PUE | PAD_CTL_PUS_100K_UP)
#define GPMI_PAD_CTRL1 (PAD_CTL_DSE_40ohm | PAD_CTL_SPEED_MED | \
			PAD_CTL_SRE_FAST)
#define GPMI_PAD_CTRL2 (GPMI_PAD_CTRL0 | GPMI_PAD_CTRL1)

static const iomux_v3_cfg_t gpmi_pads[] = {
	MX6_PAD_NAND_CLE__RAWNAND_CLE		| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_ALE__RAWNAND_ALE		| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_WP_B__RAWNAND_WP_B		| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_READY_B__RAWNAND_READY_B	| MUX_PAD_CTRL(GPMI_PAD_CTRL0),
	MX6_PAD_NAND_CE0_B__RAWNAND_CE0_B	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_RE_B__RAWNAND_RE_B		| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_WE_B__RAWNAND_WE_B		| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA00__RAWNAND_DATA00	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA01__RAWNAND_DATA01	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA02__RAWNAND_DATA02	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA03__RAWNAND_DATA03	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA04__RAWNAND_DATA04	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA05__RAWNAND_DATA05	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA06__RAWNAND_DATA06	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
	MX6_PAD_NAND_DATA07__RAWNAND_DATA07	| MUX_PAD_CTRL(GPMI_PAD_CTRL2),
};

static void setup_gpmi_nand(void)
{
	struct mxc_ccm_reg *mxc_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

	/* config gpmi nand iomux */
	imx_iomux_v3_setup_multiple_pads(gpmi_pads, ARRAY_SIZE(gpmi_pads));

	setup_gpmi_io_clk(MXC_CCM_CS2CDR_QSPI2_CLK_PODF(0) |
			  MXC_CCM_CS2CDR_QSPI2_CLK_PRED(3) |
			  MXC_CCM_CS2CDR_QSPI2_CLK_SEL(3));

	/* enable apbh clock gating */
	setbits_le32(&mxc_ccm->CCGR0, MXC_CCM_CCGR0_APBHDMA_MASK);
}
#endif /* CONFIG_NAND_MXS */

#ifdef CONFIG_FEC_MXC
#define ENET_PAD_CTRL		(PAD_CTL_PUS_100K_UP | PAD_CTL_PUE |	\
				 PAD_CTL_SPEED_HIGH  |			\
				 PAD_CTL_DSE_48ohm   | PAD_CTL_SRE_FAST)
#define ENET_RX_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |		\
				 PAD_CTL_SPEED_HIGH | PAD_CTL_SRE_FAST)

#define ETH_PHY_POWER	IMX_GPIO_NR(1, 13)
#define ETH_PHY_RESET	IMX_GPIO_NR(2, 17)

static const iomux_v3_cfg_t fec1_pads[] = {
	MX6_PAD_GPIO1_IO05__ENET1_REF_CLK1	| MUX_PAD_CTRL(ENET_PAD_CTRL) |
						  MUX_MODE_SION,
	MX6_PAD_ENET1_MDC__ENET1_MDC		| MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_ENET1_MDIO__ENET1_MDIO		| MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_RGMII1_RX_CTL__ENET1_RX_EN   | MUX_PAD_CTRL(ENET_RX_PAD_CTRL),
	MX6_PAD_RGMII1_RD0__ENET1_RX_DATA_0  | MUX_PAD_CTRL(ENET_RX_PAD_CTRL),
	MX6_PAD_RGMII1_RD1__ENET1_RX_DATA_1  | MUX_PAD_CTRL(ENET_RX_PAD_CTRL),
	MX6_PAD_RGMII1_TX_CTL__ENET1_TX_EN	| MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_RGMII1_TD0__ENET1_TX_DATA_0	| MUX_PAD_CTRL(ENET_PAD_CTRL),
	MX6_PAD_RGMII1_TD1__ENET1_TX_DATA_1	| MUX_PAD_CTRL(ENET_PAD_CTRL),

	/* FEC_PWR_EN - ENET PHY Power Enable */
	MX6_PAD_GPIO1_IO13__GPIO1_IO_13		| MUX_PAD_CTRL(NO_PAD_CTRL),

	/* ENET_RST - ENET Reset GPIO */
	MX6_PAD_KEY_ROW2__GPIO2_IO_17		| MUX_PAD_CTRL(NO_PAD_CTRL),
};

static void setup_iomux_fec1(void)
{
	imx_iomux_v3_setup_multiple_pads(fec1_pads, ARRAY_SIZE(fec1_pads));
}

static int setup_fec(void)
{
	u32 *gpr = (u32 *)IOMUXC_GPR_BASE_ADDR;
	int err;

	/* clear gpr1[13], set gpr1[17] to select anatop clock output */
	clrbits_le32(&gpr[1], 1 << 13);
	setbits_le32(&gpr[1], 1 << 17);

	err = enable_fec_anatop_clock(0, ENET_50MHZ);
	if (err)
		return err;

	gpio_request(ETH_PHY_POWER, "eth_phy_power");
	gpio_request(ETH_PHY_RESET, "eth_phy_reset");

	/* Hold PHY in reset */
	gpio_direction_output(ETH_PHY_RESET, 0);

	/* Required to avoid system reset on cold boot */
	mdelay(100);

	/* Power up PHY */
	gpio_direction_output(ETH_PHY_POWER, 0);
	mdelay(30);

	/* Out of reset */
	gpio_set_value(ETH_PHY_RESET, 1);
	mdelay(1);

	return 0;
}

int board_eth_init(bd_t *bis)
{
	setup_iomux_fec1();
	setup_fec();

	return fecmxc_initialize_multi(bis, 0, CONFIG_FEC_MXC_PHYADDR,
				       IMX_FEC_BASE);
}

#endif /* CONFIG_FEC_MXC */

#ifdef CONFIG_USB_EHCI_MX6
#define USBNC_OTG1_CTRL_REG_OFFSET	0x800
#define UCTRL_PWR_POL			(1 << 9)

#define USB_OTG1_POWER	IMX_GPIO_NR(1, 9)
#define USB_OTG2_POWER	IMX_GPIO_NR(1, 12)

static const iomux_v3_cfg_t usb_otg_pads[] = {
	/* OTG1 */
	MX6_PAD_GPIO1_IO09__GPIO1_IO_9		| MUX_PAD_CTRL(NO_PAD_CTRL),

	/* OTG2 */
	MX6_PAD_GPIO1_IO12__GPIO1_IO_12		| MUX_PAD_CTRL(NO_PAD_CTRL)
};

static void setup_usb(void)
{
	imx_iomux_v3_setup_multiple_pads(usb_otg_pads,
					 ARRAY_SIZE(usb_otg_pads));
}

int board_usb_phy_mode(int port)
{
	/* All ports are host on CANvu500 */
	return USB_INIT_HOST;
}

int board_ehci_hcd_init(int port)
{
	u32 *usbnc_usb_ctrl;

	if (port > 1)
		return -EINVAL;

	/* Set Power polarity */
	usbnc_usb_ctrl =
		(u32 *)(USB_BASE_ADDR + USBNC_OTG1_CTRL_REG_OFFSET) + port;
	setbits_le32(usbnc_usb_ctrl, UCTRL_PWR_POL);

	if (port == 0) {
		gpio_request(USB_OTG1_POWER, "usb_otg1_power");
		gpio_direction_output(USB_OTG1_POWER, 1);
	} else {
		gpio_request(USB_OTG2_POWER, "usb_otg2_power");
		gpio_direction_output(USB_OTG2_POWER, 1);
	}

	return 0;
}
#endif /* CONFIG_USB_EHCI_MX6 */

#ifdef CONFIG_VIDEO_MXS
#define LCD_PAD_CTRL    (PAD_CTL_HYS | PAD_CTL_PUS_100K_UP | PAD_CTL_PUE | \
	PAD_CTL_PKE | PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm)

#define LCD_BACKLIGHT	IMX_GPIO_NR(5, 13)

static iomux_v3_cfg_t const lcd_pads[] = {
	MX6_PAD_LCD1_CLK__LCDIF1_CLK | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_ENABLE__LCDIF1_ENABLE | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_HSYNC__LCDIF1_HSYNC | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_VSYNC__LCDIF1_VSYNC | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA00__LCDIF1_DATA_0 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA01__LCDIF1_DATA_1 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA02__LCDIF1_DATA_2 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA03__LCDIF1_DATA_3 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA04__LCDIF1_DATA_4 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA05__LCDIF1_DATA_5 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA06__LCDIF1_DATA_6 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA07__LCDIF1_DATA_7 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA08__LCDIF1_DATA_8 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA09__LCDIF1_DATA_9 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA10__LCDIF1_DATA_10 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA11__LCDIF1_DATA_11 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA12__LCDIF1_DATA_12 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA13__LCDIF1_DATA_13 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA14__LCDIF1_DATA_14 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA15__LCDIF1_DATA_15 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA16__LCDIF1_DATA_16 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA17__LCDIF1_DATA_17 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA18__LCDIF1_DATA_18 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA19__LCDIF1_DATA_19 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA20__LCDIF1_DATA_20 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA21__LCDIF1_DATA_21 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA22__LCDIF1_DATA_22 | MUX_PAD_CTRL(LCD_PAD_CTRL),
	MX6_PAD_LCD1_DATA23__LCDIF1_DATA_23 | MUX_PAD_CTRL(LCD_PAD_CTRL),

	/* backlight control */
	MX6_PAD_RGMII2_RD1__GPIO5_IO_13 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

static int setup_lcd(void)
{
	enable_lcdif_clock(LCDIF1_BASE_ADDR, 1);
	imx_iomux_v3_setup_multiple_pads(lcd_pads, ARRAY_SIZE(lcd_pads));

	gpio_request(LCD_BACKLIGHT, "lcd_backlight");
	gpio_direction_output(LCD_BACKLIGHT , 1);

	return 0;
}
#endif

int board_early_init_f(void)
{
	setup_iomux_uart();

	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_NAND_MXS
	setup_gpmi_nand();
#endif

#ifdef CONFIG_USB_EHCI_MX6
	setup_usb();
#endif

#ifdef CONFIG_VIDEO_MXS
	setup_lcd();
#endif

	return 0;
}

#define ATTN_BTN IMX_GPIO_NR(2, 19)

int board_late_init(void)
{
	struct src *src = (struct src *)SRC_BASE_ADDR;
	int bmode = (src->sbmr2 & SRC_SBMR2_BMOD_MASK) >> SRC_SBMR2_BMOD_SHIFT;

	gpio_request(ATTN_BTN, "attn_btn");
	gpio_direction_input(ATTN_BTN);

	if (bmode == SRC_SBMR2_BMOD_SERIAL || !gpio_get_value(ATTN_BTN)) {
		set_default_env(NULL);
		env_set("recovery", "1");
	} else {
		env_set("recovery", "0");
	}

	return 0;
}

int checkboard(void)
{
	puts("Board: CANVU500\n");

	return 0;
}
