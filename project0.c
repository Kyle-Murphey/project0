#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char * underTen[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static char * underTwenty[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
static char * multiplesOfTen[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
static char * bigNumbers[] = {"hundred", "thousand", "million"};

void parseOverThree(char inputArr[], int * digitsLeft, int * pos, char ** output, int * index)
{
  int comFlag = 0;
  int number = inputArr[*pos] - '0';

  //checks if the input is the start of a triplet
  if (*digitsLeft % 3 == 0 && number > 0)
    {
      output[*index] = underTen[number - 1];
      ++*index;
      output[*index] = bigNumbers[0];
      ++*index;
      ++*pos;
      --*digitsLeft;
    }
  //checks if digit is one place infront of a triplet
  if ((*digitsLeft == 4 || *digitsLeft == 7) && inputArr[*pos] - '0' > 0 && inputArr[*pos - 1] - '0' != 1 )
    {
      output[*index] = underTen[(inputArr[*pos] - '0') - 1];
      comFlag = 1;
      ++*index;
    }
  //checks for a nonzero digit in the tens place
  else if (inputArr[*pos] - '0' > 0 && *digitsLeft > 1)
    {
      //checks if number is over 19
      if (inputArr[*pos] - '0' != 1)
	{
	  output[*index] = multiplesOfTen[(inputArr[*pos] - '0') - 2];
	  ++*index;
	  ++*pos;
	  --*digitsLeft;
	}
      //digit is a teen
      else
	{
	  output[*index] = underTwenty[inputArr[*pos + 1] - '0'];
	  ++*index;
	  ++*pos;
	  --*digitsLeft;
	  comFlag = 1;
	}
    }
  //increments to next digit if current is zero and next is > zero
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft > 1 && inputArr[*pos + 1] - '0' > 0)
    {
      ++*pos;
      --*digitsLeft;
    }
  //check if triplet of zeros
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft % 3 == 0 && inputArr[*pos + 1] - '0' == 0 && inputArr[*pos + 2] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
    }
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft % 3 == 0 && inputArr[*pos + 1] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
    }
  //check for double zeros
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft > 2 && inputArr[*pos + 1] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
      comFlag = 1;
    }


  if (inputArr[*pos] - '0' > 0 && comFlag != 1)
    {
      if (*digitsLeft == 2 || *digitsLeft == 5)
	{
	  //checks if number is over 19
	  if (inputArr[*pos] - '0' != 1)
	    {
	      output[*index] = multiplesOfTen[(inputArr[*pos] - '0') - 2];
	      ++*index;
	      ++*pos;
	      --*digitsLeft;

	      output[*index] = underTen[(inputArr[*pos] - '0') - 1];
	      ++*index;
	      ++*pos;
	      --*digitsLeft;
	    }
	  //digit is a teen
	  else
	    {
	      output[*index] = underTwenty[inputArr[*pos + 1] - '0'];
	      ++*index;
	      ++*pos;
	      ++*pos;
	      --*digitsLeft;
	      --*digitsLeft;
	    }
	}
      else
	{
	  output[*index] = underTen[(inputArr[*pos] - '0') - 1];
	  ++*index;
	  ++*pos;
	  --*digitsLeft;
	}
    }
  else if(comFlag == 1 && inputArr[*pos - 1] - '0' == 0 && inputArr[*pos - 2] - '0' == 0)
    {
      //scuffed shit
    }
  else
    {
      ++*pos;
      --*digitsLeft;
    }
}

void process_input(char input[], int length, int upperCase)
{
  int number; //holds the number at the given index
  int flag = 0; //flag to determine when the first nonzero int is reached
  int actualLength = length; //length of int minus leading zeros
  int * ptr_digitsLeft; //number of digits left in the array to parse
  char * output[100];

  int index = 0;
  int * ptr_index;
  ptr_index = &index;

  int pos = 0;
  int * ptr_pos;
  ptr_pos = &pos;

  for (int i = 0; i < length; ++i)
    {
      number = input[i] - '0';
      if (number > 0)
	{
	  flag = 1;
	  break;
	}
      if (number == 0 && flag == 0)
	{
	  --actualLength;
	  ++pos;
	  continue;
	}
    }

  int digitsLeft = actualLength;
  ptr_digitsLeft = &digitsLeft;

  int triples = 0;
  if (actualLength > 6)
    {
      triples = 3;
    }
  else if (actualLength > 3)
    {
      triples = 2;
    }
  else
    {
      triples = 1;
    }

  for (int i = 0; i < triples; ++i)
    {
      while (*ptr_digitsLeft % 3 != 0)
	{
	  if (*ptr_digitsLeft > 6)
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	      output[*ptr_index] = bigNumbers[2];
	      ++index;
	    }
	  else if (*ptr_digitsLeft > 3)
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	      output[*ptr_index] = bigNumbers[1];
	      ++index;
	    }
	  else
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	    }
	}

      int indexChanged = index;
      if (*ptr_digitsLeft == 9)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	  output[*ptr_index] = bigNumbers[2];
	  ++index;
	  indexChanged = index;
	}
      else if (*ptr_digitsLeft == 6)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	  if (indexChanged != index)
	    {
	      output[*ptr_index] = bigNumbers[1];
	      ++index;
	    }
	}
      else if (*ptr_digitsLeft == 3)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	}
      else
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index);
	}

    }
  output[*ptr_index] = '\0';
  int strLength = 0;
  char * ch;
  char charHold[1];
  if (upperCase == 1)
    {
      for (int i = 0; output[i] != '\0'; ++i)
	{
	  strLength = strlen(output[i]);
	  ch = output[i];
	  for (int j = 0; j < strLength; ++j)
	    {
	      charHold[0] = *ch;
	      charHold[0] = toupper(charHold[0]);
	      printf("%c", charHold[0]);
	      ++ch;
	    }
	  printf(" ");
	}
    }
  else
    {
      for (int i = 0; output[i] != '\0'; ++i)
	{
	  printf("%s ", output[i]);
	}
    }
  printf("\n");
}


/***
 * main function
 ***/
int main(int argc, char** argv)
{
  int upperCase = 0;

  if (argc == 1)
    {
      char buffer[11];
      int length;
      while (fgets(buffer, 11, stdin))
	{
	  length = strlen(buffer) - 1;
	  process_input(buffer, length, upperCase);
	}
    }
  else if (argc > 2 || *argv[1] != 'u')
    {
      fprintf(stderr, "too many or invalid argument(s)\n");
    }
  else
    {
      upperCase = 1;
      char buffer[11];
      int length;
      while (fgets(buffer, 11, stdin))
	{
	  length = strlen(buffer) - 1;
	  process_input(buffer, length, upperCase);
	}
    }
}
