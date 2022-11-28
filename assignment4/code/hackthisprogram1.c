#include <stdio.h>
#include <string.h>

int IsPasswordOkay(char *pwd)
{
  char Password[12];
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
  // can add more puts here
  puts("Important data");
  puts("Important data");
  puts("Important data");
  puts("Important data");
  puts("Important data");
  return 0;
} 
