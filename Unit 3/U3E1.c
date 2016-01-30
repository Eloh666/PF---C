#include <stdio.h>
#include <string.h>

void change(char *p);

int main(int argc, char **argv)
{
  char test[] = "James\n";
  int len;
  char *p = &test[0];
  printf("this is a sample intel syntaxed and inlined c program\n");
  len = strlen(test);
  printf("%d\n",len);
  printf(test);
  change(p);
  printf(test);
  return 0;
}

void change(char *p)
{
  __asm__ __volatile__(
    ".intel_syntax noprefix 			\n\t"
    "mov        eax,[ebp+8]                     \n\t"
    "mov        byte ptr [eax],65               \n\t"
    ".att_syntax prefix 			\n\t"
    :
    :"g"(p)
    :"%eax"
    );
}
