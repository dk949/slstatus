#include "../util.h"
#include <stdlib.h>

int
keep_time(int threshold){
    static int time = 0;
    if (time > threshold){
        time = 0;
        return 1;
    }
    else{
        time++;
        return 0;
    }
}

const char*
run_command_timed(const char *cmd){
    if (keep_time(7200)){
        system(cmd);
        return "!";
    }
    return "";
}
