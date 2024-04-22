#ifndef PERSON_H
#define PERSON_H

// Maximum length for names
#define NAME_LEN 20

// Structure to store personal information.
typedef struct {
    char name[NAME_LEN]; // Last name of this person
    char first_name[NAME_LEN]; // First name of this person
    unsigned int age; // Age of this person
} person_t;

// Compares two person objects based on last name, first name, and age.
// Returns >0 if a > b, 0 if a == b, and <0 if a < b.
int person_compare(const person_t *a, const person_t *b);

#endif //PERSON_H