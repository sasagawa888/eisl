# TCP/IP
Currently, only IPv4 is supported. There are plans to support IPv6 in the future.
The functionality is minimal. If you need any additional features, please write in the issues.
Pull requests are also welcome.


| Function                      | Description                                    |
| ----------------------------- | ---------------------------------------------- |
| (create-server-socket port)   | create socket for server see TCPIP.md          |
| (create-client-socket port ip)| create socket for client see TCPIP.md          |
| (send-socket socket str)      | send message to socket                         |
| (recv-socket socket)          | receive message from socket                    |
| (close-socket socket)         | close socket                                   |
  

# Specifications
- (create-server-socket port)
Creates and returns a socket as a server based on the port number.
Provide the port number to port. It ranges from 0 to 65536.

- (create-client-socket port ip-address)
Provide the port number to port. It ranges from 0 to 65536.
ip-address is given as a string. Example: "127.1.1.1"
Returns a socket as a client if successful.

- (send-socket socket string)
Sends a string to the socket.
Returns T.

- (recv-socket socket)
Receives from the socket and returns a string.

- (close-socket socket)
Closes the socket.
Returns T.


# Usage

See the following sample code:

```lisp
;;; test code for TCP/IP functions

(defglobal ip "127.1.1.1") ; change your server ip address

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
```

# Error Handling

- Port Number: If a non-integer is provided, a non-integer error is raised.
- IP Address: If a non-string is provided, a non-string error is raised.
- Socket: If a non-socket is provided, a WRONG_ARGUMENT error is raised.
- Internal Processing: If an error occurs in socket(...), bind(...), listen(...), accept(...), connect(...), send(...), or recv(...), a system error is raised.
