
(defclass <grand> () ((slot3 :accessor slot3 :initarg s3)))
(defclass <parent> (<grand>) ((slot :accessor slot :initarg s)))
(defclass <brother> () ((slot1 :accessor slot1 :initarg s1)))
(defclass <child> (<parent> <brother>) ((slot2 :accessor slot2 :initarg s2)))
(defglobal *x* (create (class <child>) 's 'foo 's2 'bar 's3 'boo 's1 'uoo))

