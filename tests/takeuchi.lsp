#|
初めての人のためのLISP
竹内郁雄　著　より
|#


(defun fact (n)
    (if (= n 0)                   ;base
        1                         ;base value
        (* n (fact (- n 1))) ))

;;;１４７ページ
(defun delete-1 (x y)
    (setq y (cons 'dummy y))    ;dummy set
    (del2 x y)                ;call del2
    (cdr y) )

;;;８９ページ
(defun atom-count (x)
    (cond ((nullx) 0)         ;null
          ((atom x) 1)        ;atom
          ;;else
          (t (+ (atom-count (car x))
                (atom-count (cdr x))))))

;;;７９ページ
(defun last-elm (x)
    (cond ((null x) nil)
          (t (last-elm2 x)) ))

;;９６ページ
(defun my-reverse (x)
    (cond ((null x) x)
          (t (append (my-reverse (cdr x)) (list (car x)))) ))


#|
ppの原則（２５１ページ）
（１）１行にS式が打てるなら、その行に打つ。
（２）同一行に対応する開きガッコがない閉じガッコ（「お供」と呼ぼう）が並ぶときは
それの左端に空白を１個はさむ
（３）カッコのレベルが１つ深まると、段が２文字分深まる。
お供
コンスが内包するコンスがお供を有している場合には（２）に関わらず空白は挟まない。
追加ルール
（４）コンスにつき、先頭要素以外の要素につきいずれも文字数が１５を超えるならば
それらについてインデントする。
（５）コンスをインデントするときにおいて、組み込み関数であるときは残りの要素のインデントは
第一要素の位置に合わせる。
（６）cond節の条件帰結が１行で書けるとしても、総文字数が一定数を超える場合には条件式と帰結式を分けて書く。
（７）クオート、バッククオートのときで１行で書けないときは１文字下げて改行する。
（８）cond節など書法の慣習が定着しているシンタックスはそれに従う。
|#



