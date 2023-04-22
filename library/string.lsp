(defmodule string
    
    (defpublic split (str)
        (split1 (convert str <list>) "") )

    (defun split1 (ls x)
        (cond ((null ls) (list x))
              ((char= (car ls) #\space) (cons x (split1 (cdr ls) "")))
              (t (split1 (cdr ls) (string-append x (create-string 1 (car ls))))) ))

    (defpublic replace (str x y)
        (replace1 (convert str <list>) x y))

    (defun replace1 (ls x y)
        (cond ((null ls) "")
              ((char= (car ls) x) (string-append (create-string 1 y) (replace1 (cdr ls) x y)))
              (t (string-append (create-string 1 (car ls)) (replace1 (cdr ls) x y)))))

    ;;; TO-STRING converts a given non-sequence atom to a string value
    (defgeneric to-string (value))

    (defmethod to-string ((value <character>)) (create-string 1 value))
    (defmethod to-string (value) (convert value <string>))
    
    ;;; JOIN concatenates together a sequence of strings into a single string with the joiner string separating each element string.
    ;;; Comparable to .join() in Python or Javascript 
    ;;; ELEMENTS is a sequence of strings to be joined
    ;;; JOINER is a string that will be concatenated between the element strings
    (defgeneric join (elements joiner))

    (defmethod join
               ((elements <list>) (joining-string <string>))
               (let ((joined-string (car elements))
                     (remaining-elements (cdr elements)) )
                  (while (consp remaining-elements)
                     (setf joined-string
                           (string-append joined-string joining-string (car remaining-elements)))
                     (setf remaining-elements (cdr remaining-elements)))
                  joined-string))
    (defmethod join
               ((elements <general-vector>) (joining-string <string>))
               (join (convert elements <list>) joining-string))
    (defmethod join
               (elements (joining-char <character>))
               (join elements (to-string joining-char)))
    
)
