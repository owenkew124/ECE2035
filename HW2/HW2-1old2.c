//=================================================================
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*    
Please fill in the following
 Student Name:
 Date:

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

#define DEBUG 1 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami, 
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums, SumYears=0;
   int  Load_Mem(char *, int *, int *);
   void Print_Timelines(int *, int *);
   int sTime, hTime, hCity, sCity, time, ind, bTime, hPrevCity, bFarTime, sPrevCity, hFar, sFar = 0;
   int hPrev, sPrev = 10; 

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
	while (ind < 5) {
		hCity = HarryTimeline[ind*2 + 1];
		sCity = SallyTimeline[ind*2 + 1];
		hTime = HarryTimeline[ind*2];
		sTime = SallyTimeline[ind*2];
		hPrevCity = HarryTimeline[hPrev*2 + 1];
		sPrevCity = SallyTimeline[sPrev*2 + 1];
		printf("htime %d\n",hTime);
		printf("stime %d\n",sTime);
		if (HarryTimeline[hFar*2 + 1] == sCity) {
			if (bTime > sTime) {
				time = sTime;
				hPrev = ind;
				sTime = 0;
			} else {
				time = bFarTime;
				sTime = sTime - bFarTime;
			}
			SumYears = SumYears + time;
		}
		if (SallyTimeline[sFar*2 + 1] == hCity) {
			if (hTime < bTime) {
				time = hTime;
				sPrev = ind;
				hTime = 0;
			} else {
				time = bFarTime;
				hTime = hTime - bFarTime;
			}
			SumYears = SumYears + time;
		}
		if (sPrev == 10 && bTime > hTime) {
			hFar = hPrev;
			bFarTime = bTime - hTime;
		}
		if (hPrev == 10 && bTime > sTime) {
			sFar = hPrev;
			bFarTime = bTime - sTime;
		}
		if (hPrevCity == sCity) {
			if (bTime > sTime) {
				time = sTime;
				hPrev = ind;
				sTime = 0;
			} else {
				time = bTime;
				sTime = sTime - bTime;
			}
			SumYears = SumYears + time;
		}
		if (sPrevCity == hCity) {
			if (hTime < bTime) {
				time = hTime;
				sPrev = ind;
				hTime = 0;
			} else {
				time = bTime;
				hTime = hTime - bTime;
			}
			SumYears = SumYears + time;
		}
		hPrev = 0;
		sPrev = 0;
		if (hCity == sCity) {
			if (hTime > sTime) {
				time = sTime;
				hPrev = ind;
				bTime = hTime - sTime;
			} else if (sTime > hTime) {
				time = hTime;
				sPrev = ind;
				bTime = sTime - hTime;
			} else {
				time = sTime;
			}
			SumYears = SumYears + time;
		} else {
			if (hTime > sTime) {
				hPrev = ind;
			} else if (sTime > hTime) {
				sPrev = ind;
			}
		}
		ind = ind + 1;
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
