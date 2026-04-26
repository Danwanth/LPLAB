# Q3b: Count Vowels, Consonants, Digits & Special Characters (Lex)

## Question
Implement a Lex specification to count the number of vowels, consonants, digits, and special characters in a text.

## How It Works

The Lex specification uses pattern-matching rules:

| Pattern | Action |
|---------|--------|
| `[aeiouAEIOU]` | Increment vowel count |
| `[a-zA-Z]` | Increment consonant count |
| `[0-9]` | Increment digit count |
| `[^a-zA-Z0-9 \t\n]` | Increment special char count |
| Whitespace | Ignored |

> **Note:** Vowels are matched first, so they are not double-counted as consonants.

## How to Compile & Run

```bash
lex program.l
gcc lex.yy.c -o program -ll
./program
```

> **Note:** Type input and press `Ctrl+Z` (Windows) or `Ctrl+D` (Linux) to stop.

## Sample Input

```
Hello World! 123
```

## Sample Output

```
Enter input:
Vowels = 3
Consonants = 7
Digits = 3
Special Characters = 1
```
