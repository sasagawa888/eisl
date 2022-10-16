# Prolog library
under construction

# import
(import "prolog")

# usage as Prolog intepreter

## invoke 
```
> (prolog)
```

## builtin predicate

- (assert x)
- (consult filename)
- (reconsult filename)
- (load filename) load lisp code
- (halt)
- (is x y)
- (= x y)
- (== x y)
- (/= x y)
- (> x y)
- (>= x y)
- (< x y)
- (<= x y)
- (write x)
- (nl)
- (system x) call bash 
- (trace)
- (notrace)
- (defun ...)
- (defgeneric ...)
- (defmethod ...)
- (findall x y z)


# usage as embedded Prolog in Lisp

### assert
(assert predicate/clause)

### prove
(-? predicate)

### deref
(~? variable environment)