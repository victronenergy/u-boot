#ifndef _NANOPI_EASYSOLAR_CONFIG_H
#define _NANOPI_EASYSOLAR_CONFIG_H

#include "sun8i.h"

#define CONFIG_ENV_OFFSET_REDUND (CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)

/*
 * Load the board ID from eeprom.  If booting from uSD card, let the
 * 'board_id' file override if it exists.
 */
#define CONFIG_PREBOOT \
	"i2c read ${eeprom_addr} 0 4 ${kernel_addr_r}; " \
	"if test ${mmc_bootdev} = 0; then " \
		"load mmc 0:1 ${kernel_addr_r} board_id; " \
	"fi; " \
	"setexpr.l board_id *${kernel_addr_r}"

#ifndef CONFIG_SPL_BUILD
#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
	"eeprom_addr=50\0" \
	"console=ttyS0,115200\0" \
	"bootfile=zImage\0" \
	"fdtfile=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0" \
	"ramdiskfile=initramfs\0" \
	"setfdt=" \
		"if test ${board_id} = 53454556; then " \
			"setenv fdtfile sun8i-h3-nanopi-easysolar.dtb; " \
		"elif test ${board_id} = 47504556; then " \
			"setenv fdtfile sun8i-h3-nanopi-paygo.dtb; " \
		"fi\0" \
	"setroot=" \
		"if test \"${version}\" = 1; then " \
			"setenv bootpart 1:2; " \
			"setenv mmcroot /dev/mmcblk1p2; " \
		"else " \
			"setenv bootpart 1:3; " \
			"setenv mmcroot /dev/mmcblk1p3; " \
		"fi\0" \
	"loadfdt=" \
		"load mmc ${bootpart} ${fdt_addr_r} ${bootdir}/${fdtfile}\0" \
	"loadimage=" \
		"load mmc ${bootpart} ${kernel_addr_r} ${bootdir}/${bootfile}\0" \
	"loadramdisk=" \
		"load mmc ${bootpart} ${ramdisk_addr_r} ${bootdir}/${ramdiskfile}\0" \
	"mmcargs=" \
		"setenv bootargs console=${console} root=${mmcroot} rootwait ro rootfstype=ext4\0" \
	"boot_mmc0=" \
		"setenv bootpart 0:1; " \
		"load mmc ${bootpart} ${scriptaddr} boot.scr && " \
			"source ${scriptaddr}; " \
		"run boot_mmc1\0" \
	"boot_mmc1=" \
		"setenv bootdir /boot; "\
		"run setroot loadfdt loadimage mmcargs && " \
			"bootz ${kernel_addr_r} - ${fdt_addr_r}\0" \
	"boot_mmc_auto=run boot_mmc${mmc_bootdev}\0"
#endif	/* !CONFIG_SPL_BUILD */

#endif
