#include <stdio.h>

int main(int argc, char** argv)
{
  char buffer[10];
  fgets(buffer, 10, stdin);
  printf("Got: %s\n", buffer);
}
