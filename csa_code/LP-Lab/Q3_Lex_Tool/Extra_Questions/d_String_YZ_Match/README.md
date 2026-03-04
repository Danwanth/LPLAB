# Extra Q4: Accept Strings where y == z (Lex)

## Question
Implement a Lex specification to accept strings of 0's, 1's, and 2's of the form `xyz` where `y == z`.

## How It Works

The string must be exactly 3 characters from `{0, 1, 2}`, where the 2nd and 3rd characters are equal.

| Pattern | Matches |
|---------|---------|
| `{digit}[0][0]` | `x00` — any digit followed by `00` |
| `{digit}[1][1]` | `x11` — any digit followed by `11` |
| `{digit}[2][2]` | `x22` — any digit followed by `22` |

Anything else is invalid.

## How to Compile & Run

```bash
flex program.l
gcc lex.yy.c -o a.exe
./a.exe
```

## Sample Input/Output

```
011
Valid

012
Invalid

222
Valid
```
