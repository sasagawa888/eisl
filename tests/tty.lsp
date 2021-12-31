(defun foo ()
    (system "stty raw -echo")
    (for ((i 0 (+ i 1)))
         ((> i 10) t)
         (print (read-char)))
    (system "stty -raw echo"))

