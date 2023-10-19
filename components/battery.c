/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#if defined(__linux__)
#include <limits.h>
#include <stdint.h>
#include <unistd.h>

static const char *
pick(const char *bat, const char *f1, const char *f2, char *path,
     size_t length)
{
    if (esnprintf(path, length, f1, bat) > 0 &&
        access(path, R_OK) == 0) {
        return f1;
    }

    if (esnprintf(path, length, f2, bat) > 0 &&
        access(path, R_OK) == 0) {
        return f2;
    }

    return NULL;
}

typedef enum { Charging, Discharging, Full, Unknown, Error } State;

State
battery_state(const char *bat)
{
    static struct {
        char *state_str;
        State state;
    } map[] = {
        { "Charging",    Charging },
        { "Discharging", Discharging },
        { "Full",        Full },
    };
    size_t i;
    char path[PATH_MAX], state[12];

    if (esnprintf(path, sizeof(path),
                  "/sys/class/power_supply/%s/status", bat) < 0) {
        return Error;
    }
    if (pscanf(path, "%12s", state) != 1) {
        return Error;
    }

    for (i = 0; i < LEN(map); i++) {
        if (!strcmp(map[i].state_str, state)) {
            break;
        }
    }
    return (i == LEN(map)) ? Unknown : map[i].state;
}

const char *
battery_perc(const char *bat)
{
    int perc;
    char path[PATH_MAX];

    if (esnprintf(path, sizeof(path),
                  "/sys/class/power_supply/%s/capacity", bat) < 0) {
        return NULL;
    }
    if (pscanf(path, "%d", &perc) != 1) {
        return NULL;
    }

    char const *symbol = NULL;
    switch(battery_state(bat)){
        break;case Discharging:
                 if(perc <= 10) symbol = "󰁺 ";
            else if(perc <= 20) symbol = "󰁻 ";
            else if(perc <= 30) symbol = "󰁼 ";
            else if(perc <= 40) symbol = "󰁽 ";
            else if(perc <= 50) symbol = "󰁾 ";
            else if(perc <= 60) symbol = "󰁿 ";
            else if(perc <= 70) symbol = "󰂀 ";
            else if(perc <= 80) symbol = "󰂁 ";
            else if(perc <= 90) symbol = "󰂂 ";
            else                symbol = "󰁹 ";
        break;case Charging:
                 if(perc <= 10) symbol = "󰢜 ";
            else if(perc <= 20) symbol = "󰂆 ";
            else if(perc <= 30) symbol = "󰂇 ";
            else if(perc <= 40) symbol = "󰂈 ";
            else if(perc <= 50) symbol = "󰢝 ";
            else if(perc <= 60) symbol = "󰂉 ";
            else if(perc <= 70) symbol = "󰢞 ";
            else if(perc <= 80) symbol = "󰂊 ";
            else if(perc <= 90) symbol = "󰂋 ";
            else                symbol = "󰂅 ";
        break;case Full: symbol = "󱟢 ";
        break;case Unknown:  symbol = "󰂑 ";
        break;case Error: return "󰂃 ";
    }
    if(!symbol) return "";
    const char *b = bprintf("%s:%s%d", symbol, percent_pad(perc), perc);


    return b;
}

#else
#error "Only linux is supported :("
#endif
