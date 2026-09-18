#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long long *items;
    int count;
    int capacity;
} Stack;

static int stack_push(Stack *stack, unsigned long long value) {
    if (stack->count == stack->capacity) {
        int new_capacity = (stack->capacity == 0) ? 8 : stack->capacity * 2;
        unsigned long long *new_items = malloc((size_t)new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return 0;
        }
        for (int i = 0; i < stack->count; ++i) {
            new_items[i] = stack->items[i];
        }
        stack->items = new_items;
        stack->capacity = new_capacity;
    }

    stack->items[stack->count] = value;
    stack->count += 1;
    return 1;
}

static int stack_pop(Stack *stack, unsigned long long *value) {
    if (stack == NULL || value == NULL || stack->count == 0) {
        return 0;
    }

    stack->count -= 1;
    *value = stack->items[stack->count];
    return 1;
}

static int is_valid_binary_digit(char c) {
    return c == '0' || c == '1';
}

static int is_valid_decimal_digit(char c) {
    return c >= '0' && c <= '9';
}

static int hex_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static int parse_unsigned_number(const char *token, unsigned long long *result) {
    unsigned long long value = 0;
    int radix = 10;
    int index = 0;

    if (token == NULL || result == NULL) {
        return 0;
    }

    if (token[0] == '0' && (token[1] == 'b' || token[1] == 'B')) {
        radix = 2;
        index = 2;
    } else if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
        radix = 16;
        index = 2;
    }

    if (token[index] == '\0') {
        return 0;
    }

    while (token[index] != '\0') {
        int digit = 0;
        char c = token[index];

        if (radix == 2) {
            if (!is_valid_binary_digit(c)) {
                return 0;
            }
            digit = (c == '0') ? 0 : 1;
        } else if (radix == 10) {
            if (!is_valid_decimal_digit(c)) {
                return 0;
            }
            digit = c - '0';
        } else {
            digit = hex_value(c);
            if (digit < 0) {
                return 0;
            }
        }

        if (value > (ULLONG_MAX / (unsigned long long)radix) ||
            (value == (ULLONG_MAX / (unsigned long long)radix) &&
             (unsigned long long)digit > (ULLONG_MAX % (unsigned long long)radix))) {
            return 0;
        }

        value = (value * (unsigned long long)radix) + (unsigned long long)digit;
        index += 1;
    }

    *result = value;
    return 1;
}

static int apply_operator(const char *op, Stack *stack) {
    unsigned long long left = 0;
    unsigned long long right = 0;
    unsigned long long result = 0;

    if (strcmp(op, "+") == 0) {
        if (stack->count < 2) {
            return 0;
        }
        if (!stack_pop(stack, &right) || !stack_pop(stack, &left)) {
            return 0;
        }
        result = left + right;
        return stack_push(stack, result);
    }

    if (strcmp(op, "-") == 0) {
        if (stack->count == 0) {
            return 0;
        }
        if (stack->count == 1) {
            if (!stack_pop(stack, &left)) {
                return 0;
            }
            result = 0ULL - left;
            return stack_push(stack, result);
        }

        if (!stack_pop(stack, &right) || !stack_pop(stack, &left)) {
            return 0;
        }
        result = left - right;
        return stack_push(stack, result);
    }

    if (strcmp(op, "*") == 0) {
        if (stack->count < 2) {
            return 0;
        }
        if (!stack_pop(stack, &right) || !stack_pop(stack, &left)) {
            return 0;
        }
        result = left * right;
        return stack_push(stack, result);
    }

    if (strcmp(op, "/") == 0) {
        if (stack->count < 2) {
            return 0;
        }
        if (!stack_pop(stack, &right) || !stack_pop(stack, &left)) {
            return 0;
        }
        if (right == 0) {
            return 0;
        }
        result = left / right;
        return stack_push(stack, result);
    }

    if (strcmp(op, "%") == 0) {
        if (stack->count < 2) {
            return 0;
        }
        if (!stack_pop(stack, &right) || !stack_pop(stack, &left)) {
            return 0;
        }
        if (right == 0) {
            return 0;
        }
        result = left % right;
        return stack_push(stack, result);
    }

    return 0;
}

int main(int argc, char **argv) {
    Stack stack = {NULL, 0, 0};

    if (argc < 2) {
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        const char *token = argv[i];

        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "%") == 0) {
            if (!apply_operator(token, &stack)) {
                printf("Error\n");
                return 1;
            }
            continue;
        }

        unsigned long long value = 0;
        if (!parse_unsigned_number(token, &value) || !stack_push(&stack, value)) {
            printf("Error\n");
            return 1;
        }
    }

    if (stack.count != 1) {
        printf("Error\n");
        return 1;
    }

    printf("%llu\n", stack.items[0]);
    return 0;
}