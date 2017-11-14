hellloooo

/*  the characters array where the date that is read will be stored in will
have the max length of 30 characters. */

/* COMMAND FOR THE TERMINAL
      -  gcc read.c -o read  // Using c99 becasue i dont want to do implicit declaration
      -  ./read < dates.dat 2
      -  ./read < dates.dat 2 | ./write > output.dat
*/

/* THINGS STILL MISSING
  - you need to validate for leap years
  - depending on the number the user inputs you have to loop
    through and print out that number of dates to the second Program
  */

#include <stdio.h> //
#include <stdlib.h> // used for atoi();
#include <string.h> // pg350[DD] used for strcpy();
#include <limits.h> // used to get INT_MIN -2147483648 and INT_MAX 2147483647

// ENUMS CONSTANTS
// months work
enum MONTHS {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
enum ASCII {NEGATIVE_ASCII = 45, FOWARD_SLASH = 47, ZERO_ASCII = 48, NINE_ASCII = 57};
enum VALIDATE {VALID_PASS = 1, VALID_FAIL = 0};
enum COMMAND_LINE_VALIDATE {FAIL = 0, PASS = 1};
enum NUMBER_OF_ARGUMENTS_READ {numOfArgumentsRead = 2};

// prototypes
int validateCommandLineArg(int argc, char * argv[]);
int checkForTwoArguments(int argc, char * argv[]);
int checkForOnlyNumbers(int argc, char * argv[]);

int validateDate(char dateValue[]);
int validateTwoFowardSlash(char value[]);
int validateStringMonth(char value[]);
int validateIntegerMonth(int value);
int validateStringDay(char value[]);
int validateIntegerDay(int value);
int validateStringYear(char value[]);
int validateIntegerYear(long int value);
int validateIndividualNumber(char value[]);
void convertDate(char dateValue[], char convertedValue[]);

/* else loop through the pointer and read each sentence */

int main(int argc, char *argv[]) {
  if (validateCommandLineArg(argc,argv) == FAIL) {
    return FAIL;
  }
  FILE *dfPtr;

  if((dfPtr = fopen("dates.dat", "r")) == NULL){
    printf("%s\n", "File could not be opened");
  } else{
    while (!feof(dfPtr)) {
      char strOldDate[30] = "";
      char strCpyDate[30] = ""; // array holding a copy of the date
      fscanf(dfPtr, "%[^\n]%*c", strOldDate);
      strcpy(strCpyDate, strOldDate);
      if (validateDate(strOldDate) == VALID_FAIL){
        /* Do nothing becasue the date is invalid and move on to the next date */
      } else {
        char strNewDate[30] = "";
        convertDate(strCpyDate, strNewDate);
        // The date is correct
        printf("%s\n", strNewDate);
      } // end else
    } // end while
    fclose(dfPtr);
  } // end else
  return 0;
}

// This was got from Assignment4/PokerGame_MainFile.c
int validateCommandLineArg(int argc, char * argv[]){
  if (checkForTwoArguments(argc,argv) == FAIL) {
    return FAIL; // didnt work is the number 0
  } else if (checkForOnlyNumbers(argc,argv) == FAIL) {
    return FAIL; // didnt work is the number 0
  }
  return PASS; // if it worked then return 1
}
int checkForTwoArguments(int argc, char * argv[]){
  if (argc != numOfArgumentsRead) {
    printf("%s\n%s\n\n",
    "Incorrect input please run the program again with the",
    "correct number of arguments.");
    printf("%s\n\n", "Example of correct input is: ./v1R.c < dates.dat 2");
    printf("%s\n%s\n", "Where the number is the number of valid days you want",
    "converted and outputed to a file named output.dat");
    printf("%s\n", "");
    return FAIL; // didnt work is the number 0
  }
  // *********** This was from the PokerGame_MainFile.c ***********=
  // else if (argc == numOfArgumentsRead){
  //   printf("\nThis is the cards per player desired: %s\n", argv[1]);
  //   printf("This is the number of players desired: %s\n", argv[2]);
  // }
  return PASS; // if it worked then return 1
}
int checkForOnlyNumbers(int argc, char * argv[]){
  // ********* CHECK IF THERE IS ANYTHING INPUTED BESIDES NUMBERS *************
  size_t row, column;
  for(row = 1; row < argc; row++){
    for(column = 0; argv[row][column] != '\0'; column++){
      int valueOfArgv = argv[row][column];
      if (valueOfArgv < ZERO_ASCII || valueOfArgv > NINE_ASCII ) { //57 is 9 and 48 is 0 in ascii
        printf("\n%s\n", "***************************************************");
        printf("%s\n%s\n", "There was an incorrect input value. Only positive",
        "whole values are accepted.");
        printf("\n");
        printf("%s\n\n", "***************************************************");
        return FAIL; // didnt work is the number 0
      }
    }
  }
  return PASS; // if it worked then return 1
}

int validateDate(char dateValue[]){
  char strMonth[14] = "";
  char strDay[14] = "";
  char strYear[14] = "";
  int numMonth = 0;
  int numDay = 0;
  /* using long int so it can store a year bigger than INT_MAX or INT_MIN and
     then it can iterpret that number and see if something is wrong with it */
  long int numYear = 0;

  // IF THIS TEST FAILS JUST RETURN AND DONT KEEP VALIDATING
  if(validateTwoFowardSlash(dateValue) == VALID_FAIL){
    return VALID_FAIL;
  }

  //printf("This is how the string look as soon as you pass it %s\n", dateValue);
  strcpy(strMonth, strtok(dateValue,"/"));
  strcpy(strDay, strtok(NULL,"/"));
  strcpy(strYear, strtok(NULL,"/"));
  numMonth = atoi(strMonth);
  numDay = atoi(strDay);
  /* Same using string converter to long so that it can interpret a year bigger
     than INT_MAX or INT_MIN */
  numYear = atol(strYear);

  if (validateStringMonth(strMonth) == VALID_FAIL){return VALID_FAIL;}
  else if (validateIntegerMonth(numMonth) == VALID_FAIL){return VALID_FAIL;}
  else if (validateStringDay(strDay) == VALID_FAIL){return VALID_FAIL;}
  else if (validateIntegerDay(numDay) == VALID_FAIL){return VALID_FAIL;}
  else if (validateStringYear(strYear) == VALID_FAIL){return VALID_FAIL;}
  else if (validateIntegerYear(numYear) == VALID_FAIL){return VALID_FAIL;}
  return VALID_PASS;
}
int validateTwoFowardSlash(char value[]){
  int TWO_FOWARD_SLASH = 2;
  int charON = 0;
  int countOfFowardSlash = 0;

  // FIND THE SUM OF FOWARD SLASH
  while (value[charON] != '\0') {
    int charValue = value[charON];
    if (charValue != FOWARD_SLASH){
      charON++;
    } else if (charValue == FOWARD_SLASH){
      countOfFowardSlash++;
      charON++;
    } else {
      charON++;
    } // end else
  } // end while
  // COUNT MUST BE TWO TO PASS THE TEST
  if(countOfFowardSlash != TWO_FOWARD_SLASH){
    return VALID_FAIL;
  } else{
    return VALID_PASS;
  } // end else
} // end of Function
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
int validateStringMonth(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
int validateIntegerMonth(int value){
  if (value < 1 || value > 12) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
int validateStringDay(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
int validateIntegerDay(int value){
  if (value < 1 || value > 31) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
int validateStringYear(char value[]){
  // this should check that the year only holds the valid chracters which are
  // numbers from 0-9 or the negative sign.
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
int validateIntegerYear(long int value){
  /* you are passing it as a long int becasue if you pass it as an int then it
     would have converted any number pass INT_MIN or INT_MAX into a valid
     number. I think this had to do with how atoi() was converting the string
     into an integer so you changed it to atol(); */
  if (value < INT_MIN || value > INT_MAX) {
    return VALID_FAIL;
  }
  return VALID_PASS;
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
void convertDate(char dateValue[], char convertedValue[]){
  char strOldMonth[14] = "";
  char strNewMonth[14] = "";
  char strOldDay[14] = "";
  char strNewDay[14] = "";
  char strOldYear[14] = "";
  char strNewYear[14] = "";
  int numMonth = 0;
  int numDay = 0;
  /* using long int so it can store a year bigger than INT_MAX or INT_MIN and
     then it can iterpret that number and see if something is wrong with it */
  long int numYear = 0;

  strcpy(strOldMonth, strtok(dateValue,"/"));
  strcpy(strOldDay, strtok(NULL,"/"));
  strcpy(strOldYear, strtok(NULL,"/"));
  numMonth = atoi(strOldMonth);
  numDay = atoi(strOldDay);
  /* Same using string converter to long so that it can interpret a year bigger
     than INT_MAX or INT_MIN */
  numYear = atol(strOldYear);

  /*********** This is meant to delete trailing zeros in the number **********/
  sprintf(strNewMonth, "%d/", numMonth);
  sprintf(strNewDay, "%d/", numDay);
  sprintf(strNewYear, "%ld", numYear);

  strcat(convertedValue, strNewMonth);
  strcat(convertedValue, strNewDay);
  strcat(convertedValue, strNewYear);
  /***************************************************************************/
}
// int validateLeapYear(){
//
// }
