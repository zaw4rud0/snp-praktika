/**
 * Task 2: Sorting Strings
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_LENGTH 20

/**
 * Converts a string to uppercase.
 * @param word A pointer to the string.
 */
void toUpperCase(char *word);

/**
 * Checks if a word is a duplicate in the provided list.
 * @param words The list of words to check against.
 * @param wordCount The number of words in the list.
 * @param word The word to check.
 * @return 1 if duplicate, 0 otherwise.
 */
int isDuplicate(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount, const char *word);

/**
 * Reads up to MAX_WORDS words from stdin, converts them to uppercase,
 * and stores unique words in the provided array.
 * @param words The array to store the words.
 * @param wordCount A pointer to an int that will contain the number of words read.
 */
void readAndProcessWords(char words[MAX_WORDS][MAX_LENGTH + 1], int *wordCount);

/**
 * Sorts the words in the provided array in ascending alphabetical order using Bubble Sort.
 * @param words The array of words to sort.
 * @param wordCount The number of words in the array.
 */
void sortWords(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount);

/**
 * Prints the sorted words to stdout.
 * @param words The array of sorted words to print.
 * @param wordCount The number of words in the array.
 */
void printWords(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount);

int main() {
    char words[MAX_WORDS][MAX_LENGTH + 1];
    int wordCount = 0;

    readAndProcessWords(words, &wordCount);
    sortWords(words, wordCount);
    printWords(words, wordCount);

    return 0;
}

void toUpperCase(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = (char) toupper((unsigned char) word[i]);
    }
}

int isDuplicate(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount, const char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void readAndProcessWords(char words[MAX_WORDS][MAX_LENGTH + 1], int *wordCount) {
    printf("Enter up to 10 words (or ZZZ to stop):\n");
    while (*wordCount < MAX_WORDS) {
        char word[MAX_LENGTH + 1];
        scanf("%20s", word);
        toUpperCase(word);

        if (strcmp(word, "ZZZ") == 0) {
            break;
        }

        if (!isDuplicate(words, *wordCount, word)) {
            strcpy(words[*wordCount], word);
            (*wordCount)++;
        }
    }
}

void sortWords(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount) {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char temp[MAX_LENGTH + 1];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}

void printWords(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount) {
    printf("Sorted words:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s\n", words[i]);
    }
}