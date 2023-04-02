# Structure editor
Structure editor for Lisp

# Usage
(import "sedit")

# Example

```
Easy-ISLisp Ver2.87
> (defun foo (x) (+ x 1))
FOO
> (import "sedit")
T
> (editf 'foo)
* p
(DEFUN FOO ### ###)  [0]
* 3
* d
* p
(+ X 1)  [0]
* 2
* s 3
* p
(+ X 3)  [2]
* u
* p
(DEFUN FOO ### ###)  [3]
* (foo 1)
4
* (foo 10)
13
* h
q quit
h help
r move right
l move left
u move up
d move down
t move top
positive number move right n
negative number move left n
i insert s-exp at left side of index
a insert s-exp at right side of index
k kill s-exp at index
s replace s-exp at index
p print s-exp and index
(s-exp) eval s-exp and print it
* q
T
>
```

# Spec
## q quit
## h help
## r move right
## l move left
## u move up
## d move down
## t move top
## positive number move right n
## negative number move left n
## i insert s-exp at left side of index
## k kill s-exp at index
## s replace s-exp at index
## p print s-exp and index
## (s-exp) eval s-exp and print it
