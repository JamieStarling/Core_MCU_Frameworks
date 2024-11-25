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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
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
* Description: Enables or disables global interrupts by setting or clearing the GIE bit 
*   in the INTCON register, based on the `setState` parameter.
*
* Parameters:
*   - setState (LogicEnum_t): Set to ENABLED to enable global interrupts or 
*     DISABLED to disable them.
*  
*******************************************************************************/
void ISR_Global_Interrupt(LogicEnum_t setState)
{
  INTCONbits.GIE = setState;
}

/******************************************************************************
* Function : ISR_Peripheral_Interrupt
* Description: Enables or disables peripheral interrupts by setting or clearing the PEIE 
*   bit in the INTCON register, based on the `setState` parameter.
*
* Parameters:
*   - setState (LogicEnum_t): Set to ENABLED to enable peripheral interrupts or 
*     DISABLED to disable them.
* 
*******************************************************************************/
void ISR_Peripheral_Interrupt(LogicEnum_t setState)
{
  INTCONbits.PEIE = setState;
}

/******************************************************************************
* Function : ISR_Enable_System_Default()
* Description: Enables global interrupts and, if configured, peripheral interrupts by 
* calling `ISR_Global_Interrupt` and `ISR_Peripheral_Interrupt`.
*
*******************************************************************************/
void ISR_Enable_System_Default(void)
{  
    #ifdef _CORE16F_ENABLE_PERIPHERAL_INTERRUPT
        ISR_Peripheral_Interrupt(ENABLED);
    #endif /*_CORE16F_ENABLE_PERIPHERAL_INTERRUPT*/
    
    ISR_Global_Interrupt(ENABLED);  
}

/*** End of File **************************************************************/
