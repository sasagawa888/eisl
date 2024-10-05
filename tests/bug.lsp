
(block exit
    (with-handler
        (lambda (condition)
            (return-from exit nil))
        (foo1)))


