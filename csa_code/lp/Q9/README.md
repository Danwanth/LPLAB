# Q9: Backend Compiler — TAC to Assembly

## Question
Implement the back end of the compiler which takes three address code and produces assembly language instructions (MOV, ADD, SUB, MUL, DIV).

## How It Works

The program reads a single TAC instruction and generates equivalent assembly:

### Case 1: Simple Assignment (`a=b`)
```
Input:  a=b
Output: MOV R1, b
        MOV a, R1
```

### Case 2: Expression (`a=b+c`)
```
Input:  a=b+c
Output: MOV R1, b
        MOV R2, c
        ADD R1, R2
        MOV a, R1
```

### Supported Operators

| Operator | Assembly |
|----------|----------|
| `+` | `ADD R1, R2` |
| `-` | `SUB R1, R2` |
| `*` | `MUL R1, R2` |
| `/` | `DIV R1, R2` |

## How to Compile & Run

```bash
gcc program.c -o program
./program
```

## Sample Input & Output

```
Enter TAC instruction: a=b+c

Generated Code:
MOV R1, b
MOV R2, c
ADD R1, R2
MOV a, R1
```

```
Enter TAC instruction: x=y

Generated Code:
MOV R1, y
MOV x, R1
```
