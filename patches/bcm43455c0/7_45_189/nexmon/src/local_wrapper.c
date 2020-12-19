/***************************************************************************
 *                                                                         *
 *          ###########   ###########   ##########    ##########           *
 *         ############  ############  ############  ############          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ###########   ####  ######  ##   ##   ##  ##    ######          *
 *          ###########  ####  #       ##   ##   ##  ##    #    #          *
 *                   ##  ##    ######  ##   ##   ##  ##    #    #          *
 *                   ##  ##    #       ##   ##   ##  ##    #    #          *
 *         ############  ##### ######  ##   ##   ##  ##### ######          *
 *         ###########    ###########  ##   ##   ##   ##########           *
 *                                                                         *
 *            S E C U R E   M O B I L E   N E T W O R K I N G              *
 *                                                                         *
 * This file is part of NexMon.                                            *
 *                                                                         *
 * Copyright (c) 2016 NexMon Team                                          *
 *                                                                         *
 * NexMon is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * NexMon is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with NexMon. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 **************************************************************************/
#include <structs.h>
#include <stdarg.h>

#ifndef LOCAL_WRAPPER_C
#define LOCAL_WRAPPER_C

#include <firmware_version.h>
#include <structs.h>
#include <stdarg.h>

#ifndef WRAPPER_H
    // if this file is not included in the wrapper.h file, create dummy functions
    #define VOID_DUMMY { ; }
    #define RETURN_DUMMY { ; return 0; }

    #define AT(CHIPVER, FWVER, ADDR) __attribute__((weak, at(ADDR, "dummy", CHIPVER, FWVER)))
#else
    // if this file is included in the wrapper.h file, create prototypes
    #define VOID_DUMMY ;
    #define RETURN_DUMMY ;
    #define AT(CHIPVER, FWVER, ADDR)
#endif

AT(CHIP_VER_BCM43455c0, FW_VER_7_45_189, 0x19A548)
void
hndrte_print_memuse(void)
VOID_DUMMY

AT(CHIP_VER_BCM43455c0, FW_VER_7_45_189, 0x58950)
bool
wlc_quiet_chanspec(void *wlc_cmi, unsigned short chanspec)
RETURN_DUMMY

AT(CHIP_VER_BCM43455c0, FW_VER_7_45_189, 0x49874)
void
wlc_bmac_mute(struct wlc_hw_info *wlc_hw, bool on, uint32 flags)
VOID_DUMMY

AT(CHIP_VER_BCM43455c0, FW_VER_7_45_189, 0x57b70)
void
wlc_clr_quiet_chanspec(void *wlc_cmi, unsigned short chanspec)
VOID_DUMMY

AT(CHIP_VER_BCM43430a1, FW_VER_ALL, 0x85399c)
AT(CHIP_VER_BCM43455c0, FW_VER_ALL, 0x5DA48)
void *
wlc_hwtimer_alloc_timeout(void *wlc_off_0x5D0)
RETURN_DUMMY

AT(CHIP_VER_BCM43430a1, FW_VER_ALL, 0x853928)
AT(CHIP_VER_BCM43455c0, FW_VER_ALL, 0x5D9D4)
void *
wlc_hwtimer_add_timeout(void *timeout_inst, unsigned int timeout, void (*fn)(void *), void *fn_arg)
RETURN_DUMMY

AT(CHIP_VER_BCM43430a1, FW_VER_ALL, 0x8539c4)
AT(CHIP_VER_BCM43455c0, FW_VER_ALL, 0x5DA70)
void *
wlc_hwtimer_del_timeout(void *timeout_inst)
RETURN_DUMMY

AT(CHIP_VER_BCM43430a1, FW_VER_ALL, 0x880E30)
void *
wlc_hwtimer_free_timeout(void *timeout_inst)
RETURN_DUMMY

#undef VOID_DUMMY
#undef RETURN_DUMMY
#undef AT

#endif /*LOCAL_WRAPPER_C*/
