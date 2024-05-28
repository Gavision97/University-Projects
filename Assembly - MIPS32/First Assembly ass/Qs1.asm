.data
# ------------------------Write Your Code Here------------------------------

# ------------------------Write Your Code Here-----------------------------
newline:    .asciiz "\n"
result_true: .asciiz "True\n"
result_false: .asciiz "False\n"



.text
main:
    # You must use the values of these registers
    li $t0, 15 #A
    li $t1, 30 #B
    # ------------------------Write Your Code Here------------------------------
    #solving C
    add $s0, $t0,$t1
    # ------------------------Write Your Code Here-------------------------------
   #Solving D
   
    addi $t3, $t0,200
    subi $t3, $t3,6
    add $s1,$t3,$zero
    
    #Solving from here for E
    move $t3,$zero
    move $t4,$zero
    
 loopforE: #creating a loop to simulate multiplying b bTimes 
    
    add $t4,$t4,$t1
    addi $t3,$t3,1 		
    bne $t3,$t1,loopforE
    j loopFinished
    
 loopFinished:		
   addi $s2,$t4,$zero
 
 #Solving for F
   add $t2,$s0,$s1
   add $t2,$t2,$s2
   subi $s3,$t2,2
   
    j checkQs1Partialy


checkQs1Partialy:
	li $t5, 900
	#beq $s0, $t5, print_true
	beq $s2,$t5, print_true
	j print_false

print_true:
    # Print True
    li $v0, 4      # System call for print_str
    la $a0, result_true
    syscall
    j end_program

print_false:
    # Print False
    li $v0, 4      # System call for print_str
    la $a0, result_false
    syscall

end_program:
    # Exit the program
    li $v0, 10
    syscall
