;; macro for test

(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(let ((ans ,form1))
          (if (equal ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad, correct is ~A but got ~A ~%" ',form1 ',form2 ans)))
      `(let ((ans ,form1))
         (if (,@pred ans ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad correct is ~A but got ~A ~%" ',form1, ',form2 ans)))))
