# Q3c: Extract Email IDs from a Text File (Lex)

## Question
Write a Lex program to extract all email IDs from a text file.

## How It Works

The Lex specification uses a regex pattern to match valid email addresses:

```
[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}
```

| Part | Matches |
|------|---------|
| `[a-zA-Z0-9._%+-]+` | Local part (before @) |
| `@` | The @ symbol |
| `[a-zA-Z0-9.-]+` | Domain name |
| `\.[a-zA-Z]{2,}` | Top-level domain (.com, .org, etc.) |

The program reads from `example.txt` and prints all matched emails.

## How to Compile & Run

```bash
lex program.l
gcc lex.yy.c -o program -ll
./program
```

> **Note:** Place your test text in `example.txt` in the same folder.

## Sample Input (`example.txt`)

```
Hello, contact us at support@example.com or sales@company.org.
You can also reach john.doe@university.edu for queries.
Invalid emails: @missing.com, noat.sign
```

## Sample Output

```
support@example.com
sales@company.org
john.doe@university.edu
```
