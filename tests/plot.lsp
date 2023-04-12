(import "plot")

(defun foo ()
    (open-plot)
    (send-plot "set title \"sin cos curve\"")
    (send-plot "set xlabel \"x\"")
    (send-plot "set ylabel \"y\"")
    (send-plot "set xtics 1")
    (send-plot "set ytics 0.5")
    (send-plot "plot sin(x),cos(x)")
    (close-plot))

