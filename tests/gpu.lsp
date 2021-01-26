(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(if (equal ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))
      `(if (,@pred ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))))


(defglobal a #2f((1.0 2.0 3.0)(4.0 5.0 6.0)))

(defglobal b #2f((4.0 7.0)(5.0 8.0)(6.0 9.0)))

(test (gpu-mult a b) #2f((32.0 50.0) (77.0 122.0)))
(test (gpu-add b b) #2f((8.0 14.0) (10.0 16.0) (12.0 18.0)))
(test (gpu-sub b b) #2f((0.0 0.0) (0.0 0.0) (0.0 0.0)))
(test (gpu-smult 2.0 a) #2f((2.0 4.0 6.0) (8.0 10.0 12.0)))


(defglobal c (create-array '(30 30) 'rand 'float))

(defun test1 (n)
    (for ((i 0 (+ i 1)))
         ((> i n) t)
         (gpu-mult c c)))

(defglobal d (create-array '(3000 3000) 'rand 'float))

(defun test2 ()
    (gpu-mult d d))