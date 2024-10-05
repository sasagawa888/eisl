(import "test")

($assert
    (+ 1
       (catch 'foo
         (+ 2 (throw 'foo 1)))
       3)
    5)

