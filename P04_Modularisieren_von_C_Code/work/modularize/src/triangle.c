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
#include <string.h>
#include "read.h"
#include "rectang.h"

/// max side length
#define MAX_NUMBER 1000

int parse_triangle_edge(char *message);

/**
 * @brief Main entry point.
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) on failure.
 */
int main(void)
{
    // begin students to add code for task 4.1
    while(1) {
        printf("\nDreiecksbestimmung (CTRL-C: Abbruch)\n\n");

        int a;
        int b;
        int c;
        char str[10];

        a = parse_triangle_edge("Seite a: ");
        if (a == READ_ERROR ) break;
        b = parse_triangle_edge("Seite b: ");
        if (b == READ_ERROR ) break;
        c = parse_triangle_edge("Seite c: ");
        if (c == READ_ERROR ) break;

        if (isRectangular(a, b, c) == true) strcpy(str,"");
        else strcpy(str,"nicht ");

        printf("-> Dreieck %d-%d-%d ist %srechtwinklig\n", a, b, c, str);

        printf("\n\n");
    }
    printf("\n\nbye bye\n\n");
    return EXIT_SUCCESS;
}

int parse_triangle_edge(char *message) {
    int edge;

    do {
        printf("%s", message);
        edge = getInt(MAX_NUMBER);
    } while (edge < 0 && edge != READ_ERROR);

    return edge;
}