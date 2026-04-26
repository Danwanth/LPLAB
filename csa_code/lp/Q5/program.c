#include <stdio.h>
#include <stdlib.h>

int i = 0;
char input[50];

void S();
void S1();
void A();
void A1();
void B();

void error() {
    printf("INVALID INPUT CHARACTER!\n");
    exit(0);
}

void forward(char c) {
    if (input[i] == c)
        i++;
    else
        error();
}

void S() {
    if (input[i] == 'a') {
        forward('a');
        S1();
    }
    else if (input[i] == 'b') {
        forward('b');
    }
    else {
        error();
    }
}

void S1() {
    if (input[i] == 'a') {
        A();
        forward('d');
    }
    else if (input[i] == 'c' || input[i] == 'd') {
        B();
    }
    else {
        error();
    }
}

void A() {
    forward('a');

    if (input[i] == 'c') {
        forward('c');          // A → a c
    }
    else {
        A1();                  // A → a A1 (A1 may be ε)
    }
}

void A1() {
    if (input[i] == 'b') {
        forward('b');  // A1 → b
    }
    else {
        // A1 → ε
        return;
    }
}

void B() {
    if (input[i] == 'c') {
        forward('c');
        forward('c');
        forward('d');
    }
    else if (input[i] == 'd') {
        forward('d');
        forward('d');
        forward('c');
    }
    else {
        error();
    }
}

int main() {
    printf("Enter the string (end with $): ");
    scanf("%s", input);

    S();

    if (input[i] == '$')
        printf("VALID STRING!\n");
    else
        printf("INVALID STRING!\n");

    return 0;
}
