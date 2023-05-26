;;;
;;; macro.lsp : ISLisp 用マクロ
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;

;;; when test body ...
(defmacro when (test &rest args)
  `(if ,test (progn ,@args)))

;;; unless test body ...
(defmacro unless (test &rest args)
  `(if ,test nil (progn ,@args)))

;;; prog1 expr body ...
(defmacro prog1 (expr &rest args)
  (let ((x (gensym)))
    `(let ((,x ,expr))
       (progn ,@args)
       ,x)))

;;; prog2 expr1 expr2 body ...
(defmacro prog2 (expr1 expr2 &rest args)
  `(progn ,expr1 (prog1 ,expr2 ,@args)))

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

;;; push X to end of PLACE
(defmacro push-end (x place)
  `(setf ,place (reverse 
               (cons ,x
                     (reverse ,place)))))

;;; pop place
(defmacro pop (place)
  `(prog1 (car ,place) (setf ,place (cdr ,place))))

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
      (for ((,var nil)
            (,ys ,xs (cdr ,ys)))
           ((null ,ys) ,result)
           (setq ,var (car ,ys))
           ,@body))))

