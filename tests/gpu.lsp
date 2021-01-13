
(defglobal a #2f((1.0 2.0)(3.0 4.0)))

(defglobal b #2f((1.0 2.0)(3.0 4.0)))

(print (gpu-mult a b))
(print (gpu-add a b))

(defglobal c (create-array '(30 30) 1.0 t))

(defun test (n)
    (for ((i 0 (+ i 1)))
         ((> i n) t)
         (gpu-mult c c)))