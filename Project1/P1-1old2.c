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
   int done = 0, UpperColumn = 0, UpperRow = 0, height = 0, k = 0, LastRow = 0, LastRowColumn = 0, width = 0, PrevRowColumn = 0, l = 0, PrevUpperRowColumn = 0;

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
   for (int i = 0; i < 40; i++) {                             //Finds the farthest left column of the part
	   for (int j = 0; j < 40; j++) {
			int k = i * 64 + j;
			if (Pile[k] == ColorToFind && (Pile[k+64] == ColorToFind || Pile[k+128] == ColorToFind)) { //checks for a column (has to check 3 rows because of occlusion)
				UpperColumn = j;        //assigns the coordinate of the column to UpperColumn
				UpperRow = i;           // assigns the coordinate of the row to UpperRow
				done = 1;               // tells the outer loop to stop
				break;
			}
	    }
	   if (done) {
		   break;
	   }
   }
   /* Calculates the height of the vertical lines and  width of the horizontal lines*/
   done = 0;       
   k = UpperRow*64 + UpperColumn + 64; 
   while(Pile[k] == ColorToFind || Pile[k + 64] == ColorToFind) {
		k = k + 64;
		height = height + 1;
		if (Pile[k + 1] == ColorToFind) {
			l = k;
			LastRow = (k - UpperColumn)/64;
			k = LastRow*64 + UpperColumn;
			PrevUpperRowColumn = LastRowColumn;
			LastRowColumn = UpperColumn;
			while (Pile[l - 1] == ColorToFind) {
				l = l - 1;
				LastRowColumn -= 1;
			}
			if (PrevUpperRowColumn > LastRowColumn) {
				LastRowColumn = PrevUpperRowColumn;
			}
			l = LastRow*64 + LastRowColumn + 1;
			PrevRowColumn = width;
			width = 0;
			while (Pile[l] == ColorToFind || Pile[l+1] == ColorToFind) {
				l = l + 1;
				width += 1;
			}
			if (PrevRowColumn > width) {
				width = PrevRowColumn;
			}
		}
   }
   
   UpperLeft = LastRowColumn + UpperRow * 64;
   printf("%d bottom\n", (UpperRow) * 64);
   printf("%d right\n", LastRowColumn + width);
   printf("%d height\n", height);
   printf("%d width\n", width);
   LowerRight = (LastRowColumn + width) + ((UpperRow + height) * 64);  
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
