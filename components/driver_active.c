/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

char*
get_third_value(char* string)
{
    char* pch = strtok(string, " ");
    int i = 0;
    while (pch != NULL) {
        i++;
        if(i == 3){
            return pch;
        }
        pch = strtok (NULL, " ,.-");
    }
    return "Something went wrong. Check /proc/modules";
}



const char *
driver_active(const char *mod_name)
{
    FILE *fp;
    fp = fopen("/proc/modules", "r");

    while(fgets(buf, 256, (FILE*)fp)){
        if (!strncmp(buf, mod_name, strlen(mod_name))){
            strcpy(buf, get_third_value(buf));
            break;
        }
    }

    if ((int)buf[0] != 48){
        fclose(fp);
        return "ON";
    }
    else {
        fclose(fp);
        return "OFF";
    }
}
