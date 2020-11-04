(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(if (equal ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))
      `(if (,@pred ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))))


;;; (SYMBOLP obj) --> boolean
;;;
(test (symbolp 'a) t)
(test (symbolp "a") nil)
(test (symbolp #\a) nil)
(test (symbolp 't) t)
(test (symbolp t) t)
(test (symbolp 'nil) t)
(test (symbolp nil) t)
(test (symbolp '()) t)
(test (symbolp '*pi*) t)
(test (symbolp *pi*) nil)
;;;
;;;
;;; (PROPERTY symbol property-name [obj]) --> <object>
;;;
(test (property 'aaa 'bbb) nil)
(test (property 'aaa 'bbb 'zzz) zzz)

;;;
;;; (SET-PROPERTY obj symbol property-name) --> <object>
;;;
(test (setf (property 'zeus 'daughter) 'athena) athena)
(test (set-property 'athena 'zeus 'daughter) athena)
(test (property 'zeus 'daughter) athena)
;;;
(test (list (setf (property 'aaa 'bbb) 'ccc) (property 'aaa 'bbb 'zzz))
 (ccc ccc) equal)
(test (list (set-property 'ccc 'aaa 'bbb) (property 'aaa 'bbb 'zzz))
 (ccc ccc) equal)

;;;
;;; (REMOVE-PROPERTY symbol property-name) --> <object>
;;;

(test (remove-property 'zeus 'daughter) athena)
;;;
;;;
(test (list (remove-property 'aaa 'bbb) (property 'aaa 'bbb 'zzz))
 (ccc zzz) equal)

;;;
(defmacro twice (x)
         (let ((v (gensym)))
           `(let ((,v ,x)) (+ ,v ,v))))
(test (twice 5) 10 eql)
;;;
;;;
(test (symbolp (gensym)) t)
