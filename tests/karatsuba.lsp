(defglobal a (expt 8 70000))
(defglobal b (expt 9 70000))


(defun bigtest0 (n)
    (if (= n 0)
        t
        (progn (eisl-test a b) (bigtest0 (- n 1)))))


(defun bigtest1 (n)
    (if (= n 0)
        t
        (progn (* a b) (bigtest1 (- n 1)))))