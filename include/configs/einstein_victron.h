#ifndef _EINSTEIN_VICTRON_H
#define _EINSTEIN_VICTRON_H

#include "sun7i.h"
#include "sunxi_victron_common.h"

#define VICTRON_ID_EEPROM_BUS 1
#define VICTRON_ID_TABLE \
	"board_42434556=setenv fdtfile sun7i-a20-einstein-ccgx2.dtb\0" \
	"board_53434556=setenv fdtfile sun7i-a20-einstein-cerbo-gx-s.dtb\0" \
	"board_31424356=setenv fdtfile sun7i-a20-einstein-cerbo-b1.dtb\0"

#endif
