(defmodule util
    (defclass <rect> () ((size :accessor rect-size :initarg size)))
    ;; complex-number
    (defclass <complex>
              ()
              ((r :accessor real-part :initform 0.0 :initarg r)
               (i :accessor imag-part :initform 0.0 :initarg i)))
    ;; ratinal-number
    (defclass <rational>
              ()
              ((n :accessor numerator :initform 0.0 :initarg n)
               (d :accessor denominator :initform 0.0 :initarg d)))
    (defun make-rectangler (r i)
        (create (class <complex>) 'r r 'i i))

    (defun make-rational (n d)
        (create (class <rational>) `n n `d d))

)
