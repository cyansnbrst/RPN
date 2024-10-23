#include "drawing.h"

void render_graph(lexeme *lexemes, int lexemes_amount) {
    char grid[HEIGHT][WIDTH];

    double x, y;
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            grid[i][j] = '.';
        }
    }

    for (j = 0; j < WIDTH; j++) {
        x = 4 * M_PI * j / (WIDTH - 1);
        y = calculate(x, lexemes, lexemes_amount);

        if (y >= -1.0 && y <= 1.0 && !isnan(y) && !isinf(y)) {
            int row = (int)(round((1 + y) * (HEIGHT - 1) / 2));

            if (row >= 0 && row < HEIGHT) {
                grid[row][j] = '*';
            }
        }
    }

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

void greeting_message(void) {
    printf("Enter your expression.\n");
    printf("Possible operations & functions:\n");
    printf("'+'\n'-'(unary and binary)\n'*'\n'/'\n'()'\nsin(x)\ncos(x)\ntan(x)\nctg(x)\nsqrt(x)\nln(x)\n");
    printf(">>");
}