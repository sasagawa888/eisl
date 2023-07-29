(c-include "<unistd.h>")

(defun sleep (delay-seconds)
  (c-lang "res = sleep(DELAY_SECONDS & INT_MASK) | INT_FLAG;"))

(defun usleep (delay-micro-seconds)
  (c-lang "res = usleep(DELAY_MICRO_SECONDS & INT_MASK) | INT_FLAG;"))

(defun core-count ()
  (c-lang "res = Fmakeint(sysconf(_SC_NPROCESSORS_CONF));"))