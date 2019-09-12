/*
  Project 0
  @author: Kyle Murphey
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//digits under ten
static char * underTen[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
//digits under twenty
static char * underTwenty[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
//digits that are multiples of ten
static char * multiplesOfTen[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
//nonnumber identifiers
static char * bigNumbers[] = {"hundred", "thousand", "million"};

/*
 * parses digits from the input and turns them into words
 *
 * @param:inputArr[] = array of digits to parse
 * @param:digitsLeft = reference to the amount of digits left to parse
 * @param:pos = reference to current position in array
 * @param:output = reference to array of strings in which the worded output is stored
 * @param:index = reference to next index to store word in output array
 * @param:firstDigit = reference to flag for whether or not the first digit has been read
 */
void parseOverThree(char inputArr[], int * digitsLeft, int * pos, char ** output, int * index, int * firstDigit )
{
  int comFlag = 0; //flag for sections that finish parsing before hitting all the conditionals
  int number = inputArr[*pos] - '0'; //the value stored in the input array at the current position

  //checks if the input is the start of a triplet
  if (*digitsLeft % 3 == 0 && number > 0)
    {
      output[*index] = underTen[number - 1]; //under 10 because is start of a hundred value
      ++*index; //increase position in output array
      output[*index] = bigNumbers[0]; //adds on "hundred"
      ++*index;
      ++*pos; //increase position in input array
      --*digitsLeft; //decrease the amount of digits left
    }
  //checks if digit is one place infront of a triplet
  if ((*digitsLeft == 4 || *digitsLeft == 7) && inputArr[*pos] - '0' > 0 && inputArr[*pos - 1] - '0' != 1 )
    {
      output[*index] = underTen[(inputArr[*pos] - '0') - 1];
      comFlag = 1;
      ++*index;
    }
  //checks for a nonzero digit in the tens place (second spot in triplet)
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
      //digit is under 20 but over 9
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
  //check if triplet of zeros (only inc twice since it will be inc'ed again later on)
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft % 3 == 0 && inputArr[*pos + 1] - '0' == 0 && inputArr[*pos + 2] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
    }
  //check if two leading zeros in triplet
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft % 3 == 0 && inputArr[*pos + 1] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
    }
  //check for double zeros in nontriplet
  else if (inputArr[*pos] - '0' == 0 && *digitsLeft > 2 && inputArr[*pos + 1] - '0' == 0)
    {
      ++*pos;
      ++*pos;
      --*digitsLeft;
      --*digitsLeft;
      comFlag = 1; //if nontriplet, then the two zeros will complete the triplet they're contained in (i.e. 89,300,789)
    }

  //current value is nonzero and flag has not been thrown
  if (inputArr[*pos] - '0' > 0 && comFlag != 1)
    {
      //tens or ten thousands place
      if (*digitsLeft == 2 || *digitsLeft == 5)
	{
	  //checks if number is over 19
	  if (inputArr[*pos] - '0' != 1)
	    {
	      output[*index] = multiplesOfTen[(inputArr[*pos] - '0') - 2];
	      ++*index;
	      ++*pos;
	      --*digitsLeft;
	      //completes the triplet (i.e. thirty four)
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
      //finishes parsing value
      else
	{
	  output[*index] = underTen[(inputArr[*pos] - '0') - 1];
	  ++*index;
	  ++*pos;
	  --*digitsLeft;
	}
    }
  //no increment needed
  else if(comFlag == 1 && inputArr[*pos - 1] - '0' == 0 && inputArr[*pos - 2] - '0' == 0 && *firstDigit == 1)
    {
      
    }
  //increments if zero
  else
    {
      ++*pos;
      --*digitsLeft;
    }
  *firstDigit = 1; //first digit has been read in
}

/*
 * takes in input array and cuts off leading zeros and initializes values and outputs words
 *
 * @param:input[] = array holding the input from user
 * @param:length = length of number stored in array
 * @param:upperCase = flag for upper case argument
 */
void process_input(char input[], int length, int upperCase)
{
  int number; //holds the number at the given index
  int flag = 0; //flag to determine when the first nonzero int is reached
  int actualLength = length; //length of int minus leading zeros
  int * ptr_digitsLeft; //number of digits left in the array to parse
  char * output[100]; //output array
  int firstDigit = 0; //flag for whether or not first digit has been parsed yet
  int * ptr_firstDigit = &firstDigit;

  int index = 0; //index for output array
  int * ptr_index;
  ptr_index = &index;

  int pos = 0; //current position in input array
  int * ptr_pos;
  ptr_pos = &pos;

  //filters out leading 0's
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

  int digitsLeft = actualLength; //sets the digits left to how many digits are in the number
  ptr_digitsLeft = &digitsLeft;

  int triples = 0; //holder for how many triplets are in number

  //finds amount of triplets
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

  //start of loop for parsing input
  for (int i = 0; i < triples; ++i)
    {
      //not the start of a triplet
      while (*ptr_digitsLeft % 3 != 0)
	{
	  //millions
	  if (*ptr_digitsLeft > 6)
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	      output[*ptr_index] = bigNumbers[2];
	      ++index;
	    }
	  //thousands
	  else if (*ptr_digitsLeft > 3)
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	      output[*ptr_index] = bigNumbers[1];
	      ++index;
	    }
	  //hundreds
	  else
	    {
	      parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	    }
	}

      int indexChanged = index; //keeps track of whether or not index was changed

      //hundred million
      if (*ptr_digitsLeft == 9)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit); //parses input for first triplet
	  output[*ptr_index] = bigNumbers[2]; //adds "million" to output array
	  ++index; //inc index in output array
	  indexChanged = index; //updates indexChanged to current position
	}
      //million
      else if (*ptr_digitsLeft == 6)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	  //adds "thousand" if index was changed
	  if (indexChanged != index)
	    {
	      output[*ptr_index] = bigNumbers[1];
	      ++index;
	    }
	}
      //hundreds
      else if (*ptr_digitsLeft == 3)
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	}
      //catches any other value that may get through
      else
	{
	  parseOverThree(input, ptr_digitsLeft, ptr_pos, output, ptr_index, ptr_firstDigit);
	}
    }
  
  output[*ptr_index] = '\0'; //adds terminating character
  int strLength = 0; //length of word in output array
  char * outputAddress; //holds address of first character in string
  char charHold[1]; //holds one char to capitalize

  //upper case argument
  if (upperCase == 1)
    {
      //loops through output array
      for (int i = 0; output[i] != '\0'; ++i)
	{
	  strLength = strlen(output[i]); //gets length of word at index i
	  outputAddress = output[i]; //gets address of first char at index i of the ith word

	  //loop for single word
	  for (int j = 0; j < strLength; ++j)
	    {
	      charHold[0] = *outputAddress; //stores first char in char holder
	      charHold[0] = toupper(charHold[0]); //makes char upper case
	      printf("%c", charHold[0]); //prints out char
	      ++outputAddress; //inc address to the next char in the ith word in the output array
	    }
	  printf(" "); //space between words
	}
    }
  //lower case
  else
    {
      for (int i = 0; output[i] != '\0'; ++i)
	{
	  printf("%s ", output[i]);
	}
    }
  printf("\n"); //new line at the end out printed out array
}


/*
 * checks arguments, get input, and length of input
 *
 * @param:argc = number of arguments
 * @param:argv = array of arguments
 */
int main(int argc, char** argv)
{
  int upperCase = 0; //flag for upper case

  //no argument (lower case)
  if (argc == 1)
    {
      char buffer[11]; //store input
      int length; //stores the length of input
      
      //reads in inputs until EOF
      while (fgets(buffer, 11, stdin))
	{
	  length = strlen(buffer) - 1; //gets length
	  process_input(buffer, length, upperCase); //sends input to get parsed
	}
    }
  //too many args or invalid args
  else if (argc > 2 || *argv[1] != 'u')
    {
      fprintf(stderr, "too many or invalid argument(s)\n");
    }
  //upper case
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
