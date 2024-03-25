/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "rectang.h"

/// max side length
#define MAX_NUMBER 1000


/**
 * @brief Main entry point.
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) on failure.
 */
int main(void)
{
	// begin students to add code for task 4.1
    int a, b, c;
    int result;

    while (1) {
        printf("\nDreiecksbestimmung (CTRL-C: Abbruch)\n");

        printf("Seite a: ");
        a = getInt(MAX_NUMBER);
        if (a < 0) {
            printf("Fehlerhafte Eingabe.\n");
            continue;
        }

        printf("Seite b: ");
        b = getInt(MAX_NUMBER);
        if (b < 0) {
            printf("Fehlerhafte Eingabe.\n");
            continue;
        }

        printf("Seite c: ");
        c = getInt(MAX_NUMBER);
        if (c < 0) {
            printf("Fehlerhafte Eingabe.\n");
            continue;
        }

        result = isRectangular(a, b, c);

        if (result) {
            printf("-> Dreieck %d-%d-%d ist rechtwinklig\n", a, b, c);
        } else {
            printf("-> Dreieck %d-%d-%d ist nicht rechtwinklig\n", a, b, c);
        }
    }
	// end students to add code
    return EXIT_SUCCESS;
}
