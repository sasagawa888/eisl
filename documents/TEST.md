# Test 
Simple macro for code test

# Usage
(import "test")

# Specification
(test test-S-expression result-S-Expression)
If eval of test-S-expression is same as result-S-expression, no message
If eval of test-S-expression is not same as result-S-expression, print message 
The equal function is used for the judgment.

(test test-S-expression result-S-Expression pred-function)
Then pred-function is used for the judgment. e.g. eq, =, eql ...

# Code

see following macro code

```
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