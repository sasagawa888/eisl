# Test 

Simple macro for unit testing.

# Usage

```lisp
(import "test")
```

# Specification

```lisp
(test test-S-expression result-S-Expression)
```
If eval of test-S-expression is same as result-S-expression, nothing is printed.
If eval of test-S-expression is not same as result-S-expression, print a message.
The `equal` function is used for the judgment.

```lisp
(test test-S-expression result-S-Expression pred-function)
```
Pred-function is used for the judgment. e.g. eq, =, eql, etc.

# Code

See the following macro:

```lisp
(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(let ((ans ,form1))
          (if (equal ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1 ',form2 ans)))
      `(let ((ans ,form1))
         (if (,@pred ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1, ',form2 ans)))))
```
