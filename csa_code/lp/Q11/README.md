# Day 10 – Question 11: Pass I of a Two-Pass Assembler

## Question

Implement Pass-I of a two-pass assembler by constructing a symbol table and generating an intermediate representation. (C01)

---

## What Pass I Does

Pass I reads the assembly source file and does two things:
1. Assigns a memory address (location counter) to every line of the program
2. Records every label and its address into a **symbol table**

It does NOT generate machine code — that is Pass II's job. Pass I just figures out *where* everything lives in memory.

---

## Files

| File | Role |
|---|---|
| `input.txt` | Source assembly program |
| `intermediate.txt` | Output: every line with its address and length |
| `symtab.txt` | Output: all labels with their hex addresses |

---

## Input Format (`input.txt`)

Each line has three fields: `LABEL  OPCODE  OPERAND`

Use `-` when a field is absent.

```
COPY   START  1000
FIRST  LDA    ALPHA
-      ADD    ONE
-      STA    BETA
ALPHA  BYTE   C'ALAN'
ONE    RESB   2
TWO    WORD   5
BETA   RESW   1
-      END    FIRST
```

---

## How the Location Counter Works

The location counter (`locctr`) starts at the value given by `START` (in hex).  
After each line, it advances by the size of that instruction or directive:

| Opcode | Bytes Added |
|---|---|
| Normal instruction (LDA, ADD, …) | 3 |
| `WORD` | 3 |
| `RESW n` | 3 × n |
| `RESB n` | n |
| `BYTE C'...'` | number of characters in the string |
| `BYTE X'...'` | 1 |

---

## Symbol Table

Every time a line has a label (anything other than `-`), the label and the **current value of locctr** are stored together.

Example from the sample input:

| # | Label | Address |
|---|---|---|
| 1 | FIRST | 1000 |
| 2 | ALPHA | 100F |
| 3 | ONE   | 1013 |
| 4 | TWO   | 1015 |
| 5 | BETA  | 1018 |

---

## Intermediate File Format

Each line written to `intermediate.txt`:

```
<address(hex)>  <length>  <label>  <opcode>  <operand>
```

Example output:
```
1000    0    COPY     START    1000
1000    3    FIRST    LDA      ALPHA
1003    3    -        ADD      ONE
1006    3    -        SUB      TWO
1009    3    -        STA      BETA
100C    3    -        RSUB     -
100F    4    ALPHA    BYTE     C'ALAN'
1013    2    ONE      RESB     2
1015    3    TWO      WORD     5
1018    3    BETA     RESW     1
101B    0    -        END      FIRST
```

---

## Code Walkthrough

```c
// 1. Open files
fin    = fopen("input.txt",        "r");
finter = fopen("intermediate.txt", "w");
fsym   = fopen("symtab.txt",       "w");

// 2. Read first line; if START → set locctr to that hex address
if (strcmp(opcode, "START") == 0) {
    start  = strtol(operand, NULL, 16);
    locctr = start;
    ...
}

// 3. Loop until END
while (strcmp(opcode, "END") != 0) {
    // Save label if present
    if (strcmp(label, "-") != 0) { ... sym_count++; }

    // Calculate length of this line
    if      (WORD)  len = 3;
    else if (RESW)  len = 3 * n;
    else if (RESB)  len = n;
    else if (BYTE)  len = characters in string;
    else            len = 3;

    // Write line to intermediate, advance locctr
    fprintf(finter, ...);
    locctr += len;
}

// 4. Write symbol table
for each symbol → fprintf(fsym, ...)
```

---

## Code Notes

### `%04X` — address formatting
All addresses are printed with `fprintf(finter, "%04X", locctr)`.  
- `X` → uppercase hex  
- `4` → minimum 4 digits wide  
- `0` → pad with leading zeros instead of spaces  

So `0x5` prints as `0005`, and `0xFF` prints as `00FF`.

### `BYTE` length calculation
```c
len = (operand[0] == 'C') ? strlen(operand) - 3 : 1;
```
`BYTE` has two forms:
- `C'HELLO'` — character constant: each character is 1 byte, so length = number of chars inside the quotes. `strlen` counts the whole string (e.g. `"C'EOF'"` = 6), minus 3 for the `C`, `'`, and closing `'` → **3 bytes**.
- `X'1F'` — hex constant: always **1 byte**, regardless of how many hex digits.

---

## Console Output

```
PASS 1 Completed Successfully
Program Length = 1B
```

Program length = `101B - 1000 = 1B` (hex).
