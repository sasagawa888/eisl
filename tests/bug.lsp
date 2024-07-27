;;; test code for TCP/IP functions

(defglobal ip "127.001.001.01") ; change your server ip address

(defun server ()
    (let ((socket (listen-socket (bind-socket (create-socket) 5000)))
          (msg nil) )
       (setq msg (receive-socket socket))
       (while (not (equal msg "quit"))
          (format (standard-output) msg)
          (send-socket socket "receive data")
          (setq msg (receive-socket socket)))
       (close-socket socket)))

(defun client (ip)
    (let ((socket (connect-socket (create-socket) ip))
          (msg nil) )
       (setq msg (read-line))
       (while (not (equal msg "end"))
          (send-socket socket msg)
          (setq msg (receive-socket socket))
          (format (standard-output) msg)
          (setq msg (read-line)))
       (close socket)))
