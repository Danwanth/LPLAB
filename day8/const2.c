#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int main() {

    char line[MAX];

    printf("Enter statements (type 'exit' to stop):\n");

    while (1) {

        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0)
            break;

        char lhs[20], op1[20], op2[20], operator;

        // Try binary expression
        if (sscanf(line, "%[^=]=%[^+*/-]%c%s", lhs, op1, &operator, op2) == 4) {

            sscanf(lhs, "%s", lhs);
            sscanf(op1, "%s", op1);
            sscanf(op2, "%s", op2);

            if (isNumber(op1) && isNumber(op2)) {

                int val1 = atoi(op1);
                int val2 = atoi(op2);
                int result;

                switch (operator) {
                    case '+': result = val1 + val2; break;
                    case '-': result = val1 - val2; break;
                    case '*': result = val1 * val2; break;
                    case '/': result = val1 / val2; break;
                }

                printf("%s = %d\n", lhs, result);
            }
            else {
                printf("%s = %s %c %s\n", lhs, op1, operator, op2);
            }
        }

        // Simple assignment
        else if (sscanf(line, "%[^=]=%s", lhs, op1) == 2) {

            sscanf(lhs, "%s", lhs);
            sscanf(op1, "%s", op1);

            printf("%s = %s\n", lhs, op1);
        }
    }

    return 0;
}

