#include <stdio.h>

void main() {
    FILE *fptr = fopen("input.c", "r");
    if (!fptr) {
        printf("Error opening file\n");
        return;
    }

    int ch, chr;
    int spaceF = 0;    // flag: was last char a space?
    int lstart = 1;    // flag: are we at line start?
    int lcontent = 0;  // flag: does current line have content?
    int k = 0;
    char out[5000];

    while ((ch = fgetc(fptr)) != EOF) {
        // --- Handle comments ---
        if (ch == '/') {
            chr = fgetc(fptr);

            if (chr == '/') {
                // Single-line comment: skip till end of line
                while ((ch = fgetc(fptr)) != EOF && ch != '\n') {
                    continue;
                }
                if (lcontent) {
                    out[k++] = '\n';
                }
                lstart = 1;
                lcontent = 0;
                spaceF = 0;
            }
            else if (chr == '*') {
                // Multi-line comment: skip till */
                while ((ch = fgetc(fptr)) != EOF) {
                    if (ch == '*') {
                        ch = fgetc(fptr);
                        if (ch == '/') {
                            break;
                        }
                    }
                }
            }
            else {
                // Not a comment, just a '/' character
                out[k++] = '/';
                out[k++] = chr;
            }
        }
        else {
            // --- Handle whitespace ---
            if (ch == ' ' || ch == '\t') {
                // Keep only one space, skip leading spaces
                if (!lstart && !spaceF) {
                    out[k++] = ' ';
                    spaceF = 1;
                }
            }
            else if (ch == '\n') {
                // Skip blank lines (only keep lines with content)
                if (lcontent) {
                    out[k++] = '\n';
                }
                lstart = 1;
                lcontent = 0;
                spaceF = 0;
            }
            else {
                // Normal character
                out[k++] = ch;
                lstart = 0;
                lcontent = 1;
                spaceF = 0;
            }
        }
    }

    fclose(fptr);
    out[k] = '\0';

    // --- Print output with line numbers ---
    printf("1: ");
    int line = 1;
    for (int i = 0; out[i] != '\0'; i++) {
        putchar(out[i]);
        if (out[i] == '\n' && out[i + 1] != '\0') {
            line++;
            printf("%d: ", line);
        }
    }
    printf("\n");
}
