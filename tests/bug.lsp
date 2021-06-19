(import "test")

(test (let ((a #()) (b #()) (c #(a b c))) (list (map-into a #'list b c) a b c))
 (#() #() #() #(a b c))
 equal)
