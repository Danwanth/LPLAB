#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

struct Symbol {
    char name[MAX];
};

struct Symbol symtab[MAX];
int symcount = 0;

int addIdentifier(char *name) {
    for (int i = 0; i < symcount; i++)
        if (strcmp(symtab[i].name, name) == 0)
            return i;

    strcpy(symtab[symcount].name, name);
    return symcount++;
}

int isKeyword(char *str) {
    char *keywords[] = {"if","else","while","for",
                        "int","float","char","return","void"};
    int n = sizeof(keywords)/sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    return 0;
}

int main() {

    FILE *fp = fopen("input.c", "r");
    if (!fp) return 1;

    char input[1000], lexeme[MAX];
    int i = 0, l = 0, state = 0;
    char ch;

    int idx = 0;
    while ((ch = fgetc(fp)) != EOF && idx < 999)
        input[idx++] = ch;
    input[idx] = '\0';
    fclose(fp);

    while (input[i] != '\0') {

        ch = input[i];

        switch (state) {

        /* ---------- STATE 0 ---------- */
        case 0:
            l = 0;

            if (ch == '<') state = 1;
            else if (ch == '>') state = 4;
            else if (ch == '!') state = 7;
            else if (ch == '=') state = 19;
            else if (ch == '+') state = 10;
            else if (ch == '-') state = 11;
            else if (ch == '*') state = 12;
            else if (ch == '/') state = 13;
            else if (ch == '%') state = 14;
            else if (ch == '&') state = 15;
            else if (ch == '|') state = 17;
            else if (strchr(";,(){}[]", ch)) state = 22;
            else if (isalpha(ch)) { lexeme[l++] = ch; state = 23; }
            else if (isdigit(ch)) { lexeme[l++] = ch; state = 25; }

            i++;
            break;

        /* < */
        case 1:
            if (input[i] == '=') { state = 2; i++; }
            else state = 3;
            break;

        case 2:
            printf("<RELATIONAL OP <= >\n");
            state = 0;
            break;

        case 3:
            printf("<RELATIONAL OP < >\n");
            state = 0;
            break;

        /* > */
        case 4:
            if (input[i] == '=') { state = 5; i++; }
            else state = 6;
            break;

        case 5:
            printf("<RELATIONAL OP >= >\n");
            state = 0;
            break;

        case 6:
            printf("<RELATIONAL OP > >\n");
            state = 0;
            break;

        /* ! */
        case 7:
            if (input[i] == '=') { state = 8; i++; }
            else state = 9;
            break;

        case 8:
            printf("<RELATIONAL OP != >\n");
            state = 0;
            break;

        case 9:
            printf("<LOGICAL OP NOT>\n");
            state = 0;
            break;

        /* Arithmetic */
        case 10: printf("<ARITHMETIC OP +>\n"); state = 0; break;
        case 11: printf("<ARITHMETIC OP ->\n"); state = 0; break;
        case 12: printf("<ARITHMETIC OP *>\n"); state = 0; break;
        case 13: printf("<ARITHMETIC OP />\n"); state = 0; break;
        case 14: printf("<ARITHMETIC OP %>\n"); state = 0; break;

        /* && */
        case 15:
            if (input[i] == '&') { state = 16; i++; }
            break;

        case 16:
            printf("<LOGICAL OP AND>\n");
            state = 0;
            break;

        /* || */
        case 17:
            if (input[i] == '|') { state = 18; i++; }
            break;

        case 18:
            printf("<LOGICAL OP OR>\n");
            state = 0;
            break;

        /* = */
        case 19:
            if (input[i] == '=') { state = 20; i++; }
            else state = 21;
            break;

        case 20:
            printf("<RELATIONAL OP ==>\n");
            state = 0;
            break;

        case 21:
            printf("<ASSIGNMENT OP =>\n");
            state = 0;
            break;

        /* Special symbol */
        case 22:
            printf("<SPECIAL SYMBOL>\n");
            state = 0;
            break;

        /* Identifier / Keyword */
        case 23:
            if (isalnum(input[i])) {
                lexeme[l++] = input[i++];
            } else {
                lexeme[l] = '\0';
                if (isKeyword(lexeme))
                    state = 24;
                else
                    state = 24;
            }
            break;

        case 24:
            if (isKeyword(lexeme))
                printf("<KEYWORD %s>\n", lexeme);
            else {
                int id = addIdentifier(lexeme);
                printf("<IDENTIFIER #%d %s>\n", id, lexeme);
            }
            state = 0;
            break;

        /* Constant */
        case 25:
            if (isdigit(input[i])) {
                lexeme[l++] = input[i++];
            } else {
                lexeme[l] = '\0';
                state = 26;
            }
            break;

        case 26:
            printf("<CONSTANT %s>\n", lexeme);
            state = 0;
            break;
        }
    }

    printf("\nSYMBOL TABLE\n");
    printf("Index\tIdentifier\n");

    for (int j = 0; j < symcount; j++)
        printf("%d\t%s\n", j, symtab[j].name);

    return 0;
}