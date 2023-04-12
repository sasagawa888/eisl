;; macro for test

(defmacro $test (form1 form2 :rest pred)
  (let ((test-predicate (if (null pred) '(equal) pred)))
      `(progn
          (eisl-ignore-toplevel-check t)
          (let ((ans ,form1))
            (if (,@test-predicate ans ',form2)
              (format (standard-output) "" ',form1)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1, ',form2 ans)))
          (eisl-ignore-toplevel-check nil)
      )))
          

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
      (let ((ans (catch 'c-parse-error
              (with-handler 
                (lambda (c) (throw 'c-parse-error c))
                ,form))))
          (if (equal (class-of ans) (class ,name))
              (format (standard-output) "" ',form)
              (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form (class ,name) (class-of ans))))))



(defmacro $ap (n name :rest page)
    (if (null page)
        `(format (standard-output) "~A ~A~%" ,n ,name)
        `(format (standard-output) "~A ~A ~A ~%",n ,name ',page)))


(defmacro $argc (x1 x2 x3 x4) `nil)
(defmacro $predicate (x1 x2 :rest x3) `nil)
(defmacro $type (x1 x2 x3 :rest x4) `nil)
(defmacro $stype (x1 x2 x3 :rest x4) `nil)
