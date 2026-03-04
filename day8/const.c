#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && !(i == 0 && str[i] == '-'))
            return 0;
    }
    return 1;
}

void constantFold(char *expr) {
    char lhs[MAX], rhs[MAX];
    char *token;
    int result = 0;
    char operator = '+';
    char variables[MAX] = "";

    // Split LHS and RHS
    if (sscanf(expr, "%[^=]=%[^\n]", lhs, rhs) != 2) {
        printf("Invalid assignment format\n");
        return;
    }

    // Trim spaces from LHS
    char *p = lhs;
    while (isspace(*p)) p++;

    token = strtok(rhs, " \n");

    while (token != NULL) {

        if (isNumber(token)) {
            int num = atoi(token);

            switch (operator) {
                case '+': result += num; break;
                case '-': result -= num; break;
                case '*': result *= num; break;
                case '/':
                    if (num == 0) {
                        printf("Error: Division by zero\n");
                        return;
                    }
                    result /= num;
                    break;
            }
        }
        else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            operator = token[0];
        }
        else {
            strcat(variables, token);
            strcat(variables, " ");
        }

        token = strtok(NULL, " \n");
    }

    printf("After Constant Folding:\n");

    printf("%s = ", p);

    if (result != 0)
        printf("%d ", result);

    if (strlen(variables) > 0)
        printf("+ %s", variables);

    printf("\n");
}

int main() {
    char expression[MAX];

    printf("Enter assignment (e.g., t1 = 5 + 3 + x): ");
    fgets(expression, sizeof(expression), stdin);

    constantFold(expression);

    return 0;
}

