# string 

# usage
(import "string")

# spec (test case)

```
($test (string-split "asdf def gh" " ") ("asdf" "def" "gh"))
($test (string-split "asdf,def,gh" ",") ("asdf" "def" "gh"))
($test (string-slice "hello" 3 5) "lo")
($test (string-replace "hello" "e" "a") "hallo")
($test (string-remove "hello" 3 5) "hel")
($test (string-reverse "hello") "olleh")
($test (string-delete "hello" "l") "heo")
($test (string-head "hello") "h")
($test (string-tail "hello") "o")

($test (string-upper "asdf") "ASDF")
($test (string-lower "ASDF") "asdf")
($test (list-to-string '(#\h #\e #\l #\l #\o)) "hello")
($test (string-null-p "") t)
($test (string-null-p "1") nil)
($test (string-null-p t) nil)

($test (char-digit-p #\0) t)
($test (char-digit-p #\9) t)
($test (char-digit-p #\a) nil)
($test (char-alpha-p #\a) t)
($test (char-alpha-p #\Z) t)
($test (char-alpha-p #\9) nil)

($test (to-string "derp") "derp")
($test (to-string #\a) "a")
($test (to-string 9) "9")

($test (join `("a" "b" "c") ",") "a,b,c")
($test (join #("a" "b" "c") ",") "a,b,c")
($test (join `("a" "b" "c") "xyz") "axyzbxyzc")
($test (join `("a" "b" "c") #\,) "a,b,c")
($test (join `("a" "b" "c") #\z) "azbzc")

```