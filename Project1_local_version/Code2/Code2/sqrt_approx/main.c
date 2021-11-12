/************************************************************************//**
* \file main.c
* \brief LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
*
* Write an assembly code subroutine to approximate the square root of an 
* argument using the bisection method. All math is done with integers, so the 
* resulting square root will also be an integer
******************************************************************************
* GOOD LUCK!
 ****************************************************************************/

 #include "stdint.h"
 
 
 /** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
 #include "string.h"
 /** @endcond */
 
 /**
 * @brief 5863 Write a brief description of the function here
 *
 * Detailed description of the function after one line gap
 *
 * @note You can also add a note this way
 *
 * @param[in] 
 *  You can also start writing on a new line. 
 *  And continue on the next line. This is how you describe an input parameter
 *
 * @return
 *  This is how you describe the return value
 * 
 */
__asm int my_sqrt(int x){
	
		//Write your code here
	
//R6 = x
//R1 = a = 0
//R7 = a
//R3 = b = square root of largest possible argument (e.g. ~216).
//R2 = R0 = c = -1
//R5 = c_old
		
	LDR R6, [r13]
	MOVS R1, #0
	MOVS R7, #0
	MOVS R2, #1
	MOVS R3, #255
	MOVS R5, #0

//do {	
loop
//	c_old <- c
				MOV R5, R2
//	c <- (a+b)/2	
				ADD R1, R1, R3	// a = a+b
				MOV R2, R1		// c = a
				MOV R1, R7		// restoring a
				LSRS R2, R2, #1
//	if (c*c == x) {
				MOV R0, R2		// take backup of C
				MULS R2,R2,R2	// c = c*c
				MOV R4, R2
				MOV R2, R0		// restoring c
				CMP R4,R6 
//		done = 1
				beq exit_loop 

//	} else if (c*c < x) {
				CMP R4, R6
//		a <- c
				BGT GT_LABEL
				MOV R1, R2
				B COMP_DONE
//	} else {
GT_LABEL
//		b <- c
				MOV R3, R2
//	}
COMP_DONE
//} while (!done) && (c != c_old)
				CMP R5, R2
				BNE loop
		
//return c 
exit_loop
				bx lr
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
 /**
 * @brief Main function
 *
 * Detailed description of the main
 */
int main(void){
	volatile int r, j=0;
	int i;                  
  r = my_sqrt(0);     // should be 0
  r = my_sqrt(25);    // should be 5
	r = my_sqrt(133); 	// should be 11
  for (i=0; i<10000; i++){
		r = my_sqrt(i);
    j+=r;
  }
	while(1)
		;
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************/
