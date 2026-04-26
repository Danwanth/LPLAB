#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 50

char lhs[MAX][10], op1[MAX][10], op2[MAX][10], op[MAX][5];

int isConst(char *s) {
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}

int main() {
    int n;
    char line[100];

    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC:\n");

    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);

        int count = sscanf(line, "%s = %s %s %s",
                           lhs[i], op1[i], op[i], op2[i]);

        if (count == 3) {
            strcpy(op[i], "");
            strcpy(op2[i], "");
        }
    }

    // -------- Constant Folding --------
    for (int i = 0; i < n; i++) {
        if (isConst(op1[i]) && isConst(op2[i])) {
            int a = atoi(op1[i]);
            int b = atoi(op2[i]);
            int res;

            if (strcmp(op[i], "+") == 0)
                res = a + b;
            else if (strcmp(op[i], "-") == 0)
                res = a - b;
            else if (strcmp(op[i], "*") == 0)
                res = a * b;
            else if (strcmp(op[i], "/") == 0)
                res = a / b;
            else
                continue;

            sprintf(op1[i], "%d", res);
            strcpy(op[i], "");
            strcpy(op2[i], "");
        }
    }

    // -------- Output --------
    printf("\nOptimized TAC:\n");

    for (int i = 0; i < n; i++) {
        if (strcmp(op[i], "") == 0)
            printf("%s = %s\n", lhs[i], op1[i]);
        else
            printf("%s = %s %s %s\n", lhs[i], op1[i], op[i], op2[i]);
    }

    return 0;
}
