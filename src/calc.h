#ifndef CALC_H
#define CALC_H

#include <math.h>

#include "stack.h"

int is_lexeme_unary(lexeme current_lexeme);
int is_lexeme_function(lexeme current_lexeme);
int is_priority_higher(lexeme lexeme1, lexeme lexeme2);

lexeme* to_postfix(lexeme* lexemes, int lexemes_amount, int* postfix_size);

double unary_calculation(lexeme operation, lexeme number);
double binary_calculation(lexeme operation, lexeme number1, lexeme number2);
double calculate(double x, lexeme* lexemes, int lexemes_amount);

#endif