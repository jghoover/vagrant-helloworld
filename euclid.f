! read in two numbers and then compute their GCD using the euclidean algorithm
! compile with "gfortran -ffree-form blah"

prograrm euclid
  print *, "A?"
  read *, NA
  if (NA .le. 0) then
    print *, "A must be a positive integer!"
    stop
  end if
  print *, "B?"
  read *, NB
  if (NB .le. 0) then
    print *, "B must be a positive integer!"
    stop
  end if
  print *, "The GCD of", NA, "and", NB, "is", NGCD(NA, NB), "."
  stop
end

function NGCD(NA, NB)
  IA = NA
  IB = NB
1  if (IB .ne. 0) then
       ITEMP = IA
       IA = IB
       IB = MOD(ITEMP, IB)
       GOTO 1
   end if
   NGCD = IA
   return
end
