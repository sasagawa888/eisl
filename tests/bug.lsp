
(defmodule foo

(defun opcode (op)
        (case op
           ((+) '+)
           ((-) '-)
           ((/) '/)
           ((*) '*)
           ((^) '^)
           (t (if (subrp op)
                  op
                  (error "opecode else: " op))) ))

)