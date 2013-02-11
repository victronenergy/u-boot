/*
 * Copyright (C) 2011
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * Copyright (C) 2009 TechNexion Ltd.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <i2c.h>
#include <nand.h>
#include <netdev.h>
#include <stdio_dev.h>
#include <asm/io.h>
#include <asm/arch/clocks.h>
#include <asm/arch/clocks_omap3.h>
#include <asm/arch/mem.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/omap_gpio.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/gpio.h>
#ifdef CONFIG_USB_EHCI
#include <usb.h>
#endif
#include <asm/ehci-omap.h>
#include <asm/arch/dss.h>
#include "bpp3.h"

DECLARE_GLOBAL_DATA_PTR;

extern int video_display_bitmap(ulong, int, int);

/* Timing definitions for Ethernet Controller */
static const u32 gpmc_smc911[] = {
	NET_GPMC_CONFIG1,
	NET_GPMC_CONFIG2,
	NET_GPMC_CONFIG3,
	NET_GPMC_CONFIG4,
	NET_GPMC_CONFIG5,
	NET_GPMC_CONFIG6,
};

static const u32 gpmc_XR16L2751[] = {
	XR16L2751_GPMC_CONFIG1,
	XR16L2751_GPMC_CONFIG2,
	XR16L2751_GPMC_CONFIG3,
	XR16L2751_GPMC_CONFIG4,
	XR16L2751_GPMC_CONFIG5,
	XR16L2751_GPMC_CONFIG6,
};

#ifdef CONFIG_VIDEO

#define CFG_PER_M4X2			10

# ifdef CFG_PER_M4X2
#  define DSS_CLOCK			(864000 / CFG_PER_M4X2)
# else
#  define DSS_CLOCK			432000
# endif
# define PIXEL_DIV(f)			((u8) (DSS_CLOCK / (f)))

# define BACKLIGHT_OFF_GPIO		42
# define BACKLIGHT_ON_GPIO		53
# define DSP_POWER_GPIO			139

static void enable_lcd(int on)
{
	gpio_request(BACKLIGHT_ON_GPIO, "BKL_ON");
	gpio_direction_output(BACKLIGHT_ON_GPIO, on);
	gpio_free(BACKLIGHT_ON_GPIO);
}

# ifdef CFG_PER_M4X2
/*
 * The init code will set the dss_timer to 432Mhz. Linux sets
 * the timer to a far lower value, but the display refresh
 * becomes distorted when the dss timer was running fast, so
 * a lower clock rate is used to drive the dss for the splash.
 */
void adjust_dss_timer(void)
{
	struct prcm *prcm_base = (struct prcm *)PRCM_BASE;

	/* EN_PERIPH_DPLL: CM_CLKEN_PLL[16:18] */
	sr32(&prcm_base->clken_pll, 16, 3, PLL_STOP);
	wait_on_value(ST_PERIPH_CLK, 0, &prcm_base->idlest_ckgen, LDELAY);

	/* M4 */
	sr32(&prcm_base->clksel_dss, 0, 5, (CFG_PER_M4X2 + 1));
	sr32(&prcm_base->clksel_dss, 0, 5, CFG_PER_M4X2);

	/* LOCK MODE (EN_PERIPH_DPLL): CM_CLKEN_PLL[16:18] */
	sr32(&prcm_base->clken_pll, 16, 3, PLL_LOCK);
	wait_on_value(ST_PERIPH_CLK, 2, &prcm_base->idlest_ckgen, LDELAY);
}
# else
void adjust_dss_timer(void)
{
}
# endif

# define SIZE_X	480
# define SIZE_Y	272

static struct panel_config panel = {
	.timing_h	= DSS_HBP(45) | DSS_HFP(1) | DSS_HSW(1),
	.timing_v	= DSS_VBP(16) | DSS_VFP(0) | DSS_VSW(1),
	.divisor	= 0x00010000 | PIXEL_DIV(9000),
	.lcd_size	= (SIZE_Y - 1) << 16 | (SIZE_X - 1),
	.panel_type	= 0x01,
	.data_lines	= 0x03,
	.load_mode	= 0x02,
	.panel_color	= 0x000000ff,
};

# ifdef CONFIG_SPL_BUILD

static int load_splash(void)
{
	uint32_t src = CONFIG_SPLASH_SCREEN_NAND_OFF;
	uint32_t *dst = (uint32_t *) gd->fb_base;

	if (!dst)
		return -1;

	nand_spl_load_image(src, SIZE_X * SIZE_Y * 4, dst);

	return 0;
}

int board_video_init(void)
{
	gpio_request(BACKLIGHT_ON_GPIO, "BKL_ON");
	gpio_direction_output(BACKLIGHT_ON_GPIO, 0);

	gpio_request(BACKLIGHT_OFF_GPIO, "BKL_OFF");
	gpio_direction_output(BACKLIGHT_OFF_GPIO, 0);

	gpio_request(DSP_POWER_GPIO, "DSP_POWER");
	gpio_direction_output(DSP_POWER_GPIO, 1);

	adjust_dss_timer();
	panel.frame_buffer = (void *) gd->fb_base;
	omap3_dss_panel_config(&panel);
	omap3_dss_enable();
	return load_splash();
}

# else /* CONFIG_SPL_BUILD */
int board_video_init(void)
{
	ulong *p = (ulong *) gd->fb_base;
	u32 n;
	char *s;
	ulong color;

	panel.frame_buffer = (void *) gd->fb_base;
	omap3_dss_panel_config(&panel);
	omap3_dss_enable();
	adjust_dss_timer();

	s = getenv("stdout");
	if (s && strcmp(s, "vga") == 0)
		color = 0x000000;
	else
		color = 0x0000FF;

	for (n = 0; n < SIZE_X * SIZE_Y; n++)
		*p++ = color;

	enable_lcd(1);

	return 0;
}

# endif /* CONFIG_SPL_BUILD */

#else /* CONFIG_VIDEO */
static void enable_lcd(int on)
{
}
#endif /* CONFIG_VIDEO */

#ifdef CONFIG_USB_EHCI
static struct omap_usbhs_board_data usbhs_bdata = {
	.port_mode[0] = OMAP_EHCI_PORT_MODE_PHY,
	.port_mode[1] = OMAP_USBHS_PORT_MODE_UNUSED,
	.port_mode[2] = OMAP_USBHS_PORT_MODE_UNUSED,
};

int ehci_hcd_init(int index, struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
	return omap_ehci_hcd_init(&usbhs_bdata, hccr, hcor);
}

int ehci_hcd_stop(void)
{
	return omap_ehci_hcd_stop();
}
#endif

int board_init(void)
{
	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */

	/* boot param addr */
	gd->bd->bi_boot_params = OMAP34XX_SDRC_CS0 + 0x100;

	/* Chip select 1 and 3 are used for XR16L2751 UART controller */
	enable_gpmc_cs_config(gpmc_XR16L2751, &gpmc_cfg->cs[1],
		XR16L2751_UART1_BASE, GPMC_SIZE_16M);

	enable_gpmc_cs_config(gpmc_XR16L2751, &gpmc_cfg->cs[3],
		XR16L2751_UART2_BASE, GPMC_SIZE_16M);

	gpio_request(CONFIG_OMAP_EHCI_PHY1_RESET_GPIO, "USB_PHY1_RESET");
	gpio_direction_output(CONFIG_OMAP_EHCI_PHY1_RESET_GPIO, 1);

	return 0;
}

/* position the framebuffer like linux */
#define CONFIG_VIDEO_ALIGNMENT	(2 * 1024 * 1024)
ulong video_setmem(ulong addr)
{
	addr -= SIZE_X * SIZE_Y * 4;
	addr = ALIGN(addr - CONFIG_VIDEO_ALIGNMENT + 1, CONFIG_VIDEO_ALIGNMENT);

	return addr;
}

int misc_init_r(void)
{
	dieid_num_r();
	enable_lcd(1);

	return 0;
}

void set_muxconf_regs(void)
{
	MUX_BPP3();
}

#ifdef CONFIG_DRIVER_TI_EMAC

# define CONTROL_EFUSE_EMAC_LSB  0x48002380
# define CONTROL_EFUSE_EMAC_MSB  0x48002384

int board_eth_init(bd_t *bis)
{
	u8 mac_addr[6];
	u32 mac_hi, mac_lo;
	const char *ethaddr;

	ethaddr = getenv("ethaddr");

	if (!ethaddr) {
		mac_lo = readl(CONTROL_EFUSE_EMAC_LSB);
		mac_hi = readl(CONTROL_EFUSE_EMAC_MSB);
		mac_addr[0] = (u8) (mac_hi >> 16);
		mac_addr[1] = (u8) (mac_hi >> 8);
		mac_addr[2] = (u8) (mac_hi >> 0);
		mac_addr[3] = (u8) (mac_lo >> 16);
		mac_addr[4] = (u8) (mac_lo >> 8);
		mac_addr[5] = (u8) (mac_lo >> 0);

		eth_setenv_enetaddr("ethaddr", mac_addr);
	}

	return davinci_emac_initialize();
}
#endif

#if defined(CONFIG_OMAP_HSMMC) && !defined(CONFIG_SPL_BUILD)
int board_mmc_init(bd_t *bis)
{
	return omap_mmc_init(0, 0, 0);
}
#endif

#ifdef CONFIG_SPL_OS_BOOT
void spl_board_prepare_for_linux(void)
{
	enable_lcd(1);
}

void spl_board_prepare_for_u_boot(void)
{
	dcache_disable();
}

int spl_start_uboot(void)
{
	int val = 0;
	if (!gpio_request(CONFIG_SPL_OS_BOOT_KEY, "U-Boot key")) {
		gpio_direction_input(CONFIG_SPL_OS_BOOT_KEY);
		val = gpio_get_value(CONFIG_SPL_OS_BOOT_KEY);
		gpio_free(CONFIG_SPL_OS_BOOT_KEY);
	}
	return !val;
}

# ifdef CONFIG_SPL_BUILD

void spl_board_init(void)
{
	if (!spl_start_uboot()) {
		dram_init_banksize();

		/* reserve TLB table (4k) */
		gd->tlb_addr = 0x8fff0000;
		debug("TLB table at: %08lx\n", gd->tlb_addr);

		/* add sram (64k actually, but the cp15 counts in MiBs) */
		gd->bd->bi_dram[1].start = CONFIG_SPL_TEXT_BASE;
		gd->bd->bi_dram[1].size =  (1 << 20);

		/* Enable caches */
		enable_caches();
	}

	gpmc_init();
	nand_init();

#  ifdef CONFIG_VIDEO
	board_video_init();
#  endif
}
# endif
#endif
