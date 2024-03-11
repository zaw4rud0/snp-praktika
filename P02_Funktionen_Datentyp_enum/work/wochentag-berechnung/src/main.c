/* ----------------------------------------------------------------------------
* --  _____       ______  _____                                              -
* -- |_   _|     |  ____|/ ____|                                             -
* --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
* --   | | | '_ \|  __|  \___ \   Zürcher Hochschule Winterthur             -
* --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
* -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
* ----------------------------------------------------------------------------
*/
/**
 * @file
 * @brief Lab P02 weekday
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// *** TASK1: typedef enum types for month_t (Jan=1,...Dec} ***
typedef enum month_t {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
} month_t;

// *** TASK1: typedef struct for date_t ***
typedef struct date_t {
    int day;
    int month;
    int year;
} date_t;

// *** TASK2: typedef enum weekday_t (Sun=0, Mon, ...Sat) ***
typedef enum weekday_t {
    Sun = 0,
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat
} weekday_t;

/**
 * @brief   TASK1: Checks if the given date is a leap year.
 * @returns 0 = is not leap year, 1 = is leap year
 */
int is_leap_year(date_t date);

/**
 * @brief   TASK1: Calculates the length of the month given by the data parameter
 * @returns 28, 29, 30, 31 if a valid month, else 0
 */
int get_month_length(date_t date);

/**
 * @brief   TASK1: Checks if the given date is in the gregorian date range
 * @returns 0 = no, 1 = yes
 */
int is_gregorian_date(date_t date);

/**
 * @brief   TASK1: Checks if the given date is a valid date.
 * @returns 0 = is not valid date, 1 = is valid date
 */
int is_date_valid(date_t date);

/**
 * @brief   TASK2: calculated from a valid date the weekday
 * @returns returns a weekday in the range Sun...Sat
 */
weekday_t calculate_weekday(date_t date);

/**
 * @brief   TASK2: print weekday as 3-letter abbreviated English day name
 */
void print_weekday(weekday_t day);

/**
 * @brief   main function
 * @param   argc [in] number of entries in argv
 * @param   argv [in] program name plus command line arguments
 * @returns returns success if valid date is given, failure otherwise
 */
int main(int argc, const char *argv[]) {
    // TASK1: parse the mandatory argument into a date_t variable and check if the date is valid
    if (argc != 2) {
        printf("Usage: %s <yyyy-mm-dd>\n", argv[0]);
        return EXIT_FAILURE;
    }

    date_t date;
    sscanf(argv[1], "%04d-%02d-%02d", &date.year, &date.month, &date.day);

    if (sizeof(date) != 12 || !is_date_valid(date)) {
        printf("Error: invalid date format\n");
        return EXIT_FAILURE;
    }

    // TASK2: calculate the weekday and print it in this format: "%04d-%02d-%02d is a %s\n"
    weekday_t weekday = calculate_weekday(date);
    printf("%04d-%02d-%02d is a ", date.year, date.month, date.day);
    print_weekday(weekday);
    return EXIT_SUCCESS;
}

int is_leap_year(date_t date) {
    if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int get_month_length(date_t date) {
    switch (date.month) {
        case Jan:
        case Mar:
        case May:
        case Jul:
        case Aug:
        case Oct:
        case Dec:
            return 31;
        case Feb:
            return is_leap_year(date) ? 29 : 28;
        case Apr:
        case Jun:
        case Sep:
        case Nov:
            return 30;
        default:
            return 0;
    }
}

/* implementation of is_gregorian_date */
int is_gregorian_date(date_t date) {
    if (date.year < 1582 || date.year > 9999) {
        return 0;
    } else if ((date.year == 1852 && date.month < 11) || (date.year == 1582 && date.month == 10 && date.day < 15)) {
        return 0;
    } else {
        return 1;
    }
}

int is_date_valid(date_t date) {
    int current_month = get_month_length(date);
    if ((!is_gregorian_date(date)) || (date.month < 1 || date.month > 12)) {
        return 0;
    } else if (date.day < 1 || date.day > current_month) {
        return 0;
    } else {
        return 1;
    }
}

weekday_t calculate_weekday(date_t date) {
    int a, y, m, c;
    int weekday;
    assert(is_date_valid(date));
    m = 1 + (date.month + 9) % 12;
    a = (date.month < 3) ? (date.year - 1) : date.year;
    y = a % 100;
    c = a / 100;
    weekday = ((date.day + (13 * m - 1) / 5 + y + y / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    switch (weekday) {
        case 0:
            return Sun;
        case 1:
            return Mon;
        case 2:
            return Tue;
        case 3:
            return Wed;
        case 4:
            return Thu;
        case 5:
            return Fri;
        case 6:
            return Sat;
        default:
            return -1;
    }
}

void print_weekday(weekday_t day) {
    switch (day) {
        case Sun:
            printf("Sun\n");
            break;
        case Mon:
            printf("Mon\n");
            break;
        case Tue:
            printf("Tue\n");
            break;
        case Wed:
            printf("Wed\n");
            break;
        case Thu:
            printf("Thu\n");
            break;
        case Fri:
            printf("Fri\n");
            break;
        case Sat:
            printf("Sat\n");
            break;
        default:
            assert(!"day is out-of-range");
    }
}