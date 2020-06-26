#ifndef _SUNXI_VICTRON_COMMON_H
#define _SUNXI_VICTRON_COMMON_H

#define CONFIG_ENV_OFFSET_REDUND (CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)

#define VICTRON_ID_EEPROM_DT \
	"i2c" __stringify(VICTRON_ID_EEPROM_BUS) "/eeprom@50"

/*
 * Load the board ID from eeprom.  If booting from uSD card, let the
 * 'board_id' file override if it exists.
 */
#define CONFIG_PREBOOT \
	"i2c dev " __stringify(VICTRON_ID_EEPROM_BUS) "; " \
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
	VICTRON_ID_TABLE \
	"setfdt=run board_${board_id} || echo unknown board_id ${board_id}\0" \
	"setroot=" \
		"if test \"${version}\" = 1; then " \
			"setenv bootpart 1:2; " \
			"setenv mmcroot /dev/mmcblk1p2; " \
		"else " \
			"setenv bootpart 1:3; " \
			"setenv mmcroot /dev/mmcblk1p3; " \
		"fi\0" \
	"setmodel=" \
		"if env exists model; then fdt set / model \"$model\"; else true; fi\0" \
	"loadfdt=" \
		"load mmc ${bootpart} ${fdt_addr_r} ${bootdir}/${fdtfile}; fdt addr $fdt_addr_r; run setmodel\0" \
	"loadimage=" \
		"load mmc ${bootpart} ${kernel_addr_r} ${bootdir}/${bootfile}\0" \
	"loadramdisk=" \
		"load mmc ${bootpart} ${ramdisk_addr_r} ${bootdir}/${ramdiskfile}\0" \
	"mmcargs=" \
		"setenv bootargs console=${console} root=${mmcroot} rootwait ro rootfstype=ext4 ${runlevel}\0" \
	"testmode=" \
		"if test \"${runlevel}\" = 4; then " \
			"fdt rm " VICTRON_ID_EEPROM_DT " read-only; " \
		"else true; fi\0" \
	"boot_mmc0=" \
		"setenv bootpart 0:1; " \
		"load mmc ${bootpart} ${scriptaddr} boot.scr && " \
			"source ${scriptaddr}; " \
		"run boot_mmc1\0" \
	"boot_mmc1=" \
		"setenv bootdir /boot; "\
		"run setroot loadfdt loadimage mmcargs testmode && " \
			"bootz ${kernel_addr_r} - ${fdt_addr_r}\0" \
	"boot_mmc_auto=run boot_mmc${mmc_bootdev}\0"
#endif	/* !CONFIG_SPL_BUILD */

#endif
