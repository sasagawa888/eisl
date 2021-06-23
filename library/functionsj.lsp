;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Search Function 
;;;   関数名の先頭の一部を与えて、該当するシステム関数のシグネチャを
;;;   リストにする
;;;    (search-function function-name [short])
;;;
;;;    Exp. (search-function 'char) 
;;;          --->
;;;         (((CHARACTERP OBJ) BOOLEAN) 
;;;          ((CHAR= CHAR1 CHAR2) BOOLEAN) 
;;;           ... )
;;;    Exp. (search-function 'char t) 
;;;          --->
;;;         (CHARACTERP CHAR= ...) 
;;;       
;;; Say Function
;;;   関数名の先頭の一部を与えて、該当するシステム関数の説明を整形して
;;;   画面に表示する
;;;   (say function-name [output-file]) function-name で始まる関数を表示する
;;;   (say-all [output-file]) すべてのシステム関数の説明を整形して画面に表示する
;;;
;;; written by GOMI Hiroshi 2011/6/21-22, 29-30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;
;;; function list
;;;  (((function-name args ...) return-value [special]) ...)
(defglobal *functions* nil)

;;;
;;; object list
;;;  (function-name ...)
(defglobal *oblist* nil)

;;;
;;; reaf from data file
;;;
(defun read-functions (file)
   (with-open-input-file 
      (stream file)
      (for ((data (read stream 'nil 'eof) (read stream 'nil 'eof)))
	   ((eq data 'eof) 
            (setq *functions* (nreverse *functions*))
            (setq *oblist* (nreverse *oblist*)) )
         (setq *oblist* (cons (car (car data)) *oblist*))
         (setq *functions* (cons data *functions*)) )))

(flet ((library-file (basename)
          (let ((prefix (getenv "EASY_ISLISP")))
               (if (null prefix)
                   (string-append (getenv "HOME") "/eisl/library/" basename)
                   (string-append prefix "/library/" basename)))))
   (read-functions (library-file "functions-dataj.lsp")))

;;;
;;; search function from *functions*
;;; exp. (search-function 'a)
;;;      (search-function 'a t)
;;;
(defun search-function (function &rest short)
   (let ((ret nil))
      (for ((funs *functions* (cdr funs))
            (fun nil) )
           ((null funs) 
            (if (null short) ret (mapcar (lambda (x) (car (car x))) ret)) )
         (setq fun (car funs))
         (let ((fname (car (car fun))))
            (if (eq function fname) 
                (setq ret (cons fun ret))
                (let ((name1 (convert function <string>))
                      (name2 (convert fname <string>)) )
                   (if (<= (length name1) (length name2))
                       (if (string= name1 (subseq name2 0 (length name1))) 
                           (setq ret (cons fun ret)) ))))))))

;;;
;;; say object
;;; exp. (say 'char=)
;;;
(defun say (object &rest output-file)
   (let ((flist (search-function object))
         (stream (if (null output-file) 
                     (standard-output) 
                     (open-output-file (car output-file)) )))
      (if flist 
          (describe-system-function flist stream)
          (describe object) )
      (if output-file (close stream)) 
      object))

(defun describe-system-function (funlist &rest stream)
   (if (null stream) (setq stream (standard-output)) (setq stream (car stream)))
   (for ((flist funlist (cdr flist)) 
         (fun nil) )
        ((null flist))
     (setq fun (car flist))
     (format stream 
             "関数: ~S~%仕様: ~S ---> ~S~%" (car (car fun)) (car fun) (car (cdr fun)) )
     (let ((ex (cdr (cdr fun))))
        (if ex 
            (format stream "説明: ~A~%~%" (car (cdr (cdr fun))))
            (format stream "~%") ))))     

(defun say-all (&rest output-file)
   (let ((stream (if (null output-file) 
                     (standard-output) 
                     (open-output-file (car output-file)) )))
      (format stream "OKI ISLisp 関数一覧 (~S個)*拡張分を含む~%~%" (length *functions*))
      (describe-system-function *functions* stream) 
      (if output-file (close stream)) 
      'end))

     

