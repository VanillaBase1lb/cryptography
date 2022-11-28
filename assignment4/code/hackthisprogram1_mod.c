#include <stdio.h>
#include <string.h>

int IsPasswordOkay(char *pwd)
{
  char Password[36];
  // gets(Password);
	strcpy(Password, pwd);
  if (!strcmp(Password, "goodpass"))
    return 1;

  printf("%s",Password);
	return 0;
}

int main(int argc,char* argv[])
{
  int PwStatus;

  puts("Enter password:");
  PwStatus = IsPasswordOkay(argv[1]);
  if (PwStatus == 0) {
    puts("Access denied");
    return -1;
  }
  puts("Access granted");
  return 0;
} 
