#include <stdio.h>
#include <string.h>

#define MAX 50

char stack[MAX], input[MAX];
char prod[MAX][MAX];
int top = -1, n;
int ip = 0;   //global input pointer

/* Function reductions */
/*void check_reduce() {
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
}*/

void check_reduce() {

    int i, len;
    char temp[MAX];

    // Loop through all productions entered by the user
    for (i = 0; i < n; i++) {

        // Calculate the length of RHS (Right Hand Side)
        // Example production: E->E+E
        // strlen = 6
        // We subtract 3 to skip "E->"
        // So RHS length = 3 (E+E)
        len = strlen(prod[i]) - 3;

        // Check if stack contains at least 'len' symbols
        // Reduction can only happen if stack has enough symbols
        if (len <= top + 1) {

            // Copy the top 'len' characters from stack
            // This extracts the substring from stack
            // that may match the RHS of a production
            strncpy(temp, stack + top - len + 1, len);

            // Add null character to make it a proper string
            temp[len] = '\0';

            // Compare extracted stack substring
            // with RHS of the production (prod[i] + 3)
            if (strcmp(temp, prod[i] + 3) == 0) {

                // If match found, perform reduction

                // Remove RHS symbols from stack
                top -= len;

                // Push LHS (Left Hand Side) of production onto stack
                // Example: E->E+E → push 'E'
                stack[++top] = prod[i][0];

                // Add string terminator
                stack[top + 1] = '\0';

                // Print reduction step
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
