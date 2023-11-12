#tiny-lexer

##What is compilation?

The compilation process transforms source code written in a high-level programming language into machine code that a computer's processor can execute. This process typically involves several stages, which will describe step-by-step here, focusing on a language like C.

##Compilation Steps

**Preprocessing** — ✅

Input: Source code files

Process: The preprocessor handles directives that begin with `#` in C, like `#include` or `#if`. That includes header files, macro expansions and conditional compilation

Output: A modified source code, with all preprocessor directives executed and expanded

**Tokenization** — ✅

Input: Preprocessed source code

Process: The lexer or tokenizer breaks the source code into tokens. Tokens are the fundamental elements like keywords, operators, identifiers, literals and etc.

Output: A stream of tokens *[in progress]*

**Syntax Analysis** — In Progress

Input: Tokens from Lexical Analysis

Process: The parser checks the syntax according to the language grammar rules and constructs a data structure, usually called an AST. The AST represents the hierarchical synctactic structure of the code.

Output: AST 

**Semantic Analysis**

Input: AST

Process: This stage involves checking for semantic errors, resolving variable and function references and type checking. It ensures that the code makes sense in the context of the language rules.

Output: Annotated AST with semantic information

**Intermediate Code Generation**

Input: Annotated AST

Process: The compiler generates an intermediate representation or IR of the source code. This IR is a lower-level representaion of the code, but is not yet machine code. It is more abstract than machine code, but more concrete than high-level code.

Output: IR, often in form like Three Address Code or TAC.

**Optimization**

Input: IR code

Proccess: The compiler optimizes the IR code to improve performance and reduce resource usage. Optimization can happen at multiple levels, like loop optimization or inlining the functions.

Outptu: Optimized IR code.

**Code Generation**

Input: Optimized IR code.

Process: This stage translates the IR code into machine code specific to the target platforms CPU architecture. This involves register allocation, instruction selection and other low-level details.

Output: Machine code or Assembly

**Linking**

Input: Compiled machine code files and libraries

Process: The linker combines the machine code from various files and libraries into a single executable file. It resolves references to external functions and variables across files.

Output: A single executable file that can be run on the specific machine architecture.