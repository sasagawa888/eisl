# Formula

  translater from infix to prefix, from prefix to infix.

  Written by Dr. Shimoji.
  We will use the code with the permission of Dr. Shimoji. 

# Acknowledgments
Thank you Dr. Shimoji.

# Usage

```
(import "formula)
```

# Function

| Function                          | Description                                             |
| --------------------------------- | --------------------------------------------------------|
| (formula x)                       | Translate infix-notation to prefix-notation and eval it |
| (infix-prefix x)                  | Translate infix-notation sexp to prefix-notation        |
| (prefix->infix x)                 | Translate prefix-notation sexp to infix-notation        |
| (formulas x)                      | Translate infix-notation-string to prefix-notation and eval it |
| (string->infix x)                 | Translate infix-notation-strin to infix-notation s-expression  |
| (infix->string x)                 | Translate infix-notation-S-expression to infix-notation-string   |
| (/ x y)                           | (quotient x y)                                          |
| (^ x y)                           | (expt x y)                                              |


# Operator

- + plus
- - sub
- * multiple
- / divide
- ^ exponent
- = number-equal
- > greater
- < smaller
- >= equal-greater
- <= equal-smaller

# Example

```
> (import "formula")
T
> (formula 2 ^ 3 + 3 * 4 + 1)
21
> (infix->prefix '(1 + 2))
(+ 1 2)
> (prefix->infix '(+ 1 2))
(1 + 2)
> (formulas "2^3+3*4+1")
21
> (string->infix  "2^3+3*4+1")
(2 ^ 3 + 3 * 4 + 1)
> (infix->prefix (string->infix  "2^3+3*4+1"))
(+ (+ (EXPT 2 3) (* 3 4)) 1)
> (string->infix  "expt(2,3)+sin(0)")
((EXPT 2 3) + (SIN 0))
> (infix->prefix (string->infix  "expt(2,3)+sin(0)"))
(+ (EXPT 2 3) (SIN 0))
> (let ((a 2)) (formulas "a^3"))
8
```