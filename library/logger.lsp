(c-include "<syslog.h>")

(defconstant LOG_LOCAL0 #x80)
(defconstant LOG_PID #x01)
(defconstant LOG_ALERT 1)
(defconstant LOG_CRIT 2)
(defconstant LOG_ERR 3)
(defconstant LOG_WARNING 4)
(defconstant LOG_NOTICE 5)
(defconstant LOG_INFO 6)
(defconstant LOG_DEBUG 7)

(defconstant +priorities+ (list (cons 'debug LOG_DEBUG)
                                (cons 'info LOG_INFO)
                                (cons 'notice LOG_NOTICE)
                                (cons 'warning LOG_WARNING)
                                (cons 'err LOG_ERR)
                                (cons 'crit LOG_CRIT)
                                (cons 'alert LOG_ALERT)))

;; Clang doesn't support nested C functions.
(defun openlog--calc-logopt-flags (logopts)
   (the <list> logopts)
   (let ((res 0))
        (for ((xs logopts (cdr xs)))
             ((null xs) res)
             (setq res (+ res (car xs))))))
(defun openlog (ident logopts facility)
   (the <string> ident)(the <list> logopts) (the <fixnum> facility)
   (let ((logopt-flags (openlog--calc-logopt-flags logopts)))
        (c-lang "res = 0; openlog(Fgetname(IDENT), LOGOPT_FLAGS & INT_MASK, FACILITY & INT_MASK);")))
(openlog "eisl" (list LOG_PID) LOG_LOCAL0)

(defun syslog (priority message)
   (the <fixnum> priority)(the <string> message)
   (c-lang "res = 0; syslog(PRIORITY & INT_MASK, \"%s\", Fgetname(MESSAGE));"))
(defun log-add (level fmt &rest args)
   ;; Try to add a log entry.
   (the <symbol> level)(the <string> fmt)(the <list> args)
   (let ((str (create-string-output-stream)))
        (format str "[~C] " (elt (convert level <string>) 0))
        (apply #'format str fmt args)
        (syslog (+ (cdr (assoc level +priorities+)) LOG_LOCAL0) (get-output-stream-string str))))

(defun closelog ()
   (c-lang "res = 0; closelog();"))

;; Doesn't seem to work, on macOS at least?
(defun log-set-level (level)
   (the <symbol> level)
   (let ((intlvl (cdr (assoc level +priorities+))))
        (c-lang "res = setlogmask(LOG_UPTO(INTLVL & INT_MASK)) | INT_FLAG;")))

;; Test code:

#|
;; Low-level UNIX syslog interface, not recommended:
(defun my-test ()
   (openlog "test" (list LOG_PID) LOG_LOCAL0)
   (syslog LOG_INFO "This is a test")
   (closelog))
;; The OpenLisp-compatible interface is recommended instead:
(log-add 'debug "f: x ~A y ~A" x y)
|#
;; To see the result of the above on macOS, run
;;   log stream --level debug --predicate "process == 'eisl'"
;; in a Terminal beforehand. Or use Console.app
;;
;; On Linux, messages will probably appear in /var/log/messages,
;; but ensure that they're not filtered out by /etc/*syslog.conf because of low priority.
