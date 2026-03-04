#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char symbolTable[MAX][20];
int addressTable[MAX];
int symbolCount = 0;
int locationCounter = 1000;

int checkKeyword(char *word)
{
    char *keywords[] = {"int","float","char","double","if","else","while","for","return","long"};
    for(int i = 0; i < 10; i++)
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

void addSymbol(char *word)
{
    for(int i = 0; i < symbolCount; i++)
        if(strcmp(symbolTable[i], word) == 0)
            return;

    strcpy(symbolTable[symbolCount], word);
    addressTable[symbolCount] = locationCounter;
    locationCounter += 4;
    symbolCount++;
}

int main()
{
    FILE *sourceFile;
    char sourceBuffer[5000];

    sourceFile = fopen("input.c", "r");
    if(sourceFile == NULL)
    {
        printf("Error: Cannot open file\n");
        return 1;
    }

    fread(sourceBuffer, sizeof(char), sizeof(sourceBuffer), sourceFile);
    fclose(sourceFile);

    int currentState = 0;
    char tokenBuffer[50];
    int tokenIndex = 0;

    for(int index = 0; index < strlen(sourceBuffer); index++)
    {
        char currentChar = sourceBuffer[index];

        switch(currentState)
        {
        case 0:
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

        case 1: printf("'+' = <arithmetic operator>\n"); currentState = 0; break;
        case 2: printf("'-' = <arithmetic operator>\n"); currentState = 0; break;
        case 3: printf("'*' = <arithmetic operator>\n"); currentState = 0; break;
        case 4: printf("'/' = <arithmetic operator>\n"); currentState = 0; break;
        case 5: printf("'%%' = <arithmetic operator>\n"); currentState = 0; break;

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

        case 22:
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

        case 23:
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
        }
    }

    printf("\n---- SYMBOL TABLE ----\n");
    printf("Name\tAddress\n");
    for(int i = 0; i < symbolCount; i++)
        printf("%s\t%d\n", symbolTable[i], addressTable[i]);

    return 0;
}

