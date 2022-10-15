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
- (system x)
- (trace)
- (notrace)
- (defun ...)
- (defgeneric ...)
- (defmethod ...)
- (findall x y z)


# usage as embedded Prolog in Lisp

### prove

(assert predicate/clause)

(-? predicate)

### deref
(~? variable environment)