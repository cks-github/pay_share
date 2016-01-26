/*
 * Charles Smith
 *
 * Wed Jan 26, 2016
 *
 * config.c
 */

#include "pay.h"

/*
 * Global configurations
 */

/*
 * This list is used to add people to the pay group.
 */
const char *names[] = {
    "Charles",
    "Cory",
    "David",
    "Daryl",
    "Lydia",
    NULL,
};

/*
 * This list is used to generate transaction scenarios 
 * (mainly for testing)
 */
transaction_configuration trans_config[] = {
    { 50,  "pizza at the mall",  "Charles" },
    { 50,  "uber downtown",      "Cory"    },
    { 200, "cabin rental",       "David"   },
    { 100, "equipment",          "Daryl"   },
    { 0,   NULL                            },
};

