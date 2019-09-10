#include <stdio.h>
#include <string.h>

void process_input(char input[])
{
  char * underTen[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  char * underTwenty[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  char * multiplesOfTen[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
  char * bigNumbers[] = {"hundred", "thousand", "million"};

  
}

int main(int argc, char** argv)
{
  char buffer[10];
  int length;
  fgets(buffer, 10, stdin);
  length = strlen(buffer) - 1;
  printf("Length: %d\n", length);
  printf("Got: %s\n", buffer);
}
