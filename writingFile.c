/* COMMAND FOR THE TERMINAL
      -  gcc write.c -o write
      -  ./write > output.dat
      -  ./read < dates.dat 2 | ./write > output.dat
*/

/* TEST THESE DATES
1/25/2017
2/13/2000
3/12/1996
4/31/1991
5/28/1983
6/14/1967
7/11/1973
8/26/1745
9/16/1546
10/1/1430
11/19/1000
12/10/1993

12/10/1993
12/10/-2147483648
12/10/-2147483649
01/13/-1793
q12/10/1993
05/23/1459
fred
1/000007/1210
000002/00003/123
*/

#include <stdio.h>
#include <stdlib.h> // used for atoi();
#include <string.h> // pg350[DD] used for strcpy();

// ENUMS CONSTANTS
// months work
enum MONTHS {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

// prototypes
void convertDate(char dateValue[], char convertedValue[]);

int main( void ) {
  FILE *ofPtr; // ofPtr = output file pointer

  char oldDate[30];

  // fopen opens file. Exit program if unable to create file
  if ( ( ofPtr = fopen( "output.dat", "w" ) ) == NULL ) {
    printf("%s\n", "File could not be opened");
  } else {
    /* This will hold the date that is scan and will pass it to the function
       so that the function can work on it */
    char oldDate[30] = "";
    scanf ("%[^\n]%*c", oldDate); // scan the date and save it to the array
    while (!feof(stdin)) {
      /* This will hold the modifed date that is return from the funcition and
      its this one that we will want to output. */
      char newDate[30] = "";
      convertDate(oldDate, newDate);//********* call the function to convert the date to the proper format *************
      fprintf(ofPtr, "%s\n", newDate /*newDate*/);
      scanf ("%[^\n]%*c", oldDate); // scan the date and save it to the array
    } // end while
    fclose( ofPtr ); // fclose closes file
  } // end else
} //endmain

/* receive an input and convert it for example
    - 12/10/1993 converts to
    - 12 DEC 1993
    */
void convertDate(char dateValue[], char convertedValue[]){
  char strOldMonth[14] = "";
  char strNewMonth[6] = "";
  char strOldDay[14] = "";
  char strOldYear[14] = "";

  int numMonth = 0;
  // int numDay = 0;
  // long int numYear = 0;
  //     Destination,       Source
  strcpy(strOldMonth, strtok(dateValue,"/"));
  strcpy(strOldDay, strtok(NULL,"/"));
  strcpy(strOldYear, strtok(NULL,"/"));

  numMonth = atoi(strOldMonth);
  // numDay = atoi(strOldDay);
  // numYear = atol(strOldYear);
  // printf("%s\n", convertedValue);

  if (numMonth == JAN) {strcpy(strNewMonth , " JAN ");}
  else if (numMonth == FEB) {strcpy(strNewMonth, " FEB ");}
  else if (numMonth == MAR) {strcpy(strNewMonth, " MAR ");}
  else if (numMonth == APR) {strcpy(strNewMonth, " APR ");}
  else if (numMonth == MAY) {strcpy(strNewMonth, " MAY ");}
  else if (numMonth == JUN) {strcpy(strNewMonth, " JUN ");}
  else if (numMonth == JUL) {strcpy(strNewMonth, " JUL ");}
  else if (numMonth == AUG) {strcpy(strNewMonth, " AUG ");}
  else if (numMonth == SEP) {strcpy(strNewMonth, " SEP ");}
  else if (numMonth == OCT) {strcpy(strNewMonth, " OCT ");}
  else if (numMonth == NOV) {strcpy(strNewMonth, " NOV ");}
  else if (numMonth == DEC) {strcpy(strNewMonth, " DEC ");}

  // strcpy("This is destination",  "This is source");
  //
  // strcat(dest, src);
  strcat(convertedValue, strOldDay);
  strcat(convertedValue, strNewMonth);
  strcat(convertedValue, strOldYear);

  // printf("%s\n", convertedValue);
}
// 4 JUL 1776


/*  pass it two arrays one that is empty and will initialize and the other one
    is used to compare the months */
