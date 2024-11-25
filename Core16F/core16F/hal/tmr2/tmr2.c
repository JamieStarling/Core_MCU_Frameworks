/****************************************************************************
* Title                 :   Timer 2 Functions
* Filename              :   tmr2.c
* Author                :   Jamie Starling
* Origin Date           :   2024/09/09
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
*   2024/09/09  1.0.0       Jamie Starling  Initial Version
*  
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "tmr2.h"

/******************************************************************************
* TMR2 Interface
*******************************************************************************/
const TMR2_Interface_t TIMER2 = {
  .Enable = &TMR2_Enable,
  .Set_OutputPostscaler = &TMR2_Set_Output_Postscaler,
  .Set_ClockSource =  &TMR2_Set_Clock_Source,  
  .Set_PrescalerRate =  &TMR2_Set_Prescaler_Rate,
  .Read_8bitValue =  &TMR2_Get_8bit_Value,
  .Clear_InterruptFlag =  &TMR2_Clear_Interrupt_Flag,
  .Set_InterruptEnable =  &TMR2_Enable_Interrupt,
  .IsInterruptFlagSet =  &TMR2_Interrupt_Flag_Set
};


/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : TMR2_Enable()
* Description: Starts or stops Timer2 based on the input parameter.
*
* Parameters:
*   - setState: `ENABLED` to start Timer2, `DISABLED` to stop it.
*
*******************************************************************************/
void TMR2_Enable(LogicEnum_t setState)
{
  T2CONbits.ON = setState; // Set or clear the ON bit to control Timer2
}

/******************************************************************************
* Function : TMR2_Set_Prescaler_Rate()
* Description: Sets the prescaler rate for Timer2, which controls the counting rate.
*
* Parameters:
*   - value: Prescaler rate from `TMR2_PreScaler_SelectEnum_t`.
*
*******************************************************************************/
void TMR2_Set_Prescaler_Rate(TMR2_PreScaler_SelectEnum_t value)
{  
  T2CONbits.CKPS = value;  // Set Timer2 prescaler rate
}

/******************************************************************************
* Function : TMR2_Set_Clock_Source()
* Description: Sets the clock source for Timer2. The selected clock source controls how 
* Timer2 increments its counter.
*
* Parameters:
*   - value: The clock source, selected from `TMR2_Clock_Source_SelectEnum_t`.
*
*
*******************************************************************************/
void TMR2_Set_Clock_Source(TMR2_Clock_Source_SelectEnum_t value)
{
  T2CLKCONbits.CS = value;  // Set Timer2 clock source
}

/******************************************************************************
* Function : TMR2_Set_Output_Postscaler()
* Description: Configures the output postscaler for Timer2. The postscaler determines how 
* many Timer2 overflows are needed before triggering an event or changing the 
* output.
*
* Parameters:
*   - value: The postscaler setting, from `TMR2_PostScaler_SelectEnum_t`.
*
*******************************************************************************/
void TMR2_Set_Output_Postscaler(TMR2_PostScaler_SelectEnum_t value)
{  
  T2CONbits.OUTPS = value; // Set Timer2 postscaler
}

/******************************************************************************
* Function : TMR2_Set_Mode()
* Description: Sets the operational mode for Timer2 by configuring the `T2HLTbits.MODE` register.
* Timer2 can be set to modes such as free-running, monostable, or retriggerable.
*
* Parameters:
*   - value: The mode for Timer2, chosen from `TMR2_Mode_SelectEnum_t`.
*
*******************************************************************************/
void TMR2_Set_Mode(TMR2_Mode_SelectEnum_t value)
{
  T2HLTbits.MODE = value;  // Configure Timer2 mode
}

/******************************************************************************
* Function : TMR2_Get_8bit_Value()
* Description: Returns the current 8-bit value from the Timer2 counter (`TMR2` register).
*
*
* Post-Condition:
*   - Returns the current 8-bit Timer2 value.
*
*******************************************************************************/
uint8_t TMR2_Get_8bit_Value(void)
{
  return TMR2; // Return the current Timer2 counter value
}

/******************************************************************************
* Function : TMR2_Clear_Interrupt_Flag()
* Description: Clears the Timer2 interrupt flag (`TMR2IF`) in the `PIR4` register, allowing
* Timer2 to generate new interrupts.
*
*******************************************************************************/
void TMR2_Clear_Interrupt_Flag(void)        
{  
  PIR4bits.TMR2IF = 0; // Clear the Timer2 interrupt flag
}

/******************************************************************************
* Function : TMR2_Enable_Interrupt()
* Description: Enables or disables the Timer2 interrupt by setting or clearing the `TMR2IE` bit in `PIE4`.
* Timer2 will continue counting even if the interrupt is disabled.
*
* Parameters:
*   - setState: `ENABLED` to enable the interrupt, `DISABLED` to disable it.
* 
*******************************************************************************/
void TMR2_Enable_Interrupt(LogicEnum_t setState)
{
    PIE4bits.TMR2IE = setState; // Set or clear the Timer2 interrupt enable bit
}

/******************************************************************************
* Function : TMR2_Interrupt_Flag_Set()
* Description: Checks if the Timer2 interrupt flag (`TMR2IF`) is set, indicating an overflow event.
*
* * Returns:
*   - `TRUE` if `TMR2IF` is set (interrupt occurred).
*   - `FALSE` if `TMR2IF` is clear.
*******************************************************************************/
LogicEnum_t TMR2_Interrupt_Flag_Set(void)
{
  return PIR4bits.TMR2IF;
}

/*** End of File **************************************************************/