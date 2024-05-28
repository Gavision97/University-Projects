.data
NameBuffer: .space 100
IntBufferID: .space 4
IntBufferBalance: .space 4
StartingStackPointer: .space 4

MainMenuPrompt: .asciiz "Main Menu:\n 1.add_customer\n 2.display_customer\n 3.update_balance\n 4.delete_record\n 5.exit_program\n Enter your choice (1-5): "
InvalidMenuInputPrompt: .asciiz "Invalid choice. Please enter a number between 1 and 5\n"
EnterIdPrompt: .asciiz "Enter ID: "
EnterNamePrompt: .asciiz "Enter Name: "
EnterBalancePrompt: .asciiz "Enter Balance: "
CustomerAlreadyInDatabasePromptPart1: .asciiz "Error:Customer "
CustomerAlreadyInDatabasePromptPart2: .asciiz " already exists\n"
AddCustomerSuccessPromptPart1: .asciiz "Success:Customer "
AddCustomerSuccessPromptPart2: .asciiz " was added\n"
DisplayCustomerSuccessPrompt: .asciiz "Success: "
DisplayCustomerDoesntExistPromptPart1: .asciiz "Error: Customer "
DisplayCustomerDoesntExistPromptPart2: .asciiz " doesn't exist\n"
BalanceNotValidPrompt: .asciiz "Error: The inputted balance isn’t valid\n"
CustomerDeletedPromptPart1: .asciiz "Success: Customer "
CustomerDeletedPromptPart2: .asciiz " deleted\n"
ExitPrompt: .asciiz "Exiting program"
AllocationFailed: .asciiz "Allocation Failed!\n"
Space: .asciiz " "
newLine: .asciiz "\n"
BackshlashZeroBite: .asciiz "\0"

.text
	sw $sp,StartingStackPointer
main:

	la $a0,MainMenuPrompt
	jal print_Str
	
	jal read_Int
	
	#for each part, if user input not equal the part int, it jumps to the next part
	# if user input=2, main checks if its not ==1 then it jumps to next check
	addCustomerPart:
	
	bne $v0,1,displayCustomerPart
	
	la $a0,EnterIdPrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferID
	
	la $a0,EnterNamePrompt
	jal print_Str
	jal read_Str
	
	la $a0,EnterBalancePrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferBalance
	
	j addCustomerFunc
	
	displayCustomerPart:
	bne $v0,2,updateBalancePart
	la $a0,EnterIdPrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferID
	
	j displayCustomerFunc
	
	updateBalancePart:
	bne $v0,3,deleteRecordPart
	
	la $a0,EnterIdPrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferID
	
	la $a0,EnterBalancePrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferBalance
	
	j updateBalanceFunc
	
	deleteRecordPart:
	bne $v0,4,exitProgramPart
	la $a0,EnterIdPrompt
	jal print_Str
	jal read_Int
	sw $v0,IntBufferID
	
	j deleteRecordFunc
	exitProgramPart:
	bne $v0,5,InvalidInput
	j exitProgramFunc
	InvalidInput:
	la $a0,InvalidMenuInputPrompt
	jal print_Str
	
	j main



addCustomerFunc:
	
	jal CheckIfGivenIdInDatabase
	bne $s0,0,CustomerAlreadyInDatabase
	

	jal AllocateNewCustomerMemory #allocates memory for new customer, 
				       #now address of allocated memory in $v0
				       #if allocation failed the program returns to main
	
	la $a0,($v0) #loades the allocated memory into $a0
	sub $sp,$sp,4
	sw $a0,($sp) #stores the customer memory address to the stack
	
	
	#now go and store each user input in its place in memory
	lw $v0,IntBufferID
	sw $v0,($a0)
	
	
	# TODO : Delete it
	# I change the code because when trying to add the name to the heap, it's
	# added only 4bits. For example : if the name was : Victorrrrrr
	# the name on the heap was only : Vict
	# So i added loop which iterates and adds letter letter (bite afrer bite)
	# to the heap, now it work
	
	# TODO : Delete the old two lines:
	#lw $v0,NameBuffer
	#sw $v0,4($a0)
	
    	# Copy the string input to the allocated memory block
    	move $s2, $zero     # Counter for string input
    	add $a0, $a0, 4     # Start of string buffer in allocated memory
    	loop_copy_string:
        	lb $t0, NameBuffer($s2)     
        	beq $t0, $zero, end_copy_string   # If null terminator, end loop
        	sb $t0, ($a0)                   # Store byte to allocated memory block
        	addi $s2, $s2, 1                # Increment string buffer counter
        	addi $a0, $a0, 1                # Increment allocated memory block counter
        	j loop_copy_string
        	
        	
    	end_copy_string:
    	# After done copying, go one byte backwards in order to replace "\n" byte with "\0" byte.
    	# Then, substract from 100 the number of bytes the Name nedeed, in order to know how many
    	# bites to go further to reach the 104th byte. 
    	# For example, if the name 'Yossiel' , $t1 <- 100 - 7 = 93
    	
    		    subi $a0, $a0, 1
    		    subi $s2, $s2, 1
    		    lb $t0, BackshlashZeroBite
    		    sb $t0, ($a0)
        	    li $t1, 100
        	    sub $t1, $t1, $s2
        	    
	add $a0, $a0, $t1     # Fix heap pointer according to $t1 register value
	
	lw $v0,IntBufferBalance
	sw $v0, ($a0)
	
	#print customer success
	la $a0,AddCustomerSuccessPromptPart1
	jal print_Str
	lw $a0,IntBufferID
	jal print_Int
	la $a0,AddCustomerSuccessPromptPart2
	jal print_Str
	
	j main




displayCustomerFunc:

	#in this function we run on each stored data in stack and check if the id is
	#== to user given id
	lw $a0,($sp)
	la $a0,($a0)
	
	lw $t0,IntBufferID
	lw $t1,StartingStackPointer
	
	LookForIDLoop:
	lw $t2,($a0) #loads id to $t2
	beq $t2,$t0,FoundIDAddress
	beq $a0,$t1,CustomerNotInDatabase #check if we are at the limit of $sp addresses
	addi $a0,$a0,4
	j LookForIDLoop
	
	#if we find a match we execute this part
	FoundIDAddress:
	la $t0,($a0)
	la $a0,DisplayCustomerSuccessPrompt
	jal print_Str
	
	lw $a0,($t0)
	jal print_Int
	
	la $a0,Space
	jal print_Str
	
	la $a0,4($t0)
	jal print_Str
	
	la $a0,Space
	jal print_Str
	
	lw $a0,104($t0)
	jal print_Int
	
	la $a0,newLine
	jal print_Str

	j main
	
updateBalanceFunc:
	jal CheckIfGivenIdInDatabase
	beq $s0,0,CustomerNotInDatabase
	
	#go directly to the balance in memory using the address in $s0
	la $s0,104($s0)
	lw $t0,IntBufferBalance
	
	bgt $t0,99999,BalanceNotValid
	blt $t0,0,BalanceNotValid
	la $a0,($s0)
	sw $t0,($a0)
	j main	
	
deleteRecordFunc:
	#looks for the id in memory, if theres a match we run on each memory and maake it zero
	#because zero is an integer it takes 4 byte so to make 108 bytes equal 0 we need to run
	#the loop 26~ times
	jal CheckIfGivenIdInDatabase
	beq $s0,0,CustomerNotInDatabase
	
	li $t0,0
	move $t1,$zero
	la $a0,($s0)
	sw $t1,($a0)
	addi $a0,$a0,4
	move $t4,$zero
	NullLoop:
	sw $zero,($a0)
	addi $a0,$a0,4
	addi $t0,$t0,1
	bne $t0,26,NullLoop
	
	la $a0,CustomerDeletedPromptPart1
	jal print_Str
	
	lw $a0,IntBufferID
	jal print_Int
	
	la $a0,CustomerDeletedPromptPart2
	jal print_Str
	  
	j main
		
exitProgramFunc:
	la $a0,ExitPrompt
	jal print_Str
	
	li $v0,10
	syscall
	
CheckIfGivenIdInDatabase: #$s0 is 0 if doesnt exist,else its the address
	la $a0,($sp)
	
	lw $t0,IntBufferID
	lw $t1,StartingStackPointer
	
	LookForIDLoopInCheck:
	beq $a0,$t1,DidntFindID
	lw $t2,($a0)
	lw $t2,($t2)
	beq $t2,$t0,FoundIDAddressInCheck
	addi $a0,$a0,4
	j LookForIDLoopInCheck
	
	FoundIDAddressInCheck:
	lw $s0,($a0)
	jr $ra	
	DidntFindID:
	li $s0,0
	jr $ra
	
CustomerAlreadyInDatabase:
	la $a0,CustomerAlreadyInDatabasePromptPart1
	jal print_Str
	
	la $a0,IntBufferID
	jal print_Int
	
	la $a0,CustomerAlreadyInDatabasePromptPart2
	jal print_Str
	
	j main
	
CustomerNotInDatabase:
	la $a0,DisplayCustomerDoesntExistPromptPart1
	jal print_Str
	
	lw $a0,IntBufferID
	jal print_Int
	
	la $a0,DisplayCustomerDoesntExistPromptPart2
	jal print_Str
	
	j main
BalanceNotValid:
	la $a0,BalanceNotValidPrompt
	jal print_Str
	
	j main

AllocateNewCustomerMemory:
	 li $v0, 9   # Set syscall number for sbrk
   	 li $a0, 108        # Set the amount of space to allocate (e.g., 100 bytes)
    	 syscall            # Invoke sbrk syscall
    	beqz $v0, allocation_unsuccessful  # Branch if successful
    	jr $ra
    	allocation_unsuccessful:
    	j main

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
	la $a0,NameBuffer 
	li $a1,100       # syscall code for reading a string            # maximum number of characters to read
	syscall
	jr $ra
