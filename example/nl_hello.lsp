;; Unfortunately the setup for this is quite involved.
;; I've only tested this procedure on macOS for now.
;;
;; ```sh
;; # Compile i18n.lsp in library
;; export NLSPATH="/usr/share/locale/%L/%N:/usr/share/locale/%L/LC_MESSAGES/%N:$HOME/locale/%L/%N"
;; gencat $HOME/locale/de_DE.UTF-8/i18n.cat de.msg
;; gencat $HOME/locale/en_GB.UTF-8/i18n.cat en.msg
;; gencat $HOME/locale/fr_FR.UTF-8/i18n.cat fr.msg
;; export LANG=de_DE.UTF-8
;; eisl -s example/nl_hello.lsp
;; export LANG=en_GB.UTF-8
;; eisl -s example/nl_hello.lsp
;; export LANG=fr_FR.UTF-8
;; eisl -s example/nl_hello.lsp
;; ```

(import "i18n")
;; Please compile i18n.lsp in library beforehand.

(defun main ()
   (let ((locname (safe-setlocale))
         (catd (catopen "i18n.cat")))
	(init-locale locname)
        (format (standard-output) "~A~%" (str-ltou (catgets catd 1 1 "Hello world")))
        (format (standard-output) "~A~%" (str-ltou (catgets catd 1 2 "The four seasons are spring, summer, autumn and winter.")))
        (catclose catd))
   (cleanup-locale))

(main)
