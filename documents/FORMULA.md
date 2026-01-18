# Formula

**Formula** is a translator between **infix notation** and **prefix notation (S-expression)** for **ISLisp**.

It supports:

- infix → prefix translation  
- prefix → infix translation  
- optional evaluation of translated expressions  

This library is written by **Dr. Shimoji**.  
The code is used with the kind permission of Dr. Shimoji.

---

## Acknowledgments

Special thanks to **Dr. Shimoji** for providing this elegant and practical implementation.

---

## Important Notes

- This library follows **ISLisp arithmetic semantics**.
- In ISLisp, the operator `/` performs **integer division** and is equivalent to `quotient`.
- This is **not a rational-number arithmetic system**.

---

## Usage

```lisp
(import "formula")

Functions
Function	Description
(formula x)	Translate an infix S-expression to prefix notation and evaluate it
(infix->prefix x)	Translate an infix S-expression to prefix notation
(prefix->infix x)	Translate a prefix S-expression to infix notation
(formulas x)	Translate an infix string to prefix notation and evaluate it
(string->infix x)	Translate an infix string to an infix S-expression
(infix->string x)	Translate an infix S-expression to an infix string
Operators

Arithmetic operators follow ISLisp semantics.
Arithmetic
Operator	Meaning
+	addition
-	subtraction
*	multiplication
/	integer division (quotient)
^	exponentiation (expt)
Comparison
Operator	Meaning
=	numeric equal
>	greater than
<	less than
>=	greater than or equal
<=	less than or equal
Examples

> (import "formula")
T

Infix S-expression

> (formula 2 ^ 3 + 3 * 4 + 1)
21

> (infix->prefix '(1 + 2))
(+ 1 2)

> (prefix->infix '(+ 1 2))
(1 + 2)

Infix String

> (formulas "2^3+3*4+1")
21

> (string->infix "2^3+3*4+1")
(2 ^ 3 + 3 * 4 + 1)

> (infix->prefix (string->infix "2^3+3*4+1"))
(+ (+ (EXPT 2 3) (* 3 4)) 1)

Function Calls

> (string->infix "expt(2,3)+sin(0)")
((EXPT 2 3) + (SIN 0))

> (infix->prefix (string->infix "expt(2,3)+sin(0)"))
(+ (EXPT 2 3) (SIN 0))

Lexical Variables

Lexical variables are correctly handled during evaluation.

> (let ((a 2)) (formulas "a^3"))
8

Design Philosophy

    Infix notation is translated, not embedded, into Lisp.

    All expressions are converted into proper S-expressions before evaluation.

    Translation and evaluation are intentionally separated.

    This preserves Lisp’s structural clarity while improving mathematical readability.

Recommended Usage

    Use infix->prefix or string->infix when inspection or safety is required.

    Use formula / formulas for interactive REPL experiments.