# Day 11 – Question 12: Pass II of a Two-Pass Assembler

## Question

Implement Pass-II of a two-pass assembler to produce final machine code using the symbol table and intermediate file. (C01)

---

## What Pass II Does

Pass II reads the **intermediate file** and **symbol table** produced by Pass I, then generates the final **object code** in SIC (Simplified Instructional Computer) format.

It prints three types of records:
- **H** — Header record (program name, start address, length)
- **T** — Text record (the actual machine code bytes)
- **E** — End record (execution start address)

---

## Files

| File | Role |
|---|---|
| `intermediate.txt` | Input: every line with its address, from Pass I |
| `symtab.txt` | Input: label → address mappings, from Pass I |

Both files are produced by running Pass I (`1.c`) first.

---

## Opcode Table (hardcoded in the program)

| Mnemonic | Machine Code |
|---|---|
| LDA  | 00 |
| ADD  | 18 |
| SUB  | 1C |
| STA  | 0C |
| RSUB | 4C |

---

## Object Code Format

### Header Record
```
H^ProgramName^StartAddress^ProgramLength
```
Example: `H^COPY^001000^00001C`

### Text Record
```
T^StartAddress^Length^ObjCode1^ObjCode2^...
```
Each object code entry is **6 hex digits**: 2 for the opcode + 4 for the operand address.

Example: `T^001000^13^001000^180000^...`

### End Record
```
E^ExecutionStartAddress
```
Example: `E^001000`

---

## How Object Code is Generated

For each line in the intermediate file:

1. **Normal instruction** (e.g., `LDA ALPHA`):
   - Look up `LDA` in the opcode table → get `00`
   - Look up `ALPHA` in the symbol table → get address `100F`
   - Combine → `00100F`

2. **BYTE directive** (e.g., `BYTE C'ALAN'`):
   - Convert each character to its ASCII hex value
   - `A=41`, `L=4C`, `A=41`, `N=4E` → `414C414E`

3. **WORD directive** (e.g., `WORD 5`):
   - Convert the integer to a 6-digit hex value
   - `5` → `000005`

4. **RESB / RESW** — these reserve space, no object code is generated.

---

## Code Walkthrough

```c
// 1. Load symbol table from symtab.txt into arrays
while (fscanf(fsym, "%d %s %x", ...) != EOF)
    sym_count++;

// 2. Read START line → get program name and start address
if (strcmp(opcode, "START") == 0) {
    start = strtol(operand, NULL, 16);
    strcpy(progname, label);
}

// 3. Print Header record
printf("H^%s^%06X^00001C\n", progname, start);
printf("T^%06X^13^", start);

// 4. Loop until END
while (strcmp(opcode, "END") != 0) {

    // Check if opcode is in optab
    for i in 0..OPTAB_SIZE:
        if opcode matches optab_mnem[i]:
            find operand in symtab → get address
            print  opcode_code + address

    // Handle BYTE → print ASCII hex of each character
    if BYTE:  for each char in string → printf("%02X", char)

    // Handle WORD → print integer as 6-digit hex
    if WORD:  printf("%06X", value)
}

// 5. Print End record
printf("E^%06X\n", start);
```

---

## Sample Output

```
H^COPY^001000^00001C
T^001000^13^001000^181013^1C1015^0C1018^4C0000^414C414E^000005^
E^001000
```

Each caret `^` separates fields/object code entries in SIC object program format.

---

## How to Run (both passes)

```bash
# Compile
gcc 1.c -o pass1
gcc 2.c -o pass2

# Run Pass I first (creates intermediate.txt and symtab.txt)
./pass1

# Then run Pass II (reads those files and prints object code)
./pass2
```
