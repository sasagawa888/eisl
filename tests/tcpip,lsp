;;; test code for TCP/IP functions

(defglobal ip "127.1.1.11") ; change your server ip address

(defun server ()
    (let ((socket (create-server-socket 5000))
           (msg nil) )
       (setq msg (recv-socket socket))
       (while (not (equal msg "quit"))
          (format (standard-output) "~A~%" msg)
          (finish-output (standard-output))
          (send-socket socket "receive data")
          (setq msg (recv-socket socket)))
       (close-socket socket)))

(defun client ()
    (let ((socket (create-client-socket 5000 ip))
          (msg nil) )
       (setq msg (read-line))
       (while (not (equal msg "end"))
          (send-socket socket msg)
          (setq msg (recv-socket socket))
          (format (standard-output) "~A~%" msg)
          (setq msg (read-line)))
       (close-socket socket)))