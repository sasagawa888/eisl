;;multi-process

;(mp-create 5)
;(primep* 100000000000031)
(defun primep* (n)
    (if (= (mod n 2) 0)
        nil
        (let* ((limit (isqrt n))
               (span (div limit 5)))
            (mp-part (coprimep n 3 span)
                     (coprimep n (near-odd span) (* 2 span ))
                     (coprimep n (near-odd (* 2 span)) (* 3 span))
                     (coprimep n (near-odd (* 3 span)) (* 4 span))
                     (coprimep n (near-odd (* 4 span)) limit)))))

(defun near-odd (n)
    (if (= (mod n 2) 0)
        (- n 1)
        n))


(defun coprimep (n s e)
    (cond ((> s e) t)
          ((= (mod n s) 0) nil)
          (t (coprimep n (+ s 2) e))))

(defun primep (n)
    (cond ((= (mod n 2) 0) nil)
          (t (coprimep n 3 (sqrt n)))))

