#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    int state = 0;   // Starting state q0 = 0
    int i;

    printf("Enter the input string: ");
    scanf("%s", input);

    for (i = 0; i < strlen(input); i++) {
        switch (state) {
            case 0:   // q0 (initial state)
                if (input[i] == 'a')
                    state = 1;
                else if (input[i] == '<')
                    state = 3;
                else if (input[i] == '>')
                    state = 6;
                else if (input[i] == '!')
                    state = 9;
                else if (input[i] == '=')
                    state = 11;
                else if (input[i] == '&')
                    state = 13;
                else if (input[i] == 'I')
                    state = 15;
                else if (input[i] == '+' )
                    state = 18;
                else if (input[i] == '-')
                    state = 19;
                else if (input[i] == '*')
                    state = 20;
                else if (input[i] == '/')
                    state = 21;
                else {
                    printf("Invalid symbol at position %d\n", i);
                    return 0;
                }
                break;

            case 1:   // q1
                // Define transitions for state 1 (can be customized as needed)
                break;

            case 3:   // q3
                // Define transitions for state 3 (can be customized as needed)
                break;

            case 6:   // q6
                // Define transitions for state 6 (can be customized as needed)
                break;

            case 9:   // q9
                // Define transitions for state 9 (can be customized as needed)
                break;

            case 11:   // q11
                // Define transitions for state 11 (can be customized as needed)
                break;

            case 13:   // q13
                // Define transitions for state 13 (can be customized as needed)
                break;

            case 15:   // q15
                // Define transitions for state 15 (can be customized as needed)
                break;

            case 18:   // q18
                // Define transitions for state 18 (can be customized as needed)
                break;

            case 19:   // q19
                // Define transitions for state 19 (can be customized as needed)
                break;

            case 20:   // q20
                // Define transitions for state 20 (can be customized as needed)
                break;

            case 21:   // q21
                // Define transitions for state 21 (can be customized as needed)
                break;

            default:
                printf("Invalid state transition\n");
                return 0;
        }
    }

    // Final state check (can be customized as needed)
    if (state == 2) {
        printf("String is ACCEPTED\n");
    } else {
        printf("String is REJECTED\n");
    }

    return 0;
}

