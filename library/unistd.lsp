(c-include "<unistd.h>")

(defun sleep (delay-seconds)
  (c-lang "res = sleep(DELAY_SECONDS & INT_MASK) | INT_FLAG;"))
