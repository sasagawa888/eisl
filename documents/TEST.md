# Test 
Simple macro for unit testing.

# Usage

```lisp
(import "test")
```

# Specification

```lisp
($test-assert test-expression expected-value [pred-function])
```
Compares the evaluated values of `test-expression` and `expected-value`.
If the comparison fails, an error message is printed.
An optional `pred-function` can be used to specify how to compare the values e.g. `eq`, `=`, `eql`, ...
The `equal` function is used for comparison by default.

```lisp
($test test-expression expected-value [pred-function])
```
Compares the evaluated value of `test-expression` and the quoted value of `expected-value`.
If the comparison fails, an error message is printed.
An optional `pred-function` can be used to specify how to compare the values e.g. `eq`, `=`, `eql`, ...
The `equal` function is used for comparison by default.



```lisp
($eval form)
```
Evaluate form. Ignore top level check. 

```lisp
($error form error-class)
```
Error check. Error class of form is error-class?

```lisp
($error1 form error-class)
```
Error check. Error class of form is error-class? Not ignore top-level check.
