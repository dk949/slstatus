/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"

const char *
check_updates()
{
    const char *num_updates = getenv("NUM_UPDATES");
    const char *important_updates = getenv("IMPORTANT_UPDATES");
    const char *kernel_updates = getenv("KERNEL_UPDATES");
    buf[0] = '\0';
    strcat(buf, num_updates);

    if((int)important_updates[0] != 48){
        strcat(buf, "(I");
        strcat(buf, important_updates);
        if((int)kernel_updates[0] != 48){
            strcat(buf, "L)");
        }
        else{
            strcat(buf, ")");
        }
    }else if ((int)kernel_updates[0] != 48){
        strcat(buf, "(L)");
    }

    return buf;

}
