(import "plot")

(defun foo (msg)
    (open-plot)
    (set-title msg)
    (set-xlabel "xjiku")
    (set-ylabel "yjiku")
    (set-xtics 1)
    (set-ytics 0.5)
    (send-plot "plot sin(x)")
    (close-plot))

(defun set-title (x)
    (let ((stm (create-string-output-stream)))
        (format stm (string-append "set title \"" x "\""))
        (send-plot (get-output-stream-string stm))))

(defun set-xlabel (x)
    (let ((stm (create-string-output-stream)))
        (format stm (string-append "set xlabel \"" x "\""))
        (send-plot (get-output-stream-string stm))))

(defun set-ylabel (y)
    (let ((stm (create-string-output-stream)))
        (format stm (string-append "set ylabel \"" y "\""))
        (send-plot (get-output-stream-string stm))))

(defun set-xtics (x)
    (send-plot (string-append "set xtics " (convert x <string>))))

(defun set-ytics (y)
    (send-plot (string-append "set ytics " (convert y <string>))))