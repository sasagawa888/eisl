(import "macro")
;; macro for test

;;; $TEST checks if the evaluated value of FORM1 and the quoted FORM2 are equal.
;;; If they are not, an error message is printed
;;; PRED specifies the comparison function, which is EQUAL by default
(defmacro $test (form1 form2 :rest pred)
  `($assert ,form1 ',form2 ,@pred))

;;; $ASSERT checks if the evaluated value of FORM1 and the evaluated value of FORM2 are equal.
;;; If they are not, an error message is printed
;;; PRED specifies the comparison function, which is EQUAL by default
(defmacro $assert (form1 form2 :rest pred)
  (let ((test-predicate (if (null pred) '(equal) pred))
        (actual (gensym))
        (expected (gensym)))
      `(progn
          (eisl-ignore-toplevel-check t)
          (let ((,actual ,form1)
                (,expected ,form2))
            (if (,@test-predicate ,actual ,expected)
              (format (standard-output) "" ',form1)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1, ,expected ,actual)))
          (eisl-ignore-toplevel-check nil))))
          
;;; RECORD-OPERATION appends the given ORDER-IN-SEQUENCE value to the
;;; dynamic *operation-sequence* list, which serves as a record of the
;;; order in which operations occur.
(defun record-operation (order-in-sequence)
  (push-end order-in-sequence (dynamic *operation-sequence*)))

;;; $ASSERT-ORDERED-OPERATIONS evaluates the provided BODY forms, which
;;; may contain operation orders recorded by the RECORD-OPERATION function.
;;; After evaluating the BODY forms, it asserts that the recorded operations
;;; in the dynamic *operation-sequence* list match EXPECTED-SEQUENCE. 
(defmacro $assert-ordered-operations (expected-sequence &rest body)
  `(dynamic-let ((*operation-sequence* (list)))
                ,@body
                ($assert (dynamic *operation-sequence*) ,expected-sequence)))

(defmacro $eval (form)
  `(progn 
        (eisl-ignore-toplevel-check t)
        (eval ',form)
        (eisl-ignore-toplevel-check nil)))

(defmacro $error (form name)
  `(progn
      (eisl-ignore-toplevel-check t)
      (let ((ans (catch 'c-parse-error
              (with-handler 
                (lambda (c) (throw 'c-parse-error c))
                ,form))))
          (if (equal (class-of ans) (class ,name))
              (format (standard-output) "" ',form)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form (class ,name) (class-of ans))))
      (eisl-ignore-toplevel-check nil)))

(defmacro $error1 (form name)
  `(progn
      (eisl-ignore-toplevel-check 0)
      (let ((ans (catch 'c-parse-error
              (with-handler 
                (lambda (c) (throw 'c-parse-error c))
                ,form))))
          (if (equal (class-of ans) (class ,name))
              (format (standard-output) "" ',form)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form (class ,name) (class-of ans))))
      (eisl-ignore-toplevel-check nil)))        



(defmacro $ap (n name :rest page)
    (if (null page)
        `(format (standard-output) "~A ~A~%" ,n ,name)
        `(format (standard-output) "~A ~A ~A ~%",n ,name ',page)))


(defmacro $argc (x1 x2 x3 x4) `nil)
(defmacro $predicate (x1 x2 :rest x3) `nil)
(defmacro $type (x1 x2 x3 :rest x4) `nil)
(defmacro $stype (x1 x2 x3 :rest x4) `nil)
