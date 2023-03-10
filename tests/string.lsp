(import "string")
(import "test")

($test (string::to-string "derp") "derp")
($test (string::to-string #\a) "a")
($test (string::to-string 9) "9")

($test (string::join `("a" "b" "c") ",") "a,b,c")
($test (string::join #("a" "b" "c") ",") "a,b,c")
($test (string::join `("a" "b" "c") "xyz") "axyzbxyzc")
($test (string::join `("a" "b" "c") #\,) "a,b,c")
($test (string::join `("a" "b" "c") #\z) "azbzc")
