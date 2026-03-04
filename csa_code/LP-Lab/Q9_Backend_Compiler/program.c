#include <stdio.h>
#include <string.h>

int main()
{
    char tac[20];
    char result[10], op1[10], op2[10];
    char operator;

    printf("Enter TAC instruction: ");
    scanf("%s", tac);

    /* Case 1: simple assignment a=b */
    if(sscanf(tac, "%[^=]=%s", result, op1) == 2 &&
       strchr(tac, '+') == NULL &&
       strchr(tac, '-') == NULL &&
       strchr(tac, '*') == NULL &&
       strchr(tac, '/') == NULL)
    {
        printf("\nGenerated Code:\n");
        printf("MOV R1, %s\n", op1);
        printf("MOV %s, R1\n", result);
    }
    else
    {
        /* Case 2: expression a=b+c */
        sscanf(tac, "%[^=]=%[^+-*/]%c%s", result, op1, &operator, op2); //&operator important

        printf("\nGenerated Code:\n");

        printf("MOV R1, %s\n", op1);
        printf("MOV R2, %s\n", op2);

        switch(operator)
        {
            case '+':
                printf("ADD R1, R2\n");
                break;

            case '-':
                printf("SUB R1, R2\n");
                break;

            case '*':
                printf("MUL R1, R2\n");
                break;

            case '/':
                printf("DIV R1, R2\n");
                break;
        }

        printf("MOV %s, R1\n", result);
    }

    return 0;
}
