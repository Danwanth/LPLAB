#include <stdio.h>
#include <string.h>

#define MAX 20

char stack[50];
char input[50];
char lhs[MAX][10], rhs[MAX][10];
char action[100];
int top = -1;
int n;   // number of productions

void shift() {
    stack[++top] = input[0];

    for(int i = 0; i < strlen(input); i++)
        input[i] = input[i+1];
}

int reduce() {
    for(int i = 0; i < n; i++) {
        int len = strlen(rhs[i]);

        if(top+1 >= len) {
            int match = 1;

            for(int j = 0; j < len; j++) {
                if(stack[top-len+1+j] != rhs[i][j]) {
                    match = 0;
                    break;
                }
            }

            if(match) {
                top = top - len + 1;
                stack[top] = lhs[i][0];
                stack[top+1] = '\0';
                sprintf(action, "Reduce %s -> %s", lhs[i], rhs[i]);
                printf("%-15s\t%-15s\t%s\n", stack, input, action);
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    printf("Enter number of productions: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter production (E=E+E format): ");
        scanf("%s", input);

        lhs[i][0] = input[0];
        lhs[i][1] = '\0';

        int j = 2, k = 0;
        while(input[j] != '\0')
            rhs[i][k++] = input[j++];

        rhs[i][k] = '\0';
    }

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-15s\t%-15s\t%s\n\n", "Stack", "Input", "Action");

    while(strlen(input) > 0) {
        shift();
        stack[top+1] = '\0';
        printf("%-15s\t%-15s\tShift %c\n", stack, input, stack[top]);

        while(reduce());
    }

    while(reduce());

    if(top == 0)
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
