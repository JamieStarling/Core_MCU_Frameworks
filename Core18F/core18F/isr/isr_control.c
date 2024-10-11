/****************************************************************************
* Title                 :   Device ISR Control Functions
* Filename              :   isr_control.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :    
* Copyright             :   Jamie Starling
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


/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "isr_control.h"


/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : ISR_GIE_Disable
*//** 
* \b Description:
*
* Disables Global Interrupt
*  
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
*
* @return 		
*
* \b Example:
* @code
* 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/

void ISR_Global_Interrupt(LogicEnum_t setState)
{
  INTCON0bits.GIE = setState;
}

void ISR_Global_Low_Priority_Interrupt(LogicEnum_t setState)
{
  INTCON0bits.GIEL = setState;
}

void ISR_Interrupt_Priority_Enable(LogicEnum_t setState)
{
  INTCON0bits.IPEN = setState;  
}

ISR_Interrupt_StateEnum_t ISR_Interrupt_Status(void)
{
  return INTCON1 >> 6;  
}
        
void ISR_Enable_System_Default(void)
{
  if(_CORE18F_ENABLE_LOW_PRIORITY_INTERRUPTS){ISR_Global_Low_Priority_Interrupt(ENABLED);}
  if(_CORE18F_ENABLE_INTERRUPT_PRIORITY){ISR_Interrupt_Priority_Enable(ENABLED);}
  ISR_Global_Interrupt(ENABLED);  
}



/*** End of File **************************************************************/
