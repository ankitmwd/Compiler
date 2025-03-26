# MyCompiler

## Overview
MyCompiler is a simple programming language with its own syntax and parser. This project includes tokenization, parsing, and evaluation of expressions based on a well-defined grammar. The compiler supports variable assignments, conditional statements, and arithmetic operations. Additionally, the compiler also generates assembly code.

## Features
- Variable declaration and assignment (`let ident = Expr;`)
- Arithmetic operations (`+`, `-`, `*`, `/`)
- Conditional statements (`if`, `elif`, `else`)
- Scope handling with `{}` blocks
- Program termination with `exit(Expr);`
- Multiple line comments ( /* comment */ )
- Single line comments ( // comment )


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
├── 📄 generation         # Generating Assembly code

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

## Compilation and Execution
To compile and run your Hydro Compiler project, follow these steps:

### 1. Prerequisites
Ensure you have the following installed on your system:
- CMake (version 3.10 or higher)
- GCC or Clang (C++ compiler)
- NASM (Netwide Assembler)
- LD (GNU Linker)

### 2. Setup Instructions
#### Step 1: Create a Build Directory
Organize the build files by creating a separate directory:
```
mkdir build
```

#### Step 2: Generate Build Files with CMake
Run the following command to generate the necessary build files:
```
cmake -S . -B build/
```

#### Step 3: Compile the Project
Build the project using CMake:
```
cmake --build build/
```

### 3. Running the Compiler
#### Step 1: Create a Test File
Create a file named `test.hy` in the root directory of your project and add the following:
```
let y = (10 - 2 * 3) / 2;
let x = 3; // first
// first
if (1) {
    x = 1;
} elif (0) {
    x = 2;
} else {
    x = 3;
}

exit(x);

/*
exit(4);
*/

```

## Contribution
Feel free to contribute by submitting issues or pull requests!





##MIND MAP
![Screenshot from 2025-03-26 22-57-52](https://github.com/user-attachments/assets/96eb22ba-dc53-4f8a-bd59-839d659ab14a)

