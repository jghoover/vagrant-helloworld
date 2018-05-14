(defun prime-rec (n div limit) "Recursively check if  (= (mod n div) 0)."
  (cond ((> div limit) t)
	((= (mod n div) 0) nil)
	(t (prime-rec n (+ div 2) limit))))

(defun primeP (n) "Takes a number as input and then determines if it's prime.  Returns TRUE or NIL."
  (cond ((= 2 n) t)
	((< n 2) nil)
        ((evenp n) nil)
	(t (prime-rec n 3 (ceiling (sqrt n))))))

(defun count-primes-rec (limit next count) "Recursively iterate through numbers and increment count if next is prime."
  (cond ((> next limit) count) ; base case
	((primeP next) (count-primes-rec limit (+ next 2) (+ count 1))) ; first recursive case: next is prime
	(t (count-primes-rec limit (+ next 2) count)))) ; second recursive case: next isn't prime

(defun count-primes (limit) "Count the number of primes <= limit."
  (cond ((= 2 limit) 1)
	((< limit 2) 0)
	(t (count-primes-rec limit 3 1 ))))


;;; fast-count-primes doesn't work right now.
(defun divides-anyP (n numbers sqrtN) "Check if any element of numbers divides n evenly. Assumes that numbers is sorted in nondecreasing order" 
  (cond ((> (car numbers) sqrtN) nil) ; base case 1: we've exhausted our search range, so there are no divisors
	((= (mod n (car numbers)) 0) t) ; base case 2: we found a divisor for n
	(t (divides-anyP n (cdr numbers) sqrtN)))) ; recursive case: check the rest of the list

(defun fast-count-primes-rec (limit next numbers) "Recursively iterate through numbers up to the limit, appending primes to a list of next numbers to check."
  (cond ((> next limit) (list-length numbers)) ; base case
	((divides-anyP next numbers (ceiling(sqrt next))) (fast-count-primes-rec limit (+ next 2) numbers)) ; first recursive case: next isn't prime
	(t (fast-count-primes-rec limit (+ next 2) (append numbers next))))) ; second recursive case: next is prime

(defun fast-count-primes (limit) "Count the number of primes <= limit, a little faster."
  (cond ((= 2 limit) 1)
	((< limit 2) 0)
	(t (fast-count-primes-rec limit 3 `(2)))))