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
#include "list.h"

#define INPUT_BUFFER_SIZE 1024
#define NAME_LEN 20

// Prompts the user to input a person
int input_person(person_t *person) {
    char name_buffer[INPUT_BUFFER_SIZE];
    char first_name_buffer[INPUT_BUFFER_SIZE];
    unsigned int age;

    printf("Enter name: ");
    scanf("%1023s", name_buffer);
    if (strlen(name_buffer) >= NAME_LEN) {
        printf("Name too long, It should be less than %d characters.\n", NAME_LEN);
        return -1;
    }
    strcpy(person->name, name_buffer);

    printf("Enter first name: ");
    scanf("%1023s", first_name_buffer);
    if (strlen(first_name_buffer) >= NAME_LEN) {
        printf("First name too long. It should be less than %d characters.\n", NAME_LEN);
        return -1;
    }
    strcpy(person->first_name, first_name_buffer);

    printf("Enter age: ");
    if (scanf("%u", &age) != 1) {
        printf("Invalid input for age. Please enter a valid number.\n");
        while (getchar() != '\n');
        return -1;
    }
    person->age = age;

    while (getchar() != '\n');

    return 0;
}

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char *argv[]) {
    char choice;
    node_t *list = list_init();
    person_t temp_person;

    if (list == NULL) {
        fprintf(stderr, "Failed to initialize the list.\n");
        return EXIT_FAILURE;
    }

    do {
        printf("I(insert), R(emove), S(how), C(lear), E(nd): ");
        choice = getchar();
        while (getchar() != '\n');

        switch (choice) {
            case 'I':
                if (input_person(&temp_person) == 0) {
                    if (!list_contains(list, temp_person)) {
                        list_insert(list, temp_person);
                        printf("Person successfully inserted.\n");
                    } else {
                        printf("Person already exists in the list. Operation canceled.\n");
                    }
                } else {
                    printf("Invalid input. Operation canceled.\n");
                }
                break;
            case 'R':
                if (input_person(&temp_person) == 0) {
                    if (list_contains(list, temp_person)) {
                        list_remove(list, temp_person);
                        printf("Person successfully removed.\n");
                    } else {
                        printf("Person is not in the list. Operation canceled.\n");
                    }
                } else {
                    printf("Invalid input. Operation canceled.\n");
                }
                break;
            case 'S':
                list_show(list);
                break;
            case 'C':
                list_clear(&list);
                printf("List successfully cleared.\n");
                break;
            case 'E':
                printf("Ending program...\n");
                list_clear(&list);
                free(list);
                list = NULL;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 'E');

    return EXIT_SUCCESS;
}