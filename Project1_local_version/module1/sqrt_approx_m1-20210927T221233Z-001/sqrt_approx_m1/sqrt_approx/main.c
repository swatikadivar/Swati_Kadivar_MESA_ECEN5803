/**
 **********************************************************************//**
 * @file main.c
 * @brief LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
 *
 * Write an assembly code subroutine to approximate the square root of an 
 * argument using the bisection method. All math is done with integers, so the 
 * resulting square root will also be an integer
 */

 #include "stdint.h"
 /** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
 #include "string.h"
 /** @endcond */
 
 /**
  * @brief my_sqrt routine calculates square root of the given input
  * Approximate square root with bisection method.
  *
  * @note This routine is written in assembly language
  *
  * @param[x] 
  *  input parameter x contains a number of which we want to find sqrt 
  *
  * @return
  *  The return value will give sqrt of x.
  * 
  */
__asm int my_sqrt(int x){
///< R6 = x
///< R1 = a = 0
///< R2 = b = square root of largest possible argument (e.g. ~216).
///< R3 = c = -1
///< R5 = c_old	
	MOV R6, R0
	MOVS r1, #0
	MOVS r3, #0XFF
	MOVS r2, #255
	MOVS r5, #0
///< do {	
loop MOV R5,R3
///< c_old <- c	
///< c <- (a+b)/2
	MOV R0,R1
	ADD R1,R1,R2
	LSRS R1,R1,#1
	MOV R3,R1
	MOV R1,R0
///< if (c*c == x) {
	MOV R0,R3
	MULS R3,R3,R3
	MOV R7,R3
	MOV R3,R0
	CMP R7,R6 
///< done = 1
	BEQ exit_loop 
///< } else if (c*c < x) {
	CMP R7,R6
	
	BGT GT_LABEL
///< a <- c
	MOV R1,R3
	B COMP_DONE
///< } else {
///< b <- c
GT_LABEL MOV R2,R3
///< 	}
///< } while (!done) && (c != c_old)
COMP_DONE CMP R5,R3
	BNE loop		
///< return c 
exit_loop BX LR
}
	

/**
 *----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------
 */
 /**
  * @brief Main function
  * Program starts from here
  *
  * This program calculates square root of given number.
  */
int main(void){
	volatile int r1, r2, r3, a, b, c, d, j=0,r;
	int i;                  
    r1 = my_sqrt(0);     ///< should be 0
    r2 = my_sqrt(25);    ///< should be 5
	r3 = my_sqrt(133); 	 ///< should be 11
	a = my_sqrt(2);
	b = my_sqrt(4);
	c = my_sqrt(22);
	d = my_sqrt(121);
	
    for (i=0; i<10000; i++){
		r = my_sqrt(i);
        j+=r;
    }
	while(1)
		;
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************/
