#include <stdio.h> //
#include <stdlib.h> // used for atoi();
#include <string.h> // pg350[DD] used for strcpy();
#include <limits.h> // used to get INT_MIN and INT_MAX

// ENUMS CONSTANTS
// months work
enum MONTHS {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
enum ASCII{NEGATIVE_ASCII = 45, ZERO_ASCII = 48, NINE_ASCII = 57};
enum VALIDATE{VALID_PASS = 1, VALID_FAIL = 0};


// prototypes
void validateStringMonth(char value[]);
void validateMonth(int value);

void validateStringDay(char value[]);
void validateDay(int value);

int validateNumber(char value[]);

int main(void) {

  char strMonth[10]= "";
  char strDay[10] = "";
  char strYear[10] = "";
  char date[22] = "";

  printf("%s", "Enter a date: ");
  scanf ("%[^\n]%*c", date);
  printf("%s\n", "");
  printf("The date entered is %s\n", date);

  printf("%s\n", "");
  strcpy(strMonth, strtok(date,"/"));
  strcpy(strDay, strtok(NULL,"/"));
  strcpy(strYear, strtok(NULL,"/"));
  printf("The string month entered is %s\n", strMonth);
  printf("The string day entered is %s\n", strDay);
  printf("The string year entered is %s\n", strYear);

  int numMonth = 0;
  int numDay = 0;
  int numYear = 0;

  printf("%s\n", "");
  printf("%s\n", "This is the date entered in int values");
  numMonth = atoi(strMonth);
  numDay = atoi(strDay);
  numYear = atoi(strYear);
  printf("%d/%d/%d\n", numMonth,numDay,numYear);

  printf("%s\n", "");
  validateStringMonth(strMonth);
  validateMonth(numMonth);
  printf("%s\n", "");
  validateStringDay(strDay);
  validateDay(numDay);
  printf("%s\n", "");
  return 0;
}

void validateStringMonth(char value[]){
  int answer = validateNumber(value);
  if (answer == VALID_FAIL) {
    printf("%s\n", "Somthing is wrong with the String Month Date");
  }
}
void validateMonth(int value){
  if (value < 1 || value > 12) {
    printf("%s\n", "Month entered is incorrect");
    // some how skip this date and dont save
  }else{
    printf("%s\n", "Month entered is valid");
  }
}

void validateStringDay(char value[]){
  int answer = validateNumber(value);
  if (answer == VALID_FAIL) {
    printf("%s\n", "Somthing is wrong with the String Day Date");
  }
}
void validateDay(int value) {
  if (value < 1 || value > 31) {
    printf("%s\n", "Day entered is incorrect");
    // some how skip this date and dont save
  }else{
    printf("%s\n", "Day entered is valid");
  }
}

int validateNumber(char value[]){
  int charON = 0;
  while (value[charON] != '\0') {
    int charValue = value[charON];
    // Meant to see that the character was increasing
    // printf("%c\n", value[charON]);
    if(charValue < ZERO_ASCII || charValue > NINE_ASCII){
      if(charValue == NEGATIVE_ASCII){
        charON++;
      } else {
        // have each indivual call print out the message of what went wrong
        // printf("%s\n", "Something is wrong with the string value for the month");
        return VALID_FAIL; // lets say 0 is a VALID_FAIL
      }
    } else{
      charON++;
    }
  }
  return VALID_PASS; // lets say 1 is a VALID_PASS
}


/********************* This could be helpfull dont delete ********************
******** 1. ********
// atoi does read negative numbers
// char date[]= "-24";
// int value = 0;
// printf("value is %d\n", value);
// value = atoi(date);
// printf("%s\n", "");
// printf("value is %d\n", value);

******** 2. ********
int day, year;
 char weekday[20], month[20], dtm[100];

 strcpy( dtm, "Saturday March 25 1989" );
 sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );

 printf("%s %d, %d = %s\n", month, day, year, weekday );
****************************************************************************/


/*********************** research done for strcpy() ************************
based of this we can see that if we pass it this string the result will
be
    - "1H12H" then it will return 1
    - "H12H" then it will  return 0
    - "a1" then it will return 0
    - "1a" then it will return 1
    - "12a" then it will return 12
    - "1a2" then it will return 1
Based on what i can see it will read any number correct untill it reaches
letters. If it encounters letters first then the answer will be 0.
****************************** Test program ********************************
int val;
char str[20];

strcpy(str, "98993489");
val = atoi(str);
printf("String value = %s, Int value = %d\n", str, val);

strcpy(str, "12a");
val = atoi(str);
printf("String value = %s, Int value = %d\n", str, val);
****************************************************************************
****************************************************************************/

/************* FOR VALIDATION *******************
have it scan the date and then pass each number into the validation function
void validateDate(int mon)
*/

// feof function 445, 458

/******* somthing you thought might work
// // you might need to modify the 8 so that it can recieve the INT_MIN or INT_MAX
//   char date[3][8];
//
//   char str[80] = "12-12-1111";
//   const char s[2] = "-";
//   char *token;
//
//   // get the first token
//   token = strtok(str, s);
//
//   // walk through other tokens
//   while( token != NULL ) {
//      printf( "%s\n", token );
//
//      count = 3;
//       for (size_t row = 0; row < count; row++) {
//         for (size_t column = 0; column < count; column++) {
//           code
//         }
//       }
//
//      token = strtok(NULL, s);
//   }
*/


// printf("%s", "Enter a date: ");
// scanf("%d%*c%d%*c%d", &month, &day, &year);
//
//
// printf( "month = %d day = %d year = %d\n\n", month, day, year );
//
// // printf("%s", "Enter a date in the form mm-dd-yyyy: ");
// // scanf("%d%*c%d%*c%d", &month1, &day1, &year1);
// //
// // printf( "month = %d day = %d year = %d\n\n", month1, day1, year1 );

/*
#include <stdio.h>
int main(void) {
int month, day, year;
printf("%s", "Enter a date: ");
scanf("Enter MM/DD/YYYY %d%*c%d%*c%d\n", &month, &day, &year);
printf("The date entered was %d/%d/%d\n", month, day, year);
return 0;
}
*/

/************************** PseudoCode ***************************************

- read inputs from the command line until they enter EOF character
it should be '<Ctrl> d'

- validate the input that comes in so that it can be in the format of

month/day/year
EXAMPLES OF DATES ARE
- 12/12/1900
-  1/ 5/1993
- 02/09/1493

- the max number that can be put is two integers for month
- the max number that can be put is two integers for day

Years is going to be more tricky since we can accept negative numbers
and 0 the range for years is INT MIN and Int MAX
- INT MIN and Int MAX may be system dependent so when you validate them
assign them to a variable and then pass this variable to the validation
- the max number that can be put is four integers for year
*******************************************************************************
*/
