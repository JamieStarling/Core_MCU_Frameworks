/****************************************************************************
* Title                 :   Core8 System Delays
* Filename              :   delays.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.2
* Compiler              :   XC8 
* Target                :   Microchip PIC16F series  
* Copyright             :   © 2024 Jamie Starling
* All Rights Reserved
*
* THIS SOFTWARE IS PROVIDED BY JAMIE STARLING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL JAMIE STARLING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/******************************************************************************
*                     LICENSED FOR NON-COMMERCIAL USE
*                Visit http://jamiestarling.com/corelicense
*                           for details 
*******************************************************************************/

/*************** TODO *********************************************************
 * 
 * 
 * 
*****************************************************************************/


/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
***** Includes
*******************************************************************************/
#include "delays.h"
#include "../timer/isr_core16F_system_timer.h"


/******************************************************************************
****** Functions
*******************************************************************************/
/******************************************************************************
* Function : CORE16F_Delay_BlockingMS()
*//** 
* \b Description:
*
* Generates a blocking delay for a specified time in milliseconds.
* This function blocks the program execution for the given number of milliseconds.
* It is primarily used for implementing time delays in the Core8 system.
*  
* PRE-CONDITION: The system timer must be enabled and properly initialized. 
* PRE-CONDITION: _CORE16F_SYSTEM_TIMER_ENABLE should be set in core16F.h
*
* POST-CONDITION: Program execution is delayed by the specified time.
*
* @param[in] : timeMS  The delay time in milliseconds. 	
*
* @return : void. This function does not return a value.		
*
* \b Example:
* @code
* 	
* CORE16F_Delay_BlockingMS(1000);  //Performs a 1000Ms Delay or 1 second.
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  1.0.2 Updated function to check for input value if less than Min Delay - Set to min delay value
* <hr>
*******************************************************************************/
void CORE16F_Delay_BlockingMS(uint32_t timeMS)
{
  
  if (timeMS < _CORE16F_MIN_DELAY_VALUE){timeMS = _CORE16F_MIN_DELAY_VALUE;}
  
  // Store the current time in milliseconds  
  uint32_t startMS = ISR_CORE16F_SYSTEM_TIMER_GetMillis();
    
  // Block execution until the specified time has passed 
  while (ISR_CORE16F_SYSTEM_TIMER_GetMillis() - startMS < timeMS){}
}

/*** End of File **************************************************************/
