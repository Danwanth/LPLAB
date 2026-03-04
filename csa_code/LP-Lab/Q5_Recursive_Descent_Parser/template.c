/*
    Recursive Descent Parser - Template
    ====================================

    HOW TO USE THIS TEMPLATE:
    1. Write your grammar in a comment below
    2. Eliminate left recursion (if any)
    3. Left-factor common prefixes (if any)
    4. Create one function per non-terminal
    5. Use FIRST sets to decide which production to pick

    GRAMMAR (example):
        E  → T E'
        E' → + T E' | ε
        T  → F T'
        T' → * F T' | ε
        F  → ( E ) | id

    This is the classic expression grammar after removing left recursion.
*/

#include <stdio.h>
#include <stdlib.h>

int i = 0;
char input[50];

// Forward declarations — one per non-terminal
void E();
void E1();  // E'
void T();
void T1();  // T'
void F();

void error() {
    printf("INVALID STRING!\n");
    exit(0);
}

/*
    forward(c): Match the current input character with expected character 'c'.
    If it matches, advance the pointer. Otherwise, error.
*/
void forward(char c) {
    if (input[i] == c)
        i++;
    else
        error();
}

/*
    For each non-terminal, look at the FIRST set of each production
    to decide which branch to take.

    If a production can produce ε (empty), check FOLLOW set to decide
    whether to take the ε path (just return).
*/

// E → T E'
void E() {
    T();
    E1();
}

// E' → + T E' | ε
//   FIRST(+ T E') = { + }
//   FOLLOW(E') = { ), $ }  → if we see these, take ε
void E1() {
    if (input[i] == '+') {
        forward('+');
        T();
        E1();
    }
    else {
        // ε production — just return
        return;
    }
}

// T → F T'
void T() {
    F();
    T1();
}

// T' → * F T' | ε
//   FIRST(* F T') = { * }
//   FOLLOW(T') = { +, ), $ }  → if we see these, take ε
void T1() {
    if (input[i] == '*') {
        forward('*');
        F();
        T1();
    }
    else {
        // ε production — just return
        return;
    }
}

// F → ( E ) | id
//   Using 'a'-'z' as identifiers for simplicity
void F() {
    if (input[i] == '(') {
        forward('(');
        E();
        forward(')');
    }
    else if (input[i] >= 'a' && input[i] <= 'z') {
        forward(input[i]);   // match any lowercase letter as 'id'
    }
    else {
        error();
    }
}

int main() {
    printf("Enter the string (end with $): ");
    scanf("%s", input);

    E();    // Start parsing from the start symbol

    if (input[i] == '$')
        printf("VALID STRING!\n");
    else
        printf("INVALID STRING!\n");

    return 0;
}
