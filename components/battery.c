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

char
battery_state(const char *bat)
{
    static struct {
        char *state;
        char symbol;
    } map[] = {
        { "Charging",    '+' },
        { "Discharging", '-' },
        { "Full",        ' ' },
    };
    size_t i;
    char path[PATH_MAX], state[12];

    if (esnprintf(path, sizeof(path),
                  "/sys/class/power_supply/%s/status", bat) < 0) {
        return '\0';
    }
    if (pscanf(path, "%12s", state) != 1) {
        return '\0';
    }

    for (i = 0; i < LEN(map); i++) {
        if (!strcmp(map[i].state, state)) {
            break;
        }
    }
    return (i == LEN(map)) ? '?' : map[i].symbol;
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
    const char *b = bprintf("%s%c%d", percent_pad(perc), battery_state(bat), perc);


    return b;
}

#else
#error "Only linux is supported :("
#endif
