;;;testing formatter
;;; written by M.hiroi
;リスト : ナンバープレースの解法
;;;
;;; micro.l : micro Scheme with ISLisp
;;;
;;;           Copyright (C) 2016 Makoto Hiroi
;;;

;; ライブラリのロード
(load "list.l")

;; 大域変数
(defglobal global-environment nil)

;; 変数束縛
(defun add-binding (vars vals env)
    (cond ((null vars) env)
          ((symbolp vars) (cons (cons vars vals) env))
          (t (cons (cons (car vars) (car vals)) (add-binding (cdr vars) (cdr vals) env))) ))

;; 変数の値を取得
(defun lookup (var env)
    (let ((value (assoc var env)))
       (if value
           value
           (assoc var global-environment) )))

;; 自己評価フォームか
(defun self-eval-p (expr)
    (and (not (consp expr)) (not (symbolp expr))) )

;; 真か？
(defun truep (x)
    (not (eq x 'false)) )

;; クロージャか？
(defun closurep (xs)
    (and (consp xs) (eq (car xs) 'closure)) )

;;
;; apply
;;
(defun m-apply (expr env)
    (let ((proc (m-eval (car expr) env))
          (actuals (mapcar (lambda (x) (m-eval x env)) (cdr expr))) )
       (cond ((functionp proc) (apply proc actuals))
             ((closurep proc)                       ; (closure (lambda (args ..) body ...)) env)
             (let* ((result nil)
                    (args (second (second proc)))
                    (body (drop (second proc) 2))
                    (env1 (add-binding args actuals (third proc))) )
                 (while (consp body)
                    (setq result (m-eval (car body) env1))
                    (setq body (cdr body)))
                 result))
             (t (error "unknown procedure type: ~A" proc)))))

;;
;; eval
;;
(defun m-eval (expr env)
    (cond ((self-eval-p expr) expr)          ; 自己評価フォーム
          ((symbolp expr)                     ; 変数
          (let ((cell (lookup expr env)))
              (if cell
                  (cdr cell)
                  (error "unbound variable: ~A" expr))))
          ((consp expr)
             (cond ((eq (car expr) 'quote) (second expr))
                 ((eq (car expr) 'if)
                    (if (truep (m-eval (second expr) env))
                      (m-eval (third expr) env)
                      (and (drop expr 3) (m-eval (fourth expr) env))))
                 ((eq (car expr) 'lambda) (list 'closure expr env))
                 ((eq (car expr) 'define)
                    (setf
                     global-environment
                     (cons (cons (second expr) (m-eval (third expr) env)) global-environment))
                    (second expr))
                 (t (m-apply expr env))))
          (t (error "unknown expression type -- m-eval: ~A" expr))))

; 初期化
(setf
   global-environment
   (list
    (cons 'true 'true)
    (cons 'false 'false)
    (cons 'nil 'nil)
    (cons 'quit 'quit)
    (cons 'car #'car)
    (cons 'cdr #'cdr)
    (cons 'cons #'cons)
    (cons 'eq? (lambda (x y) (if (eq x y)
                               'true
                               'false)))
    (cons 'pair? (lambda (x) (if (consp x)
                               'true
                               'false)))
    (cons '+ #'+)
    (cons '- #'-)
    (cons '* #'*)
    (cons '/ #'quotient)
    (cons '= (lambda (x y) (if (= x y)
                             'true
                             'false)))
    (cons '/= (lambda (x y) (if (/= x y)
                              'true
                              'false)))
    (cons '< (lambda (x y) (if (< x y)
                             'true
                             'false)))
    (cons '<= (lambda (x y) (if (<= x y)
                              'true
                              'false)))
    (cons '> (lambda (x y) (if (> x y)
                             'true
                             'false)))
    (cons '>= (lambda (x y) (if (>= x y)
                              'true
                              'false)))))
(defun print (xs)
    (format (standard-output) "~A~%" xs) )

(defun princ (xs)
    (format (standard-output) "~A" xs) )

;;; read-eval-print-loop
(defun repl ()
    (for ((result nil))
         ((eq result 'quit))
         (princ ">>> ")
         (setq result (m-eval (read) '()))
         (print result)) )
