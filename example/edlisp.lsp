;;Copyright (C) Kenichi Sasagawa (2017). All Rights Reserved.
;;Subset ISLisp for larning Ver1.1 for EISL

;;大域変数
(defglobal *global* nil)
;;動的変数
(defglobal *dynamic* nil)
;;関数　ISLispはLISP2であり、変数と関数の名前空間が異なる
(defglobal *function* nil)
;;組込み関数
(defglobal *primitive*
  '(atom + - * div = eq sin cos tan atan print symbolp car))
;;特殊形式
(defglobal *special-form*
  '(quote setq if progn defun defglobal defdynamic
     cond lambda function let let*))

(defun islisp ()
  (initialize)
  (repl))

(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read) (read)))
                  ((equal s '(quit)) (return-from repl t))
                  (print (eval* s nil))
                  (setq *dynamic* nil)
                  (prompt))) t)
          (t (prompt)(repl)))))

;;初期化
;;メッセージを表示し、プロンプトを表示する。
(defun initialize ()
  (format (standard-output) "Subset ISLisp for education~%")
  (prompt))


;;プロンプトを表示する。
(defun prompt ()
  (format (standard-output) "L> "))

;;評価器
(defun eval* (s env)
  (cond ((null s) s)
        ((numberp s) s)
        ((characterp s) s)
        ((stringp s) s)
        ((general-vector-p s) s)
        ((general-array*-p s) s)
        ((symbolp s)
         (if (eq s t)
             s
             (lookup s env)))
        ((consp s)
         (cond ((eq (car s) 'funcall)
                (apply* (eval* (elt s 1) env) (cdr (cdr s)) env))
               ((and (consp (car s))(eq (car (car s)) 'lambda))
                (apply* (eval* (car s) env) (evlis (cdr s) env) env))
               ((special-form-p (car s)) (apply* (car s) (cdr s) env))
               ((primitivep (car s)) (apply* (car s) (evlis (cdr s) env) env))
               ((functionp* (car s)) (apply* (car s) (evlis (cdr s) env) env))
               (t
                 (apply* (function-lookup (car s)) (evlis (cdr s) env) env))))
        (t (error* "undefined object" s))))

(defun apply* (f arg env)
  (cond ((special-form-p f)(special-form f arg env))
        ((primitivep f)(apply (symbol-function f) arg))
        ((functionp* f)
         (let ((env1 (bindarg (elt (elt f 1) 0) arg (elt f 2))))
           (for ((body (cdr (elt f 1)) (cdr body)))
                ((null (cdr body)) (eval* (car body) env1))
                (eval* (car body) env1))))
        (t (error* "Illegal function call apply* " f))))

;;実引数を仮引き数に束縛し、環境に追加する。
;;例 var=(x,y,z) arg=(1,2,3) env=((a . 10))
;; -> env=((x . 1)(y . 2)(z . 3)(a . 10))
(defun bindarg (var arg env)
  (for ((var1 var (cdr var1))
        (arg1 arg (cdr arg1))
        (res nil (cons (cons (car var1) (car arg1)) res)))
       ((null var1) (append res env))))

;;実引数をevalしてリストにする。
(defun evlis (arg env)
  (cond ((null arg) nil)
        (t (cons (eval* (car arg) env)
                 (evlis (cdr arg) env)))))

;;シンボルsymに束縛された値を探す。
;;最初に局所環境から探し、なければ大域環境から探す。
;;シンボルsymが組込み関数ならばprimitiveを返す。
(defun lookup (sym env)
  (cond ((assoc sym env) (cdr (assoc sym env)))
        ((assoc sym *global*) (cdr (assoc sym *global*)))
        ((primitivep sym) 'primitive)
        (t (error* "Undefined variable " sym))))


;;関数名空間においてシンボルsymの束縛を探す。
(defun function-lookup (sym)
  (cond ((assoc sym *function*) (cdr (assoc sym *function*)))
        (t (error* "Undefined function " sym))))

;;動的環境においてシンボルsymの束縛を探す。
(defun dynamic-lookup (sym)
  (cond ((assoc sym *dynamic*) (cdr (assoc sym *dynamic*)))
        (t (error* "Undefined variable " sym))))


;;局所環境あるいは大域環境においてシンボルsymに値valを束縛する。
(defun bind (sym val env)
  (cond ((assoc sym env) (set-cdr val (assoc sym env)))
        ((assoc sym *global*) (set-cdr val (assoc sym *global*)))
        (t (error* "Undefined variable " sym))))

;;エラー処理
(defun error* (msg arg)
  (format (standard-output) msg)
  (print arg)
  (format (standard-output) "~%")
  (throw 'exit nil))

;;組込み関数ならt
(defun primitivep (x)
  (member x *primitive*))

;;ユーザ定義関数であればt
(defun functionp* (x)
  (and (consp x)(eq (car x) 'func)))

;;特殊形式であればt
(defun special-form-p (x)
  (member x *special-form*))

;;特殊形式の種類に応じた処理を呼び出す。
(defun special-form (f arg env)
  (cond ((eq f 'quote) (car arg))
        ((eq f 'lambda) (list 'func arg env))
        ((eq f 'cond) (evcon arg env))
        ((eq f 'setq) (evsetq arg env))
        ((eq f 'defun) (evdefun arg env))
        ((eq f 'if) (evif arg env))
        ((eq f 'let) (evlet arg env))
        ((eq f 'let*) (evlet* arg env))
        ((eq f 'progn) (evprogn arg env))
        ((eq f 'defglobal) (evdefglobal arg env))
        ((eq f 'defdynamic) (evdefdynamic arg env))
        ((eq f 'dynamic) (evdynamic arg env))
        ((eq f 'function)
         (if (primitivep (car arg))
             (car arg)
             (function-lookup (car arg))))))

;;特殊形式　cond
(defun evcon (arg env)
  (cond ((not (null (car (car arg))))
         (evprogn (cdr (car arg)) env))
        (t (evcon (cdr arg) env))))

;;特殊形式　if
(defun evif (arg env)
  (if (not (null (eval* (elt arg 0) env)))
      (eval* (elt arg 1) env)
      (eval* (elt arg 2) env)))

;;特殊形式　let
(defun evlet (arg env)
  (for ((vars (car arg) (cdr vars))
        (env1 env))
       ((null vars) (setq env env1))
       (setq env1 (cons (cons (elt (car vars) 0)
                             (eval* (elt (car vars) 1) env))
                       env1)))
  (for ((body (cdr arg) (cdr body)))
       ((null (cdr body)) (eval* (car body) env))
       (eval* (car body) env)))

;;特殊形式　let*
(defun evlet* (arg env)
  (for ((vars (car arg) (cdr vars)))
       ((null vars) t)
       (setq env (cons (cons (elt (car vars) 0)
                             (eval* (elt (car vars) 1) env))
                       env)))
  (for ((body (cdr arg) (cdr body)))
       ((null (cdr body)) (eval* (car body) env))
       (eval* (car body) env)))

;;特殊形式　progn
(defun evprogn (arg env)
  (for ((body arg (cdr body)))
       ((null (cdr body)) (eval* (car body) env))
       (eval* (car body) env)))

;;特殊形式　setq
(defun evsetq (arg env)
  (bind (car arg) (eval* (elt arg 1) env) env)
  (car arg))

;;特殊形式　defglobal
(defun evdefglobal (arg env)
  (cond ((assoc (elt arg 0) *global*)
         (set-cdr (eval* (elt arg 1) env)
                  (assoc (elt arg 0) *global*))
         (elt arg 0))
        (t (setq *global* (cons (cons (elt arg 0)(elt arg 1)) *global*))
           (elt arg 0))))

;;特殊形式　dynamic
(defun evdynamic (arg env)
  (dynamic-lookup (elt arg 0)))

;;特殊形式　defdynamic
(defun evdefdynamic (arg env)
  (cond ((assoc (elt arg 0) *dynamic*)
         (set-cdr (eval* (elt arg 1) env)
                  (assoc (elt arg 0) *dynamic*))
         (elt arg 0))
        (t (setq *dynamic* (cons (cons (elt arg 0)(elt arg 1)) *dynamic*))
           (elt arg 0))))


;;特殊形式defunの処理
;;関数名空間にあればその実体を上書きし、無ければ追加する。
;; (name . (func (args body) env))　のような連想リストになっている。
(defun evdefun (arg env)
  (cond ((assoc (elt arg 0) *function*)
         (set-cdr (list 'func (cdr arg) env)
                  (assoc (elt arg 0) *function*)))
        (t
          (setq *function* (cons (cons (elt arg 0)
                                     (list 'func (cdr arg) env))
                               *function*))))
  (elt arg 0))
