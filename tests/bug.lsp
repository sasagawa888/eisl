;;; bug compiled flet

(defun foo (x)
    (flet ((f (x)
               (+ x 3) ))
        (flet ((f (x)
                   (+ x (f x)) ))
            (f x))) )

(defun fact (x a)
  (if (= x 0)
      a
    (fact (- x 1) (* a x))))

(defun facti (x a)
  (block facti
    (tagbody
      loop
      (if (= x 0)
          (return-from facti a))
      (setq a (* a x))
      (setq x (- x 1))
      (go loop))))

;; ライブラリのロード
(import "list")
(import "cxr")

;; 大域変数
(defglobal global-environment nil)

;; 変数束縛
(defun add-binding (vars vals env)
  (cond ((null vars) env)
        ((symbolp vars)
         (cons (cons vars vals) env))
        (t
         (cons (cons (car vars) (car vals))
               (add-binding (cdr vars) (cdr vals) env)))))

;; 変数の値を取得
(defun lookup (var env)
  (let ((value (assoc var env)))
    (if value
        value
      (assoc var global-environment))))

;; 自己評価フォームか
(defun self-eval-p (expr)
  (and (not (consp expr)) (not (symbolp expr))))

;; 真か？
(defun truep (x) (not (eq x 'false)))

;; クロージャか？
(defun closurep (xs)
  (and (consp xs) (eq (car xs) 'closure)))

;;
;; eval
;;
(defun m-eval (expr env)
  (block exit
   (tagbody loop
     (cond ((self-eval-p expr)        ; 自己評価フォーム
            (return-from exit expr))
           ((symbolp expr)            ; 変数
            (let ((cell (lookup expr env)))
              (if cell
                  (return-from exit (cdr cell))
                (error "unbound variable: ~A" expr))))
           ((consp expr)
            (cond ((eq (car expr) 'quote)
                   (return-from exit (second expr)))
                  ((eq (car expr) 'if)
                   (if (truep (m-eval (second expr) env))
                       (progn
                         (setq expr (third expr))
                         (go loop))
                     (and (drop expr 3)
                          (progn
                            (setq expr (fourth expr))
                            (go loop)))))
                  ((eq (car expr) 'lambda)
                   (return-from exit (list 'closure expr env)))
                  ((eq (car expr) 'define)
                   (setf global-environment
                         (cons (cons (second expr)
                                     (m-eval (third expr) env))
                               global-environment))
                   (return-from exit (second expr)))
                  (t
                   ; apply
                   (let ((proc (m-eval (car expr) env))
                         (actuals (mapcar (lambda (x) (m-eval x env)) (cdr expr))))
                     (cond ((functionp proc)
                            (return-from exit (apply proc actuals)))
                           ((closurep proc)
                            ; (closure (lambda (args ..) body ...)) env)
                            (let* ((args (second (second proc)))
                                   (body (drop (second proc) 2))
                                   (env1 (add-binding args actuals (third proc))))
                              (while (consp (cdr body))
                                (m-eval (car body) env1)
                                (setq body (cdr body)))
                              (setq expr (car body))
                              (setq env env1)
                              (go loop)))
                           (t
                            (error "unknown procedure type: ~A" proc)))))))
           (t
            (error "unknown expression type -- m-eval: ~A" expr))))))

; 初期化
(setf global-environment
      (list
       (cons 'true  'true)
       (cons 'false 'false)
       (cons 'nil   'nil)
       (cons 'quit  'quit)
       (cons 'car   #'car)
       (cons 'cdr   #'cdr)
       (cons 'cons  #'cons)
       (cons 'eq?   (lambda (x y) (if (eq x y) 'true 'false)))
       (cons 'pair? (lambda (x) (if (consp x) 'true 'false)))
       (cons '+     #'+)
       (cons '-     #'-)
       (cons '*     #'*)
       (cons '/     #'quotient)
       (cons '=     (lambda (x y) (if (=  x y) 'true 'false)))
       (cons '/=    (lambda (x y) (if (/= x y) 'true 'false)))
       (cons '<     (lambda (x y) (if (<  x y) 'true 'false)))
       (cons '<=    (lambda (x y) (if (<= x y) 'true 'false)))
       (cons '>     (lambda (x y) (if (>  x y) 'true 'false)))
       (cons '>=    (lambda (x y) (if (>= x y) 'true 'false)))
       ))

;(defun print (xs)
;  (format (standard-output) "~A~%" xs))

(defun princ (xs)
  (format (standard-output) "~A" xs))

;;; read-eval-print-loop
(defun repl ()
  (for ((result nil))
       ((eq result 'quit))
       (princ ">>> ")
       (setq result (m-eval (read) '()))
       (print result)))
