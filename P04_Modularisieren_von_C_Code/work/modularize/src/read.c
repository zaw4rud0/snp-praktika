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
#include "read.h"
#include <stdio.h>

int getInt(int maxResult) {
    int EOF = -1;
    int EOL = '\n';
    int PARSE_ERROR = -1;
    int READ_ERROR = -2;
    int ASCII_SPACE = 32;
    int ASCII_DIGIT_0 = '0';
    int ASCII_DIGIT_9 = '9';

    int BUFFERSIZE = 10;
    char buffer[BUFFERSIZE];
    int result = 0;
    int bytes = 0;
    int input = getchar();

    while ((input != EOL) && (input != EOF)) {
        if (bytes < BUFFERSIZE) {
            buffer[bytes++] = (char)input;
        } else {
            result = PARSE_ERROR;
            break;
        }
        input = getchar();
    }
    if (input == EOF && bytes == 0) {
        return READ_ERROR;
    }
    if (result != PARSE_ERROR) {
        int i = 0;
        while (i < bytes && buffer[i] <= ASCII_SPACE) i++;
        int posOfFirstDigit = i;
        int posOfLastDigit = -1;
        while (i < bytes && buffer[i] >= ASCII_DIGIT_0 && buffer[i] <= ASCII_DIGIT_9) {
            posOfLastDigit = i++;
        }
        while (i < bytes && buffer[i] <= ASCII_SPACE) i++;
        if (i == bytes && posOfLastDigit != -1) {
            result = 0;
            for (int j = posOfFirstDigit; j <= posOfLastDigit; j++) {
                result = result * 10 + (buffer[j] - ASCII_DIGIT_0);
                if (result > maxResult) {
                    return PARSE_ERROR;
                }
            }
        } else {
            return PARSE_ERROR;
        }
    }
    return result;
}
// end students to add code
