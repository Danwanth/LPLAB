# Extra Q1: Count Words and Characters (Lex)

## Question
Implement a Lex specification to count the number of words and characters in a text.

## How It Works

The Lex specification uses pattern-matching rules:

| Pattern | Action |
|---------|--------|
| `{sp}` (space) | Increment word count |
| `.` (any other char) | Increment character count |

> **Note:** Word count starts at 1 since the last word has no trailing space.

## How to Compile & Run

```bash
flex program.l
gcc lex.yy.c -o a.exe
./a.exe
```

> **Note:** Type input and press `Ctrl+Z` (Windows) or `Ctrl+D` (Linux) to stop.

## Sample Input

```
hello world foo
```

## Sample Output

```
3 13
```
