# Chitin's omega
The eval function is extended to test the stopping probability (Ω) of Chitin' theory.

see The LIMITS of MATHEMATICS by Gregory J. Chitin.

# extended eval

(eval S-expression limit-time)

limit-time(integer)  micro seconds

If an integer is given to the second argument, the S-expression of the first argument is evaluated with that time as the limit.

If the calculation finishes within the time
Returns a list of the following three values:

(success value argument-of-calculation-process)

If the calculation did not finish within the time
Returns a list of the following three values:

(false value argument-of-calculation-process)

# example

```
> (eval '(fib 3) 100)
(SUCCESS 2 ((1) (2) (3)))
> (eval '(fib 10) 100)
(FALSE NIL ((3) (2) (1) (2) (3) (4) (5) (2) (1) (2) (3) (4) (1) (2) (3) (2) (1) (2) (3) (4) (5) (6) (7) (8) (9) (10)))

```