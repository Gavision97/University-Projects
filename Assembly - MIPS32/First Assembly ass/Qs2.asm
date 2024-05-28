.data
# ------------------------Write Your Code Here------------------------------
arr: .space 40 # Allocate space for the array (10 integers)
# ------------------------Write Your Code Here-------------------------------
newline:    .asciiz "\n"
result_true: .asciiz "True\n"
result_false: .asciiz "False\n"

.text
main:
    # first 2 elements, don't forget to store them in arr
    li $t0, 0 
    li $t1, 1
    
    # ------------------------Write Your Code Here------------------------------
    la $a0, arr # loading arr address to register
    la $a0, arr  # loading arr address to register
    sw $t0, 0($a0)  # store the first element in arr
    sw $t1, 4($a0)  # store the second element in arr
    addi $a0,$a0,8
    li $t7, 8 # for loop the bnez 

loop:
    add $t2, $t0, $t1
    sw $t2,0($a0)
    
    move $t0, $t1
    move $t1, $t2
    
    addi $a0, $a0, 4   # move to the next position in the destination array
    sub $t7, $t7, 1    # decrement the loop counter
    bnez $t7, loop     # branch back to loop if $t7 is not zero


    # ------------------------Write Your Code Here-------------------------------
    la $s0, arr
    j check_array


check_array:
    # Check if the first element is 0 and the second one is 1
    lw $t1, 0($s0)   # Load the first element from the array pointed by $s0
    lw $t2, 4($s0)   # Load the second element from the array pointed by $s0

    li $t3, 0       # Constant value for comparison
    li $t4, 1     # Constant value for comparison

    # Check the conditions
    beq $t1, $t3, check_second_element
    j print_false

check_second_element:
    beq $t2, $t4, print_true
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
