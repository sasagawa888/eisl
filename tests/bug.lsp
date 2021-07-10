
(defclass <parent> () ((slot :accessor slot :initarg s)))
(defclass <child> (<parent>) ((slot2 :accessor slot2 :initarg s2)))
(defglobal *x* (create (class <child>) 's 'foo 's2 'bar))