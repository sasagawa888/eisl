# TCPIP

This is a library for TCP/IP communication.
Thanks to "poldy" for his contributions.

# Usage

```lisp
(import "tcpip")
```

See the following sample code:

```lisp
(import "tcpip")
;; Please compile tcpip.lsp in library before. 

;; (set-dynamic *default-ip-version* 'ipv6)

(defun server ()
  (let ((s (create (class socket)))
        (c nil)
        (msg ""))
    (setf (socket-ip s) (get-host-address "localhost"))
    (setf (socket-n s) 5000)
    (create-server s)
    (setq c (server-accept s))
    (while (not (string= msg "end"))
           (setq msg (socket-receive c))
           (print msg)
           (socket-send c msg))
    (socket-close s)))

(defun client ()
  (let ((s (create (class socket)))
        (msg ""))
    (setf (socket-ip s) (get-host-address "localhost"))
    (setf (socket-n s) 5000)
    (client-connect s)
    (while (not (string= msg "end"))
           (setq msg (read))
           (socket-send s msg)
           (setq msg (socket-receive s))
           (print msg))
    (socket-close s)))
```

Support for I/O multiplexing, e.g. `select` or `poll`, may be necessary in the future.
