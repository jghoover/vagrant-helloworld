(defun hello (name) "Doc string: When given a name as an argument, tell that person hello!"
  (write-line (format nil "Hello, ~A!" name)))

(write-line "Hello, World!")
(write-line "What is your name?")
(hello (read-line))