# Subset ISLisp Interpreter (for Education)
source code ./example/edlisp.lsp

## Overview
This is a lightweight educational implementation of a subset of **ISLisp**.  
It is designed for learning purposes, with a simplified evaluator, support for global and dynamic variables, user-defined functions, and a set of built-in primitives and special forms.

## Features
- Separate namespaces for variables and functions (LISP2 model)
- Global and dynamic variables
- User-defined functions (`defun`)
- Built-in functions (e.g., `+`, `-`, `*`, `div`, `car`, `sin`, `cos`, etc.)
- Special forms:
  - `quote`
  - `setq`
  - `if`
  - `progn`
  - `defun`
  - `defglobal`
  - `defdynamic`
  - `cond`
  - `lambda`
  - `function`
  - `let`
  - `let*`

## How It Works
- The evaluator (`eval*`) recursively evaluates S-expressions.
- `apply*` handles special forms, built-in primitives, and user-defined functions.
- Variable binding is managed through local, global, and dynamic environments.
- Errors are handled with a simple mechanism that prints a message and exits the current REPL loop.

## Usage
Start the interpreter with:
```lisp
(islisp)

L> (defglobal x 10)
X
L> (defun square (n) (* n n))
SQUARE
L> (square x)
100
L> (quit)
```

# Educational Purpose
This subset interpreter is intended as a tool to understand:
- The basic structure of a Lisp evaluator
- The role of environments in variable/function lookup
- The mechanics of applying functions and handling special forms

It is not a complete ISLisp implementation, but rather a simplified core suitable for learning language processing and Lisp fundamentals.