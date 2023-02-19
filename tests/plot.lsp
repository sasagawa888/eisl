#| 
for gnuplot
|#


(c-include  "<stdio.h>")

(defun send-plot (msg)
    (c-lang "FILE *gp;")
    (c-lang "gp = popen(\"gnuplot -persist\",\"w\");")
    (c-lang "fprintf(gp, \"%s\\n\", Fgetname(MSG));")
    (c-lang "pclose(gp);")
    t)

