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

#pragma NEXMON targetregion "patch"

#include <firmware_version.h>   // definition of firmware version macros
#include <debug.h>              // contains macros to access the debug hardware
#include <wrapper.h>            // wrapper definitions for functions that already exist in the firmware
#include <structs.h>            // structures that are used by the code in the firmware
#include <helper.h>             // useful helper functions
#include <patcher.h>            // macros used to craete patches such as BLPatch, BPatch, ...
#include <rates.h>              // rates used to build the ratespec for frame injection
#include <nexioctls.h>          // ioctls added in the nexmon patch
#include <version.h>            // version information
#include <argprintf.h>          // allows to execute argprintf to print into the arg buffer
#include <bcmwifi_channels.h>

#define NULL 0

int 
wlc_ioctl_hook(struct wlc_info *wlc, int cmd, char *arg, int len, void *wlc_if)
{
    int ret = IOCTL_ERROR;
    argprintf_init(arg, len);

    switch(cmd) {

        case 512:
        {
            unsigned int chanspec = get_chanspec(wlc);
            unsigned int channel = CHSPEC_CHANNEL(chanspec);

            printf("ioctl.c:504: INFO: chanspec = 0x%x\n", chanspec);
            printf("ioctl.c:504: INFO: currently used channel=%d\n", channel);

            unsigned char tmp_channel = channel;
            if (arg != 0) {
                printf("ioctl.c:504: arg != 0: tmp_channel = %d\n", tmp_channel);
                tmp_channel = *((unsigned int*)arg);
            } else {
                ret = IOCTL_SUCCESS;
                break;
            }
            printf("ioctl.c:504: INFO: new channel = %d\n", tmp_channel);

            /*if (tmp_channel > 14 || tmp_channel == 0) {
                ret = IOCTL_SUCCESS;
                break;
            }*/

            // set the channel
            set_chanspec(wlc, CH20MHZ_CHSPEC(tmp_channel));

            chanspec = get_chanspec(wlc);
            channel = CHSPEC_CHANNEL(chanspec);
            unsigned int bandwidth = CHSPEC_BW(chanspec);

            printf("ioctl.c:504: INFO: chanspec = 0x%x\n", chanspec);
            printf("ioctl.c:504: INFO: BW=%d; CH=%d\n", (bandwidth == WL_CHANSPEC_BW_20) ? 20 : 80, channel);

            break;
        }

        case 510:
        {
            argprintf("%s\n", __FUNCTION__);
            ret = IOCTL_SUCCESS;
            break;
        }

        case 511:
        {
            dumpcb_t *d;
            struct bcmstrbuf b;
            int err;

            bcm_binit(&b, arg, len);

            for (d = wlc->dumpcb_head; d != NULL; d = d->next) {
                bcm_bprintf(&b, "%s\n", d->name);
                err = d->dump_fn(d->dump_fn_arg, &b);
                if (err) bcm_bprintf(&b, "ERR: %d\n", err);
                bcm_bprintf(&b, "\n");
            }
            ret = IOCTL_SUCCESS;
            break;
        }

        default:
            ret = wlc_ioctl(wlc, cmd, arg, len, wlc_if);
    }

    return ret;
}

__attribute__((at(0x20CD80, "", CHIP_VER_BCM43455c0, FW_VER_7_45_189)))
GenericPatch4(wlc_ioctl_hook, wlc_ioctl_hook + 1);
