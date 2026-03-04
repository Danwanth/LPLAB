# Q6: Shift-Reduce Parser

## How It Works

A shift-reduce parser uses a **stack** and an **input buffer**. It has two operations:

| Operation | What it does |
|---|---|
| **Shift** | Move the first character from input → push onto stack |
| **Reduce** | If the top of stack matches a production's RHS → replace with LHS |

### The Loop
```
1. Shift one character from input onto stack
2. Try to reduce (repeatedly, until no more reductions possible)
3. Repeat until input is empty
4. Try final reductions
5. If stack has only the start symbol → ACCEPTED
```

### Code Breakdown

**Parsing productions** (e.g. `E=E+E`):
- `lhs[i]` = everything before `=` → `"E"`
- `rhs[i]` = everything after `=` → `"E+E"`

**`shift()`**: Takes `input[0]`, pushes onto `stack`, shifts input left.

**`reduce()`**: Scans all productions. If the **top of stack** ends with a production's RHS, replaces it with the LHS. Returns 1 if reduced, 0 if not.

**Acceptance**: After all shifts and reductions, if `top == 0` (stack has exactly 1 symbol = start symbol) → string accepted.

### Example

Grammar: `E=E+E`, `E=a` | Input: `a+a`

```
Step    Stack    Input    Action
1       a        +a       Shift 'a'
2       E        +a       Reduce: E -> a
3       E+       a        Shift '+'
4       E+a               Shift 'a'
5       E+E               Reduce: E -> a
6       E                  Reduce: E -> E+E
→ Stack has only 'E' → ACCEPTED
```

## How to Compile & Run

```bash
gcc program.c -o program
./program
# Enter: 2 productions → E=E+E, E=a
# Enter input: a+a
```
