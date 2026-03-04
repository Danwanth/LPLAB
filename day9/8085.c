#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    int n, i;
    char tac[MAX][MAX];
    char result[20], op1[20], op2[20], operator;

    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar();  // clear newline

    printf("Enter TAC statements:\n");

    for (i = 0; i < n; i++) {
        fgets(tac[i], MAX, stdin);
        tac[i][strcspn(tac[i], "\n")] = 0;
    }

    printf("\nAssembly Code:\n");

    for (i = 0; i < n; i++) {

        // Case 1: a = b + c
        if (sscanf(tac[i], "%s = %s %c %s", result, op1, &operator, op2) == 4) {

            printf("MOV R1, %s\n", op1);
            printf("MOV R2, %s\n", op2);

            switch(operator) {
                case '+': printf("ADD R1, R2\n"); break;
                case '-': printf("SUB R1, R2\n"); break;
                case '*': printf("MUL R1, R2\n"); break;
                case '/': printf("DIV R1, R2\n"); break;
            }

            printf("MOV %s, R1\n", result);
        }

        // Case 2: a = b
        else if (sscanf(tac[i], "%s = %s", result, op1) == 2) {
            printf("MOV %s, %s\n", result, op1);
        }
    }

    return 0;
}
