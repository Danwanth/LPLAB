# Q7: Three Address Code Generator

## Question
Write a C program to generate Three Address Code for a given arithmetic expression.

## How It Works

The program reads arithmetic expressions and converts them into **Three Address Code (TAC)** — an intermediate representation used in compilers.

### Algorithm

1. **First pass** — scan for `*` and `/` (higher precedence), generate temp variables and shift the expression string to remove processed operators
2. **Second pass** — scan for `+` and `-` (lower precedence), generate temp variables similarly
3. **Final assignment** — assign the last temp to the result variable

## How to Compile & Run

```bash
gcc program.c -o a.exe
./a.exe
```

## Sample Output

```
Enter the Expression to be Converted to 3AC:
a=b+c*d-e
Expression Converted to 3AC is:
t1 = c*d
t2 = b+t1
t3 = t2-e
a = t3
```

```
Enter the Expression to be Converted to 3AC:
a=b*c+d*e-f
Expression Converted to 3AC is:
t1 = b*c
t2 = d*e
t3 = t1+t2
t4 = t3-f
a = t4
```
