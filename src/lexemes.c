#include "lexemes.h"

lexeme* parse_lexeme(const char* expression, int* lexemes_amount, int* error) {
    int parentheses = 0, next_lexeme_is_not_operator = 1;
    int capacity = 20, size = 0;
    lexeme* lexemes = malloc(capacity * sizeof(lexeme));

    const char* current_char = expression;
    while (*current_char != '\0' && *error == 0) {
        lexeme new_lexeme = {};
        const char* func_name = is_function(current_char);
        if ((func_name != NULL || *current_char == '-') && next_lexeme_is_not_operator == 1) {
            if (func_name != NULL)
                new_lexeme = read_function(&current_char, func_name, error);
            else
                new_lexeme = read_unary(&current_char);
        } else if (is_digit(*current_char)) {
            new_lexeme = read_number(&current_char);
            next_lexeme_is_not_operator--;
        } else if (is_variable(*current_char)) {
            new_lexeme = read_variable(&current_char);
            next_lexeme_is_not_operator--;
        } else if (is_parentheses(*current_char)) {
            new_lexeme = read_parenthesis(&current_char);
            parentheses += (new_lexeme.symbol == '(') ? 1 : -1;
        } else if (is_operator(*current_char)) {
            new_lexeme = read_operator(&current_char);
            next_lexeme_is_not_operator++;
        } else
            *error = 1;

        if (parentheses < 0 || (next_lexeme_is_not_operator != 0 && next_lexeme_is_not_operator != 1))
            *error = 1;

        if (*error == 0) lexemes = add_lexeme(lexemes, &size, &capacity, new_lexeme);
    }

    if (parentheses != 0 || next_lexeme_is_not_operator != 0) *error = 1;

    *lexemes_amount = size;
    return lexemes;
}

int is_digit(char ch) { return ch >= '0' && ch <= '9'; }

int is_variable(char ch) { return ch == 'x'; }

int is_parentheses(char ch) { return ch == '(' || ch == ')'; }

int is_operator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }

const char* is_function(const char* str) {
    const char* result = NULL;
    const char* functions[FUNCTIONS_COUNT] = {FUNCTIONS};

    for (int i = 0; i < FUNCTIONS_COUNT; i++) {
        int len = strlen(functions[i]);
        if (strncmp(str, functions[i], len) == 0) {
            result = functions[i];
        }
    }

    return result;
}

lexeme* add_lexeme(lexeme* lexemes, int* size, int* capacity, lexeme new_lexeme) {
    if (*size >= *capacity) {
        *capacity *= 2;
        lexemes = realloc(lexemes, *capacity * sizeof(lexeme));
    }

    lexemes[(*size)++] = new_lexeme;
    return lexemes;
}

lexeme read_number(const char** expression_ptr) {
    lexeme result = {.type = NUMBER, .priority = 0};
    result.number = strtod(*expression_ptr, (char**)expression_ptr);
    return result;
}

lexeme read_variable(const char** expression_ptr) {
    lexeme result = {.type = VARIABLE, .priority = 0, .symbol = 'x'};

    (*expression_ptr)++;
    return result;
}

lexeme read_operator(const char** expression_ptr) {
    lexeme result;
    result.type = OPERATOR;
    result.symbol = **expression_ptr;

    if (**expression_ptr == '+' || **expression_ptr == '-') {
        result.priority = 1;
    } else if (**expression_ptr == '*' || **expression_ptr == '/') {
        result.priority = 2;
    }

    (*expression_ptr)++;
    return result;
}

lexeme read_parenthesis(const char** expression_ptr) {
    lexeme result = {.type = OPERATOR, .symbol = **expression_ptr, .priority = 0};

    (*expression_ptr)++;
    return result;
}

lexeme read_unary(const char** expression_ptr) {
    lexeme result = {.type = OPERATOR, .symbol = 'u', .priority = 0};

    (*expression_ptr)++;
    return result;
}

lexeme read_function(const char** expression_ptr, const char* function_name, int* error) {
    lexeme result = {.type = OPERATOR, .symbol = function_name[1], .priority = 0};

    *expression_ptr += strlen(function_name);
    if (**expression_ptr != '(') *error = 1;

    return result;
}