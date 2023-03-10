(defmodule string
           ;;; TO-STRING converts a given non-sequence atom to a string value
           (defgeneric to-string (value))

           (defmethod to-string ((value <character>))
             (create-string 1 value))

           (defmethod to-string (value)
             (convert value <string>))

           ;;; JOIN concatenates together a sequence of strings into a single string with the joiner string separating each element string.
           ;;; Comparable to .join() in Python or Javascript
           ;;; ELEMENTS is a sequence of strings to be joined
           ;;; JOINER is a string that will be concatenated between the element strings
           (defgeneric join (elements joiner))

           (defmethod join ((elements <list>) (joining-string <string>))
             (let ((joined-string (car elements))
                   (remaining-elements (cdr elements)))
               (while (consp remaining-elements)
                      (setf joined-string 
                            (string-append joined-string 
                                           joining-string
                                           (car remaining-elements)))
                      (setf remaining-elements (cdr remaining-elements)))
               joined-string))

           (defmethod join ((elements <general-vector>) (joining-string <string>))
             (join (convert elements <list>) joining-string))

           (defmethod join (elements (joining-char <character>))
             (join elements (to-string joining-char))))
