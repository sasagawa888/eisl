;;; test code for TCP/IP functions

(defglobal ip "127.001.001.01") ; change your server ip address

(defun server ()
    (let* ((s1 (progn (print "create") (socket-create)))
           (s2 (progn (print "bind") (socket-bind s1 5000)))
           (s3 (progn (print "listen") (socket-listen s2)))
           (socket (progn (print "accept") (socket-accept s3)))
           (msg nil) )
       (setq msg (receive-socket socket))
       (while (not (equal msg "quit"))
          (format (standard-output) msg)
          (socket-send socket "receive data")
          (setq msg (socket-receive socket)))
       (socket-close socket)))

(defun client ()
    (let ((socket (socket-connect (socket-create) ip))
          (msg nil) )
       (setq msg (read-line))
       (while (not (equal msg "end"))
          (socket-send socket msg)
          (setq msg (socket-receive socket))
          (format (standard-output) msg)
          (setq msg (read-line)))
       (socket-close socket)))
