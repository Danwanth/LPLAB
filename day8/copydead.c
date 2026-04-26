#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
#define VARS 50

char var[VARS][20];
char val[VARS][20];
int used[VARS];
int count = 0;

// check if number
int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i])) return 0;
    return 1;
}

// find variable index
int findVar(char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(var[i], name) == 0)
            return i;
    }
    return -1;
}

// store variable
void store(char *name, char *value) {
    int idx = findVar(name);
    if (idx == -1) {
        strcpy(var[count], name);
        strcpy(val[count], value);
        used[count] = 0;
        count++;
    } else {
        strcpy(val[idx], value);
        used[idx] = 0;
    }
}

// mark usage
void markUsed(char *name) {
    int idx = findVar(name);
    if (idx != -1)
        used[idx] = 1;
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

        // Binary expression
        if (sscanf(line, "%[^=]=%[^+*/-]%c%s", lhs, op1, &operator, op2) == 4) {

            sscanf(lhs, "%s", lhs);
            sscanf(op1, "%s", op1);
            sscanf(op2, "%s", op2);

            // COPY PROPAGATION
            int idx1 = findVar(op1);
            if (idx1 != -1) strcpy(op1, val[idx1]);

            int idx2 = findVar(op2);
            if (idx2 != -1) strcpy(op2, val[idx2]);

            // mark used
            markUsed(op1);
            markUsed(op2);

            // CONSTANT FOLDING
            if (isNumber(op1) && isNumber(op2)) {

                int v1 = atoi(op1);
                int v2 = atoi(op2);
                int res;

                switch (operator) {
                    case '+': res = v1 + v2; break;
                    case '-': res = v1 - v2; break;
                    case '*': res = v1 * v2; break;
                    case '/': res = v1 / v2; break;
                }

                printf("%s = %d\n", lhs, res);

                char temp[20];
                sprintf(temp, "%d", res);
                store(lhs, temp);
            }
            else {
                printf("%s = %s %c %s\n", lhs, op1, operator, op2);

                char expr[50];
                sprintf(expr, "%s %c %s", op1, operator, op2);
                store(lhs, expr);
            }
        }

        // Simple assignment
        else if (sscanf(line, "%[^=]=%s", lhs, op1) == 2) {

            sscanf(lhs, "%s", lhs);
            sscanf(op1, "%s", op1);

            // COPY PROPAGATION
            int idx = findVar(op1);
            if (idx != -1)
                strcpy(op1, val[idx]);

            markUsed(op1);

            printf("%s = %s\n", lhs, op1);

            store(lhs, op1);
        }
    }

    // DEAD CODE ELIMINATION
    printf("\nAfter Dead Code Elimination:\n");

    for (int i = 0; i < count; i++) {
        if (used[i]) {
            printf("%s = %s\n", var[i], val[i]);
        }
    }

    return 0;
}