# Extra Q2: Check Divisibility by 7 (Lex)

## Question
Implement a Lex specification to check whether a given number is divisible by 7.

## How It Works

| Pattern | Action |
|---------|--------|
| `{digit}+` | Convert to integer using `atoi()`, check if divisible by 7 |
| `.|\n` | Ignore non-digit characters |

## How to Compile & Run

```bash
flex program.l
gcc lex.yy.c -o a.exe
./a.exe
```

> **Note:** Type input and press `Ctrl+Z` (Windows) or `Ctrl+D` (Linux) to stop.

## Sample Input

```
14 25 49
```

## Sample Output

```
14 is Divisible by 7
25 is Not Divisible by 7
49 is Divisible by 7
```
