#include <stdio.h>

int is_space(char c) {
    return c==' ' || c=='\t' || c=='\n' || c=='\r';
}

int main() {
    FILE *f = fopen("source.c", "r");
    if (!f) return 1;

    FILE *fw = fopen("output.c", "w");     // <<--- NEW OUTPUT FILE
    if (!fw) { fclose(f); return 1; }

    int c, nc;
    int in_sl = 0;
    int in_ml = 0;
    int last_space = 0;
    int printed = 0;
    int ln = 1;

    printf("%d: ", ln);
    fprintf(fw, "%d: ", ln);

    while ((c = fgetc(f)) != EOF) {

        // Detect start of comment
        if (!in_ml && !in_sl && c=='/') {
            nc = fgetc(f);

            // Single-line comment
            if (nc=='/') { in_sl = 1; continue; }

            // Multi-line comment
            if (nc=='*') { in_ml = 1; continue; }

            // Not a comment, print '/'
            putchar(c);
            fputc(c, fw);
            c = nc;
        }

        // End of single-line comment
        if (in_sl && c=='\n') {
            in_sl = 0;
            if (printed) {
                putchar('\n');
                fputc('\n', fw);
                ln++;
                printf("%d: ", ln);
                fprintf(fw, "%d: ", ln);
                printed = 0;
            }
            continue;
        }

        // End of multi-line comment
        if (in_ml && c=='*') {
            nc = fgetc(f);
            if (nc=='/') { in_ml = 0; continue; }
            c = nc;
        }

        // Skip characters inside comments
        if (in_sl || in_ml) continue;

        // Handle whitespace compression
        if (is_space(c)) {
            if (!last_space && printed) {
                putchar(' ');
                fputc(' ', fw);
                last_space = 1;
            }
            if (c=='\n') {
                if (printed) {
                    putchar('\n');
                    fputc('\n', fw);
                    ln++;
                    printf("%d: ", ln);
                    fprintf(fw, "%d: ", ln);
                    printed = 0;
                }
            }
            continue;
        }

        // Normal character
        last_space = 0;
        printed = 1;

        putchar(c);
        fputc(c, fw);
    }

    fclose(f);
    fclose(fw);
    return 0;
}

