(defun foo ()
    (tagbody tag1
             (tagbody tag2
                      (unwind-protect (go tag1) ;;; tag2 invalid (go tag2)))))


;($error
; (tagbody
;  tag1
;  (tagbody
;   tag2
;   (unwind-protect 
;       (go tag1) ;;; tag2 invalid
;     (go tag2)))) <control-error>)
;;;
;;; sasagawa888 memo
;;; ((lambda ()) (go tag)) ocuures wrong argument error (<program-error>).
;;; processor find above error at first. I modify error case.



