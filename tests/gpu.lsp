(defmacro test (form1 form2 :rest pred)
    (if (null pred)
        `(if
          (equal ,form1 ',form2)
          (format (standard-output) "" ',form1)
          (format (standard-output) "~S is bad~%" ',form1))
        `(if
          (,@pred ,form1 ',form2)
          (format (standard-output) "" ',form1)
          (format (standard-output) "~S is bad~%" ',form1))))


(defglobal a #2f((1.0 2.0 3.0) (4.0 5.0 6.0)))
(defglobal b #2f((4.0 7.0) (5.0 8.0) (6.0 9.0)))
(defglobal c #2f((2.0 3.0) (4.0 5.0) (6.0 7.0)))
(test (gpu-mult a b) #2f((32.0 50.0) (77.0 122.0)))
(test (gpu-add b b) #2f((8.0 14.0) (10.0 16.0) (12.0 18.0)))
(test (gpu-sub b b) #2f((0.0 0.0) (0.0 0.0) (0.0 0.0)))
(test (gpu-smult 2.0 a) #2f((2.0 4.0 6.0) (8.0 10.0 12.0)))
(test (gpu-emult b c) #2f((8.0 21.0) (20.0 40.0) (36.0 63.0)))
(test (array-dimensions c) (3 2))

(defglobal z (create-array '(3000 3000) 'rand 'float))

(defun test1 ()
    (gpu-mult z z) )

(defun test2 (n)
  (for ((i n (- i 1)))
       ((< i 0) t)
       (test1)))

(defglobal m #2f((1.0 2.0) (3.0, 4.0)))
(defglobal m1 #2f((1.0 -2.0 3.0) (4.0 5.0 -6.0)))
(defglobal m2 #2f((1010.0 1000.0 990.0) (1010.0 1000.0 990.0)))
(defglobal m4 #2f((1.0 2.0 3.0) (2.0 3.0 1.2)))
(defglobal m5 #2f((1.1 2.9 2.0) (2.2 3.1 1.2)))
(test (gpu-emult m1 m1) #2f((1.0 4.0 9.0) (16.0 25.0 36.0)))
(test (gpu-sum m) 10.0)
(test (gpu-trace m) 5.0)
(test (gpu-ident 3) #2f((1.0 0.0 0.0) (0.0 1.0 0.0) (0.0 0.0 1.0)))
(test (gpu-transpose m1) #2f((1.0 4.0) (-2.0 5.0) (3.0 -6.0)))
(test (gpu-activate m2 'softmax)
#2f((0.9900544881820679 4.494840686675161e-05 2.040654534241071e-09) (0.9900544881820679 4.494840686675161e-05 2.040654534241071e-09)))
(test (gpu-loss m4 m5 'square) 0.4675000309944153)
(test (gpu-loss m4 m5 'cross) -4.678380012512207)

(format (standard-output) "All tests are done~%")


