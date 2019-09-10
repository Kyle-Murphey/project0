#include <stdio.h>
#include <string.h>

void process_input(char input[], int length)
{
  const char * underTen[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const char * underTwenty[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  const char * multiplesOfTen[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
  const char * bigNumbers[] = {"hundred", "thousand", "million"};

  int number;
  int flag = 0;
  int actualLength = length;
  for (int i = 0; i < length; ++i)
    {
      number = input[i] - '0';
      if (number > 0)
	{
	  flag = 1;
	}
      if (number == 0 && flag == 0)
	{
	  --actualLength;
	  continue;
	}
      else if (actualLength == 1)
	printf("output: %s\n", underTen[number - 1]);
    }
  if (length == 1)
    {
      //int number = input[0] - '0';
      //printf("output: %s\n", underTen[number - 1]);
    }
}

int main(int argc, char** argv)
{
  char buffer[10];
  int length;
  fgets(buffer, 10, stdin);
  length = strlen(buffer) - 1;

  if (length == 1)
    {
      int a = buffer[0] - '0';
      printf("item: %d\n", a);
    }
  
  printf("Length: %d\n", length);
  printf("Got: %s\n", buffer);

  process_input(buffer, length);
}
