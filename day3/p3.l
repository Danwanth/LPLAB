%{
#include <stdio.h>
#include <string.h>

FILE *yyin;  // Declare the input file
%}

%%

[A-Za-z0-9_%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}  { 
    printf("Email: %s\n", yytext); 
}

.|\n  { /* Ignore other characters */ }

%%

int main() {
    // Open the file 'input.txt' for reading
    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    yyin = input_file;  // Set input file to `yyin`

    yylex();  // Start lexical analysis to extract emails

    fclose(input_file);  // Close the file after processing
    return 0;
}

