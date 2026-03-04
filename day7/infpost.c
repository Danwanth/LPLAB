#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int tempCount = 1;

// Stack functions
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {

        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            while ((c = pop()) != '(')
                postfix[j++] = c;
        }
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[j++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

// Generate Three Address Code
void generateTAC(char postfix[]) {

    char tacStack[MAX][10];
    int tacTop = -1;
    char temp[10];

    for (int i = 0; postfix[i] != '\0'; i++) {

        if (isalnum(postfix[i])) {
            tacStack[++tacTop][0] = postfix[i];
            tacStack[tacTop][1] = '\0';
        }
        else {
            char op = postfix[i];

            char op2[10], op1[10];
            strcpy(op2, tacStack[tacTop--]);
            strcpy(op1, tacStack[tacTop--]);

            sprintf(temp, "t%d", tempCount++);
            printf("%s = %s %c %s\n", temp, op1, op, op2);

            strcpy(tacStack[++tacTop], temp);
        }
    }
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nThree Address Code:\n");
    generateTAC(postfix);

    return 0;
}
/*sample OUTPUT :
PS C:\Users\Dhanwanth\Desktop\vscode\MINI-PROJ> gcc 3ac.c
PS C:\Users\Dhanwanth\Desktop\vscode\MINI-PROJ> ./a.exe
Enter Infix Expression: a+b*c

Three Address Code:
t1 = b * c
t2 = a + t1
*/