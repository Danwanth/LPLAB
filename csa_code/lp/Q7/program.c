#include<stdio.h>
#include<ctype.h>
#include<string.h>

void printOperand(char c) {
    if(isdigit(c)) { printf("t%c", c); }
    else { printf("%c", c); }
}

int main() {

    char exp[100];
    printf("Enter the Expression to be Converted to 3AC:\n");
    scanf("%s", exp);
    int temp=1, i, j;
    printf("Expression Converted to 3AC is:\n");
    for(i= 0; exp[i]!= '\0'; i++) {
        if(exp[i]== '*' || exp[i]== '/') {
            printf("t%d = ", temp);
            printOperand(exp[i-1]);
            printf("%c", exp[i]);
            printOperand(exp[i+1]);
            printf("\n");
            exp[i-1]= '0'+temp;
            for(j= i; exp[j]!= '\0'; j++) {
                exp[j]= exp[j+2]; }
            exp[j]='\0';
            i--;
            temp++;
        }
    }

    for(i= 0; exp[i]!= '\0'; i++) {
        if(exp[i]== '+' || exp[i]== '-') {
            printf("t%d = ", temp);
            printOperand(exp[i-1]);
            printf("%c", exp[i]);
            printOperand(exp[i+1]);
            printf("\n");
            exp[i-1]= '0'+temp;
            exp[i+1]= '0'+temp;
            for(j= i; exp[j]!= '\0'; j++) {
                exp[j]= exp[j+2]; }
            exp[j]='\0';
            i--;
            temp++;
        }
    }
    printf("%c = t%d\n", exp[0], temp-1);
    return 0;
}