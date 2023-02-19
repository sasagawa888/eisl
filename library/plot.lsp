#| 
for gnuplot
|#


(c-include  "<stdio.h>")
(c-lang "FILE *gp;")

(defun open-plot ()
    (c-lang "gp = popen(\"gnuplot -persist\",\"w\");")
    t)

(defun send-plot (msg)
    (c-lang "fprintf(gp, \"%s\\n\", Fgetname(MSG));")
    t)

(defun close-plot ()    
    (c-lang "pclose(gp);")
    t)

