/*
 * Copyright 2016, CANtronik Ltd.
 *
 * Configuration settings for the CANtronik CANvu500 board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "mx6_common.h"
#include "imx6_spl.h"

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_MALLOC_LEN		SZ_32M

#define CONFIG_MXC_UART_BASE		UART1_BASE

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_USDHC_NUM	1

/* Network */
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE             RMII
#define CONFIG_ETHPRIME                 "FEC0"
#define CONFIG_FEC_MXC_PHYADDR          0

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR
#define PHYS_SDRAM_SIZE			SZ_256M
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET 	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR 	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* NAND stuff */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x40000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8

#define CONFIG_ENV_OFFSET		SZ_4M
#define CONFIG_ENV_SECT_SIZE		SZ_256K
#define CONFIG_ENV_SIZE			CONFIG_ENV_SECT_SIZE

#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS

/* USB Configs */
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2

/* Watchdog */
#define CONFIG_HW_WATCHDOG
#define CONFIG_IMX_WATCHDOG

#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_LOGO
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_BMP_GZIP
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE SZ_2M
#define MXS_LCDIF_BASE MX6SX_LCDIF1_BASE_ADDR
#define SPLASH_NAND_OFFS 0x380000
#define SPLASH_NAND_SIZE 0x80000
#define SPLASH_LOAD_ADDR 0x86000000
#endif

#define CONFIG_BOOTCOMMAND "run recovercmd; run setroot setargs ubiboot"

#define CONFIG_ENV_VARS_UBOOT_CONFIG
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"bootargs=\0"							\
	"console=ttymxc0\0"						\
	"mtdids=" CONFIG_MTDIDS_DEFAULT "\0"				\
	"mtdparts=" CONFIG_MTDPARTS_DEFAULT "\0"			\
	"netboot=dhcp ${board}/fitImage && bootm\0"			\
	"recovercmd=test ${recovery} = 1 && setenv stdout serial,vga && run usbboot\0" \
	"rdaddr=0x88000000\0"						\
	"setargs=setenv bootargs ${bootargs} "				\
		"console=${console},${baudrate} "			\
		"${mtdparts} ubi.mtd=ubi "				\
		"root=${root} rootfstype=ubifs ${runlevel}\0"		\
	"setroot=setenv root ubi0:rootfs${swversion}\0"			\
	"swversion=1\0"							\
	"ubiboot=ubi part ubi && ubifsmount ${root} && ubifsload ${loadaddr} boot/fitImage && bootm\0" \
	"usbboot=usb reset && load usb 0 ${loadaddr} boot.scr && source ${loadaddr}; sleep 2; run usbboot\0" \
	"videomode=video=ctfb:x:800,y:480,depth:24,pclk:37037,le:40,ri:60,up:10,lo:10,hs:20,vs:10,sync:0,vmode:0\0"

#endif				/* __CONFIG_H */
