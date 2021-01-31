(defglobal comp-global-var
           '(instream
             not-need-res
             not-need-colon
             global-variable
             function-arg
             generic-name-arg
             catch-block-tag
             unwind-thunk
             file-name-and-ext
             lambda-count
             lambda-nest
             c-lang-option
             code0
             code1
             code2
             code3
             code4
             code5
             code6
             code7))
(defglobal instream nil)
(defglobal not-need-res
           '(labels
             flet
             return-from
             go
             tagbody
             while
             call-next-method
             the
             c-lang
             c-define
             c-include
             c-option))
(defglobal not-need-colon '(c-lang c-define c-include c-option))
(defglobal global-variable nil)

