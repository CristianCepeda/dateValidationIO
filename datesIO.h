// /*==========================================================================
// |   Source code:  [readingDatesFile.c]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[5] [datesIO.]
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
// |
// |
// |    This is the header
// |
// *==========================================================================*/

#include <stdio.h> //
#include <stdlib.h> // used for atoi();
#include <string.h> // pg350[DD] used for strcpy();
#include <limits.h> // used to get INT_MIN -2147483648 and INT_MAX 2147483647

// ENUMS CONSTANTS
// These are the constants for the readingDatesFile and writingDatesFile
enum MONTHS {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
enum ASCII {NEGATIVE_ASCII = 45, FOWARD_SLASH = 47, ZERO_ASCII = 48, NINE_ASCII = 57};
enum VALIDATE {VALID_PASS = 1, VALID_FAIL = 0, VALID_LEAP_YEAR = 1, NOT_A_LEAP_YEAR = 0};
enum COMMAND_LINE_VALIDATE {FAIL = 0, PASS = 1, PRINT_ALL_VALID_DATES = 0};
enum NUMBER_OF_ARGUMENTS_READ {numOfArgumentsRead = 2};

// Prototypes for readingDatesFile
void validateThisNumberOfDates(char * argv[]);
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
int validateMaxDaysInMonth(int Month, int Day, long int Year);
int validateLeapYear(int Month, int Day, long int Year);
int validateIndividualNumber(char value[]);
void convertDate(char dateValue[], char convertedValue[]);
// Prototypes for readingDatesFile
void formatDate(char dateValue[], char convertedValue[]);
void displayFileContents();
