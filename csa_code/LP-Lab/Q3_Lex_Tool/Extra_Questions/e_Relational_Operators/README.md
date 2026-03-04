# Extra Q5: Validate Relational Operators (Lex)

## Question
Implement a Lex specification to recognize valid relational operators.

## How It Works

### Why `()` instead of `[]`?

- **`[...]`** is a **character class** — matches **one character** from the set
  - `[<>=!]` matches a single char: `<`, `>`, `=`, or `!`
  - Cannot match multi-character strings like `<=` or `==`

- **`(...|...)` ** is a **group with alternation** — matches **full strings**
  - `(<|>|<=|>=|!=|==)` matches any of: `<`, `>`, `<=`, `>=`, `!=`, `==`

### Pattern
```
rop (<|>|<=|>=|!=|==)
```

This matches all 6 relational operators as complete tokens.

## How to Compile & Run

```bash
flex program.l
gcc lex.yy.c -o a.exe
./a.exe
```

## Sample Input/Output

```
<=
Valid

==
Valid

=
Invalid

!=
Valid
```
