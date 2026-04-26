# Q2: Lexical Analyzer (State Machine)

## Question
Implement a lexical analyzer in C for a given language that tokenizes input and detects lexical errors.

## How It Works

Uses a **state machine with switch-case** to tokenize input from `input.c`.

### States

| State | Purpose |
|-------|---------|
| 0 | Initial — read first char, decide what token it could be |
| 1 | After `<` — check for `<=` |
| 2 | After `>` — check for `>=` |
| 3 | After `=` — check for `==` |
| 4 | After `!` — check for `!=` |
| 5 | After `&` — check for `&&` |
| 6 | After `|` — check for `||` |
| 7 | Reading a word (keyword or identifier) |
| 8 | Reading a number (constant) |

### Token Types

| Type | Examples |
|------|----------|
| Keyword | `int`, `if`, `else`, `while`, `return`, `void` |
| Identifier | Variable names (`a`, `b`) — stored in symbol table |
| Constant | Numbers (`10`, `255`) |
| Arithmetic Operator | `+`, `-`, `*`, `/`, `%` |
| Relational | `<`, `>`, `<=`, `>=`, `==`, `!=` |
| Assignment | `=` |
| Logical | `&&`, `||`, `!` |
| Special Symbol | `(`, `)`, `{`, `}`, `,`, `;`, `[`, `]` |
| Lexical Error | Any unrecognized character |

## How to Compile & Run

```bash
gcc program.c -o program
./program
```

> **Note:** Place your test code in `input.c` in the same folder.

## Sample Input (`input.c`)

```c
int a, b;
if a < b
a = a + 10;
```

## Sample Output

```
int <Keyword>
a <Identifier #0>
, <Special Symbol>
b <Identifier #1>
; <Special Symbol>
if <Keyword>
a <Identifier #0>
< <Relational>
b <Identifier #1>
a <Identifier #0>
= <Assignment>
a <Identifier #0>
+ <Arithmetic Operator>
10 <Constant>
; <Special Symbol>

Symbol Table
Index   Identifier
0       a
1       b
```
