(import "test")
;;;
;;;  chapter10 Symbol class
;;;

($ap 1 "Symbol class")

;;;
;;; function (SYMBOLP obj) --> boolean
;;;
($ap 2 "symbolp" P.63)
($test (symbolp 'a) t)
($test (symbolp "a") nil)
($test (symbolp #\a) nil)
($test (symbolp 't) t)
($test (symbolp t) t)
($test (symbolp 'nil) t)
($test (symbolp nil) t)
($test (symbolp '()) t)
($test (symbolp '*pi*) t)
($test (symbolp *pi*) nil)
;;;
($argc symbolp 1 0 0)
($predicate symbolp $symbol $t $null)

;;;
;;; function (PROPERTY symbol property-name [obj]) --> <object>
;;;
($ap 2 "property" P.65)
;;;
($argc property 2 1 0)
($type property ($symbol $null) :target (quote abc))
($type property ($symbol $null) (quote abc) :target)
;;;
($test (property 'aaa 'bbb) nil)
($test (property 'aaa 'bbb 'zzz) zzz)

;;;
;;; function (SET-PROPERTY obj symbol property-name) --> <object>
;;;
($ap 2 "set-property" P.66)
($test (setf (property 'zeus 'daughter) 'athena) athena)
($test (set-property 'athena 'zeus 'daughter) athena)
($test (property 'zeus 'daughter) athena)
;;;
($argc set-property 3 0 0)
($type set-property ($symbol $null) (quote a) :target (quote abc))
($type set-property ($symbol $null) (quote a) (quote abc) :target)
;;;
($test (list (setf (property 'aaa 'bbb) 'ccc) (property 'aaa 'bbb 'zzz)) 
 (ccc ccc) equal)
($test (list (set-property 'ccc 'aaa 'bbb) (property 'aaa 'bbb 'zzz)) 
 (ccc ccc) equal)

;;;
;;; function (REMOVE-PROPERTY symbol property-name) --> <object>
;;;
($ap 2 "remove-property" P.66)
($test (remove-property 'zeus 'daughter) athena)
;;;
($argc remove-property 2 0 0)
($type remove-property ($symbol $null) :target (quote abc))
($type remove-property ($symbol $null) (quote abc) :target)
;;;
($test (list (remove-property 'aaa 'bbb) (property 'aaa 'bbb 'zzz)) 
 (ccc zzz) equal)

;;;
;;; function (GENSYM) --> <symbol>
;;;
($ap 2 "gensym" P.66)
($eval (defmacro twice (x)
         (let ((v (gensym)))
           `(let ((,v ,x)) (+ ,v ,v)))))
($test (twice 5) 10 eql)
;;;
($argc gensym 0 0 0)
;;;
($test (symbolp (gensym)) t)
