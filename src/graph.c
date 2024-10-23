#include "drawing.h"

int main() {
    char expression[200];
    greeting_message();
    scanf("%s", expression);

    int error = 0;

    int lexeme_count;
    lexeme* lexemes = parse_lexeme(expression, &lexeme_count, &error);

    if (error == 0) {
        int postfix_size = 0;
        lexeme* postfix = to_postfix(lexemes, lexeme_count, &postfix_size);

        render_graph(postfix, postfix_size);

        free(postfix);
    } else
        printf("error: invalid expression\n");

    free(lexemes);
    return 0;
}
