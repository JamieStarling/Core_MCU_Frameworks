/****************************************************************************
* Title                 :   Microchip PIC16F series ISR Control Functions
* Filename              :   isr_control.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
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
* Enables or disables global interrupts.
* This function enables or disables global interrupts by setting the GIE bit
* in the INTCON register. It is controlled by the `setState` parameter.
*  
* PRE-CONDITION:  The interrupt source should be configured before enabling global interrupts.
*
* POST-CONDITION: GIE flag is set based on `setState` parameter.
*
* @param[in] setState  LogicEnum_t value to either enable (ENABLED) or disable (DISABLED) global interrupts.	
*
* @return 		
*
* \b Example:
* @code
* ISR_Global_Interrupt(ENABLED);  // Enable global interrupts
* ISR_Global_Interrupt(DISABLED); // Disable global interrupts
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
  INTCONbits.GIE = setState;
}

/******************************************************************************
* Function : ISR_Peripheral_Interrupt
*//** 
* \b Description:
*
* Enables or disables peripheral interrupts.
* This function enables or disables peripheral interrupts by setting the PEIE bit
* in the INTCON register. It is controlled by the `setState` parameter.
* 
* PRE-CONDITION: The interrupt source should be configured before enabling peripheral interrupts. 
*
* POST-CONDITION: PEIE flag is set based on `setState` parameter.
*
* @param[in] setState  LogicEnum_t value to either enable (ENABLED) or disable (DISABLED) peripheral interrupts.
*
* @return 		
*
* \b Example:
* @code
* ISR_Peripheral_Interrupt(ENABLED);  // Enable peripheral interrupts
* ISR_Peripheral_Interrupt(DISABLED); // Disable peripheral interrupts	
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
void ISR_Peripheral_Interrupt(LogicEnum_t setState)
{
  INTCONbits.PEIE = setState;
}


void ISR_Enable_System_Default(void)
{  
    #ifdef _CORE16F_ENABLE_PERIPHERAL_INTERRUPT
    ISR_Peripheral_Interrupt(ENABLED);
    #endif /*_CORE16F_ENABLE_PERIPHERAL_INTERRUPT*/
    
    ISR_Global_Interrupt(ENABLED);  
}

/*** End of File **************************************************************/
