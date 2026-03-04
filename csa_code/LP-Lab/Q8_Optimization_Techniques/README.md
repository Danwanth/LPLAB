# Q8: Basic Optimization Techniques

Single program that applies all three optimizations **in sequence** on the same TAC array.

## How It Works

### 1. Parsing
```c
int count = sscanf(line, "%s = %s %s %s", lhs[i], op1[i], op[i], op2[i]);
```
- `t1 = 2 + 3` → count=4: `lhs="t1"`, `op1="2"`, `op="+"`, `op2="3"`
- `t3 = t2` → count=3: `lhs="t3"`, `op1="t2"`, `op=""`, `op2=""`

### 2. Constant Folding
If **both operands are numbers**, compute the result and collapse:
```
t1 = 2 + 3  →  op1 becomes "5", op and op2 become ""  →  t1 = 5
```

### 3. Copy Propagation
Finds copies (`op==""` and `op1` is not a constant, e.g. `t2 = t1`). Replaces all later uses of `lhs` with `op1`:
```
t2 = t1          ← copy detected
t3 = t2 * c      → t3 = t1 * c   (t2 replaced with t1)
```

### 4. Dead Code Elimination
Checks if each statement's `lhs` appears in any later statement's operands. If not → removed. Last statement is always kept.
```
t2 = c + d       ← t2 never used later → REMOVED
```

### Why This Order?
1. **Constant folding first** → `t1 = 2+3` becomes `t1 = 5`
2. **Copy propagation second** → propagates simplified values forward
3. **Dead code last** → after propagation, unused assignments get removed

## How to Compile & Run

```bash
gcc program.c -o program
./program
```
