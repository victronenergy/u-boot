#ifndef _EINSTEIN_VICTRON_H
#define _EINSTEIN_VICTRON_H

#include "sun7i.h"
#include "sunxi_victron_common.h"

#define VICTRON_ID_EEPROM_BUS 1
#define VICTRON_ID_CMD \
	"if test ${board_id} = 32584556; then " \
		"setenv fdtfile sun7i-a20-einstein-ccgx2.dtb; " \
	"fi"

#endif
