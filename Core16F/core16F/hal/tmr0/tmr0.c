/****************************************************************************
* Title                 :   CORE MCU Framework : TMR0 for 16F devices
* Filename              :   tmr0.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/30
* Version               :   1.0.1
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
*   2024/04/30  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
****** Includes
*******************************************************************************/
#include "tmr0.h"


/******************************************************************************
* TMR0 Interface
*******************************************************************************/
const TMR0_Interface_t TIMER0 = {
  .Enable = &TMR0_Enable,
  .Set_16bitMode = &TMR0_Set_16bit_Mode,
  .Set_OutputPostscaler = &TMR0_Set_Output_Postscaler,
  .Set_ClockSource =  &TMR0_Set_Clock_Source,
  .Set_InputAsyncMode =  &TMR0_Set_Input_Async_Mode,
  .Set_PrescalerRate =  &TMR0_Set_Prescaler_Rate,
  .Read_8bitValue =  &TMR0_Get_8bit_Value,
  .Read_16bitValue =  &TMR0_Get_16bit_Value,
  .Clear_InterruptFlag =  &TMR0_Clear_Interrupt_Flag,
  .Set_InterruptEnable =  &TMR0_Enable_Interrupt,
  .IsInterruptFlagSet =  &TMR0_Interrupt_Flag_Set
};

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : TMR0_Enable()
* Description: Enables or disables the TMR0 module based on the input parameter.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable TMR0, DISABLED to disable it.
*
*******************************************************************************/
void TMR0_Enable(LogicEnum_t setState)
{
    T0CON0bits.T0EN = setState; // Set TMR0 enable/disable bit
}

/******************************************************************************
* Function : TMR0_Set_16bit_Mode()
* Description: Enables or disables 16-bit mode for the TMR0 module.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable 16-bit mode, DISABLED to disable it.
*
*******************************************************************************/
void TMR0_Set_16bit_Mode(LogicEnum_t setState)
{
    T0CON0bits.T016BIT = setState; // Set TMR0 16-bit mode based on the parameter
}

/******************************************************************************
* Function : TMR0_Set_Output_Postscaler()
* Description: Sets the postscaler value for the TMR0 module.
*
* Parameters:
*   - value (TMR0_PostScaler_SelectEnum_t): The postscaler value to set (refer to device lookup table).
*
*******************************************************************************/
void TMR0_Set_Output_Postscaler(TMR0_PostScaler_SelectEnum_t value)
{  
  T0CON0bits.T0OUTPS = value; // Set the TMR0 postscaler
}

/******************************************************************************
* Function : TMR0_Set_Clock_Source()
* Description: Sets the clock source for the TMR0 module.
*
* Parameters:
*   - value (TMR0_Clock_Source_SelectEnum_t): The clock source to set (refer to device lookup table).
*
*******************************************************************************/
void TMR0_Set_Clock_Source(TMR0_Clock_Source_SelectEnum_t value)
{
    T0CON1bits.T0CS = value; // Set the TMR0 clock source
}

/******************************************************************************
* Function :  TMR0_Set_Input_Async_Mode()
* Description: Enables or disables the asynchronous mode for TMR0.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable async mode, DISABLED to disable it.
*
*******************************************************************************/
void TMR0_Set_Input_Async_Mode(LogicEnum_t setState)
{
    T0CON1bits.T0ASYNC = setState; // Set TMR0 async mode based on the parameter
}

/******************************************************************************
* Function : TMR0_Set_Prescaler_Rate()
* Description: Sets the prescaler value for the TMR0 module.
*
* Parameters:
*   - value (TMR0_PreScaler_SelectEnum_t): The prescaler value to set (refer to device lookup table).
*
*******************************************************************************/
void TMR0_Set_Prescaler_Rate(TMR0_PreScaler_SelectEnum_t value)
{
  T0CON1bits.T0CKPS = value; // Set the TMR0 prescaler value
}

/******************************************************************************
* Function :  TMR0_Get_8bit_Value()
* Description: Returns the current 8-bit value of the TMR0L register.
*
* Returns:
*   - uint8_t: The value of the TMR0L register.
*
*******************************************************************************/
uint8_t TMR0_Get_8bit_Value(void)
{
    return TMR0L; // Return the 8-bit value of the TMR0L register
}

/******************************************************************************
* Function :  TMR0_Get_16bit_Value()
* Description: Returns the current 16-bit value of TMR0 by combining the TMR0H and TMR0L registers.
*
* Parameters:
*   - None
*
* Returns:
*   - uint16_t: The combined 16-bit value from TMR0H and TMR0L.
*******************************************************************************/
uint16_t TMR0_Get_16bit_Value(void)
{
  return CORE.Make16(TMR0H,TMR0L); // Combine TMR0H and TMR0L to return a 16-bit value
}

/******************************************************************************
* Function :  TMR0_Clear_Interrupt_Flag()
* Description: Clears the TMR0 interrupt flag.
*
*******************************************************************************/
inline void TMR0_Clear_Interrupt_Flag(void)        
{  
  PIR0bits.TMR0IF = 0;
}

/******************************************************************************
* Function : TMR0_Enable_Interrupt()
* Description: Enables or disables the TMR0 interrupt.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable the interrupt, DISABLED to disable it.
*
*******************************************************************************/
void TMR0_Enable_Interrupt(LogicEnum_t setState)
{
    PIE0bits.TMR0IE = setState; // Set the TMR0 interrupt enable bit based on setState
}
      
/******************************************************************************
* Function : TMR0_Interrupt_Flag_Set()
* Description: Checks if the TMR0 interrupt flag is set.
*
*
* Returns:
*   - LogicEnum_t: TRUE if the TMR0 interrupt flag is set, FALSE otherwise.
*
*
*******************************************************************************/
inline LogicEnum_t TMR0_Interrupt_Flag_Set(void)
{
  return PIR0bits.TMR0IF; // Return the state of the TMR0 interrupt flag
}
/*** End of File **************************************************************/
