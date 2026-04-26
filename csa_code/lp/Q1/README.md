# Q1: Whitespace & Comment Remover

## Question
Write a C program that removes all unnecessary whitespace (such as extra spaces, tabs, and blank lines) from a given C source code. The program should also remove all single-line comments (`// ...`) and multi-line comments (`/* ... */`). After cleaning the code, print the resulting program along with line numbers.

## How It Works

The program reads a C source file (`input.c`) character by character and:

1. **Removes single-line comments** (`// ...`) — skips everything from `//` to end of line
2. **Removes multi-line comments** (`/* ... */`) — skips everything between `/*` and `*/`
3. **Removes extra spaces/tabs** — keeps only one space between words, removes leading spaces
4. **Removes blank lines** — only prints lines that have actual content
5. **Adds line numbers** — prints each cleaned line with its line number

### Key Variables
| Variable | Purpose |
|----------|---------|
| `spaceF` | Tracks if we already placed a space (avoids multiple spaces) |
| `lstart` | Tracks if we're at the start of a line (skips leading spaces) |
| `lcontent` | Tracks if the current line has any real content (skips blank lines) |
| `out[]` | Buffer to store the cleaned output |

## How to Compile & Run

```bash
gcc program.c -o program
./program
```

> **Note:** Make sure `input.c` is in the same folder as the program.

## Sample Input (`input.c`)

```c
#include <stdio.h>

void    main() {
     //Declare two numbers
    int a,b;
    printf("Enter two numbers: \n"); //test
    //Reading from user
    scanf("%d %d", &a, &b);
    
    /* Here we calculate
    and print the sum 
    in one line */
    printf("The sum is %d\n", a+b);
}
```

## Sample Output

```
1: #include <stdio.h>
2: void main() {
3: int a,b;
4: printf("Enter two numbers: \n");
5: scanf("%d %d", &a, &b);
6: printf("The sum is %d\n", a+b);
7: }
```

## What Was Removed
- `//Declare two numbers` — single-line comment ✅
- `//test` — inline single-line comment ✅
- `//Reading from user` — single-line comment ✅
- `/* Here we calculate ... */` — multi-line comment ✅
- Extra spaces in `void    main()` → `void main()` ✅
- Leading spaces/tabs ✅
- Blank lines ✅
