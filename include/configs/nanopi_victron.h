#ifndef _NANOPI_VICTRON_H
#define _NANOPI_VICTRON_H

#include "sun8i.h"
#include "sunxi_victron_common.h"

#define VICTRON_ID_EEPROM_BUS 0
#define VICTRON_ID_CMD \
	"if test ${board_id} = 53454556; then " \
		"setenv fdtfile sun8i-h3-nanopi-easysolar.dtb; " \
	"elif test ${board_id} = 47504556; then " \
		"setenv fdtfile sun8i-h3-nanopi-paygo.dtb; " \
	"elif test ${board_id} = 32584556; then " \
		"setenv fdtfile sun7i-a20-einstein-ccgx2.dtb; " \
	"elif test ${board_id} = 3456584d; then " \
		"setenv fdtfile sun8i-h3-nanopi-v4-smart-hub.dtb; " \
	"fi"

#endif
