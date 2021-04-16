;;;

(c-include "<locale.h>" macos)
(c-include "<stdlib.h>" openbsd)
(c-include "<stdio.h>" linux)
(c-include "<syslog.h>")

(c-option "-fPIC" linux)

(defun foo (x)
    (c-lang "printf(\"%d\",X);"))

