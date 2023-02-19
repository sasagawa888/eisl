(import "plot")

(defun foo (msg)
    (open-plot)
    (send-plot msg)
    (close-plot))