;;; クラス定義
(defclass foo1 () ())
(defclass foo2 (foo1) ())
(defclass foo3 (foo2) ())

(defglobal x1 (create (class foo1)))
(defglobal x2 (create (class foo2)))
(defglobal x3 (create (class foo3)))

(defgeneric bar (x))
;;; 基本メソッド
(defmethod bar ((x foo1)) (format (standard-output) "foo1 bar~%"))
(defmethod bar ((x foo2)) (format (standard-output) "foo2 bar~%") (call-next-method))
(defmethod bar ((x foo3)) (format (standard-output) "foo3 bar~%") (call-next-method))

;;; :after メソッド
(defmethod bar :after ((x foo1)) (format (standard-output) "foo1 bar after~%"))
(defmethod bar :after ((x foo2)) (format (standard-output) "foo2 bar after~%"))
(defmethod bar :after ((x foo3)) (format (standard-output) "foo3 bar after~%"))

;;; :before メソッド
(defmethod bar :before ((x foo1)) (format (standard-output) "foo1 bar before~%"))
(defmethod bar :before ((x foo2)) (format (standard-output) "foo2 bar before~%"))
(defmethod bar :before ((x foo3)) (format (standard-output) "foo3 bar before~%"))