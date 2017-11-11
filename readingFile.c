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
int validateIndividualNumber(char value[]);

void validateStringMonth(char value[]);
void validateStringDay(char value[]);
void validateStringYear(char value[]);

void validateIntegerMonth(int value);
void validateIntegerDay(int value);
void validateIntegerYear(long int value);



int main(void) {

  printf("This is the max integer: %d\n", INT_MAX);
  printf("This is the min integer: %d\n", INT_MIN);
  printf("%s\n", "");

  char date[42] = "";

  printf("%s", "Enter a date: ");
  scanf ("%[^\n]%*c", date);
  printf("%s\n", "");
  printf("The date entered is %s\n", date);


  printf("%s\n", "");
  validateDate(date);

  char strMonth[14]= "";
  char strDay[14] = "";
  char strYear[14] = "";

  printf("%s\n", "");
  strcpy(strMonth, strtok(date,"/"));
  strcpy(strDay, strtok(NULL,"/"));
  strcpy(strYear, strtok(NULL,"/"));
  printf("The string month entered is %s\n", strMonth);
  printf("The string day entered is %s\n", strDay);
  printf("The string year entered is %s\n", strYear);

  int numMonth = 0;
  int numDay = 0;
  long int numYear = 0;

  printf("%s\n", "");
  printf("%s\n", "This is the date entered in int values");
  numMonth = atoi(strMonth);
  numDay = atoi(strDay);
  numYear = atol(strYear);
  printf("%d/%d/%ld\n", numMonth,numDay,numYear);


  printf("%s\n", "");
  validateStringMonth(strMonth);
  validateStringDay(strDay);
  validateStringYear(strYear);
  printf("%s\n", "");
  validateIntegerMonth(numMonth);
  validateIntegerDay(numDay);
  validateIntegerYear(numYear);
  printf("%s\n", "");
  return 0;
}
// You may need to validate a date that is inputed in this format
//            1-2/13-1/1111

int validateDate(char value[]){
  // if the date is wrong skip and advance to the next date.


}
/*---------------------------- validateIndividualNumber ----------------------------
  int validateIndividualNumber(char value[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            specific part of the date that will be checked. Have it be the
  |            month, day, or year. It will loop through each character and
  |            check it to see that it is only and integer in the range of 0-9
  |            or a negative sign. If any other character is encountered then
  |            it returns VALID_FAIL otherwise then it returns VALID_PASS.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific date to be checked.
  |                        Have it be Month, Day, or Year.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateIndividualNumber(char value[]){
  int charON = 0;
  while (value[charON] != '\0') {
    int charValue = value[charON];
    // Meant to see that the character was increasing
    // printf("%c\n", value[charON]);
    if(charValue < ZERO_ASCII || charValue > NINE_ASCII){
      if(charValue == NEGATIVE_ASCII){
        charON++;
      } else {
        // have each individual call print out the message of what went wrong
        // printf("%s\n", "Something is wrong with the string value for the month");
        return VALID_FAIL; // lets say 0 is a VALID_FAIL
      }
    } else{
      charON++;
    }
  }
  return VALID_PASS; // lets say 1 is a VALID_PASS
}
/*---------------------------- validateStringMonth ----------------------------
  void validateStringMonth(char value[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            the month date that is being checked. It then uses this value
  |            and passes it as a parameter to the function validateIndividualNumber.
  |            If the function validateIndividualNumber returns VALID_FAIL then it prints
  |            out that something is wrong with the inputed month date.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific Month date to be
  |                        checked.
  |
  |  @return This function prints out a string saying something is wrong with
  |          the String Month date if something was wrong else it doesn't do
  |          anything hence it passed the test.
  *-------------------------------------------------------------------*/
void validateStringMonth(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    printf("%s\n", "Something is wrong with the String Month Date");
  }
}
void validateStringDay(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    printf("%s\n", "Something is wrong with the String Day Date");
  }
}
void validateStringYear(char value[]){
  // this should check that the year only holds the valid chracters which are
  // numbers from 0-9 or the negative sign.
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    printf("%s\n", "Something is wrong with the String Year Date");
  }
}

void validateIntegerMonth(int value){
  if (value < 1 || value > 12) {
    printf("%s\n", "Month entered is incorrect");
    // some how skip this date and don't save
  }else{
    printf("%s\n", "Month entered is valid");
  }
}
void validateIntegerDay(int value) {
  if (value < 1 || value > 31) {
    printf("%s\n", "Day entered is incorrect");
    // some how skip this date and don't save
  }else{
    printf("%s\n", "Day entered is valid");
  }
}
void validateIntegerYear(long int value){
  /* you are passing it as a long int becasue if you pass it as an int then it
     would have converted any number pass INT_MIN or INT_MAX into a valid
     number. I think this had to do with how atoi() was converting the string
     into an integer so you changed it to atol(); */
  if (value < INT_MIN || value > INT_MAX) {
    printf("%s\n", "Year entered is incorrect");
  }else{
    printf("%s\n", "Year entered is valid");
  }
}



/********************* This could be helpful don't delete ********************
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
Based on what i can see it will read any number correct until it reaches
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

// feof function 445, 458

/******* something you thought might work
// // you might need to modify the 8 so that it can receive the INT_MIN or INT_MAX
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
