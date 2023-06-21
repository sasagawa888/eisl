(defun test (x)
    (print "call test")
    (print x)
    (if (= x 0)
        0
        (funcall
         (lambda () 
            (print "call lambda")
            (print x)
            (test (- x 1))
            (print "exit lambda")
            (print x))))
    (print "exit test")
    (print x))

