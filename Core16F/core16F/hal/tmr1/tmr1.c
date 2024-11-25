/****************************************************************************
* Title                 :   Timer1 Functions
* Filename              :   tmr1.c
* Author                :   Jamie Starling
* Origin Date           :   2024/09/08
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
*   2024/09/08  1.0.0       Jamie Starling  Initial Version
*  
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "tmr1.h"

/******************************************************************************
* TMR1 Interface
*******************************************************************************/
const TMR1_Interface_t TIMER1 = {
  .Enable = &TMR1_Enable,
  .Set_16bitModeRW = &TMR1_16bit_ReadWrite_Mode,
  .Set_ClockSource =  &TMR1_Set_Clock_Source,  
  .Set_PrescalerRate =  &TMR1_Set_Prescaler_Rate,
  .Read_8bitValue =  &TMR1_Get_8bit_Value,
  .Read_16bitValue =  &TMR1_Get_16bit_Value,
  .Clear_InterruptFlag =  &TMR1_Clear_Interrupt_Flag,
  .Set_InterruptEnable =  &TMR1_Enable_Interrupt,
  .IsInterruptFlagSet =  &TMR1_Interrupt_Flag_Set
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : TMR1_Enable()
* Description: Enables or disables Timer1 based on the input state.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to start Timer1, DISABLED to stop it.
*
*******************************************************************************/
void TMR1_Enable(LogicEnum_t setState)
{
    T1CONbits.ON = setState; // Enable or disable Timer1 based on setState
}

/******************************************************************************
* Function : TMR1_16bit_ReadWrite_Mode()
* Description: Configures Timer1 for 16-bit or 8-bit read/write operations.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED for 16-bit mode, DISABLED for 8-bit mode.
*
*******************************************************************************/
void TMR1_16bit_ReadWrite_Mode(LogicEnum_t setState)
{
  T1CONbits.RD16 = setState; // Set Timer1 read/write mode based on setState
}

/******************************************************************************
* Function : TMR1_Set_Prescaler_Rate()
* Description: Sets the prescaler rate for Timer1, which divides the input clock to control 
* the timer's counting speed.
*
* Parameters:
*   - value (TMR1_PreScaler_SelectEnum_t): The prescaler rate, such as 1:1, 1:2, 1:4, etc.
*
*******************************************************************************/
void TMR1_Set_Prescaler_Rate(TMR1_PreScaler_SelectEnum_t value)
{  
  T1CONbits.CKPS = value;  // Set the prescaler rate for Timer1
}

/******************************************************************************
* Function : TMR1_Set_Clock_Source()
* Description: Sets the clock source for Timer1, determining the input signal used for counting.
*
* Parameters:
*   - value (TMR1_Clock_Source_SelectEnum_t): The desired clock source.
*
*******************************************************************************/
void TMR1_Set_Clock_Source(TMR1_Clock_Source_SelectEnum_t value)
{
  T1CLKbits.CS = value; // Set the clock source for Timer1
}

/******************************************************************************
* Function : TMR1_Get_8bit_Value()
* Description: Retrieves the current 8-bit value from the Timer1 low byte (TMR1L).
*
*
* Returns:
*   - uint8_t: The lower 8 bits of the Timer1 counter (TMR1L).
*
*******************************************************************************/
uint8_t TMR1_Get_8bit_Value(void)
{
  return TMR1L; // Return the current value of the Timer1 low byte
}

/******************************************************************************
* Function : TMR1_Get_16bit_Value()
* Description: Retrieves the full 16-bit value from Timer1 by reading `TMR1H` and `TMR1L` 
*   and combining them.
*
* Returns:
*   - uint16_t: The 16-bit Timer1 counter value.
*
*******************************************************************************/
uint16_t TMR1_Get_16bit_Value(void)
{
  return CORE16F_Make_16(TMR1H,TMR1L); // Combine high and low bytes into 16-bit value
}

/******************************************************************************
* Function : TMR1_Clear_Interrupt_Flag()
* Description: Clears the Timer1 interrupt flag (`TMR1IF`) to allow new Timer1 interrupts.
* 
*******************************************************************************/
void TMR1_Clear_Interrupt_Flag(void)        
{  
  PIR4bits.TMR1IF = 0;  // Clear the Timer1 interrupt flag
}

/******************************************************************************
* Function : TMR1_Enable_Interrupt()
* Description:  Enables or disables the Timer1 interrupt by setting or clearing the `TMR1IE` bit.
*
* Parameters:
*   - setState: `ENABLED` to enable the interrupt, `DISABLED` to disable it.
*
*******************************************************************************/
void TMR1_Enable_Interrupt(LogicEnum_t setState)
{
    PIE4bits.TMR1IE = setState; // Enable or disable Timer1 interrupt
}

/******************************************************************************
* Function : TMR1_Interrupt_Flag_Set()
* Description:  Checks if the Timer1 interrupt flag (`TMR1IF`) is set.
*
* Returns:
*   - `ENABLED` if `TMR1IF` is set (interrupt occurred).
*   - `DISABLED` if `TMR1IF` is clear.
*
*******************************************************************************/
LogicEnum_t TMR1_Interrupt_Flag_Set(void)
{
  return PIR4bits.TMR1IF;  // Return the status of the Timer1 interrupt flag
}

/*** End of File **************************************************************/
