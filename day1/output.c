1: #include <stdio.h> 
2: int is_space(char c) { 
3: return c==' ' || c=='\t' || c=='\n' || c=='\r'; 
4: } 
5: int main() { 
6: FILE *f = fopen("source.c", "r"); 
7: if (!f) return 1; 
8: FILE *fw = fopen("output.c", "w"); 
9: if (!fw) { fclose(f); return 1; } 
10: int c, nc; 
11: int in_sl = 0; 
12: int in_ml = 0; 
13: int last_space = 0; 
14: int printed = 0; 
15: int ln = 1; 
16: printf("%d: ", ln); 
17: fprintf(fw, "%d: ", ln); 
18: while ((c = fgetc(f)) != EOF) { 
19: if (!in_ml && !in_sl && c=='/') { 
20: nc = fgetc(f); 
21: if (nc=='/') { in_sl = 1; continue; } 
22: if (nc=='*') { in_ml = 1; continue; } 
23: putchar(c); 
24: fputc(c, fw); 
25: c = nc; 
26: } 
27: if (in_sl && c=='\n') { 
28: in_sl = 0; 
29: if (printed) { 
30: putchar('\n'); 
31: fputc('\n', fw); 
32: ln++; 
33: printf("%d: ", ln); 
34: fprintf(fw, "%d: ", ln); 
35: printed = 0; 
36: } 
37: continue; 
38: } 
39: if (in_ml && c=='*') { 
40: nc = fgetc(f); 
41: if (nc=='/') { in_ml = 0; continue; } 
42: c = nc; 
43: } 
44: if (in_sl || in_ml) continue; 
45: if (is_space(c)) { 
46: if (!last_space && printed) { 
47: putchar(' '); 
48: fputc(' ', fw); 
49: last_space = 1; 
50: } 
51: if (c=='\n') { 
52: if (printed) { 
53: putchar('\n'); 
54: fputc('\n', fw); 
55: ln++; 
56: printf("%d: ", ln); 
57: fprintf(fw, "%d: ", ln); 
58: printed = 0; 
59: } 
60: } 
61: continue; 
62: } 
63: last_space = 0; 
64: printed = 1; 
65: putchar(c); 
66: fputc(c, fw); 
67: } 
68: fclose(f); 
69: fclose(fw); 
70: return 0; 
71: } 
72: 