# Test 
Simple macro for unit testing.

# Usage

```lisp
(import "test")
```

# Specification

(**$assert** *test-expression* *expected-value* [*pred-function*])\
Checks if the evaluated values of `test-expression` and `expected-value` are equal.
If they are not, an error message is printed.
An optional `pred-function` can be used to specify how to compare the values e.g. `eq`, `=`, `eql`, ...
The `equal` function is used for comparison by default.

(**$test** *test-expression* <u>expected-value</u> [*pred-function*])\
Checks to see if the evaluated value of `test-expression` and the quoted value of `expected-value` are equal.
If the comparison fails, an error message is printed.
An optional `pred-function` can be used to specify how to compare the values e.g. `eq`, `=`, `eql`, ...
The `equal` function is used for comparison by default.

(**record-operation** *order-in-sequence*)\
Appends the given `order-in-sequence` value to the dynamic `*operation-sequence*` list, which serves as a record of the order in which operations occur.

(**$assert-ordered-operations** *expected-sequence* *body**)\
Evaluates the provided `body` forms, which may contain operation orders recorded by the `record-operation` function. After evaluating the `body` forms, it asserts that the recorded operations in the dynamic `*operation-sequence*` list match `expected-sequence`.

(**$eval** *form*)\
Evaluate form. Ignore top level check. 

(**$error** *form* *error-class*)\
Error check. Error class of form is error-class?

(**$error1** *form* *error-class*)\
Error check. Error class of form is error-class? Not ignore top-level check.
