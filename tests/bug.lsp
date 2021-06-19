(import "test")

(test (let ((a "abc") (b "")) (list (map-into a #'list b) a b)) ("abc" "abc" "") equal)

