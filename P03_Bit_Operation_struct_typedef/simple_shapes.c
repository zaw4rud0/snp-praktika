#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/* 
Students: Create a new type "Graphic" that can store:
- shape (OVAL, RECTANGLE) -> create a new enum for this type
- size
- color
*/
typedef enum {
    OVAL,
    RECTANGLE
} Shape;

typedef struct {
    Shape shape;
    unsigned int size;
    char *color;
} Graphic;

void paint(Graphic graphic) {
    double radius = graphic.size / 2.0;
    int i, j;

    for (i = 0; i <= 2 * radius; i++) {
        for (j = 0; j <= 2 * radius; j++) {
            switch (graphic.shape) {
                case RECTANGLE:
                    printf("%s*" RESET, graphic.color);
                    break;
                case OVAL: {
                    double distance = sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius));
                    if (distance > radius - 0.5 && distance < radius + 0.5) {
                        printf("%s*" RESET, graphic.color);
                    } else {
                        printf(" ");
                    }
                    break;
                }
            }
        }
        printf("\n");
    }
}

int main() {
    Graphic graphic;
    int inputShape, inputColor, inputSize;
    char *colors[] = {RED, GRN, YEL};

    do {
        printf("Geben Sie die gewünschte Form an [OVAL=0 | RECTANGLE=1]:");
        scanf("%d", &inputShape);
        // Students: store the input in graphic
        if (inputShape > 1 || inputShape < 0) {
            printf("Ungültige Form!");
            continue;
        }
        graphic.shape = (Shape) inputShape;

        printf("Geben Sie die gewünschte Grösse an:");
        scanf("%u", &inputSize);
        // Students: store the input in graphic
        if (inputSize < 0) {
            printf("Ungültige Grösse!");
            continue;
        }
        graphic.size = inputSize - 1;

        printf("Geben Sie die gewünschte Farbe an [RED=0 | GREEN=1 | YELLOW=2]:");
        scanf("%d", &inputColor);
        // Students: store the input in graphic
        if (inputColor > 2 || inputColor < 0) {
            printf("Ungültige Farbe!");
            continue;
        }
        graphic.color = colors[inputColor];

        paint(graphic);

        while (getchar() != '\n'); // empty buffer
        printf("\nMöchten Sie weiter machen oder abbrechen? [(n)ext|(q)uit] ");
    } while (getchar() != 'q');

    printf("Byebye..\n");
    return EXIT_SUCCESS;
}