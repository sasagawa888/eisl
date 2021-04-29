;;;
;;; macro.lsp : ISLisp 用マクロ
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;

;;; incf place [value]
(defmacro incf (place &rest args)
  (let ((delta (if args (car args) 1)))
    `(setf ,place (+ ,place ,delta))))

;;; decf place [value]
(defmacro decf (place &rest args)
  (let ((delta (if args (car args) 1)))
    `(setf ,place (- ,place ,delta))))

;;; push item place
(defmacro push (x place)
  `(setf ,place (cons ,x ,place)))

;;; pop place
(defmacro pop (place)
  (let ((x (gensym)))
    `(let ((,x (car ,place)))
       (setf ,place (cdr ,place))
       ,x)))

;;; loop body ...
(defmacro loop (&rest body)
  `(block nil (tagbody loop1 ,@body (go loop1))))

;;; return [result]
(defmacro return (&rest args)
  (let ((result (if args (car args))))
    `(return-from nil ,result)))

;;; dotimes (var limit [result]) body ...
(defmacro dotimes (var-list &rest body)
  (let ((var (car var-list))
        (limit (car (cdr var-list)))
        (result (if (cdr (cdr var-list)) (car (cdr (cdr var-list))))))
    `(block
      nil
      (for ((,var 0 (+ ,var 1)))
           ((>= ,var ,limit) ,result)
           ,@body))))

;;; dolist (var list [result]) body ...
(defmacro dolist (var-list &rest body)
  (let ((var (car var-list))
        (xs (car (cdr var-list)))
        (ys (gensym))
        (result (if (cdr (cdr var-list)) (car (cdr (cdr var-list))))))
    `(block
      nil
      (let ((,var nil) (,ys ,xs))
        (while ,ys
          (setq ,var (car ,ys))
          ,@body
          (setq ,ys (cdr ,ys)))
        ,result))))