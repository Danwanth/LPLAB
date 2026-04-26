# Q5: Recursive Descent Parser

## Grammar

```
S  → a S1 | b
S1 → A d | B
A  → a c | a A1
A1 → b | ε
B  → c c d | d d c
```

## Valid Strings

| Input     | Derivation                             |
|-----------|----------------------------------------|
| `b$`      | S → b                                  |
| `aacd$`   | S → a S1 → a A d → a (ac) d           |
| `aabd$`   | S → a S1 → a A d → a (a A1) d → a ab d |
| `aad$`    | S → a S1 → a A d → a (a ε) d          |
| `accd$`   | S → a S1 → a B → a (ccd)              |
| `addc$`   | S → a S1 → a B → a (ddc)              |

## Files

- `program.c` — Recursive descent parser for the above grammar
- `template.c` — Reusable template (expression grammar E → E+T | T, etc.)

## How to Write Each Function

| Situation | What to do | Why |
|---|---|---|
| **Single production** (e.g. `E → T E'`) | Just call the functions in order. No `if/else` needed. | There's no decision to make. Errors are caught by the functions you call. |
| **Multiple productions, no ε** (e.g. `F → (E) \| id`) | Use `if/else` on `input[i]` using FIRST sets. Last `else` → `error()` | Something *must* match. If nothing does, input is invalid. |
| **Multiple productions, has ε** (e.g. `E' → +TE' \| ε`) | Use `if/else` on `input[i]`. Last `else` → `return;` | Not matching is fine — it just means the empty (ε) production. |

## How to Compile & Run

```bash
gcc program.c -o program
./program
# Enter: aacd$
# Output: VALID STRING!
```
