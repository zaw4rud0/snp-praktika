#include <stdio.h>
#include <stdbool.h>

int main() {
	int charCount = 0;
	int wordCount = 0;
	char c; // Current character
	bool inWord = false; // To keep track if we are going through a word

	printf("Enter a line: ");

	// Keep looping until new line is reached
	while ((c = getchar()) != '\n') {
		charCount++;

		// Check if word ended and switch
		if (c == ' ' || c == '\t') {
			if (inWord) {
				inWord = false;
				wordCount++;
			}
		} 
		
		// Still part of a word
		else {
			inWord = true;
		}
	}

	// Check if last character is part of a word
	if (inWord) {
		wordCount++;
	}

	// Format using %d as placeholder for integers
	printf("Anzahl Zeichen: %d\n", charCount);
	printf("Anzahl Wörter: %d\n", wordCount);

	return 0;
}
