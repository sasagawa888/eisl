# Class Name: <rational>
written by M Hiroi.
Thank you.

# Constructor:
    - make-ratio integer integer => rat  
      - `rat` is an object of <rational>.
      - `rat` can also be created using arithmetic operators (`op integer integer`).

# Accessors:
    - numerator rat => integer: Returns the numerator.
    - denominator rat => integer: Returns the denominator.

# Arithmetic Operators (Arguments `a` and `b` are `rat` or `integer`):
    - +/ a b => rat: Addition.
    - -/ a b => rat: Subtraction.
    - */ a b => rat: Multiplication.
    - // a b => rat: Division.
    - inv a => rat: Reciprocal (1/a).

# Comparison Operators (Arguments `a` and `b` are `rat`):
    - =/ a b => t or nil: Returns `t` if `a = b`.
    - /=/ a b => t or nil: Returns `t` if `a ≠ b`.
    - </ a b => t or nil: Returns `t` if `a < b`.
    - <=/ a b => t or nil: Returns `t` if `a ≤ b`.
    - >/ a b => t or nil: Returns `t` if `a > b`.
    - >=/ a b => t or nil: Returns `t` if `a ≥ b`.

# Other Functions:
    - rationalp obj => t or nil: Returns `t` if `obj` is a `rat`.
    - is-integer rat => t or nil: Returns `t` if `rat` is an integer (denominator is 1).
    - to-integer rat => integer: Returns `(div (numerator rat) (denominator rat))`.
    - to-float rat => integer: Returns `(quotient (numerator rat) (denominator rat))`.
    - to-string rat => string: Returns a string representation of the numerator/denominator.
    - display/ rat => nil: Outputs the numerator/denominator to the screen.
    - repeat-decimal rat => list: Converts the rational number into a repeating decimal.
        - The first element of the list represents the initial decimal part as a list.
        - The second element represents the repeating part as a list.
    - from-repeat-decimal xs ys => rat: Converts a repeating decimal into a rational number.

# License: The MIT License

# Example


```
> (import "rational")
T
> (defglobal a (// 1 2))
A
> (display/ a)
1/2NIL
> (rationalp a)
T
> (to-string a)
"1/2"
> (defglobal b (// 1 3))
B
> (display/ b)
1/3NIL
> (display/ (+/ a b))
5/6NIL
> (display/ (-/ a b))
1/6NIL
> (display/ (-/ b a))
-1/6NIL
> (display/ (*/ a b))
1/6NIL
> (display/ (// a b))
3/2NIL
> (display/ (// b a))
2/3NIL

> (=/ a b)
NIL
> (=/ a a)
T
> (/=/ a b)
T
> (/=/ a a)
NIL
> (</ a b)
NIL
> (</ b a)
T
> (>/ a b)
T
> (>/ b a)
NIL

> (is-integer a)
NIL
> (is-integer (+/ a a))
T
> (to-integer (+/ a a))
1
> (to-integer (+/ a b))
0
> (to-integer (// a b))
1
> (to-float (+/ a b))
0.833333
> (to-float (// a b))
1.5

> (repeat-decimal (// 1 2))
((0 5) (0))
> (repeat-decimal (// 1 3))
((0) (3))
> (repeat-decimal (// 1 7))
((0) (1 4 2 8 5 7))
> (repeat-decimal (// 355 113))
((3) (1 4 1 5 9 2 9 2 0 3 5 3 9 8 2 3 0 0 8 8 4 9 5 5 7 5 2 2 1 2 3 8 9 3 8 0 5 
3 0 9 7 3 4 5 1 3 2 7 4 3 3 6 2 8 3 1 8 5 8 4 0 7 0 7 9 6 4 6 0 1 7 6 9 9 1 1 5 
0 4 4 2 4 7 7 8 7 6 1 0 6 1 9 4 6 9 0 2 6 5 4 8 6 7 2 5 6 6 3 7 1 6 8))
> (display/ (apply #'from-repeat-decimal (repeat-decimal (// 1 2))))
1/2NIL
> (display/ (apply #'from-repeat-decimal (repeat-decimal (// 1 3))))
1/3NIL
> (display/ (apply #'from-repeat-decimal (repeat-decimal (// 1 7))))
1/7NIL
> (display/ (apply #'from-repeat-decimal (repeat-decimal (// 355 113))))
355/113NIL


```