#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../util.h"

const char *
check_packages(const char *cacheDir)
{

    char path[PATH_MAX];
    int numpackages;

    if (esnprintf(path, sizeof(path),
                  "%s/NUMPACKAGES", cacheDir) < 0) {
        return NULL;
    }
    if (pscanf(path, "%d", &numpackages) != 1) {
        return NULL;
    }
    return bprintf("%d", numpackages);
}
