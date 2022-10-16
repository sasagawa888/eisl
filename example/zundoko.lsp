#|
ズンドコキヨシ

(gen-zundoko n) generate list length n. Each element is "ズン" or "ドコ"
(zundoko ls) ls is above list. If find pattern "ズン" "ズン" "ズン" "ズン" "ドコ"　
　　　　　　　return "キ☆ヨ☆シ！"
|#
(import "elixir")

(defun gen-zundoko (n)
    (cond ((= n 0) nil)
          ((= (random 2) 1) (cons "ズン" (gen-zundoko (- n 1))))
          (t (cons "ドコ" (gen-zundoko (- n 1))))))


(defpattern zundoko 
    ((empty-list) nil)
    ((("ズン" "ズン" "ズン" "ズン" "ドコ" :rest _x))  "キ☆ヨ☆シ！")
    (((_x :rest _y)) (format (standard-output) "~A " _x) (zundoko _y)))
