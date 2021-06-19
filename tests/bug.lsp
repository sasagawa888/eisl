(import "test")

(test (let ((a "")) (list (map-into a #'list) a)) ("" "") equal)
;(test (let ((a "a")) (list (map-into a (lambda () #\A)) a)) ("A" "A") equal)
;(test (let ((a "abc")) (list (map-into a (lambda () #\A)) a)) ("AAA" "AAA") equal)
