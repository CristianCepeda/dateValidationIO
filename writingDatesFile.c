// /*==========================================================================
// |   Source code:  [writingDatesFile.c]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[5] [writingDatesFile.c]
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
// |                  AS writingDatesFile.c THE NAME OF THE HEADER
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
// |                    "writingDatesFile"
// |
// |                  RUN
// |                  - So Enter this to Run a test version of it
// |
// |                  ./writingDatesFile > output.dat
// |
// |                  - However this program was meant to be run with another
// |                    file.
// |                  - You will want to run this instead
// |
// |    -  ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
// |
// |  +------------------------------------------------------------------------
// |
// |  Description:  [ The main goal of this program is to receive dates and
// |                  convert them or format them into another form and output
// |                  them to a file called "output.dat". For example
// |                  12/10/1967 should look like this
// |
// |                  10 DEC 1967
// |
// |                  This program can be ran by itself and it will take inputs
// |                  from the command line. It will convert these dates as
// |                  long as they are valid dates in this format. 12/10/1967
// |                  The date cant have spaces or anything out of the ordinary
// |                  this program was meant to work with another one which that
// |                  one hands this program already valid dates. Thus I
// |                  iterate what I just said it was meant to be ran with a
// |                  program called readingDatesFile. However if you want to
// |                  run it by itself then enter this
// |
// |                      - ./writingDatesFile > output.dat
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
// |     make
// |     ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
// |
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
// |                 1. Create a file called "output.dat" and store the valid
// |                    dates that was put in the command line.
// |
// |                 If the program is ran how its suppose to be
// |                 1. It will create a file called "output.dat" with the
// |                    dates converted into the proper format followed by
// |                    all the dates found in the file "dates.dat"
// |
// |
// |      Process:  [The program’s steps are as follows:
// |                1. The program first creates a FILE pointer and then
// |                proceeds to scan dates.
// |                2. These dates that are passed are than passed to a
// |                function called formatDate() where its here that it takes
// |                care of the formatting and returns the date how we receive
// |                it.
// |                3. It then uses this formatted date and prints it to a file
// |                called "output.dat". It does this while there are still
// |                dates to be scanned.
// |                4. Then it calls a function called displayFileContents()
// |                where this function reads the dates as they are found in
// |                the file called "dates.dat" and appends them to the end of
// |                the file called "output.dat".
// |
// |
// |   Required Features Not Included:  [ Everything was completed ]
// |
// |   Known Bugs:  [There are no Bugs]
// |  *===================================================================== */
#include "datesIO.h"

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
      formatDate(oldDate, newDate);//********* call the function to convert the date to the proper format *************
      fprintf(ofPtr, "%s\n", newDate /*newDate*/);
      scanf ("%[^\n]%*c", oldDate); // scan the date and save it to the array
    } // end while
    fclose( ofPtr ); // fclose closes file
  } // end else



  /***** I created the output file and formatted the dates *******/
  displayFileContents();

  return 0;
} //endmain

/*---------------------- formatDate -----------------------------
  void formatDate(char dateValue[], char convertedValue[])
  |
  |  Purpose:  This function is what basically converts the validated dates
  |            into the proper format. It does this by checking what numerical
  |            val is given for the month and then uses this to convert it or
  |            create a string with the three letters that belong to that month.
  |            Then it uses the strcat() function to concatenate the strings and
  |            create the formatted string date.
  |
  |  @param  char dateValue[] (IN) -- This is the array that holds the
  |                          validated date.
  |  @param  char convertedValue[] (IN) -- This is the array that will hold the
  |                          validated date.
  |
  |  @return There is no return since its a void function however we use this
  |          function to return the formatted string date into an array created
  |          in main().
  *-------------------------------------------------------------------*/
void formatDate(char dateValue[], char convertedValue[]){
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
/*---------------------- formatDate -----------------------------
  void displayFileContents()
  |
  |  Purpose:  This function is meant to read the dates found in a file called
  |            "dates.dat" and append all of them to a file called "output.dat".
  |             It does this by creating to FILE pointers one so that it can
  |             read the dates of the file "dates.dat" and the other pointer so
  |             that it can append it to the end of the file called "output.dat".
  |
  |  @return There is no return since its a void function however we append the
  |          dates found in the file "dates.dat" and append them to a file
  |          called "output.dat".
  *-------------------------------------------------------------------*/
void displayFileContents(){
  FILE *dfPtr;
  FILE *ofPtr; // ofPtr = output file pointer

    if((dfPtr = fopen("dates.dat", "r")) == NULL){
      printf("%s\n", "File could not be opened");
    }
    if ( ( ofPtr = fopen( "output.dat", "a" ) ) == NULL ) {
      printf("%s\n", "File could not be opened");
    } else{
      char strOldDate[30] = "";
      fscanf(dfPtr, "%[^\n]%*c", strOldDate);
      fprintf(ofPtr, "\n%s\n", "These are all the dates from dates.dat file");
      while (!feof(dfPtr)) {
        fprintf(ofPtr, "%s\n", strOldDate /*newDate*/);
        fscanf(dfPtr, "%[^\n]%*c", strOldDate);
      } // end while
       fclose(dfPtr);
    } //end else
}

/* COMMAND FOR THE TERMINAL
      -  gcc writingDatesFile.c -o writingDatesFile
      -  ./writingDatesFile > output.dat
      -  ./readingDatesFile < dates.dat 2 | ./writingDatesFile > output.dat
*/
