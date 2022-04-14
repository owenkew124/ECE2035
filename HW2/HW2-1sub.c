//=================================================================
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*    
Please fill in the following
 Student Name: Owen Kew
 Date: 9/17/21

ECE 2035 Homework 2-1

This is the only file that should be modified for the C implementation
of Homework 2.

Do not include any additional libraries.
-----------------------------------------------

   When Harry Met Sally

This program finds the total number of years in which Harry and Sally
live in the same city at the same time.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami, 
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums, SumYears=0;
   int  Load_Mem(char *, int *, int *);
   void Print_Timelines(int *, int *);
   int Total, hTime, hInd, hCity, sTime, sInd, sCity = 0; //initialize new variables for total time left, Harry's time left in the current city, the index of Harry's current time and city values, Harry's current city, Sally's time left in her current city, the index of Sally's current city and time values, and Sally's current city

   /* You may add more local variables here if needed. */

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
   if (NumNums != 20) {
     printf("valuefiles must contain 20 entries\n");
     exit(1);
   }

   /* Your program goes here. */
   Total = 30;                                  //sets up total time left
   while (Total > 0) {                          // while total years left is greater than zero do these calculations
		
		if(hTime == 0) {                        // if Harry's time left in the current city is zero 
			hCity = HarryTimeline[hInd * 2 + 1]; // and get Harry's new city and time values
			hTime = HarryTimeline[hInd * 2];
		}
	   if (sTime == 0) {                        // if Sally's time in the current city is zero
			sCity = SallyTimeline[sInd * 2 + 1]; //and get Sally's new city and time values 
			sTime = SallyTimeline[sInd * 2];
	   }
	   if (hCity == sCity) {                    // if Sally and Harry were in the same city, do these calculations
		   if (hTime < sTime) {                 // if Harry was in the city for less time, the two were only in the city for the time Harry was in the city
			   Total = Total - hTime;           // therefore subtract the time Harry was in the city from the total years left
			   sTime = sTime - hTime;           // subtract the time Harry was in the city from Sally's time in the city to get how many years Sally was in the city after Harry left
			   SumYears = SumYears + hTime;     // add the years spent in the same city (aka the time Harry spent in the city) to the total years spent in the same city
			   hTime = 0;                       // reset Harry's time to zero as those years are accounted for and he needs a new city and time value
		   } else if (hTime > sTime) {          // if Sally was in the city for less time, the two were only in the city for the time Sally was in the city
			   Total = Total - sTime;           // therefore subtract the time Sally was in the city from the total years left
			   hTime = hTime - sTime;           // subtract the time Sally was in the city from Harry's time in the city to get how many years Harry was in the city after Sally left
			   SumYears = SumYears + sTime;     // add the years spent in the same city (aka the time Sally spent in the city) to the total years spent in the same city
			   sTime = 0;                       // reset Sally's time to zero as those years are accounted for and she needs a new time and city value
		   } else {                             // if neither of the above are true, Harry and Sally spent the same amount of time in the city
			   Total = Total - hTime;           // so subtract either value from the total years left
			   SumYears = SumYears + hTime;     // and add either value to the years spent in the same city
			   hTime = 0;                       // and reset both time values to zero as those years have been accounted for and they both need new time and city values
			   sTime = 0;
		   }
	   } else {                                 // if Harry and Sally weren't in the same city do these calculations
		   if (hTime < sTime) {                 // if Sally was in her city for longer than Harry was in his, account for the time Harry was in his city by
			   Total = Total - hTime;           // subtracting Harry's time from the total
			   sTime = sTime - hTime;           // and subtracting Harry's time from Sally's time to get the time she spent in her city after Harry left his
			   hTime = 0;                       // then reset Harry's time to zero to trigger the case where he gets a new city and time value
		   } else if (hTime > sTime) {          // if Harry was in his city for longer than Sally was in hers, account for the time Sally was in her city by
			   Total = Total - sTime;           // subtracting Sally's time from the total
			   hTime = hTime - sTime;           // and subtracting Sally's time from Harry's time to get the time he spent in his city after Sally left hers
			   sTime = 0;                       // then reset Sally's time to zero to trigger the case where she gets a new city and time value
		   } else {                             // if neither of the above are true Harry was in his city for the same amount of time Sally was in hers
			   Total = Total - hTime;           // subtract either value from the total time left
			   hTime = 0;                       // set both times to zero to get new city and time values for both Harry and Sally
			   sTime = 0;
		   }
	   }
	   if (hTime == 0) {    // if Harry's time left is 0
		   hInd = hInd + 1; // increment Harry's array index
	   }
	   if (sTime == 0) {    // if Sally's time left is 0
		   sInd = sInd + 1; // increment Sally's array index
	   }
   }

   /* Use a statement like this to print information helpful to
      debugging (e.g., the current value of some variable).
      Set DEBUG to 1 using the #define above when debugging, but
      reset it back to 0 before submitting your code so that your
      program doesn't confuse the autograder with superfluous prints. */
   if (DEBUG){
     Print_Timelines(HarryTimeline, SallyTimeline);
     printf("Sample debugging print statement. argc: %d \n", argc);
   }

   // your program should use this print statement
   printf("Total number of years in which both lived in the same city: %d\n", SumYears);
   return 0;
}

/* This subroutine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     for (N=0; N < 20; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 if (N < 10)
	   IntArray1[N] = Value;
	 else
	   IntArray2[N-10] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}

/* Colors used to display timelines.
https://en.wikipedia.org/wiki/ANSI_escape_code#Colors */

const char *colors[10] = {"\x1b[30;41m", // red
			  "\x1b[30;42m", // green
			  "\x1b[30;43m", // yellow
			  "\x1b[30;44m", // blue
			  "\x1b[30;45m", // magenta
			  "\x1b[30;46m", // cyan (light blue)
			  "\x1b[30;47m", // white bkgd
			  "\x1b[30;103m", // bright yellow
			  "\x1b[30;104m", // bright blue
			  "\x1b[30;106m"}; // bright cyan

#define RESET      "\x1b[0m"

void Print_Years(){
  int i;
  printf("  ");
  for (i=90; i<120; i++){
    printf("%3d", i%100);
  }
  printf("\n");
}

void Print_Timeline(int Timeline[]){
  int j, duration, city;
  int scale = 3;
  char interval[6];
  for (j=0; j<10; j=j+2){
    duration = Timeline[j];
    city     = Timeline[j+1];
    snprintf(interval, sizeof(interval), "%%%dd", duration*scale);
    printf("%s", colors[city]); // start highlighting in city's color
    printf(interval, city);
  }
  printf(RESET); // stop highlighting
  printf("\n");
}


void Print_Timelines(int HarryTimeline[], int SallyTimeline[]) {
  Print_Years();
  printf("H: ");

  Print_Timeline(HarryTimeline);

  printf("S: ");
  Print_Timeline(SallyTimeline);
}
