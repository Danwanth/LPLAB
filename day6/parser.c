#include <stdio.h>
#include <string.h>

#define MAX 50

char stack[MAX], input[MAX];
char prod[MAX][MAX];
int top = -1, n;
int ip = 0;   //global input pointer

/* Function reductions */
void check_reduce() {
    int i, len;
    char temp[MAX];

    for (i = 0; i < n; i++) {
        len = strlen(prod[i]) - 3;   // length of RHS

        if (len <= top + 1) {
            strncpy(temp, stack + top - len + 1, len);
            temp[len] = '\0';

            if (strcmp(temp, prod[i] + 3) == 0) {
                top -= len;
                stack[++top] = prod[i][0];
                stack[top + 1] = '\0';

                printf("%-15s %-15s REDUCE (%s)\n",
                       stack, input + ip, prod[i]);
            }
        }
    }
}

int main() {
    int i;
    char symbol;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (A->xyz):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("Enter input string: ");
    scanf("%s", input);
    strcat(input, "$");

    printf("\n%-15s %-15s ACTION\n", "STACK", "INPUT");
    printf("-----------------------------------------\n");

    while (1) {
        if (input[ip] != '$') {
            symbol = input[ip++];
            stack[++top] = symbol;
            stack[top + 1] = '\0';

            printf("%-15s %-15s SHIFT\n", stack, input + ip);
            check_reduce();
        } else {
            check_reduce();

            if (top == 0 && stack[top] == prod[0][0]) {
                printf("%-15s %-15s ACCEPT\n", stack, "$");
                break;
            } else {
                printf("ERROR\n");
                break;
            }
        }
    }

    return 0;
}
