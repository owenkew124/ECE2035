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
 Date: 10/1/2021

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------

This program locates a part of a specified color in a pile of parts and reports
its bounding box (Upper left corner pixel, Lower right corner pixel) and 
the part's color code. The pixels are specified as linear offsets from the 
pile image base.*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	             PileInts[1024];
   // This allows you to access the pixels (individual bytes)
   // as byte array accesses (e.g., Pile[25] gives pixel 25):
   char *Pile = (char *)PileInts;

   int	             NumInts, ColorToFind=0;
   int               UpperLeft=0, LowerRight=0;
   int  Load_Mem(char *, int *);
   int done = 0, UpperColumn = 0, UpperRow = 0, LowerRow = 0, LowerColumn = 0, j = 0, k = 0, l = 0, RowFound = 0, width = 1;

   if (argc != 3) {
     printf("usage: ./P1-1 testcase_file color_code\n");
     exit(1);
   }
   ColorToFind = atoi(argv[2]);
   NumInts = Load_Mem(argv[1], PileInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }

   if (DEBUG){
     printf("Pile[0] is Pixel 0: 0x%d\n", Pile[141]);
     printf("Pile[107] is Pixel 107: 0x%d\n", Pile[107]);
   }

   /* Your program goes here */
   for (int i = 0; i < 4096; i = i + 64) {
		j = i + 32;
		k = i + 31;
		l = k;
		if (Pile[j] == ColorToFind) {
			if (Pile[k] == ColorToFind) {
				while(Pile[l] == ColorToFind) {
					width++;
					l--;
				}
				RowFound = 1;
			}
			l = j;
			if (Pile[j + 1] == ColorToFind]) {
				while(Pile[l] == ColorToFind) {
					width++;
					l++;
				}
				RowFound = 1;
			}
		}
		if (RowFound) {
			break;
		}
   }
   for (int i = 0; i < 4096; i = i + 64) {
		if (RowFound) {
			break;
		}
		j = i + 16;
		k = i + 15;
		l = k;
		if (Pile[j] == ColorToFind) {
			if (Pile[k] == ColorToFind) {
				while(Pile[l] == ColorToFind) {
					width++;
					l--;
				}
				RowFound = 1;
			}
			l = j + 1;
			if (Pile[j + 1] == ColorToFind]) {
				while(Pile[l] == ColorToFind) {
					width++;
					l++;
				}
				RowFound = 1;
			}
		}
		if (RowFound) {
			break;
		}
   }
   for (int i = 0; i < 4096; i = i + 64) {
		if (RowFound) {
			break;
		}
		j = i + 48;
		k = i + 47;
		l = k;
		if (Pile[j] == ColorToFind) {
			if (Pile[k] == ColorToFind) {
				while(Pile[l] == ColorToFind) {
					width++;
					l--;
				}
				RowFound = 1;
			}
			l = j;
			if (Pile[j + 1] == ColorToFind]) {
				while(Pile[l] == ColorToFind) {
					width++;
					l++;
				}
				RowFound = 1;
			}
		}
		if (RowFound) {
			break;
		}		
   }
   
   printf("width %d\n", width); 
   printf("The part is located at: %d, %d, color: %d\n",
	  UpperLeft, LowerRight, ColorToFind);
   exit(0);
}

/* This routine loads in up to 1024 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 1024; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
