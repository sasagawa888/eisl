(defclass <parent> () ())

(defclass <child> (<parent>) ())

(defgeneric print-self (obj))

(defmethod print-self ((obj <parent>))
  (format (standard-output) "PARENT:~S~%" (class-of obj)))

(print-self (create (class <parent>)))
;; => PARENT:<class <PARENT>>

(print-self (create (class <child>)))
;; => Expected PARENT:<class <CHILD>>, Not exit matched method at PRINT-SELF (<instance>)

(defmethod print-self ((obj <object>))
  (format (standard-output) "OBJECT:~S~%" (class-of obj)))

(print-self (create (class <parent>)))
;; => PARENT:<class <PARENT>>
(print-self (create (class <child>)))
;; => Expected PARENT:<class <CHILD>>, but OBJECT:<class <CHILD>>.
