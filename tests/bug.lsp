;;; test code for TCP/IP functions

(defglobal ip "127.001.001.01") ; change your server ip address

(defun server ()
    (let ((socket (socket-accespt (socket-listen (socket-bind (socket-create) 5000))))
          (msg nil) )
       (setq msg (receive-socket socket))
       (while (not (equal msg "quit"))
          (format (standard-output) msg)
          (socket-send socket "receive data")
          (setq msg (socket-receive socket)))
       (socket-close socket)))

(defun client (ip)
    (let ((socket (socket-connect (socket-create) ip))
          (msg nil) )
       (setq msg (read-line))
       (while (not (equal msg "end"))
          (socket-send socket msg)
          (setq msg (socket-receive socket))
          (format (standard-output) msg)
          (setq msg (read-line)))
       (socket-close socket)))
