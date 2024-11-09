(defclass <inner> () ((slot-inner :accessor slot-inner :initarg slot-inner)))

(defclass <outer> () ((slot-outer :reader slot-outer :initform (create (class <inner>) 'slot-inner 'hoge))))

(let ((outer-1 (create (class <outer>)))
      (outer-2 (create (class <outer>))))
  (format (standard-output) "~S~%" (slot-inner (slot-outer outer-1)))
  ;; => HOGE
  (format (standard-output) "~S~%" (slot-inner (slot-outer outer-2)))
  ;; => HOGE
  (setf (slot-inner (slot-outer outer-1)) 'FUGA)
  (format (standard-output) "~S~%" (slot-inner (slot-outer outer-1)))
  ;; => FUGA
  (format (standard-output) "~S~%" (slot-inner (slot-outer outer-2)))
  ;; => Expected HOGE, but FUGA
  )


