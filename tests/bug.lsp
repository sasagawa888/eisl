(defmodule util

    (defclass <rect> () ((size :accessor rect-size :initarg size)))
    
    (defpublic foo ()
        (create (class <rect>) 'util::size 999) )

    (defpublic bar (x)
        (rect-size x) )

)
