#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

/* Symbol table */
char symtab[50][MAX];
int symcount = 0;

/* Add identifier */
int addIdentifier(char *name) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i], name) == 0)
            return i;
    }
    strcpy(symtab[symcount], name);
    return symcount++;
}

/* Check keyword */
int isKeyword(char *str) {
    char *keywords[] = {"if","else","while","int","float","return"};
    int n = 6;

    for (int i = 0; i < n; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;

    return 0;
}

int main() {
    char input[500];
    char word[MAX];
    int i = 0, j = 0;

    printf("Enter code:\n");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0') {

        /* IDENTIFIER / KEYWORD */
        if (isalpha(input[i])) {
            j = 0;

            while (isalnum(input[i])) {
                word[j++] = input[i++];
            }
            word[j] = '\0';

            if (isKeyword(word))
                printf("%s <Keyword>\n", word);
            else {
                int id = addIdentifier(word);
                printf("%s <Identifier %d>\n", word, id);
            }
        }

        /* NUMBER */
        else if (isdigit(input[i])) {
            j = 0;

            while (isdigit(input[i])) {
                word[j++] = input[i++];
            }
            word[j] = '\0';

            printf("%s <Number>\n", word);
        }

        /* RELATIONAL OPERATORS */
        else if (input[i] == '=' && input[i+1] == '=') {
            printf("== <Relational Operator>\n");
            i += 2;
        }
        else if (input[i] == '!' && input[i+1] == '=') {
            printf("!= <Relational Operator>\n");
            i += 2;
        }
        else if (input[i] == '<' && input[i+1] == '=') {
            printf("<= <Relational Operator>\n");
            i += 2;
        }
        else if (input[i] == '>' && input[i+1] == '=') {
            printf(">= <Relational Operator>\n");
            i += 2;
        }
        else if (input[i] == '<') {
            printf("< <Relational Operator>\n");
            i++;
        }
        else if (input[i] == '>') {
            printf("> <Relational Operator>\n");
            i++;
        }

        /* LOGICAL OPERATORS */
        else if (input[i] == '&' && input[i+1] == '&') {
            printf("&& <Logical Operator>\n");
            i += 2;
        }
        else if (input[i] == '|' && input[i+1] == '|') {
            printf("|| <Logical Operator>\n");
            i += 2;
        }
        else if (input[i] == '!') {
            printf("! <Logical Operator>\n");
            i++;
        }

        /* ARITHMETIC + ASSIGNMENT */
        else if (strchr("+-*/=%", input[i])) {
            printf("%c <Operator>\n", input[i]);
            i++;
        }

        /* SYMBOLS */
        else if (strchr(";,(){}[]", input[i])) {
            printf("%c <Symbol>\n", input[i]);
            i++;
        }

        /* SPACES */
        else if (isspace(input[i])) {
            i++;
        }

        /* INVALID */
        else {
            printf("%c <Invalid>\n", input[i]);
            i++;
        }
    }

    /* Symbol Table */
    printf("\nSymbol Table:\n");
    for (int k = 0; k < symcount; k++)
        printf("%d : %s\n", k, symtab[k]);

    return 0;
}