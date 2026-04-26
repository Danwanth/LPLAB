# Q3a: Recognize Integers, Floats & Arithmetic Operators (Lex)

## Question
Develop a Lex program to recognize integers, floating-point numbers, and arithmetic operators.

## How It Works

The Lex specification defines three token patterns:

| Pattern | Matches |
|---------|---------|
| `{digit}+` | Integers (one or more digits) |
| `{digit}*"."{digit}+` | Floating-point numbers |
| `[+\|-\|*\|/\|%]` | Arithmetic operators |

Whitespace and unrecognized characters are silently ignored.

## How to Compile & Run

```bash
lex program.l
gcc lex.yy.c -o program -ll
./program
```

> **Note:** Type input and press `Ctrl+Z` (Windows) or `Ctrl+D` (Linux) to stop.

## Sample Input

```
42 3.14 + 7 - 2.5 * 10 / 3
```

## Sample Output

```
Enter Input:
42 is an Integer
3.14 is a floating point
+ is an Arithmetic Operator
7 is an Integer
- is an Arithmetic Operator
2.5 is a floating point
* is an Arithmetic Operator
10 is an Integer
/ is an Arithmetic Operator
3 is an Integer
```
