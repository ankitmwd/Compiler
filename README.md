# MyCompiler

## Overview
MyCompiler is a simple programming language with its own syntax and parser. This project includes tokenization, parsing, and evaluation of expressions based on a well-defined grammar. The compiler supports variable assignments, conditional statements, and arithmetic operations.

## Features
- Variable declaration and assignment (`let ident = Expr;`)
- Arithmetic operations (`+`, `-`, `*`, `/`)
- Conditional statements (`if`, `elif`, `else`)
- Scope handling with `{}` blocks
- Program termination with `exit(Expr);`

## Grammar
The language follows this formal grammar:
```
Prog      -> Stmt*
Stmt      -> exit(Expr);
          | let ident = Expr;
          | ident = Expr;
          | if (Expr) Scope IfPred
          | Scope
Scope     -> { Stmt* }
IfPred    -> elif (Expr) Scope IfPred | else Scope | ε
Expr      -> Term | BinExpr
BinExpr   -> Expr * Expr  (prec = 1)
          | Expr / Expr  (prec = 1)
          | Expr + Expr  (prec = 0)
          | Expr - Expr  (prec = 0)
Term      -> int_lit | ident | (Expr)
```

## File Structure
```
📂 MyCompiler
├── 📄 tokenization.hpp   # Tokenizer definitions
├── 📄 parser.hpp         # Parser implementation
├── 📄 main               # Entry point for execution
├── 📄 tokenization       # Tokenization logic
```

## Installation
```sh
git clone https://github.com/yourusername/MyCompiler.git
cd MyCompiler
make  # If a Makefile is provided
```

## Usage
To compile and run a source file:
```sh
./MyCompiler <source_file>
```

## Example Program
```c
let x = 10;
if (x > 5) {
    exit(x);
} else {
    exit(0);
}
```

## Contribution
Feel free to contribute by submitting issues or pull requests!

##MIND MAP
![Screenshot from 2025-03-26 22-57-52](https://github.com/user-attachments/assets/96eb22ba-dc53-4f8a-bd59-839d659ab14a)

