#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{

    // Define input character array
    char inputChars[10] = "[({ ax})]";

    // Get random number
    // https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
    int r = rand() % 10;

    // Get character from input array
    char c = inputChars[r];
    return c;
}

char *inputString()
{

    // Define character array
    // Choosing characters needed to trigger function exit
    char inputStringChars[6] = "reset";

    // String to pass to testme
    // https://stackoverflow.com/questions/25798977/returning-string-from-c-function
    static char inputString[6];

    // Randomly fill inputString with characters from inputStringChars
    int s;
    int i;
    for(i=0; i<5; i++){

      s = rand() % 6;
      inputString[i] = inputStringChars[s];

    }	    
    
    return inputString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
