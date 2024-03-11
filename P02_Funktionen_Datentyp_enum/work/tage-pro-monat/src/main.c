/**
 *  P02 Praktikum
 *
 *  Das Programm liest einen Monat (1-12) und ein Jahr (1600-2400) ein und
 *  gibt die Anzahl der Tage dieses Monats aus.
 *
 *  @author Gerrit Burkert, Adaptation bazz
 *  @version 15-FEB-2013, 16-OCT-2017, 17-OCT-2019, 16-FEB-2022
 */
#include <stdio.h>
#include <stdlib.h>

#define ERROR_IN_MONTH 1
#define ERROR_IN_YEAR 2

typedef enum {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
} Monat;

/* Funktionsdeklarationen */
int gibIntWert(char const *string, int day, int month);

int istSchaltjahr(int year);

int tageProMonat(int year, int month);

int main(int argc, char *argv[]) {

    int monat, jahr;

    //  Monat einlesen und Bereich überprüfen
    monat = gibIntWert("Monat", 1, 12);
    jahr = gibIntWert("Jahr", 1600, 9999);

    //  Ausgabe zum Test
    printf("Monat: %d, Jahr: %d \n", monat, jahr);

    //  Ausgabe zum Test (hier mit dem ternären Operator "?:")
    printf("%d ist %s Schaltjahr\n", jahr, istSchaltjahr(jahr) ? "ein" : "kein");

    // Ausgabe
    printf("Der Monat %02d-%d hat %d Tage.\n", monat, jahr, tageProMonat(jahr, monat));

    return 0;
}

int gibIntWert(char const *string, int day, int month) {

    return -1;
}

int istSchaltjahr(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0;
}

int tageProMonat(int year, int month) {
    switch (month) {
        case JAN:
        case MAR:
        case MAY:
        case JUL:
        case AUG:
        case OCT:
        case DEC:
            return 31;
        case APR:
        case JUN:
        case SEP:
        case NOV:
            return 30;
        case FEB:
            return istSchaltjahr(year) ? 29 : 28;
        default:
            return 0;
    }
}