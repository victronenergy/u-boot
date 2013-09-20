/*
 * Copyright (C) 2011
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * Copyright (C) 2009 TechNexion Ltd.
 *
 * Configuration for the Technexion twister board.
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

#ifndef __CONFIG_H
#define __CONFIG_H

#include "tam3517-common.h"

#define MACH_TYPE_TAM3517	2818
#define CONFIG_MACH_TYPE	MACH_TYPE_TAM3517

#define CONFIG_TAM3517_SW3_SETTINGS
#define CONFIG_XR16L2751

#define CONFIG_BOOTDELAY	10

#define CONFIG_BOOTFILE		"uImage"

#define CONFIG_HOSTNAME		bpp3

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_PROMPT		"bpp3=> "
#define CONFIG_CMD_SETEXPR

#define CONFIG_OMAP3_GPIO_2

#define CONFIG_VIDEO
#ifdef CONFIG_VIDEO
# define CONFIG_VIDEO_OMAP3
# define CONFIG_SPLASH_SCREEN
# define CONFIG_SPLASH_SCREEN_NAND_OFF	0x340000
# define CONFIG_CFB_CONSOLE
# define CONFIG_VGA_AS_SINGLE_DEVICE
# define CONFIG_CONSOLE_MUX
# define CONFIG_VIDEO_SW_CURSOR
# define CONFIG_SYS_CONSOLE_IS_IN_ENV
# define CONFIG_SYS_CONSOLE_ENV_OVERWRITE
#endif

/* #define CONFIG_USB_KEYBOARD */
#ifdef CONFIG_USB_KEYBOARD
# define CONFIG_SYS_USB_EVENT_POLL
# define CONFIG_PREBOOT "usb start"
#endif

#ifdef MTDPARTS_DEFAULT
# undef MTDPARTS_DEFAULT
#endif
#define MTDPARTS_DEFAULT	"mtdparts=omap2-nand.0:512k(MLO),"\
		"1m(u-boot),256k(env1),256k(env2),1m(u-boot2),256k(bootparms),"\
		"768k(splash),6m(kernel),200m(data),-(rootfs)"

#define	CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=0\0" \
	"loadbootscript=fatload mmc ${mmcdev} 80004000 boot.scr\0" \
	"bootcmd=" \
		"if mmc rescan ${mmcdev}; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"if run loadbootscript; then " \
				"echo Running bootscript from mmc ...;" \
				"source 80004000;" \
			"fi;" \
		"fi;" \
		"run nandboot;\0" \
		"loadaddr=80300000\0" \
		"nandboot=nand read ${loadaddr} kernel && bootm ${loadaddr}\0"

/* SPL OS boot options */
#define CONFIG_CMD_SPL
#define CONFIG_CMD_SPL_WRITE_SIZE	0x400 /* 1024 byte */
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00400000
#define CONFIG_CMD_SPL_NAND_OFS		0x00300000

#define CONFIG_SPL_OS_BOOT
#define CONFIG_SPL_OS_BOOT_KEY	29 /* left button */

#define CONFIG_SYS_SPL_ARGS_ADDR	(PHYS_SDRAM_1 + 0x100)
#define CONFIG_SPL_BOARD_INIT
#ifdef CONFIG_VIDEO
# define CONFIG_SPL_VIDEO_SUPPORT
# define CONFIG_SPL_VIDEO_OMAP3
#endif

#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION		1

#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS  8     /* 4KB */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR	0x8   /* address 0x1000 */
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR 0x300 /* address 0x60000 */
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR	0x500 /* address 0xa0000 */

#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME	"u-boot.img"
#define CONFIG_SPL_FAT_LOAD_ARGS_NAME		"args"
#define CONFIG_SPL_FAT_LOAD_KERNEL_NAME		"uImage"

#endif /* __CONFIG_H */
