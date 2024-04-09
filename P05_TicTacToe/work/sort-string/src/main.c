#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_LENGTH 20

void toUpperCase(char *word);

int isDuplicate(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount, const char *word);

void readAndProcessWords(char words[MAX_WORDS][MAX_LENGTH + 1], int *wordCount);

void sortWords(char words[MAX_WORDS][MAX_LENGTH + 1], int wordCount);

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
        scanf("%20s", word); // %20s to only read 20 characters
        toUpperCase(word);

        // Stop reading
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
    // Bubble Sort
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                // Swap elements
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