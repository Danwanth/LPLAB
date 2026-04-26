%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(const char *s);
%}
%token NUM
%%
date:
    NUM '/' NUM '/' NUM {
        int dd = $1, mm = $3, yyyy = $5;

        if (dd < 1 || dd > 31)
            printf("Invalid day\n");
        else if (mm < 1 || mm > 12)
            printf("Invalid month\n");
        else if (yyyy < 1000 || yyyy > 9999)
            printf("Invalid year\n");
        else
            printf("Valid date: %02d/%02d/%04d\n", dd, mm, yyyy);
    }
    ;
%%
void yyerror(const char *s) {
    printf("Invalid date format\n");
}

int main() {
    printf("Enter date (DD/MM/YYYY): ");
    yyparse();
    return 0;
}
