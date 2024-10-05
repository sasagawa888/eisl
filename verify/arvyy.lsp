(import "test")

($ap 1 "Arvyy")

(defmacro m1 (a)
  `(defmacro m2 (b)
      `(list ,,a ,b)))

(m1 1)
($assert (m2 2) (list 1 2))

($test (convert 97.0 <string>) "97.0")

(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (foo1)
        ($assert t nil)))
