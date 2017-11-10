#include <stdio.h>
#include <limits.h>

 int main( void ) {
 int month;
 int day;
 int year;

printf("%d\n", INT_MAX );
printf("%d\n", INT_MIN );


//
//
// while (/* condition */) {
//   /* code */
// }
//  printf("%s", "Enter a date: ");
//  scanf("%d%*c%d%*c%d", &month, &day, &year);
//  printf( "month = %d day = %d year = %d\n\n", month, day, year );
//
//  // printf("%s", "Enter a date in the form mm-dd-yyyy: ");
//  // scanf("%d%*c%d%*c%d", &month1, &day1, &year1);
//  //
//  // printf( "month = %d day = %d year = %d\n\n", month1, day1, year1 );
//


 return 0;
 }


// feof function 445, 458





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
