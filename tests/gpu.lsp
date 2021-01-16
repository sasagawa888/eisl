
(defglobal a #2f((1.0 2.0 3.0)(4.0 5.0 6.0)))

(defglobal b #2f((4.0 7.0)(5.0 8.0)(6.0 9.0)))

(print (gpu-mult a b))
(print (gpu-add a a))

(defglobal c (create-array '(30 30) 1.0 t))

(defun test (n)
    (for ((i 0 (+ i 1)))
         ((> i n) t)
         (gpu-mult c c)))