# Combination

Combination library.
This library was written by M. Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "combination")

```

# Specification
- selects xs => list
    Select element, store selected element in CAR, store remaining elements in CDR, store it in list and return
- permutation fn n xs => nil
    Generate a permutation that selects n elements from the list xs
- permutations n xs => list
    Generate a permutation that selects n elements from the list xs
- permutation-with-repetition fn n xs => nil
    Generate a permutations with n elements from the list xs
- permutations-with-repetition n xs => list
    Generate a permutations with n elements from the list xs
- combination-number n r
    Find the number of combinations nCr
- combination fn n xs => nil
    Generate a combination that selects n elements from the list xs
- combinations n xs => list
    Generate a combination that selects n elements from the list xs
- combination-with-repetition fn n xs => nil
    Generate duplicate combinations that select n elements from the list xs
- combinations-with-repetition n xs => list
    Generate duplicate combinations that select n elements from the list xs 

# Test cases

```lisp
(test (selects '(1 2 3)) ((1 2 3) (2 1 3) (3 1 2)))
(test (selects '(a b c d)) ((A B C D) (B A C D) (C A B D) (D A B C)))
(test (permutations 3 '(1 2 3)) ((1 2 3) (1 3 2) (2 1 3) (2 3 1) (3 1 2) (3 2 1)))
(test (permutations 3 '(a b c d))
    ((A B C) (A B D) (A C B) (A C D) (A D B) (A D C) (B A C) (B A D) 
    (B C A) (B C D) (B D A) (B D C) (C A B) (C A D) (C B A) (C B D) 
    (C D A) (C D B) (D A B) (D A C) (D B A) (D B C) (D C A) (D C B)))
(test (permutations-with-repetition 2 '(1 2 3))
    ((1 1) (1 2) (1 3) (2 1) (2 2) (2 3) (3 1) (3 2) (3 3)))
(test (permutations-with-repetition 2 '(a b c d))
    ((A A) (A B) (A C) (A D) (B A) (B B) (B C) (B D) (C A) (C B) (C C) (C D) (D A) (D B) (D C) (D D)))
(test (combination-number 4 2) 6)
(test (combination-number 5 3) 10)
(test (combination-number 100 50) 100891344545564193334812497256)
(test (combinations 2 '(1 2 3 4))
    ((1 2) (1 3) (1 4) (2 3) (2 4) (3 4)))
(test (combinations 3 '(a b c d e))
    ((A B C) (A B D) (A B E) (A C D) (A C E) (A D E) (B C D) (B C E) (B D E) (C D E)))
(test (combinations-with-repetition 2 '(1 2 3))
    ((1 1) (1 2) (1 3) (2 2) (2 3) (3 3)))
(test (combinations-with-repetition 3 '(a b c d))
    ((A A A) (A A B) (A A C) (A A D) (A B B) (A B C) (A B D) (A C C) (A C D) (A D D) 
     (B B B) (B B C) (B B D) (B C C) (B C D) (B D D) (C C C) (C C D) (C D D) (D D D)))    
```

Side effect functions example

```lisp
> (load "combination.lsp")
T
>(defun display (x) (format (standard-output) "~S~%" x))
DISPLAY


>(permutation #'display 3 '(1 2 3))
(1 2 3)
(1 3 2)
(2 1 3)
(2 3 1)
(3 1 2)
(3 2 1)
NIL
>(permutation #'display 2 '(a b c d))
(A B)
(A C)
(A D)
(B A)
(B C)
(B D)
(C A)
(C B)
(C D)
(D A)
(D B)
(D C)
NIL

>(permutation-with-repetition #'display 2 '(1 2 3))
(1 1)
(1 2)
(1 3)
(2 1)
(2 2)
(2 3)
(3 1)
(3 2)
(3 3)
NIL
>(permutation-with-repetition #'display 2 '(a b c d))
(A A)
(A B)
(A C)
(A D)
(B A)
(B B)
(B C)
(B D)
(C A)
(C B)
(C C)
(C D)
(D A)
(D B)
(D C)
(D D)
NIL

>(combination #'display 2 '(1 2 3 4))
(1 2)
(1 3)
(1 4)
(2 3)
(2 4)
(3 4)
NIL
>(combination #'display 3 '(a b c d e))
(A B C)
(A B D)
(A B E)
(A C D)
(A C E)
(A D E)
(B C D)
(B C E)
(B D E)
(C D E)
NIL

>(combination-with-repetition #'display 2 '(1 2 3))
(1 1)
(1 2)
(1 3)
(2 2)
(2 3)
(3 3)
NIL
>(combination-with-repetition #'display 3 '(a b c d))
(A A A)
(A A B)
(A A C)
(A A D)
(A B B)
(A B C)
(A B D)
(A C C)
(A C D)
(A D D)
(B B B)
(B B C)
(B B D)
(B C C)
(B C D)
(B D D)
(C C C)
(C C D)
(C D D)
(D D D)
NIL

```