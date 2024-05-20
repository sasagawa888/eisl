;;multi-process

;(mp-create 5)
;(primep* 1000003)
(defun primep* (n)
    (if (= (mod n 2) 0)
        nil
        (mp-part (coprimep n 3 200)
                 (coprimep n 201 400)
                 (coprimep n 401 600)
                 (coprimep n 601 800)
                 (coprimep n 801 1000))))


(defun coprimep (n s e)
    (cond ((> s e) t)
          ((= (mod n s) 0) nil)
          (t (coprimep n (+ s 2) e))))

(defun primep (n)
    (cond ((= (mod n 2) 0) nil)
          (t (coprimep n 3 (sqrt n)))))

