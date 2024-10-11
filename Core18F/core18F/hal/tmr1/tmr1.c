/****************************************************************************
* Title                 :   Timer1 Functions
* Filename              :   tmr1.c
* Author                :   Jamie Starling
* Origin Date           :   2024/09/08
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
*   2024/09/08  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "tmr1.h"


/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : TMR1_Enable()
*//** 
* \b Description:
*
* Enables or disables Timer1 based on the input state. When enabled, Timer1 
* will start counting based on the configured clock source and prescaler settings.
*
* PRE-CONDITION:  
*    - Timer1 must be configured with the desired prescaler and clock source before enabling.
*
* POST-CONDITION: 
*    - Timer1 will either start counting (if enabled) or stop (if disabled).
*
* @param[in] setState - The desired state of Timer1, where ENABLED starts the timer 
*                       and DISABLED stops it.	
*
* @return None
*
* \b Example:
* @code
* 	
* // Enable Timer1
* TMR1_Enable(ENABLED);
*
* // Disable Timer1
* TMR1_Enable(DISABLED);
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_Enable(LogicEnum_t setState)
{
  T1CONbits.ON = setState;
}

/******************************************************************************
* Function : TMR1_16bit_ReadWrite_Mode()
*//** 
* \b Description:
*
* Enables register read/write of Timer1 in two 8-bit operation or when enabled one 16-bit operation
*  
* This function configures Timer1 to operate in either 16-bit or 8-bit read/write mode.
* When 16-bit mode is enabled, Timer1 registers are accessed in one 16-bit operation.
* When 16-bit mode is disabled, Timer1 registers are accessed as two separate 8-bit 
* operations (high byte and low byte). This setting is configured by modifying the 
* `T1CONbits.RD16` bit.
*
* PRE-CONDITION:  
*    - Timer1 must be disabled before changing the read/write mode.
*
* POST-CONDITION: 
*    - Timer1 is configured for either 16-bit or 8-bit read/write operations.
*
* @param[in] setState - The desired mode for Timer1 read/write operations. 
*                       Use `ENABLED` to enable 16-bit mode and `DISABLED` 
*                       for 8-bit mode.
*
* @return None	
*
* \b Example:
* @code
* 	
* // Enable 16-bit read/write mode for Timer1
* TMR1_16bit_ReadWrite_Mode(ENABLED);
*
* // Disable 16-bit mode (use 8-bit operations for Timer1)
* TMR1_16bit_ReadWrite_Mode(DISABLED);
* 	
* @endcode
*
 \b Notes:
* - Timer1 should be disabled before configuring the read/write mode to ensure proper operation.
* - Use 16-bit mode for faster access to Timer1 when both high and low bytes are needed.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_16bit_ReadWrite_Mode(LogicEnum_t setState)
{
  T1CONbits.RD16 = setState;
}

/******************************************************************************
* Function : TMR1_Set_Prescaler_Rate()
*//** 
* \b Description:
*
* This function sets the prescaler rate for Timer1. The prescaler divides the input clock 
* to slow down the counting rate of Timer1. This allows for longer timing intervals 
* without overflowing the timer. The prescaler rate is selected by writing to the 
* `T1CONbits.CKPS` bits.
*
* The available prescaler rates are defined in the `TMR1_PreScaler_SelectEnum_t` enum, 
* and may include options such as 1:1, 1:2, 1:4, 1:8, etc., depending on the microcontroller.
*
* PRE-CONDITION:  
*    - Timer1 must be disabled before changing the prescaler setting.
*
* POST-CONDITION: 
*    - Timer1 will count at the rate determined by the selected prescaler once it is enabled.
*
* @param[in] value - The prescaler rate to be set, chosen from the `TMR1_PreScaler_SelectEnum_t` enum.
*	
*
* @return None
*
* \b Example:
* @code
* 	
* // Set Timer1 prescaler to 1:8
* TMR1_Set_Prescaler_Rate(TMR1_PRESCALER_1_8);
* 	
* @endcode
*
* \b Notes:
* - Ensure Timer1 is disabled before changing the prescaler to avoid unexpected behavior.
* - The prescaler affects the timer's overflow rate and should be set based on the timing requirements of the application.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_Set_Prescaler_Rate(TMR1_PreScaler_SelectEnum_t value)
{  
  T1CONbits.CKPS = value;
}

/******************************************************************************
* Function : TMR1_Set_Clock_Source()
*//** 
* \b Description:
*
* This function sets the clock source for Timer1. The clock source determines 
* the input signal used by Timer1 to increment its counter. The clock source 
* can be an internal or external signal, depending on the options provided 
* in the `TMR1_Clock_Source_SelectEnum_t` enumeration.
*
* The available clock sources may include the system clock (`FOSC`), 
* an external clock pin, or other internal timers depending on the specific microcontroller. 
* This setting is configured in the `T1CLKbits.CS` bits of the Timer1 control register.
*
* PRE-CONDITION:  
*    - Timer1 must be disabled before changing the clock source to avoid incorrect behavior.
*
* POST-CONDITION: 
*    - Timer1 will use the selected clock source for its counting operation once it is enabled.
*
* @param[in] value - The clock source to be set, chosen from the `TMR1_Clock_Source_SelectEnum_t` enum.
*	
*
* @return None	
*
* \b Example:
* @code
* 	
* // Set Timer1 clock source to the system clock (FOSC)
* TMR1_Set_Clock_Source(TMR1_CLOCK_SOURCE_FOSC);
* 	
* @endcode
*
* \b Notes:
* - Ensure that Timer1 is disabled before changing the clock source.
* - The clock source determines how Timer1 increments, so select the appropriate source for the application?s timing requirements.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_Set_Clock_Source(TMR1_Clock_Source_SelectEnum_t value)
{
  T1CLKbits.CS = value;
}

/******************************************************************************
* Function : TMR1_Get_8bit_Value()
*//** 
* \b Description:
*
* This function retrieves the current 8-bit value from the lower byte of the Timer1 
* counter (`TMR1L`). Timer1 is a 16-bit timer, but this function reads only the lower 
* 8 bits of the timer value. This is useful for applications that do not require the 
* full 16-bit resolution of Timer1.
*
* The returned value represents the current state of the Timer1 low byte register.
*
* PRE-CONDITION:  
*    - Timer1 must be enabled and running.
*
* POST-CONDITION: 
*    - The current value of the `TMR1L` register is returned as an 8-bit value.
*
* @param[in] None
*
* @return uint8_t
*    - The lower 8 bits of the Timer1 counter (`TMR1L`).		
*
* \b Example:
* @code
* 	
* // Get the current 8-bit value from Timer1
* uint8_t timer_value = TMR1_Get_8bit_Value();
* 	
* @endcode
*
* \b Notes:
* - This function only reads the lower 8 bits of Timer1 (`TMR1L`). To retrieve the full 16-bit value, use `TMR1_Get_16bit_Value()`.
* - Ensure Timer1 is running before calling this function to get valid results.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t TMR1_Get_8bit_Value(void)
{
  return TMR1L;
}

/******************************************************************************
* Function : TMR1_Get_16bit_Value()
*//** 
* \b Description:
*
* This function retrieves the full 16-bit value from Timer1 by reading both the high 
* byte (`TMR1H`) and the low byte (`TMR1L`). Timer1 is a 16-bit timer, and this function 
* returns the combined 16-bit value from the two 8-bit registers.
*
* The returned value represents the current state of the Timer1 counter, which can be used 
* for timing applications requiring the full 16-bit resolution.
*
* PRE-CONDITION:  
*    - Timer1 must be enabled and running.
*    - Timer1 must be configured for 16-bit read/write mode if sequential access to 
*      the `TMR1H` and `TMR1L` registers is required.
*
* POST-CONDITION: 
*    - The current value of Timer1 is returned as a 16-bit value.
*
* @param[in] None
*
* @return uint16_t
*    - The 16-bit value of the Timer1 counter (`TMR1H` and `TMR1L` combined).
*		
*
* \b Example:
* @code
* 	
* // Get the current 16-bit value from Timer1
* uint16_t timer_value = TMR1_Get_16bit_Value();
* 	
* @endcode
*
* \b Notes:
* - This function reads both `TMR1H` (high byte) and `TMR1L` (low byte) and combines them 
*   into a 16-bit value. 
* - Ensure Timer1 is running before calling this function to get valid results.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint16_t TMR1_Get_16bit_Value(void)
{
  return CORE18F_Make_16(TMR1H,TMR1L);
}

/******************************************************************************
* Function : TMR1_Clear_Interrupt_Flag()
*//** 
* \b Description:
*
* This function clears the Timer1 interrupt flag (`TMR1IF`) in the `PIR4` register. 
* The interrupt flag is set when Timer1 overflows, signaling that an interrupt has occurred. 
* This function resets the flag to ensure that Timer1 can generate new interrupts for subsequent 
* overflows.
*
* Clearing the interrupt flag is typically done inside an interrupt service routine (ISR) 
* after the Timer1 interrupt has been handled.
*
* PRE-CONDITION:  
*    - Timer1 must be initialized and running.
*    - Timer1 interrupt must have been triggered, setting the `TMR1IF` flag.
*
* POST-CONDITION: 
*    - The Timer1 interrupt flag (`TMR1IF`) is cleared, allowing Timer1 to generate new interrupts.
*
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* 	
* // Clear the Timer1 interrupt flag after handling the interrupt
* TMR1_Clear_Interrupt_Flag();
* 	
* @endcode
*
* \b Notes:
* - This function should be called after handling a Timer1 interrupt to reset the flag 
*   and allow Timer1 to trigger further interrupts.
* - If the flag is not cleared, Timer1 will not generate additional interrupts.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_Clear_Interrupt_Flag(void)        
{  
  PIR4bits.TMR1IF = 0;
}

/******************************************************************************
* Function : TMR1_Enable_Interrupt()
*//** 
* \b Description:
*
* This function enables or disables the Timer1 interrupt. When enabled, Timer1 
* can generate an interrupt when it overflows, allowing the program to handle 
* the event via an interrupt service routine (ISR). When disabled, Timer1 will 
* continue counting but will not trigger any interrupts.
*
* The function modifies the `TMR1IE` bit in the `PIE4` register to control the interrupt.
*
* PRE-CONDITION:  
*    - Timer1 must be initialized.
*    - The global interrupt and peripheral interrupt enable bits must be configured 
*      separately if necessary.
*
* POST-CONDITION: 
*    - Timer1 interrupt is either enabled or disabled, depending on the input parameter.
*
* @param[in] setState - The desired interrupt state: `ENABLED` to enable Timer1 interrupt, 
*                       or `DISABLED` to disable it.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Enable the Timer1 interrupt
* TMR1_Enable_Interrupt(ENABLED);
*
* // Disable the Timer1 interrupt
* TMR1_Enable_Interrupt(DISABLED);
* 	
* @endcode
*
* \b Notes:
* - Ensure that global and peripheral interrupts are properly enabled in the system if Timer1 interrupts are required.
* - Disabling the interrupt will not stop Timer1 from counting but will prevent it from generating interrupts.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR1_Enable_Interrupt(LogicEnum_t setState)
{
    PIE4bits.TMR1IE = setState;
}

/******************************************************************************
* Function : TMR1_Interrupt_Flag_Set()
*//** 
* \b Description:
*
* This function checks whether the Timer1 interrupt flag (`TMR1IF`) is set, indicating 
* that Timer1 has overflowed and an interrupt event has occurred. The function returns 
* `ENABLED` if the interrupt flag is set and `DISABLED` if the flag is clear.
*
* This function is typically used to check the interrupt status in polling mode or 
* before executing any interrupt-related tasks.
*
* PRE-CONDITION:  
*    - Timer1 must be initialized and running.
*    - The Timer1 interrupt flag (`TMR1IF`) should be monitored either in an interrupt service 
*      routine (ISR) or in polling mode.
*
* POST-CONDITION: 
*    - Returns the status of the Timer1 interrupt flag (`TMR1IF`), either set or clear.
*
* @param[in] None
*
* @return LogicEnum_t
*    - `ENABLED` if the Timer1 interrupt flag is set, indicating an interrupt has occurred.
*    - `DISABLED` if the Timer1 interrupt flag is clear.		
*
* \b Example:
* @code
* 	
* // Check if the Timer1 interrupt flag is set
* if (TMR1_Interrupt_Flag_Set() == ENABLED) {
*     // Handle Timer1 interrupt event
* }
* 	
* @endcode
*
* \b Notes:
* - If the flag is set, it means Timer1 has overflowed and an interrupt has been triggered.
* - The interrupt flag must be cleared after handling the interrupt using `TMR1_Clear_Interrupt_Flag()`.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
LogicEnum_t TMR1_Interrupt_Flag_Set(void)
{
  return PIR4bits.TMR1IF;
}

/*** End of File **************************************************************/
