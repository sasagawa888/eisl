
(defclass <foo> () ((slot :initarg init :reader slot)))
(defglobal *x* (create (class <foo>) 'init 42))
(format (standard-output) "~A~%" (slot *x*))
  
