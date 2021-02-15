;; macro for test

(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(if (equal ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad ~A ~%" ',form1 ',form2))
      `(if (,@pred ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad ~A ~%" ',form1, ',form2))))
