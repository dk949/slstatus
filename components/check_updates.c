/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../util.h"

const char *
check_updates(const char *cacheDir)
{

    char path[PATH_MAX];
    int num_updates;
    int important_updates;
    int kernel_updates;

    if (esnprintf(path, sizeof(path),
                  "%s/NUM_UPDATES", cacheDir) < 0) {
        return NULL;
    }
    if (pscanf(path, "%d", &num_updates) != 1) {
        return NULL;
    }

    if (esnprintf(path, sizeof(path),
                  "%s/IMPORTANT_UPDATES", cacheDir) < 0) {
        return NULL;
    }
    if (pscanf(path, "%d", &important_updates) != 1) {
        return NULL;
    }

    if (esnprintf(path, sizeof(path),
                  "%s/KERNEL_UPDATES", cacheDir) < 0) {
        return NULL;
    }
    if (pscanf(path, "%d", &kernel_updates) != 1) {
        return NULL;
    }



    char num[16];
    esnprintf(num, sizeof(num), "%d",num_updates);
    buf[0] = '\0';
    strcat(buf, num);
    if(important_updates != 0){
        esnprintf(num, sizeof(num), "%d",important_updates);
        strcat(buf, "(I");
        strcat(buf, num);
        if(kernel_updates != 0){
            strcat(buf, "L)");
        }
        else{
            strcat(buf, ")");
        }
    }else if (kernel_updates != 0){
        strcat(buf, "(L)");
    }


    return buf;
}
