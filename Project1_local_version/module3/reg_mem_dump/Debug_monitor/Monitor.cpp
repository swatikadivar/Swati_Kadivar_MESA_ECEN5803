/**----------------------------------------------------------------------------
             \file Monitor.cpp
--                                                                           --
--              ECEN 5003 Mastering Embedded System Architecture             --
--                  Project 1 Module 3                                       --
--                Microcontroller Firmware                                   --
--                      Monitor.cpp                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.0
-- Date of current revision:  2016-09-29   
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
   Functional Description: See below 
--
--      Copyright (c) 2015 Tim Scherr All rights reserved.
--
*/              

#include <stdio.h>
#include <stdint.h>
#include "shared.h"


/*******************************************************************************
* Set Display Mode Function
* Function determines the correct display mode.  The 3 display modes operate as 
*   follows:
*
*  NORMAL MODE       Outputs only mode and state information changes   
*                     and calculated outputs
*
*  QUIET MODE        No Outputs
*
*  DEBUG MODE        Outputs mode and state information, error counts,
*                    register displays, sensor states, and calculated output
*
*
* There is deliberate delay in switching between modes to allow the RS-232 cable 
* to be plugged into the header without causing problems. 
*******************************************************************************/

void set_display_mode(void)   
{
  UART_direct_msg_put("\r\nSelect Mode");
  UART_direct_msg_put("\r\n Hit NOR - Normal");
  UART_direct_msg_put("\r\n Hit QUI - Quiet");
  UART_direct_msg_put("\r\n Hit DEB - Debug" );
	UART_direct_msg_put("\r\n Hit REG - Register Dump" );
	UART_direct_msg_put("\r\n Hit MEM - Memory Dump" );
  UART_direct_msg_put("\r\n Hit V - Version#\r\n");
  UART_direct_msg_put("\r\nSelect:  ");
  
}


//*****************************************************************************/
/// \fn void chk_UART_msg(void) 
///
//*****************************************************************************/
void chk_UART_msg(void)    
{
   UCHAR j;
   while( UART_input() )      // becomes true only when a byte has been received
   {                                    // skip if no characters pending
      j = UART_get();                 // get next character

      if( j == '\r' )          // on a enter (return) key press
      {                // complete message (all messages end in carriage return)
         UART_msg_put("->");
         UART_msg_process();
      }
      else 
      {
         if ((j != 0x02) )         // if not ^B
         {                             // if not command, then   
            UART_put(j);              // echo the character   
         }
         else
         {
           ;
         }
         if( j == '\b' ) 
         {                             // backspace editor
            if( msg_buf_idx != 0) 
            {                       // if not 1st character then destructive 
               UART_msg_put(" \b");// backspace
               msg_buf_idx--;
            }
         }
         else if( msg_buf_idx >= MSG_BUF_SIZE )  
         {                                // check message length too large
            UART_msg_put("\r\nToo Long!");
            msg_buf_idx = 0;
         }
         else if ((display_mode == QUIET) && (msg_buf[0] != 0x02) && 
                  (msg_buf[0] != 'D') && (msg_buf[0] != 'N') && 
                  (msg_buf[0] != 'V') && (msg_buf[0] != 'R') &&
                  (msg_buf[0] != 'M') && (msg_buf_idx != 0))
         {                          // if first character is bad in Quiet mode
            msg_buf_idx = 0;        // then start over
         }
         else {                        // not complete message, store character
 
            msg_buf[msg_buf_idx] = j;
            msg_buf_idx++;
            if (msg_buf_idx > 2)
            {
               UART_msg_process();
            }
         }
      }
   }
}

//*****************************************************************************/
///  \fn void UART_msg_process(void) 
///UART Input Message Processing
//*****************************************************************************/
void UART_msg_process(void)
{
   UCHAR chr,err=0;
//   unsigned char  data;

   if( (chr = msg_buf[0]) <= 0x60 ) 
   {      // Upper Case
      switch( chr ) 
      {
         case 'D':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'B') && (msg_buf_idx == 3)) 
            {
               display_mode = DEBUG;
               UART_msg_put("\r\nMode=DEBUG\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

				 case 'R':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'G') && (msg_buf_idx == 3)) 
            {
               display_mode = PRINTREGISTERS;
               UART_msg_put("\r\nMode=PRINTREGISTERS\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

				 case 'M':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'M') && (msg_buf_idx == 3)) 
            {
               display_mode = MEMORYDUMP;
               UART_msg_put("\r\nMode=MEMORYDUMP\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;
						
         case 'N':
            if((msg_buf[1] == 'O') && (msg_buf[2] == 'R') && (msg_buf_idx == 3)) 
            {
               display_mode = NORMAL;
               UART_msg_put("\r\nMode=NORMAL\n");
               //display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'Q':
            if((msg_buf[1] == 'U') && (msg_buf[2] == 'I') && (msg_buf_idx == 3)) 
            {
               display_mode = QUIET;
               UART_msg_put("\r\nMode=QUIET\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'V':
            display_mode = VERSION;
            UART_msg_put("\r\n");
            UART_msg_put( CODE_VERSION ); 
            UART_msg_put("\r\nSelect  ");
            display_timer = 0;
            break;
                
         default:
            err = 1;
      }
   }

   else 
   {                                 // Lower Case
      switch( chr ) 
      {
        default:
         err = 1;
      }
   }

   if( err == 1 )
   {
      UART_msg_put("\n\rError!");
   }   
   else if( err == 2 )
   {
      UART_msg_put("\n\rNot in DEBUG Mode!");
   }   
   else
   {
    msg_buf_idx = 0;          // put index to start of buffer for next message
      ;
   }
   msg_buf_idx = 0;          // put index to start of buffer for next message


}


//*****************************************************************************
///   \fn   is_hex
/// Function takes 
///  @param a single ASCII character and returns 
///  @return 1 if hex digit, 0 otherwise.
///    
//*****************************************************************************
UCHAR is_hex(UCHAR c)
{
   if( (((c |= 0x20) >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))  )
      return 1;
   return 0;
}

__asm uint32_t mem_ret(int m)
{
	MOVS R3,R0
	LDR R0,[R3]
	BX LR
}

/*******************************************************************************
*   \fn  DEBUG and DIAGNOSTIC Mode UART Operation
*******************************************************************************/
void monitor(void)
{

/**********************************/
/*     Spew outputs               */
/**********************************/

   switch(display_mode)
   {
      case(QUIET):
         {
             UART_msg_put("\r\n ");
             display_flag = 0;
         }  
         break;
      case(VERSION):
         {
             display_flag = 0;
         }  
         break;         
      case(NORMAL):
         {
            if (display_flag == 1)
            {
               UART_msg_put("\r\nNORMAL ");
               UART_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Freq: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               display_flag = 0;
            }
         }  
         break;
      case(DEBUG):
         {
            if (display_flag == 1)
            {
               UART_msg_put("\r\nDEBUG ");
               UART_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated               
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Freq: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               display_flag = 0;
						}
							
				  }
				  break;
 /****************      ECEN 5803 add code as indicated   ***************/             
               //  Create a display of  error counts, sensor states, and
               //  ARM Registers R0-R15
			case(PRINTREGISTERS):
			{
						if (display_flag == 1)
            {		
								UART_msg_put("\n\rr0 = ");
								register uint32_t result __ASM("r0");
								UART_hex_put((result & 0xFF000000) >> 24);
								UART_hex_put((result & 0x00FF0000) >> 16);
								UART_hex_put((result & 0x0000ff00) >> 8);
								UART_hex_put(result & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r1 = ");
								register uint32_t result1 __ASM("r1");
								UART_hex_put((result1 & 0xFF000000) >> 24);
								UART_hex_put((result1 & 0x00FF0000) >> 16);
								UART_hex_put((result1 & 0x0000ff00) >> 8);
								UART_hex_put(result1 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r2 = ");
								register uint32_t result2 __ASM("r2");
								//data = (uint8_t *) result2;
								UART_hex_put((result2 & 0xFF000000) >> 24);
								UART_hex_put((result2 & 0x00FF0000) >> 16);
								UART_hex_put((result2 & 0x0000ff00) >> 8);
								UART_hex_put(result2 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r3 = ");
								register uint32_t result3 __ASM("r3");
								UART_hex_put((result3 & 0xFF000000) >> 24);
								UART_hex_put((result3 & 0x00FF0000) >> 16);
								UART_hex_put((result3 & 0x0000ff00) >> 8);
								UART_hex_put(result3 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r4 = ");
								register uint32_t result4 __ASM("r4");
								UART_hex_put((result4 & 0xFF000000) >> 24);
								UART_hex_put((result4 & 0x00FF0000) >> 16);
								UART_hex_put((result4 & 0x0000ff00) >> 8);
								UART_hex_put(result4 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r5 = ");
								register uint32_t result5 __ASM("r5");
								UART_hex_put((result5 & 0xFF000000) >> 24);
								UART_hex_put((result5 & 0x00FF0000) >> 16);
								UART_hex_put((result5 & 0x0000ff00) >> 8);
								UART_hex_put(result5 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r6 = ");
								register uint32_t result6 __ASM("r6");
								UART_hex_put((result6 & 0xFF000000) >> 24);
								UART_hex_put((result6 & 0x00FF0000) >> 16);
								UART_hex_put((result6 & 0x0000ff00) >> 8);
								UART_hex_put(result6 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r7 = ");
								register uint32_t result7 __ASM("r7");
								UART_hex_put((result7 & 0xFF000000) >> 24);
								UART_hex_put((result7 & 0x00FF0000) >> 16);
								UART_hex_put((result7 & 0x0000ff00) >> 8);
								UART_hex_put(result7 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r8 = ");
								register uint32_t result8 __ASM("r8");
								UART_hex_put((result8 & 0xFF000000) >> 24);
								UART_hex_put((result8 & 0x00FF0000) >> 16);
								UART_hex_put((result8 & 0x0000ff00) >> 8);
								UART_hex_put(result8 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r9 = ");
								register uint32_t result9 __ASM("r9");
								UART_hex_put((result9 & 0xFF000000) >> 24);
								UART_hex_put((result9 & 0x00FF0000) >> 16);
								UART_hex_put((result9 & 0x0000ff00) >> 8);
								UART_hex_put(result9 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r10 = ");
								register uint32_t result10 __ASM("r10");
								UART_hex_put((result10 & 0xFF000000) >> 24);
								UART_hex_put((result10 & 0x00FF0000) >> 16);
								UART_hex_put((result10 & 0x0000ff00) >> 8);
								UART_hex_put(result10 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r11 = ");
								register uint32_t result11 __ASM("r11");
								UART_hex_put((result11 & 0xFF000000) >> 24);
								UART_hex_put((result11 & 0x00FF0000) >> 16);
								UART_hex_put((result11 & 0x0000ff00) >> 8);
								UART_hex_put(result11 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r12 = ");
								register uint32_t result12 __ASM("r12");
								UART_hex_put((result12 & 0xFF000000) >> 24);
								UART_hex_put((result12 & 0x00FF0000) >> 16);
								UART_hex_put((result12 & 0x0000ff00) >> 8);
								UART_hex_put(result12 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r13 = ");
								register uint32_t result13 __ASM("r13");
								UART_hex_put((result13 & 0xFF000000) >> 24);
								UART_hex_put((result13 & 0x00FF0000) >> 16);
								UART_hex_put((result13 & 0x0000ff00) >> 8);
								UART_hex_put(result13 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r14 = ");
								register uint32_t result14 __ASM("r14");
								UART_hex_put((result14 & 0xFF000000) >> 24);
								UART_hex_put((result14 & 0x00FF0000) >> 16);
								UART_hex_put((result14 & 0x0000ff00) >> 8);
								UART_hex_put(result14 & 0x000000FF);
								UART_msg_put("\n\r");
								
								UART_msg_put("r15 = ");
								register uint32_t result15 __ASM("r15");
								UART_hex_put((result15 & 0xFF000000) >> 24);
								UART_hex_put((result15 & 0x00FF0000) >> 16);
								UART_hex_put((result15 & 0x0000ff00) >> 8);
								UART_hex_put(result15 & 0x000000FF);
								UART_msg_put("\n\r");								
								
										
               //  Create a command to read a section of Memory and display it
               //  Create a command to read 16 words from the current stack 
               // and display it in reverse chronological order.
							 // clear flag to ISR      
               display_flag = 0;
             }   
         }  
         break;

			case(MEMORYDUMP):
			{
					if (display_flag == 1)
            {
							 uint32_t mem[32];
               int mem_addr = 8192; //0X2000
							 UART_msg_put("\n\rMemory dump from 0x2000 to 0x2040\r\n");
							 for(uint8_t i = 0; i < 16; i++)
							 {
								 mem[i] = mem_ret(mem_addr);							 
								 UART_hex_put((mem[i] & 0x000000FF));
								 UART_msg_put(" ");
								 UART_hex_put((mem[i] & 0x0000FF00) >> 8);
								 UART_msg_put(" ");
								 UART_hex_put((mem[i] & 0x00FF0000) >> 16);
								 UART_msg_put(" ");
								 UART_hex_put((mem[i] & 0xFF000000) >> 24);
								 UART_msg_put(" ");
								 mem_addr = mem_addr+4;
								 if( (i!=0) && ((i%8)==0) ){
										UART_msg_put("\n\r"); 
								 }
							 }
							 display_flag=0;
						}
				}
				break;
      default:
      {
         UART_msg_put("Mode Error");
      }  
   }
}  
