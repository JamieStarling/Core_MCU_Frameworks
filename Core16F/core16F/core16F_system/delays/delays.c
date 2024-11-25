/****************************************************************************
* Title                 :   Core16F System Delays
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
* Description:
*
* This function generates a blocking delay for a specified duration in milliseconds.
* It continuously checks the elapsed time using ISR_CORE16F_SYSTEM_TIMER_GetMillis()
* and blocks the program until the delay period has passed.
*  
* Parameters:
* - timeMS (uint32_t): The desired delay time in milliseconds.
*  If less than _CORE16F_MIN_DELAY_VALUE, the function sets it to the minimum delay value.
*
*  - HISTORY OF CHANGES - 
*  1.0.2 Updated function to check for input value if less than Min Delay - Set to min delay value
* 
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
