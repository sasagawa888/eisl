#| 
for gnuplot
|#


(c-include  "<stdio.h>")
(c-lang "FILE *gp;")

(defun open-plot ()
    (c-lang "gp = popen(\"gnuplot -persist\",\"w\");")
    t)

(defun send-plot (msg)
     (let ((stm (create-string-output-stream)))
        (format stm msg)
        (send-plot1 (get-output-stream-string stm))
        t))

(defun send-plot1 (msg)
    (c-lang "fprintf(gp, \"%s\\n\", Fgetname(MSG));")
    (c-lang "fflush(gp);")
    t)

(defun close-plot ()    
    (c-lang "pclose(gp);")
    t)

