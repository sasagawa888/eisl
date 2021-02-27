;; macro for test

(defmacro test (form1 form2 :rest pred)
  (if (null pred)
      `(let ((ans ,form1))
          (if (equal ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1 ',form2 ans)))
      `(let ((ans ,form1))
         (if (,@pred ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form1, ',form2 ans)))))

(defmacro $eval (form)
  `(eval ',form))

(defmacro $error (form name)
  `(let ((ans (catch 'c-parse-error
           (with-handler 
            (lambda (c) (throw 'c-parse-error c))
            ,form))))
      (if (equal (class-of ans) (class ,name))
          (format (standard-output) "" ',form)
          (format (standard-output) "~S is bad. correct is ~A but got ~A ~%" ',form (class ,name) (class-of ans)))))