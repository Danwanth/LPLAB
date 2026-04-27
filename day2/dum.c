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
    FILE *fp;
    char word[MAX];
    int c, j;

    fp = fopen("file.txt", "r");
    if (!fp) {
        printf("Error opening file.txt\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {

        /* IDENTIFIER / KEYWORD */
        if (isalpha(c)) {
            j = 0;
            word[j++] = c;

            while ((c = fgetc(fp)) != EOF && isalnum(c)) {
                word[j++] = c;
            }
            word[j] = '\0';

            if (isKeyword(word))
                printf("%s <Keyword>\n", word);
            else {
                int id = addIdentifier(word);
                printf("%s <Identifier %d>\n", word, id);
            }

            if (c != EOF) ungetc(c, fp);
        }

        /* NUMBER */
        else if (isdigit(c)) {
            j = 0;
            word[j++] = c;

            while ((c = fgetc(fp)) != EOF && isdigit(c)) {
                word[j++] = c;
            }
            word[j] = '\0';

            printf("%s <Number>\n", word);

            if (c != EOF) ungetc(c, fp);
        }

        /* RELATIONAL OPERATORS */
        else if (c == '=') {
            int next = fgetc(fp);
            if (next == '=') {
                printf("== <Relational Operator>\n");
            } else {
                printf("= <Operator>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }
        else if (c == '!') {
            int next = fgetc(fp);
            if (next == '=') {
                printf("!= <Relational Operator>\n");
            } else {
                printf("! <Logical Operator>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }
        else if (c == '<') {
            int next = fgetc(fp);
            if (next == '=') {
                printf("<= <Relational Operator>\n");
            } else {
                printf("< <Relational Operator>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }
        else if (c == '>') {
            int next = fgetc(fp);
            if (next == '=') {
                printf(">= <Relational Operator>\n");
            } else {
                printf("> <Relational Operator>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }

        /* LOGICAL OPERATORS */
        else if (c == '&') {
            int next = fgetc(fp);
            if (next == '&') {
                printf("&& <Logical Operator>\n");
            } else {
                printf("& <Invalid>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }
        else if (c == '|') {
            int next = fgetc(fp);
            if (next == '|') {
                printf("|| <Logical Operator>\n");
            } else {
                printf("| <Invalid>\n");
                if (next != EOF) ungetc(next, fp);
            }
        }

        /* ARITHMETIC */
        else if (strchr("+-*/%", c)) {
            printf("%c <Operator>\n", c);
        }

        /* SYMBOLS */
        else if (strchr(";,(){}[]", c)) {
            printf("%c <Symbol>\n", c);
        }

        /* WHITESPACE */
        else if (isspace(c)) {
            continue;
        }

        /* INVALID */
        else {
            printf("%c <Invalid>\n", c);
        }
    }

    fclose(fp);

    /* Symbol Table */
    printf("\nSymbol Table:\n");
    for (int k = 0; k < symcount; k++)
        printf("%d : %s\n", k, symtab[k]);

    return 0;
}