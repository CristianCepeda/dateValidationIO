// /*==========================================================================
// |   Source code:  [readingDatesFile.c]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[5] [readingDatesFile.c]
// |
// |        Course:  [COP 4338 (Programming III)]
// |       Section:  [U03]
// |    Instructor:  William Feild
// |      Due Date:  [14 November 2017], at the beginning of class
// |
// |	I hereby certify that this collective work is my own
// |	and none of it is the work of any other person or entity.
// |
// |	__Cristian C Cepeda____________________________________ [Signature]
// |
// |        Language:  [Program Language: C]
// |     Compile/Run: ***********************************************
// |                  MAKE SURE HEADER FILE IS IN THE SAME DIRECTORY
// |                  AS readingDatesFile.c THE NAME OF THE HEADER
// |                  FILE IS datesIO.h
// |                  ***********************************************
// |
// |                  COMPILE
// |                  Once you are in the correct directory where all the
// |                  files are found enter
// |
// |                  make
// |
// |                  - this will compile all the necessary files needed to
// |                    run
// |                  - Now this will create an executable file named
// |                    "readingDatesFile"
// |
// |                  RUN
// |                  - So Enter this to Run a test version of it
// |
// |                  ./readingDatesFile < dates.dat 2
// |
// |                  - However this program was meant to be run with another
// |                    file.
// |                  - You will want to run this instead
// |
// |    -  ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
// |
// |  +------------------------------------------------------------------------
// |
// |  Description:  [ The main goal of this program is to read dates from a
// |                  file named dates.dat and validate each date. The file
// |                  that we are reading from should hold one date per line.
// |                  When running the program by itself it will read the
// |                  dates from the file dates.dat and just output the
// |                  correct validated dates to the command line. An example
// |                  of how you would run the program from a terminal would
// |                  be like this. Assuming that you have complied the
// |                  program already
// |
// |                      - ./readingDatesFile < dates.dat 2
// |
// |                 However the main goal of this Assignment is use this
// |                 program with another program so that the first program
// |                 can read the dates and validate them and the second
// |                 program can convert these validated dates and store them
// |                 into a file called output.dat ]
// |
// |        Input:  [ The input is done through the command line. An example
// |                  looks like this:
// |
// |    -  make
// |    -  ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
// |                    - Where 2 is the first two dates validated that will
// |                      be passed on to the next program and saved to a
// |                      file named "output.dat"
// |
// |                The restriction on the program is that the numbers inputed
// |                has to be equal to or greater than zero. ]
// |
// |       Output:  [The order of the outputs for the program go in this order.
// |
// |                 If the program is ran by itself then it will be
// |                 1. The number of dates the user wants to validate and
// |                    displayed in the terminal
// |
// |                 If the program is ran how its suppose to be
// |                 1. It will create a file called "output.dat" with the
// |                    dates converted into the proper format followed by
// |                    all the dates found in the file "dates.dat"
// |
// |
// |      Process:  [The program’s steps are as follows:
// |                1. The program first validates the command line arguments
// |                there should be a total of two arguments the executable
// |                and the number of dates that you want to be validated.
// |                2. Then it goes into the function and it validates the
// |                number of dates the user asked for.
// |                3. When it goes into that function it will open the file
// |                and start scanning each line. It saves what was scanned
// |                into a string and then this string is used for further
// |                validations.
// |                4. If the date that was read is a valid date then it will
// |                 print it out. If the date was invalid then it moves to the
// |                 next line.
// |                5. It does this until the end of the file. Scanning each
// |                line and validating it.
// |
// |
// |   Required Features Not Included:  [ Everything was completed ]
// |
// |   Known Bugs:  [There are no Bugs]
// |  *===================================================================== */

#include "datesIO.h"

int main(int argc, char *argv[]) {
  // printf("%s\n", argv[0]);
  if (validateCommandLineArg(argc,argv) == FAIL) {
    return FAIL;
  }
  validateThisNumberOfDates(argv);
  return 0;
}

/*---------------------- validateThisNumberOfDates -----------------------------
  void validateThisNumberOfDates(char * argv[])
  |
  |  Purpose:  This function is the heart of the program it will create a hello
  |            FILE pointer. From here it reads each line and then passes what
  |            was scanned into another function for further validation. Here
  |            we also determine how many dates should be printed out based on
  |            the argument value that was passed.
  |
  |  @param  *argv[] (IN) -- This points to an array of characters an its used
  |                          to see the number the user wants inputed so that
  |                          we can know how many dates should be validated and
  |                          printed.
  |
  |  @return There is no return since its a void function however we use this
  |          function to print the number of validated dates the user wants to
  |          be printed out.
  *-------------------------------------------------------------------*/
void validateThisNumberOfDates(char * argv[]){
  int numberOfDatesToPrint = atoi(argv[1]);
  int numberOfDatesPrinted = 0;
  FILE *dfPtr;
  if(numberOfDatesToPrint == PRINT_ALL_VALID_DATES){
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
  } else{
    if((dfPtr = fopen("dates.dat", "r")) == NULL){
      printf("%s\n", "File could not be opened");
    } else{
      while (!feof(dfPtr) && numberOfDatesPrinted != numberOfDatesToPrint) {
        char strOldDate[30] = "";
        char strCpyDate[30] = ""; // array holding a copy of the date
        fscanf(dfPtr, "%[^\n]%*c", strOldDate);
        numberOfDatesPrinted++;
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
  }
}
/*---------------------- validateCommandLineArg -----------------------------
  int validateCommandLineArg(int argc, char * argv[])
  |
  |  Purpose:  This function is meant to check and validate the users input.
  |            It does this by calling two other function. In which each one
  |            takes care of a validation.
  |
  |  @param  argc (IN) -- This is meant to see the total amount of arguments
  |                       that is passed when running the program.
  |  @param  *argv[] (IN) -- This points to an array of characters an its here
  |                          where the values are stored.
  |
  |  @return It will return the constant Fail if it doesn't meet the requirements.
  |          And the constant Pass if it met the requirements.
  *-------------------------------------------------------------------*/
int validateCommandLineArg(int argc, char * argv[]){
  if (checkForTwoArguments(argc,argv) == FAIL) {
    return FAIL; // didnt work is the number 0
  } else if (checkForOnlyNumbers(argc,argv) == FAIL) {
    return FAIL; // didnt work is the number 0
  }
  return PASS; // if it worked then return 1
}
/*---------------------------- checkForTwoArguments -------------------------
|  int checkForTwoArguments(int argc, char *argv[])
|
|  Purpose:  This function is meant to check and validate that the users input
|            is only 2 arguments. The first argument would be the name of the
|            file. The second argument would be the number of valid dates that
|            you want to be return.
|
|  @param  argc (IN) -- This is meant to see the total amount of arguments
|                       that is passed when running the program.
|  @param  *argv[] (IN) -- This points to an array of characters an its here
|                          where the values are stored.
|
|  @return It will return the constant Fail if it doesn't meet the requirements.
|          And the constant Pass if it met the requirements.
*-------------------------------------------------------------------*/
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
/*---------------------------- checkForOnlyNumbers --------------------------
|  int checkForOnlyNumbers(int argc, char *argv[])
|
|  Purpose:  This function is meant to check and validate that the user didn't
|            input anything other than numbers. So a minus sign to indicate a
|            negative number would be wrong since negative numbers are not
|            accepted. As well as a period to indicate that its a fractional
|            number or decimal number.
|
|  @param  argc (IN) -- This is used in the double for loop to iterate through
|                       the double dimension array.
|
|  @param  *argv[] (IN) -- This points to an array of characters an its here
|                          where the values are stored, and iterated so that we
|                          can see that it is only numbers in a range from 48
|                          - 57 in ascii value.
|
|  @return It will return the constant Fail if it doesn't meet the requirements.
|          And the constant Pass if it met the requirements.
*-------------------------------------------------------------------*/
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
/*--------------------------- validateDate ----------------------------------
  int validateDate(char dateValue[])
  |
  |  Purpose:  This function will be the main validation function. It receives
  |            the date as a character string and then it tokenizes the string
  |            and copies it to individual strings. One corresponding to Month,
  |            Day, and Year. It then passes each individual string into its
  |            corresponding function for further validation. If any of the
  |            test fail then this function returns VALID_FAIL which equals 0.
  |
  |  @param  char dateValue[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific date to be checked.
  |                        Have it be Month, Day, or Year.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
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
  else if (validateMaxDaysInMonth(numMonth, numDay, numYear) == VALID_FAIL){return VALID_FAIL;}

  return VALID_PASS;
}
/*--------------------------- validateTwoFowardSlash ------------------------
  int validateTwoFowardSlash(char value[])
  |
  |  Purpose:  This function will loop through the date that is passed and
  |            validates that there are two forward slashes. We do this by
  |            looping through each character. Every time each forward slash is
  |            found then it adds it to the count.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific date to be checked
  |                        for three forward slashes.
  |
  |  @return This function returns the value stored in VALID_FAIL or
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
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
/*---------------------------- validateStringMonth --------------------------
  int validateStringMonth(char value[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            the month date that is being checked. It then uses this value
  |            and passes it as a parameter to the function
  |            validateIndividualNumber. If the function
  |            validateIndividualNumber returns VALID_FAIL then it prints out
  |            that something is wrong with the inputed month date.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific Month date to be
  |                        checked.
  |
  |  @return This function returns the value stored in VALID_FAIL or
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateStringMonth(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
/*---------------------- validateIntegerMonth -------------------------------
  int validateIntegerMonth(int value)
  |
  |  Purpose:  This function receives as a parameter an int value for the month.
  |            it checks that the value is between 1 or 12. If it fails the
  |            test then it return VALID_FAIL otherwise it returns VALID_PASS.
  |
  |  @param  int value (IN) -- This is the value for the month of the date that
  |                        we are currently validating.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateIntegerMonth(int value){
  if (value < 1 || value > 12) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
/*---------------------------- validateStringDay --------------------------
  int validateStringDay(char value[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            the day date that is being checked. It then uses this value
  |            and passes it as a parameter to the function
  |            validateIndividualNumber. If the function
  |            validateIndividualNumber returns VALID_FAIL then it prints out
  |            that something is wrong with the inputed month date.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific day date to be
  |                        checked.
  |
  |  @return This function returns the value stored in VALID_FAIL or
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateStringDay(char value[]){
  int answer = validateIndividualNumber(value);
  if (answer == VALID_FAIL) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
/*---------------------- validateIntegerDay -------------------------------
  int validateIntegerDay(int value)
  |
  |  Purpose:  This function receives as a parameter an int value for the day.
  |            it checks that the value is between 1 or 31. If it fails the
  |            test then it return VALID_FAIL otherwise it returns VALID_PASS.
  |
  |  @param  int value (IN) -- This is the value for the day of the date that
  |                        we are currently validating.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateIntegerDay(int value){
  if (value < 1 || value > 31) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
/*---------------------------- validateStringYear --------------------------
  int validateStringYear(char value[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            the year date that is being checked. It then uses this value
  |            and passes it as a parameter to the function
  |            validateIndividualNumber. If the function
  |            validateIndividualNumber returns VALID_FAIL then it prints out
  |            that something is wrong with the inputed month date.
  |
  |  @param  char value[] (IN) -- This parameter is the string array holding
  |                        the characters for the specific year date to be
  |                        checked.
  |
  |  @return This function returns the value stored in VALID_FAIL or
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateStringYear(char value[]){
    // this should check that the year only holds the valid characters which are
    // numbers from 0-9 or the negative sign.
    int answer = validateIndividualNumber(value);
    if (answer == VALID_FAIL) {
      return VALID_FAIL;
    }
    return VALID_PASS;
  }
/*---------------------- validateIntegerYear -------------------------------
  int validateIntegerYear(long int value)
  |
  |  Purpose:  This function receives as a parameter an long int value for the
  |            year. It checks that the value is between INT_MIN or INT_MAX.
  |            If it fails the test then it return VALID_FAIL otherwise it
  |            returns VALID_PASS.
  |
  |  @param  long int value(IN) -- This is the value for the year of the date
  |                        that we are currently validating.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateIntegerYear(long int value){
  /* you are passing it as a long int because if you pass it as an int then it
     would have converted any number pass INT_MIN or INT_MAX into a valid
     number. I think this had to do with how atoi() was converting the string
     into an integer so you changed it to atol(); */
  if (value < INT_MIN || value > INT_MAX) {
    return VALID_FAIL;
  }
  return VALID_PASS;
}
/*---------------------- validateMaxDaysInMonth ---------------------------
  int validateMaxDaysInMonth(int Month, int Day, long int Year)
  |
  |  Purpose:  This function receives as a parameter the numerical values of
  |            the date. It then looks for the month and checks that the day
  |            for that date we are checking is within the range of days
  |            possible for that month. For the month of FEB it also check that
  |            the date is a valid date we have to consider for leap years.
  |
  |
  |  @param  int Month (IN) -- This parameter is the numerical value for the
  |                        Month.
  |  @param  int Day (IN) -- This parameter is the numerical value for the
  |                        Day.
  |  @param  long int Year (IN) -- This parameter is the numerical value for
  |                        the Year.
  |
  |  @return This function returns the value stored in VALID_FAIL or in
  |          VALID_PASS based on what it determined through the test of the
  |          string array.
  *-------------------------------------------------------------------*/
int validateMaxDaysInMonth(int Month, int Day, long int Year){
  if (Month == JAN || Month == MAR || Month == MAY || Month == JUL ||
    Month == AUG || Month == OCT || Month == DEC){
      if(Day < 1 || Day > 31){
        return VALID_FAIL;
      }
    }
  if (Month == APR || Month == JUN || Month == SEP || Month == NOV) {
    if(Day < 1 || Day > 30){
      return VALID_FAIL;
    }
  }
  if (Month == FEB) {
    if(validateLeapYear(Month,Day,Year) == NOT_A_LEAP_YEAR){
      if (Day < 1 || Day > 28) {
        /* If it's not a leap year and month is Feb days <= 28 */
        return VALID_FAIL;
      }
    }
    if(validateLeapYear(Month,Day,Year) == VALID_LEAP_YEAR){
      if (Day < 1 || Day > 29) {
        /* If it's not a leap year and month is Feb days <= 28 */
        return VALID_FAIL;
      }
    }
  }
  return VALID_PASS;
}
/*---------------------- validateLeapYear ---------------------------
  int validateLeapYear(int Month, int Day, long int Year)
  |
  |  Purpose:  This function receives as a parameter the numerical values of
  |            the date. It then uses the year passed and checks to see if that
  |            year can be considered a leap year. If its a leap year than it
  |            returns the value stored in VALID_LEAP_YEAR otherwise it returns
  |            NOT_A_LEAP_YEAR.
  |
  |
  |  @param  int Month (IN) -- This parameter is the numerical value for the
  |                        Month.
  |  @param  int Day (IN) -- This parameter is the numerical value for the
  |                        Day.
  |  @param  long int Year (IN) -- This parameter is the numerical value for
  |                        the Year.
  |
  |  @return This function returns the value stored in answer which can hold
  |          the values VALID_LEAP_YEAR or NOT_A_LEAP_YEAR.
  *-------------------------------------------------------------------*/
int validateLeapYear(int Month, int Day, long int Year){
  int answer;
  if (Year % 400 == 0) {
    answer = VALID_LEAP_YEAR;
  } else if (Year % 100 == 0) {
    answer = NOT_A_LEAP_YEAR;
  } else if (Year % 4 == 0) {
    answer = VALID_LEAP_YEAR;
  } else{
    answer = NOT_A_LEAP_YEAR;
  }
  return answer;
}
/*---------------------- validateIndividualNumber ---------------------------
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
/*---------------------- convertDate ---------------------------
  void convertDate(char dateValue[], char convertedValue[])
  |
  |  Purpose:  This function receives as a parameter an array holding the
  |            date that was already validated it then tokenizes the date and
  |            converts each token into a numerical value. It then uses the
  |            function strcat() to concatenate the strings. The reason why we
  |            need this function is to delete leading zeros.
  |
  |  @param  char dateValue[] (IN) -- This parameter is the string array holding
  |                        the validate already.
  |  @param  char convertedValue[] (IN) -- This parameter will hold the new
  |                        string array which will hold the date without
  |                        leading zeros.
  |
  |  @return There is no return since its a void function however we use this
  |          function to return a string with the date that was already
  |          validated without the leading zeros.
  *-------------------------------------------------------------------*/
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

/*  the characters array where the date that is read will be stored in will
have the max length of 30 characters. */

/* COMMAND FOR THE TERMINAL
    -  gcc readingDatesFile.c -o readingDatesFile
    -  ./readingDatesFile < dates.dat 2
    -  ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
*/
