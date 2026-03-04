#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int i = 0;

/* Function declarations */
void S();
void S_prime();
void A();
void A_prime();
void B();
void error();

/* Match terminal */
void match(char c) {
    if (input[i] == c)
        i++;
    else
        error();
}

/* Grammar implementation */

void S() {
    if (input[i] == 'a') {
        match('a');
        S_prime();
    }
    else if (input[i] == 'b') {
        match('b');
    }
    else {
        error();
    }
}

void S_prime() {
    if (input[i] == 'a') {
        A();
        match('d');
    }
    else if (input[i] == 'c' && input[i+1] == 'd') {
        A();
        match('d');
    }
    else if (input[i] == 'c' && input[i+1] == 'c') {
        B();
    }
    else if (input[i] == 'd') {
        B();
    }
    else {
        error();
    }
}

void A() {
    if (input[i] == 'a') {
        match('a');
        A_prime();
    }
    else if (input[i] == 'c') {
        match('c');
    }
    else {
        error();
    }
}

void A_prime() {
    if (input[i] == 'b') {
        match('b');
    }
    else {
        /* epsilon production */
        return;
    }
}

void B() {
    if (input[i] == 'c') {
        match('c');
        match('c');
        match('d');
    }
    else if (input[i] == 'd') {
        match('d');
        match('d');
        match('c');
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
    scanf("%s", input);

    S();

    if (input[i] == '\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");

    return 0;
}

