## Parse Table

### Grammar

```bash
# tiger-program
1: <tiger-program> -> let <declaration-segment> in <stat-seq> end

# declaration-segment
2: <declaration-segment> -> <type-declaration-list> <var-declaration-list> <funct-declaration-list>

3: <type-declaration-list> -> <type-declaration> <type-declaration-list>
4: <type-declaration-list> -> NULL
5: <var-declaration-list> -> <var-declaration> <var-declaration-list>
6: <var-declaration-list> -> NULL
7: <funct-declaration-list> -> <funct-declaration> <funct-declaration-list>
8: <funct-declaration-list> -> NULL

# type-declaration
9: <type-declaration> -> type id = <type>;
10: <type> -> <type-id>
11: <type> -> array [INTLIT] of <type-id>
12: <type> -> id

13: <type-id> -> int
14: <type-id> -> float

# var-declaration
15: <var-declaration> -> var <id-list> : <type> <optional-init>;
16: <id-list> -> id <id-list-tail>
17: <id-list-tail> -> , id <id-list-tail>
18: <id-list-tail> -> NULL
19: <optional-init> -> := <const>
20: <optional-init> -> NULL

# funct-declaration
21: <funct-declaration> -> function id (<param-list>) <ret-type> begin <stat-seq> end;
22: <param-list> -> <param> <param-list-tail>
23: <param-list> -> NULL
24: <param-list-tail> -> , <param> <param-list-tail>
25: <param-list-tail> -> NULL
26: <ret-type> -> : <type>
27: <ret-type> -> NULL
28: <param> -> id : <type>

# stat-seq
29: <stat-seq> -> <stat> <stat-seq-tail>
30: <stat-seq-tail> -> <stat> <stat-seq-tail>
31: <stat-seq-tail> -> NULL

# stat
32: <stat> -> if <expr> then <stat-seq> <stat-if-tail>
33: <stat-if-tail> -> else <stat-seq> endif;
34: <stat-if-tail> -> endif;

35: <stat> -> id <stat-funct-or-assign>
36: <stat-funct-or-assign> -> <lvalue-tail> := <stat-assign>;
37: <stat-funct-or-assign> -> (<expr-list>);

38: <stat-assign> -> id <stat-assign-stuff>
39: <stat-assign> -> (<expr>) <stat-assign-tail>
40: <stat-assign> -> <const> <stat-assign-tail>

41: <stat-assign-stuff> -> (<expr-list>)
42: <stat-assign-stuff> -> <lvalue-tail> <stat-assign-tail>

43: <stat-assign-tail> -> <OR-op> <OR-expr> <stat-assign-tail>
44: <stat-assign-tail> -> <AND-op> <AND-expr> <stat-assign-tail>
45: <stat-assign-tail> -> <compare-op> <compare> <stat-assign-tail>
46: <stat-assign-tail> -> <add-op> <term> <compare-tail> <stat-assign-tail>
47: <stat-assign-tail> -> <mul-op> <factor> <stat-assign-tail>
48: <stat-assign-tail> -> NULL

49: <stat> -> while <expr> do <stat-seq> enddo;
50: <stat> -> for id := <expr> to <expr> do <stat-seq> enddo;


51: <stat> -> break;
52: <stat> -> return <expr>;

53: <stat> -> let <declaration-segment> in <stat-seq> end

# expr
54: <expr> -> <OR-expr> <stat-assign-tail>
55: <OR-expr> -> <AND-expr> <stat-assign-tail>
56: <AND-expr> -> <compare> <stat-assign-tail>
57: <compare> -> <term> <stat-assign-tail>
58: <term> -> <factor> <stat-assign-tail>


59: <factor> -> (<expr>)
60: <factor> -> <const>
61: <factor> -> <lvalue>

# const
62: <const> -> INTLIT
63: <const> -> FLOATLIT

# binary-operator
64: <OR-op> -> |
65: <AND-op> -> &
66: <compare-op> -> <=
67: <compare-op> -> >=
68: <compare-op> -> <
69: <compare-op> -> >
70: <compare-op> -> <>
71: <compare-op> -> =
72: <add-op> -> -
73: <add-op> -> +
74: <mul-op> -> /
75: <mul-op> -> *

76: <expr-list> -> NULL
77: <expr-list> -> <expr> <expr-list-tail>
78: <expr-list-tail> -> , <expr> <expr-list-tail>
79: <expr-list-tail> -> NULL

80: <lvalue> -> id <lvalue-tail>
81: <lvalue-tail> -> [<expr>]
82: <lvalue-tail> -> NULL
```


```bash

|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|----|----|---|---|----|--------|--------|
|   M[N][T]              |array| id |break| do | else | end | for |function| if | in | let | of | then | to | type | int |float| var |while|endif|begin| end | enddo |return| , | : | ; | ( | ) | [ | ] | { | } | + | - | * | / | = | < | > |   <>  | <= | >= | & | | | := | INTLIT |FLOATLIT|
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<tiger-program>         |     |    |     |    |      |     |     |        |    |    |  1  |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<declaration-segment>   |     |    |     |    |      |     |     |    2   |    | 2  |     |    |      |    |   2  |     |     |  2  |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<type-declaration-list> |     |    |     |    |      |     |     |    4   |    | 4  |     |    |      |    |   3  |     |     |  4  |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<var-declaration-list>  |     |    |     |    |      |     |     |    6   |    | 6  |     |    |      |    |      |     |     |  5  |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<funct-declaration-list>|     |    |     |    |      |     |     |    7   |    | 8  |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<type-declaration>      |     |    |     |    |      |     |     |        |    |    |     |    |      |    |   9  |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<type>                  | 11  | 12 |     |    |      |     |     |        |    |    |     |    |      |    |      | 10  |  10 |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<type-id>               |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      | 13  |  14 |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<var-declaration>       |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |  15 |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<id-list>               |     | 16 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<id-list-tail>          |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      | 17| 18|   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<optional-init>         |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   | 20|   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   | 19 |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<funct-declaration>     |     |    |     |    |      |     |     |   21   |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<param-list>            |     | 22 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   | 23|   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<param-list-tail>       |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      | 24|   |   |   | 25|   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<ret-type>              |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |  27 |     |       |      |   | 26|   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<param>                 |     | 28 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-seq>              |     | 29 |  29 |    |      |     |  29 |        | 29 |    |  29 |    |      |    |      |     |     |     |  29 |     |     |     |       |  29  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-seq-tail>         |     | 30 |  30 |    |  31  |  31 |  30 |        | 30 |    |  30 |    |      |    |      |     |     |     |  30 |  31 |     |     |   31  |  30  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat>                  |     | 35 |  51 |    |      |     |  50 |        | 32 |    |  53 |    |      |    |      |     |     |     |  49 |     |     |     |       |  52  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-if-tail>          |     |    |     |    |  33  |     |     |        |    |    |     |    |      |    |      |     |     |     |     |  34 |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-funct-or-assign>  |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 37|   | 36|   |   |   |   |   |   |   |   |   |   |       |    |    |   |   | 36 |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-assign>           |     | 38 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 39|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   40   |   40   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-assign-stuff>     |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   | 42| 41|   | 42|   |   |   | 42| 42| 42| 42| 42| 42| 42|   42  |  42|  42| 42| 42|    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<stat-assign-tail>      |     |    |     | 48 |      |     |     |        |    |    |     |    |  48  | 48 |      |     |     |     |     |     |     |     |       |      | 48|   | 48|   | 48|   | 48|   |   | 46| 46| 47| 47| 45| 45| 45|   45  |  45|  45| 44| 43|    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<expr>                  |     | 54 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 54|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   54   |   54   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<OR-expr>               |     | 55 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 55|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   55   |   55   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<AND-expr>              |     | 56 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 56|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   56   |   56   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<compare>               |     | 57 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 57|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   57   |   57   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<term>                  |     | 58 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 58|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   58   |   58   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<factor>                |     | 61 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 59|   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   60   |   60   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<const>                 |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |   62   |   63   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<OR-op>                 |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   | 64|    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<AND-op>                |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    | 65|   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<compare-op>            |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   | 71| 68| 69|   70  |  66| 67 |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<add-op>                |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   | 73| 72|   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<mul-op>                |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   | 75| 74|   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<expr-list>             |     | 77 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   | 77| 76|   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |    77  |   77   |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<expr-list-tail>        |     |    |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      | 78|   |   |   | 79|   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<lvalue>                |     | 80 |     |    |      |     |     |        |    |    |     |    |      |    |      |     |     |     |     |     |     |     |       |      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |    |   |   |    |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|
|<lvalue-tail>           |     |    |     | 82 |      |     |     |        |    |    |     |    |  82  | 82 |      |     |     |     |     |     |     |     |       |      | 82|   | 82|   | 82| 81| 82|   |   | 82| 82| 82| 82| 82| 82| 82|   82  |  82|  82| 82| 82| 82 |        |        |
|------------------------|-----|----|-----|----|------|-----|-----|--------|----|----|-----|----|------|----|------|-----|-----|-----|-----|-----|-----|-----|-------|------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|-------|----|----|---|---|----|--------|--------|

```