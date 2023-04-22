(import "string")
(import "test")

($test (string-split "asdf def gh" " ") ("asdf" "def" "gh"))
($test (string-slice "hello" 3 5) "lo")
($test (string-replace "hello" "e" "a") "hallo")
($test (string-remove "hello" 3 5) "hel")

($test (to-upper "asdf") "ASDF")
($test (to-lower "ASDF") "asdf")

($test (to-string "derp") "derp")
($test (to-string #\a) "a")
($test (to-string 9) "9")

($test (join `("a" "b" "c") ",") "a,b,c")
($test (join #("a" "b" "c") ",") "a,b,c")
($test (join `("a" "b" "c") "xyz") "axyzbxyzc")
($test (join `("a" "b" "c") #\,) "a,b,c")
($test (join `("a" "b" "c") #\z) "azbzc")
