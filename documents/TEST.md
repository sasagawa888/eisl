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
Checks if the evaluated values of `test-expression` and `expected-value` are equal.
If they are not, an error message is printed.
An optional `pred-function` can be used to specify how to compare the values e.g. `eq`, `=`, `eql`, ...
The `equal` function is used for comparison by default.

```lisp
($test test-expression expected-value [pred-function])
```
Checks to see if the evaluated value of `test-expression` and the quoted value of `expected-value` are equal.
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
