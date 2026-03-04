#include <stdio.h>      // For input/output functions
#include <ctype.h>      // For character checking functions
#include <string.h>     // For string operations

#define MAX 100         // Maximum size for symbol table

/* ---------------- SYMBOL TABLE DATA ---------------- */

char symbolTable[MAX][20];   // Stores identifier names
int addressTable[MAX];       // Stores memory addresses
int symbolCount = 0;         // Number of symbols stored
int locationCounter = 1000;  // Starting memory location

/*
This section defines the symbol table.
Each identifier is stored with a simulated memory address.
*/

/* ---------------- KEYWORD CHECK FUNCTION ---------------- */

int checkKeyword(char *word)
{
    char *keywords[] = {      // List of C keywords
        "int","float","char","double",
        "if","else","while","for","return","long"
    };

    for(int i = 0; i < 10; i++)        // Loop through keyword list
        if(strcmp(word, keywords[i]) == 0) // Compare strings
            return 1;                 // Word is a keyword

    return 0;                          // Word is not a keyword
}

/*
This function checks whether a given string
is a C keyword by comparing it with a predefined list.
*/

/* ---------------- SYMBOL TABLE INSERT FUNCTION ---------------- */

void addSymbol(char *word)
{
    for(int i = 0; i < symbolCount; i++)   // Check existing symbols
        if(strcmp(symbolTable[i], word) == 0)
            return;                        // Avoid duplicates

    strcpy(symbolTable[symbolCount], word); // Store identifier
    addressTable[symbolCount] = locationCounter; // Assign address
    locationCounter += 4;                  // Increment address
    symbolCount++;                         // Increase count
}

/*
This function inserts identifiers into the symbol table
only if they are not already present.
*/

/* ---------------- MAIN FUNCTION ---------------- */

int main()
{
    FILE *sourceFile;              // File pointer
    char sourceBuffer[5000];       // Buffer to store file content

    sourceFile = fopen("input.c", "r"); // Open source file
    if(sourceFile == NULL)         // Check file opening
    {
        printf("Error: Cannot open file\n");
        return 1;
    }

    fread(sourceBuffer, sizeof(char), sizeof(sourceBuffer), sourceFile); // Read file
    fclose(sourceFile);             // Close file

    /*
    This block opens the input C file and
    reads its entire content into a buffer.
    */

    int currentState = 0;           // DFA state
    char tokenBuffer[50];           // Stores current token
    int tokenIndex = 0;             // Token buffer index

    /*
    Variables used for DFA-based lexical analysis.
    */

    for(int index = 0; index < strlen(sourceBuffer); index++)
    {
        char currentChar = sourceBuffer[index]; // Current character

        switch(currentState)
        {
        case 0:  // Start state
            if(isalpha(currentChar) || currentChar == '_'){
                tokenIndex = 0;
                tokenBuffer[tokenIndex++] = currentChar;
                currentState = 22;
            }
            else if(isdigit(currentChar)){
                tokenIndex = 0;
                tokenBuffer[tokenIndex++] = currentChar;
                currentState = 23;
            }
            else if(currentChar == '+'){ currentState = 1; index--; }
            else if(currentChar == '-'){ currentState = 2; index--; }
            else if(currentChar == '*'){ currentState = 3; index--; }
            else if(currentChar == '/'){ currentState = 4; index--; }
            else if(currentChar == '%'){ currentState = 5; index--; }
            else if(currentChar == '<'){ currentState = 6; index--; }
            else if(currentChar == '>'){ currentState = 7; index--; }
            else if(currentChar == '!'){ currentState = 8; index--; }
            else if(currentChar == '='){ currentState = 9; index--; }
            else if(currentChar == '&'){ currentState = 10; index--; }
            else if(currentChar == '|'){ currentState = 11; index--; }
            else if(currentChar == ',' || currentChar == ';' ||
                    currentChar == '(' || currentChar == ')' ||
                    currentChar == '{' || currentChar == '}')
                printf("'%c' = <special character>\n", currentChar);
            break;

        /*
        State 0 decides what type of token begins
        based on the current character.
        */

        case 1: printf("'+' = <arithmetic operator>\n"); currentState = 0; break;
        case 2: printf("'-' = <arithmetic operator>\n"); currentState = 0; break;
        case 3: printf("'*' = <arithmetic operator>\n"); currentState = 0; break;
        case 4: printf("'/' = <arithmetic operator>\n"); currentState = 0; break;
        case 5: printf("'%%' = <arithmetic operator>\n"); currentState = 0; break;

        /*
        These states recognize arithmetic operators.
        */

        case 6:
            if(sourceBuffer[index+1] == '='){ printf("'<=' = <relational operator>\n"); index++; }
            else printf("'<' = <relational operator>\n");
            currentState = 0;
            break;

        case 7:
            if(sourceBuffer[index+1] == '='){ printf("'>=' = <relational operator>\n"); index++; }
            else printf("'>' = <relational operator>\n");
            currentState = 0;
            break;

        /*
        These states handle relational operators.
        */

        case 8:
            if(sourceBuffer[index+1] == '='){ printf("'!=' = <relational operator>\n"); index++; }
            else printf("'!' = <logical operator>\n");
            currentState = 0;
            break;

        case 9:
            if(sourceBuffer[index+1] == '='){ printf("'==' = <relational operator>\n"); index++; }
            else printf("'=' = <assignment operator>\n");
            currentState = 0;
            break;

        /*
        These states distinguish logical, relational,
        and assignment operators.
        */

        case 10:
            if(sourceBuffer[index+1] == '&'){ printf("'&&' = <logical operator>\n"); index++; }
            else printf("'&' = <unknown operator>\n");
            currentState = 0;
            break;

        case 11:
            if(sourceBuffer[index+1] == '|'){ printf("'||' = <logical operator>\n"); index++; }
            else printf("'|' = <unknown operator>\n");
            currentState = 0;
            break;

        /*
        These states recognize logical AND and OR operators.
        */

        case 22: // Identifier state
            if(isalnum(currentChar) || currentChar == '_')
                tokenBuffer[tokenIndex++] = currentChar;
            else
            {
                tokenBuffer[tokenIndex] = '\0';
                index--;
                if(checkKeyword(tokenBuffer))
                    printf("'%s' = <keyword>\n", tokenBuffer);
                else
                {
                    printf("'%s' = <identifier>\n", tokenBuffer);
                    addSymbol(tokenBuffer);
                }
                currentState = 0;
            }
            break;

        /*
        This state collects identifiers or keywords
        and inserts identifiers into the symbol table.
        */

        case 23: // Number state
            if(isdigit(currentChar))
                tokenBuffer[tokenIndex++] = currentChar;
            else
            {
                tokenBuffer[tokenIndex] = '\0';
                index--;
                printf("'%s' = <number>\n", tokenBuffer);
                currentState = 0;
            }
            break;

        /*
        This state recognizes numeric constants.
        */
        }
    }

    printf("\n---- SYMBOL TABLE ----\n");
    printf("Name\tAddress\n");
    for(int i = 0; i < symbolCount; i++)
        printf("%s\t%d\n", symbolTable[i], addressTable[i]);

    /*
    This block prints the final symbol table
    containing identifiers and their addresses.
    */

    return 0;
}

