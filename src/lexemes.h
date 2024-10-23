#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNCTIONS "sin", "cos", "tan", "ctg", "sqrt", "ln"
#define FUNCTIONS_COUNT 6

#define BALANCE_ERROR "invalid amount of parentheses or operands"

#define NUMBER 0
#define VARIABLE 1
#define OPERATOR 2

typedef struct lexeme {
    int type;
    union {
        char symbol;
        double number;
    };
    int priority;
} lexeme;

int is_digit(char ch);
int is_variable(char ch);
int is_parentheses(char ch);
int is_operator(char ch);

const char* is_function(const char* str);
lexeme* add_lexeme(lexeme* lexemes, int* size, int* capacity, lexeme new_lexeme);
lexeme read_number(const char** expression_ptr);
lexeme read_variable(const char** expression_ptr);
lexeme read_operator(const char** expression_ptr);
lexeme read_parenthesis(const char** expression_ptr);
lexeme read_unary(const char** expression_ptr);
lexeme read_function(const char** expression_ptr, const char* function_name, int* error);

lexeme* parse_lexeme(const char* expression, int* lexemes_amount, int* error);
