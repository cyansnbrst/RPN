#include "calc.h"

lexeme* to_postfix(lexeme* lexemes, int lexemes_amount, int* postfix_size) {
    stack* operators_stack = init();
    lexeme* output = malloc(lexemes_amount * sizeof(lexeme));

    for (int i = 0; i < lexemes_amount; i++) {
        lexeme current = lexemes[i];

        if (current.type == NUMBER || current.type == VARIABLE) {
            output[(*postfix_size)++] = current;
        } else if (current.symbol == ')') {
            while (operators_stack->top->data.symbol != '(') {
                lexeme temp = pop(operators_stack);
                if (temp.symbol != '(' && temp.symbol != ')') output[(*postfix_size)++] = temp;
            }
            pop(operators_stack);
            if (operators_stack->size > 0 && is_lexeme_function(operators_stack->top->data)) {
                output[(*postfix_size)++] = pop(operators_stack);
            }
        } else if (is_lexeme_unary(current) || operators_stack->size == 0 || current.symbol == '(') {
            push(operators_stack, current);
        } else {
            while (operators_stack->size > 0 && (is_lexeme_unary(operators_stack->top->data) == 0 &&
                                                 is_priority_higher(operators_stack->top->data, current))) {
                lexeme temp = pop(operators_stack);
                if (temp.symbol != '(' && temp.symbol != ')') output[(*postfix_size)++] = temp;
            }
            push(operators_stack, current);
        }
    }

    while (operators_stack->size > 0) {
        lexeme temp = pop(operators_stack);
        if (temp.symbol != '(' && temp.symbol != ')') output[(*postfix_size)++] = temp;
    }

    destroy_stack(operators_stack);
    return output;
}

double calculate(double x, lexeme* lexemes, int lexemes_amount) {
    stack* calculator_stack = init();
    double result = 0.0;
    int i = 0;
    while (i < lexemes_amount) {
        lexeme current = lexemes[i];
        if (current.type == VARIABLE) {
            current.number = x;
            push(calculator_stack, current);
        } else if (current.type == NUMBER) {
            push(calculator_stack, current);
        } else if (is_lexeme_unary(current)) {
            lexeme temp = pop(calculator_stack);
            temp.number = unary_calculation(current, temp);
            push(calculator_stack, temp);
        } else {
            lexeme temp2 = pop(calculator_stack);
            lexeme temp1 = pop(calculator_stack);
            temp2.number = binary_calculation(current, temp1, temp2);
            push(calculator_stack, temp2);
        }
        i++;
    }

    result = pop(calculator_stack).number;

    destroy_stack(calculator_stack);
    return result;
}

double unary_calculation(lexeme operation, lexeme number) {
    double result = 0.0;

    if (operation.symbol == 'i')
        result = sin(number.number);
    else if (operation.symbol == 'o')
        result = cos(number.number);
    else if (operation.symbol == 'a')
        result = tan(number.number);
    else if (operation.symbol == 't')
        result = 1.0 / tan(number.number);
    else if (operation.symbol == 'q')
        result = sqrt(number.number);
    else if (operation.symbol == 'n')
        result = log(number.number);
    else if (operation.symbol == 'u')
        result = -1.0 * number.number;

    return result;
}

double binary_calculation(lexeme operation, lexeme number1, lexeme number2) {
    double result = 0.0;

    if (operation.symbol == '+')
        result = number1.number + number2.number;
    else if (operation.symbol == '-')
        result = number1.number - number2.number;
    else if (operation.symbol == '/')
        result = number1.number / number2.number;
    else if (operation.symbol == '*')
        result = number1.number * number2.number;

    return result;
}

int is_lexeme_unary(lexeme current_lexeme) { return strchr("+-*/", current_lexeme.symbol) == NULL ? 1 : 0; }

int is_lexeme_function(lexeme current_lexeme) {
    return is_lexeme_unary(current_lexeme) && current_lexeme.symbol != 'u';
}

int is_priority_higher(lexeme lexeme1, lexeme lexeme2) { return lexeme1.priority >= lexeme2.priority; }
