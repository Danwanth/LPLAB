#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

/* ---------- Symbol Table ---------- */
struct Symbol {
    char name[MAX];
};

struct Symbol symtab[MAX];
int symcount = 0;

/* Add identifier to symbol table */
int addIdentifier(char *name) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i].name, name) == 0)
            return i;
    }
    strcpy(symtab[symcount].name, name);
    return symcount++;
}

/* Check if keyword */
int isKeyword(char *str) {
    char *keywords[] = {"if","else","while","for",
                        "int","float","char","return","void"};
    int n = sizeof(keywords)/sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;

    return 0;
}

/* ---------- Main ---------- */
int main() {

    FILE *fp = fopen("input.c", "r");
    if (!fp) {
        printf("File not found\n");
        return 1;
    }

    char input[1000], lexeme[MAX];
    int i = 0, l = 0, state = 0;
    char ch;

    /* Read file into buffer */
    int idx = 0;
    while ((ch = fgetc(fp)) != EOF && idx < 999)
        input[idx++] = ch;
    input[idx] = '\0';
    fclose(fp);

    /* Lexical Analysis */
    while (input[i] != '\0') {

        ch = input[i];

        switch (state) {

        /* ---------- Initial State ---------- */
        case 0:
            l = 0;

            if (ch == '<') state = 1;
            else if (ch == '>') state = 2;
            else if (ch == '=') state = 3;
            else if (ch == '!') state = 4;
            else if (ch == '&') state = 5;
            else if (ch == '|') state = 6;

            else if (strchr("+-*/%", ch))
                printf("%c <Arithmetic Operator>\n", ch);

            else if (strchr(";,(){}[]", ch))
                printf("%c <Special Symbol>\n", ch);

            else if (isalpha(ch)) {
                lexeme[l++] = ch;
                state = 7;
            }

            else if (isdigit(ch)) {
                lexeme[l++] = ch;
                state = 8;
            }

            else if (!isspace(ch))
                printf("%c <Lexical Error>\n", ch);

            i++;
            break;

        /* ---------- Relational Operators ---------- */
        case 1:
            if (input[i] == '=') { printf("<= <Relational>\n"); i++; }
            else printf("< <Relational>\n");
            state = 0;
            break;

        case 2:
            if (input[i] == '=') { printf(">= <Relational>\n"); i++; }
            else printf("> <Relational>\n");
            state = 0;
            break;

        case 3:
            if (input[i] == '=') { printf("== <Relational>\n"); i++; }
            else printf("= <Assignment>\n");
            state = 0;
            break;

        case 4:
            if (input[i] == '=') { printf("!= <Relational>\n"); i++; }
            else printf("! <Logical NOT>\n");
            state = 0;
            break;

        case 5:
            if (input[i] == '&') { printf("&& <Logical AND>\n"); i++; }
            state = 0;
            break;

        case 6:
            if (input[i] == '|') { printf("|| <Logical OR>\n"); i++; }
            state = 0;
            break;

        /* ---------- Identifier / Keyword ---------- */
        case 7:
            if (isalnum(ch)) {
                lexeme[l++] = ch;
                i++;
            } else {
                lexeme[l] = '\0';

                if (isKeyword(lexeme))
                    printf("%s <Keyword>\n", lexeme);
                else {
                    int id = addIdentifier(lexeme);
                    printf("%s <Identifier #%d>\n", lexeme, id);
                }

                state = 0;
            }
            break;

        /* ---------- Constant ---------- */
        case 8:
            if (isdigit(ch)) {
                lexeme[l++] = ch;
                i++;
            } else {
                lexeme[l] = '\0';
                printf("%s <Constant>\n", lexeme);
                state = 0;
            }
            break;
        }
    }

    /* ---------- Symbol Table ---------- */
    printf("\nSymbol Table\n");
    printf("Index\tIdentifier\n");
    for (int j = 0; j < symcount; j++)
        printf("%d\t%s\n", j, symtab[j].name);

    return 0;
}