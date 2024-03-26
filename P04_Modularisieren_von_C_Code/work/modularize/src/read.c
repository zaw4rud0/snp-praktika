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
// begin students to add code for task 4.1
#include <stdio.h>
#include "read.h"

#define ASCII_SPACE 32
#define ASCII_DIGIT_0 48
#define ASCII_DIGIT_9 57
#define BUFFERSIZE 10
#define EOL 10
#define NO_POS (-1)

/** @file @brief Lab implementation */
// begin students to add code for task 4.1

void skipSpaces(int pos, int bytes, const char buffer[]) {
}

int getInt(int maxResult) {
    int buffer[BUFFERSIZE];

    int result = 0;

    int bytes = 0;
    int input = getchar();
    while ((input != EOL) && (input != EOF)) {
        if (bytes < BUFFERSIZE) {
            buffer[bytes] = (unsigned char) input;
            bytes++;
        } else {
            result = PARSE_ERROR;
        }
        input = getchar();
    }
    if (input == EOF) {
        return READ_ERROR;
    }

    //check for numbers: skip leading and trailing spaces
    //(i.e this includes all control chars below the space ASCII code)
    int pos = 0;
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++;
    int posOfFirstDigit = pos;
    int posOfLastDigit = NO_POS;
    while ((pos < bytes) && (buffer[pos] >= ASCII_DIGIT_0) && (buffer[pos] <= ASCII_DIGIT_9)) {
        posOfLastDigit = pos;
        pos++;
    }
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++;

    // produce return value
    if ((pos != bytes) || (posOfLastDigit == NO_POS)) {
        return PARSE_ERROR;
    } else { // convert number
        for(int i = posOfFirstDigit; i <= posOfLastDigit; i++) {
            result = result * 10 + (buffer[i] - ASCII_DIGIT_0);
            if (result > maxResult) {
                return PARSE_ERROR;
            }
        }
    }
    return result;
}
// end students to add code
