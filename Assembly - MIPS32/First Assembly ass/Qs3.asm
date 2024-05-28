.data
# ------------------------Write Your Code Here------------------------------
arr: .space 40 # Allocate space for the array (10 integers)
arr2: .word -23, 2354, 34, 10, -3553, 4234, 81, 90, 634, -27

# ------------------------Write Your Code Here-----------------------------
newline:    .asciiz "\n"
result_true: .asciiz "True\n"
result_false: .asciiz "False\n"



.text
main:
    # ------------------------Write Your Code Here------------------------------
    la $a0,arr2
    li $t0,10
    lw $s0,($a0)
    lw $s1,($a0)
    li $s2,0
    li $s3,0

MainLoop:
    sub $t0,$t0,1
    lw $t1,($a0)
    add $s2,$s2,$t1
    ble $s1,$t1,NoMax
    move $s1,$t1
NoMax:
    bgt $s0,$t1,NoMin
    move $s0,$t1
NoMin:
    addi $a0,$a0,4
    bge $t0,1,MainLoop

    div $s3,$s2,10
    j checkQs3Partialy


checkQs3Partialy:
	li $t5, 4234
	beq $s0, $t5, print_true
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
