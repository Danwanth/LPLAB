#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;

char input[50];
int ip = 0;   // input pointer

// Push symbol onto stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Pop n symbols from stack
void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

// Try to reduce the stack
int reduce() {
    // E -> id
    if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
        pop(2);
        push('E');
        printf("REDUCE: E -> id\n");
        return 1;
    }

    // E -> E+E
    if (top >= 2 && stack[top] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top - 2] == 'E') {
        pop(3);
        push('E');
        printf("REDUCE: E -> E+E\n");
        return 1;
    }

    // E -> E*E
    if (top >= 2 && stack[top] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top - 2] == 'E') {
        pop(3);
        push('E');
        printf("REDUCE: E -> E*E\n");
        return 1;
    }

    // E -> (E)
    if (top >= 2 && stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(') {
        pop(3);
        push('E');
        printf("REDUCE: E -> (E)\n");
        return 1;
    }

    return 0; // no reduction possible
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");
    printf("--------------------------------\n");

    while (1) {
        // SHIFT
        if (input[ip] != '\0') {
            push(input[ip]);
            printf("%s\t%s\tSHIFT\n", stack, input + ip + 1);
            ip++;
        }

        // Try reducing as much as possible
        while (reduce()) {
            printf("%s\t%s\tREDUCE\n", stack, input + ip);
        }

        // Acceptance condition
        if (input[ip] == '\0' && strcmp(stack, "E") == 0) {
            printf("\nString ACCEPTED\n");
            break;
        }

        // Error condition
        if (input[ip] == '\0' && !reduce()) {
            printf("\nString REJECTED\n");
            break;
        }
    }

    return 0;
}

