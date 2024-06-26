### Description

Lexical tokenization is conversion of a text into (semantically or syntactically) meaningful lexical tokens belonging to categories defined by a lexer program. In case of a natural language, those categories include nouns, verbs, adjectives, punctuations etc. In case of a programming language, the categories include identifiers, operators, grouping symbols and data types.

### Examples

This is source code
```c
a : integer = 0
a := 0

b : integer
b := 0

defun foo (a:integer, b:integer):integer {

}
```

These are broken down tokens
```c
Token 0: a
Token 1: :
Token 2: integer
Token 3: =
Token 4: 0
Token 5: a
Token 6: :
Token 7: =
Token 8: 0
Token 9: b
Token 10: :
Token 11: integer
Token 12: b
Token 13: :
Token 14: =
Token 15: 0
Token 16: defun
Token 17: foo
Token 18: (
Token 19: a
Token 20: :
Token 21: integer
Token 22: ,
Token 23: b
Token 24: :
Token 25: integer
Token 26: )
Token 27: :
Token 28: integer
Token 29: {
Token 30: }
```


### Compilation Stages

**Preprocessing** — ✅ <br>
Input: Source Code <br>
Output: Modified Source Code

**Tokenization** — ✅ <br>
Input: Preprocessed Source Code <br>
Output: Stream of Tokens

(WIP)
**Syntax Analysis** <br>
Input: Tokens from Lexical Analysis (Tokenization) <br>
Output: AST 

(WIP)
**Semantic Analysis** <br>
Input: AST <br>
Output: Annotated AST with Semantic Information

(WIP)
**Intermediate Code Generation** <br>
Input: Annotated AST <br>
Output: IR

(WIP)
**Optimization** <br>
Input: IR <br>
Output: Optimized IR

(WIP)
**Code Generation** <br>
Input: Optimized IR <br>
Output: Machine Code or Assembly

**Linking** <br>
Input: Compiled Machine Code <br>
Output: Single Executable for Specific Architecture
