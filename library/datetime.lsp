(c-include "<time.h>")

(defun get-decoded-time ()
  (c-lang "struct tm *jst;
          time_t t;")

  (c-lang "t = time (NULL);
           jst = localtime (&t);")

  (c-lang "res = Fcons(Fmakeint (jst->tm_year + 1900),
                 Fcons(Fmakeint (jst->tm_mon + 1),
                 Fcons(Fmakeint (jst->tm_mday),")
  (c-lang "Fcons(Fmakeint (jst->tm_hour),
	         Fcons(Fmakeint (jst->tm_min), 
                 Fcons(Fmakeint (jst->tm_sec),NIL))))));")
)

(defun weekday (y m d)
  (cond ((< m 3)
	  (setq y (- y 1))
          (setq m (+ m 12))))

  (mod (+ y (div y 4) (- (div y 100)) (div y 400) (div (+ (* 13 m) 8) 5) d) 7))
  ;(y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7

(defun sleep (delay-seconds)
  (c-lang "sleep(DELAY_SECONDS & INT_MASK);")
  t)
