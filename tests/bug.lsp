;;; bug copy GC
;(gbc 'copy)
(gbc t)
;;; (taxi 70)

(defun taxi (n)
  (for ((a 1 (+ a 1)))
       ((< n a))
       (for ((b a (+ b 1)))
            ((< n b))
            (for ((c (+ a 1) (+ c 1)))
                 ((< n c))
                 (for ((d c (+ d 1)))
                      ((<= b d))
                      (let ((e (+ (* a a a) (* b b b))))
                        (if (= (+ (* c c c) (* d d d)) e)
                            (format (standard-output) "~D: (~D, ~D), (~D,~D)~%" e a b c d))))))))


