;; optimized takeuchi function in SBCL
(declaim (ftype (function (fixnum fixnum fixnum) fixnum) tarai))
(defun tarai(x y z)
  (declare (optimize (speed 3) (debug 0) (safety 0))
    (type fixnum x)(type fixnum y)(type fixnum z))
  (if (<= x y)
      y
      (tarai (tarai (- x 1) y z)
             (tarai (- y 1) z x)
             (tarai (- z 1) x y))))