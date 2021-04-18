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

The pred-function is used for the judgment. e.g. eq, =, eql ...


($eval form)
Evaluate form. ignore top level check. 

($error form error-class)
error check. error class of form is same error-class?



# Code

see following macro code

```lisp
(defmacro test (form1 form2 :rest pred)
  (if (null pred)
      `(progn
          (ignore-toplevel-check t)
          (let ((ans ,form1))
            (if (equal ans ',form2)
              (format (standard-output) "" ',form1)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1 ',form2 ans)))
          (ignore-toplevel-check nil)
      )
      `(progn
          (ignore-toplevel-check t)
          (let ((ans ,form1))
            (if (,@pred ans ',form2)
              (format (standard-output) "" ',form1)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1, ',form2 ans)))
          (ignore-toplevel-check nil)
      )))
          

(defmacro $eval (form)
  `(progn 
        (ignore-toplevel-check t)
        (eval ',form)
        (ignore-toplevel-check nil)))
          

(defmacro $error (form name)
  `(progn
      (ignore-toplevel-check t)
      (let ((ans (catch 'c-parse-error
              (with-handler 
                (lambda (c) (throw 'c-parse-error c))
                ,form))))
          (if (equal (class-of ans) (class ,name))
              (format (standard-output) "" ',form)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form (class ,name) (class-of ans))))
      (ignore-toplevel-check nil)))


(defmacro $ap (n name :rest page)
    (if (null page)
        `(format (standard-output) "~A ~A~%" ,n ,name)
        `(format (standard-output) "~A ~A ~A ~%",n ,name ',page)))


(defmacro $argc (x1 x2 x3 x4) `nil)
(defmacro $predicate (x1 x2 :rest x3) `nil)
(defmacro $type (x1 x2 x3 :rest x4) `nil)
(defmacro $stype (x1 x2 x3 :rest x4) `nil)

```
