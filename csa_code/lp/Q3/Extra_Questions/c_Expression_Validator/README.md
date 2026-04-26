# Extra Q3: Validate Arithmetic Expressions (Lex)

## Question
Implement a Lex specification to check whether a given arithmetic expression is valid.

## How It Works

### Definitions
| Name | Pattern | Meaning |
|------|---------|---------|
| `num` | `[0-9]+` | Integer number |
| `id` | `[a-zA-Z][a-zA-Z0-9]*` | Identifier (variable name) |
| `aop` | `[+\-*/]` | Arithmetic operator |
| `term` | `id` or `num` | An operand |

### Rule
The pattern `{id}={term}({aop}{term})*` matches a valid assignment expression like `a=b+c*d`.

## How to Compile & Run

```bash
flex program.l
gcc lex.yy.c -o a.exe
./a.exe
```

## Sample Input/Output

```
a=b+c*d
valid

hello
invalid

x=10+y
valid
```
