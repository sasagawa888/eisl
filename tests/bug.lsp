;;; compiler test with M.hiroi example
;;
;; keiro.l : 経路の探索
;;
;;           Copyright (C) 2016 Makoto Hiroi
;;

;; ライブラリのロード
(import "list")
(import "queue")

;; 隣接リスト (連想リスト)
(defglobal adjacent
           '((a b c)
             (b a c d)
             (c a b e)
             (d b e f)
             (e c d g)
             (f d)
             (g e)))

;(defun print (x)
;  (format (standard-output) "~A~%" x))

;; 深さ優先探索
(defun depth-first-search (goal path)
  (if (eq goal (car path))
      (print (reverse path))
    (for-each
     (lambda (x)
       (if (not (member x path))
           (depth-first-search goal (cons x path))))
     (cdr (assoc (car path) adjacent)))))

;; 幅優先探索
(defun breadth-first-search (start goal)
  (let ((q (create (class <queue>))))
    (enqueue q (list start))
    (while (not (emptyp q))
      (let ((path (dequeue q)))
        (if (eq (car path) goal)
            (print (reverse path))
          (for-each
           (lambda (x)
             (if (not (member x path))
                 (enqueue q (cons x path))))
           (cdr (assoc (car path) adjacent))))))))

;; 反復進化
(defun id-search (start goal)
  (labels ((dfs (limit path)
             (if (= limit (length path))
                 (if (eq (car path) goal)
                     (print (reverse path)))
               (for-each
                (lambda (x)
                  (if (not (member x path))
                      (dfs limit (cons x path))))
                (cdr (assoc (car path) adjacent))))))
    (for ((limit 1 (+ limit 1)))
         ((= limit 7))
         (format (standard-output) "----- ~D -----~%" limit)
         (dfs limit (list start)))))
         