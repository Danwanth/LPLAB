#include <stdio.h>
#include <stdlib.h>

char input[100];
int i = 0;

/* Function declarations */
void S();
void A();
void B();
void C();
void D();
void error();

/* Match function */
void match(char c) {
    if (input[i] == c)
        i++;
    else
        error();
}

/* S → a A B | C */
void S() {
    if (input[i] == 'a') {        // FIRST(aAB)
        match('a');
        A();
        B();
    }
    else if (input[i] == 'd' || input[i] == '\0') { // FIRST(C) + FOLLOW(S)
        C();
    }
    else {
        error();
    }
}

/* A → b | ε
   FIRST(A) = {b, ε}
   FOLLOW(A) = {c}
*/
void A() {
    if (input[i] == 'b') {
        match('b');
    }
    else if (input[i] == 'c') { // FOLLOW(A)
        return; // ε
    }
    else {
        error();
    }
}

/* B → c D */
void B() {
    if (input[i] == 'c') {
        match('c');
        D();
    }
    else {
        error();
    }
}

/* C → d | ε
   FOLLOW(C) = {$}
*/
void C() {
    if (input[i] == 'd') {
        match('d');
    }
    else if (input[i] == '\0') { // end of input
        return; // ε
    }
    else {
        error();
    }
}

/* D → e */
void D() {
    if (input[i] == 'e') {
        match('e');
    }
    else {
        error();
    }
}

void error() {
    printf("Invalid string\n");
    exit(1);
}

int main() {
    printf("Enter input string: ");
    scanf("%99s", input);

    S();

    if (input[i] == '\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");

    return 0;
}