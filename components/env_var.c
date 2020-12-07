/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>

#include "../util.h"

const char *
env_var(const char *env)
{
    return getenv(env);
}
