.data

menu: .asciiz "Main Menu:\n 1.Check Balance\n 2.Deposit Money\n 3.Withdraw Money\n 4.Exit\n"
exit: .asciiz "Thank you for using the ATM. Goodbye!\n"

newLine: .asciiz "\n"

total_amount: .word 1000
total_amount_msg: .asciiz "Current Balance: "

deposit_amount_msg: .asciiz "enter deposit amount: "
deposit_amount_ErrorBiggerThan5000$: .asciiz "Error: Deposit amount cannot exceed $5000\n"

ErrorNotANumber: .asciiz "Error: Input is not legal\n"

withdrawl_amount_msg: .asciiz "enter withdrawal amount: "
withdrawl_amount_ErrorBiggerThanLimitOrMoreThanDeposit: .asciiz "Error: Insufficient funds or withdrawal limit exceeded\n"

buffer: .space 32  # Buffer to store user input

stack_start_pointer: .word 0
Enter_PIN: .asciiz "Enter PIN: "
Incorrect_PIN_msg: .asciiz "Error: Incorrect PIN\n"
wrong_pin_msg: .asciiz "Error: No attempts remaining. Exiting program"

.text

li $t0,0
enter_pin:
        beq $t0,3,wrong_pin_exit

	la $a0,Enter_PIN
	jal print_Str
	
	jal read_Int
	
	bne $v0,1234,wrong_pin
	beq $v0,1234,main
wrong_pin:

	la $a0,Incorrect_PIN_msg
	jal print_Str
	add $t0,$t0,1
	j enter_pin
	
#---------------The Pin is good so now we are entering Main-------------------
main:
	la $a0,menu
	jal print_Str
	
	jal read_Int
	
	beq $v0,1,Check_Balance
	beq $v0,2,Deposit
	beq $v0,3,Withdraw
	beq $v0,4,exit_program
	
	j main
	
Check_Balance: #Checks User balance function
	la $a0, total_amount_msg  
	jal print_Str
	
	lw $a0,total_amount
	jal print_Int
	
	la $a0,newLine
	jal print_Str
	
	j main
	
Deposit: #User Deposit Function

	la $a0,deposit_amount_msg
	jal print_Str
	
	jal read_Str
	
	subi $sp,$sp,4
	sw $s1,($sp)
	jal CheckUserInputIsNumberAndSaveTo$s1
	
	bgt $s1,5000,DepositGreaterthan5000 #Checks input not bigger than 5000
	
	lw $a0,total_amount
	add $a0,$a0,$s1
	sw $a0,total_amount

	lw $s1,($sp)
	addi $sp,$sp,4
	
	j main

DepositGreaterthan5000: #Checks that user input is not bigger than 5000
	la $a0,deposit_amount_ErrorBiggerThan5000$
	jal print_Str
	
	addi $sp,$sp,4
	
	j main

Withdraw:#User withdraw Function
	la $a0,withdrawl_amount_msg
	jal print_Str
	
	jal read_Str           
        
        subi $sp,$sp,4
        sw $s1,($sp)
        jal CheckUserInputIsNumberAndSaveTo$s1
  
	bgt $s1,500,WithdrawlOverLimitOrMoreThanBalance #Checks user input is not more than 500
	lw $a0,total_amount
	bgt $s1,$a0,WithdrawlOverLimitOrMoreThanBalance #checks user input is not greater than overall balance

	sub $a0,$a0,$s1
	sw $a0,total_amount
	
	lw $s1,($sp)
	addi $sp,$sp,4
	
	j main
	
WithdrawlOverLimitOrMoreThanBalance: #called if user input bigger than balance
	la $a0,withdrawl_amount_ErrorBiggerThanLimitOrMoreThanDeposit
	jal print_Str
	addi $sp,$sp,4
	j main
ErrorNotANumberFunc: #called if user input is not an int number
	la $a0,ErrorNotANumber
	jal print_Str
	addi $sp,$sp,4
	j main
	
CheckUserInputIsNumberAndSaveTo$s1: #a function that checks that user input is an int number
    	la $a0, buffer
	find_end_of_string: #finding a pointer to the end of a user given string
    		beq $a0,5, ErrorNotANumberFunc #if user input is longer than 5 chars (4 digits + 1 "\n" )
    		lb $t1, 0($a0)        # load the next character of the input string
    		beq $t1, 0, end_of_string   # if the character is null, it's the end of the string
    		addi $a0, $a0, 1     # move to the next character
    		j find_end_of_string
    
    
	end_of_string:  #now end pointer in $a0

    	move $a1,$a0 #a1 is now pointing to end of string
    	la $a0,buffer
    			#t1 to store the letter and then converting to number
			#t2 for counting power of tens (10) 
			#t3 for number of loops
			#s1 for total sum

    	
    	
    	sub $t3,$a1,$a0 #the difference between $a1 and $a0 is the number of needed loops +1
    	sub $t3,$t3,1
    	
    	move $s1,$zero
    	li $t2,1
    	la $a0,($a1)
    	
	Convert_Char_To_Number_Loop:
    		sub $a0,$a0,1
    		lb $t1,($a0) #loads char into $t1
    	
    		beq $t1,10,Convert_Char_To_Number_Loop #if "\n" continue
    		blt $t1, 48, ErrorNotANumberFunc  # if the character is less than '0', it's not a digit
   		bgt $t1, 57, ErrorNotANumberFunc # if char is more than '9', its not a digit
    
    		sub $t1,$t1,48 #convert to digit
    		
    		mul $t1,$t2,$t1 #multiply it by power of tens
    		add $s1,$s1,$t1 #add the sum to $s1
    		
    		mul $t2,$t2,10
    		
    		sub $t3,$t3,1
    		bne $t3,0,Convert_Char_To_Number_Loop
      
       
    	jr $ra
print_Str:    
	li $v0,4
	syscall
	jr $ra
	
print_Int:
	li $v0,1
	syscall
	jr $ra
	
read_Int:
	li $v0,5
	syscall
	jr $ra 

read_Str:
	li $v0, 8   
	la $a0,buffer 
	li $a1,32        # syscall code for reading a string            # maximum number of characters to read
	syscall
	jr $ra
exit_program:
	la $a0,exit
	jal print_Str
	li $v0,10
	syscall
	
wrong_pin_exit:
	la $a0,wrong_pin_msg
	jal print_Str
	li $v0,10
	syscall
