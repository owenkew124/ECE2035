#=================================================================
# Copyright 2021 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

#     When Harry Met Sally
#
# HW2-2
# Student Name: Owen Kew
# Date:  9/17/21
#
# This program finds the total number of years during which Harry and Sally
# lived in the same city at the same time.
#
#  required output register usage:
#  $2: total number of years in same city at same time
#  result must be reported by calling: swi 590

.data
Harry:  .alloc  10               # allocate static space for 5 moves
Sally:  .alloc  10               # allocate static space for 5 moves

.text
WhenMet:	addi  $1, $0, Harry     	# set memory base
			swi     597             	# create timelines and store them
			addi  $10, $0, Sally    	# loads Sally's Array into register 10
		    addi  $4, $0, 30        	# set up total time left in register 4
			lw    $5, 0($1)         	# set up Harry's time in register 5
			addi  $1, $1, 4         	# increments Harry's Address to get city value
			lw    $6, 0($1)         	# set up Harry's city value in register 6
			lw    $7, 0($10)        	# set up Sally's time in register 7
			addi  $10, $10, 4       	# increments Sally's Address to get city value
			lw    $8, 0($10)        	# set up Sally's city value in register 8
			addi  $2, $0, 0         	# initializes the number of years spent in the same city to 0 in register 2
Loop:		beq   $4, $0, End			# branch to the end if the total time left is 0
			bne   $5, $0, Sally0    	# branch to the Sally = 0 check if Harry's time is not 0
			addi  $1, $1, 4         	# increments Harry's address to get next time value
			lw    $5, 0($1)				# puts the Harry's next time value into register 5
			addi  $1, $1, 4				# increments Harry's address to get next city value
			lw    $6, 0($1)				# puts the Harry's next city value into register 6
			
Sally0:		bne   $7, $0,  Start		# branch to the start of the calculations if Sally's time is not zero
			addi  $10, $10, 4	    	# increments Sally's address to get next time value
			lw    $7, 0($10)	    	# puts the Sally's next time value into register 7
			addi  $10, $10, 4	    	# increments Sally's address to get next city value
			lw    $8, 0($10)	    	# puts the Sally's next city value into register 8
			
Start:		bne   $6, $8, NotMet	    # branch to the "not met" set of calculations if Harry and Sally weren't in the same city   
            slt   $9, $5, $7	    	# check if Harry was in the city for a shorter time
			bne   $9, $0, SallyBig	    # branch to the SallyBig calculations if Harry was in the city for a shorter time
			slt   $9, $7, $5	    	# check if Sally was in the city for a shorter time
			bne   $9, $0, HarryBig	    # branch to the HarryBig calculations if Sally was in the city for a shorter time
			sub   $4, $4, $5	    	# subtract Harry's time from the total time left (it did not matter if I subtracted Sally's time from this as Harry's time == Sally's time)  
			add   $2, $2, $5	    	# adds Harry's time to the total years spent in the same city
			sub   $5, $5, $5	    	# resets Harry's time to 0
			sub   $7, $7, $7	    	# resets Sally's time to 0
			j Loop	    				# jump to the start of the loop
									
SallyBig:   sub   $4, $4, $5	    	# subtract the lesser time value (Harry's) from the total time left
			sub   $7, $7, $5	    	# subtract the lesser time value (Harry's) from the greater time value (Sally's) 
			add   $2, $2, $5	    	# add the lesser time value (Harry's) to the total time spent in the same city
			sub   $5, $5, $5	    	# resets Harry's time value to 0
			j Loop	    				# jump to the start of the loop
            
HarryBig:   sub   $4, $4, $7	    	# subtract the lesser time value (Sally's) from the total time left
			sub   $5, $5, $7	    	# subtract the lesser time value (Sally's) from the greater time value (Harry's) 
			add   $2, $2, $7	    	# add the lesser time value (Sally's) to the total time spent in the same city
			sub   $7, $7, $7	    	# resets Harry's time value to 0
			j Loop	    				# jump to the start of the loop
            
NotMet:     slt   $9, $5, $7	    	# check if Harry was in the city for a shorter time
			bne   $9, $0, NMSallyBig	# branch to the NMSallyBig calculations if Harry was in the city for a shorter time
			slt   $9, $7, $5	    	# check if Sally was in the city for a shorter time
			bne   $9, $0, NMHarryBig	# branch to the NMHarryBig calculations if Sally was in the city for a shorter time
			sub   $4, $4, $5	    	# subtract Harry's time from the total time left (it does not matter if I subtract Sally's time from this as Harry's time == Sally's time)
			sub   $5, $5, $5	    	# resets Harry's time to 0
			sub   $7, $7, $7	    	# resets Sally's time to 0
			j Loop	    				# jump to the start of the loop
			
NMSallyBig: sub   $4, $4, $5	    	# subtract the lesser time value (Harry's) from the total time left
			sub   $7, $7, $5	    	# subtract the lesser time value (Harry's) from the greater time value (Sally's)
			sub   $5, $5, $5	    	# resets Harry's time value to 0
			j Loop	    				# jump to the start of the loop
            
NMHarryBig: sub   $4, $4, $7	    	# subtract the lesser time value (Sally's) from the total time left
			sub   $5, $5, $7	    	# subtract the lesser time value (Sally's) from the greater time value (Harry's)
			sub   $7, $7, $7	    	# resets Harry's time value to 0
			j Loop						# jump to the start of the loop
			
End:	swi     590						# give answer
        jr      $31             		# return to caller
