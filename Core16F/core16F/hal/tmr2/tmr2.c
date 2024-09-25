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

/*************** TODO *********************************************************
 * 
 * 
 * 
*****************************************************************************/

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/09/09  1.0.0       Jamie Starling  Initial Version
*  
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
*//** 
* \b Description:
*
* Enables or disables Timer2. When enabled, Timer2 starts counting based on the 
* clock source and prescaler settings. Disabling the timer will stop the counting process.
*
* The function modifies the `T2CONbits.ON` bit to enable or disable Timer2.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized and configured with the desired clock source 
*      and prescaler settings before enabling.
*
* POST-CONDITION: 
*    - Timer2 is either enabled and begins counting, or disabled and stops counting.
*
* @param[in] setState - The desired state for Timer2: `ENABLED` to start the timer, 
*                       `DISABLED` to stop the timer.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Enable Timer2
* TMR2_Enable(ENABLED);
*
* // Disable Timer2
* TMR2_Enable(DISABLED);
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Enable(LogicEnum_t setState)
{
  T2CONbits.ON = setState;
}

/******************************************************************************
* Function : TMR2_Set_Prescaler_Rate()
*//** 
* \b Description:
*
* Sets the prescaler rate for Timer2. The prescaler divides the input clock to slow 
* down the counting rate of Timer2, allowing for longer timing intervals. 
* The available prescaler rates are defined in the `TMR2_PreScaler_SelectEnum_t` enumeration.
*
* The prescaler rate is selected by modifying the `T2CONbits.CKPS` bits.
*
* PRE-CONDITION:  
*    - Timer2 must be disabled before changing the prescaler setting.
*
* POST-CONDITION: 
*    - Timer2 will count at the rate determined by the selected prescaler once it is enabled.
*
* @param[in] value - The prescaler rate to be set, chosen from the `TMR2_PreScaler_SelectEnum_t` enum.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Set Timer2 prescaler to 1:8
* TMR2_Set_Prescaler_Rate(TMR2_PRESCALER_1_8);
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Set_Prescaler_Rate(TMR2_PreScaler_SelectEnum_t value)
{  
  T2CONbits.CKPS = value;
}

/******************************************************************************
* Function : <NAME>
*//** 
* \b Description:
*
* This function sets the clock source for Timer2. The clock source determines the input signal 
* used by Timer2 to increment its counter. Depending on the microcontroller, the available clock sources 
* can include the system clock (`FOSC`), an internal oscillator, or an external clock pin. The clock source 
* is selected by writing to the `T2CLKCONbits.CS` bits.
*
* The `TMR2_Clock_Source_SelectEnum_t` enum defines the possible clock sources that can be selected.
*
* PRE-CONDITION:  
*    - Timer2 must be disabled before changing the clock source to avoid incorrect behavior.
*
* POST-CONDITION: 
*    - Timer2 will use the selected clock source for its counting operation once it is enabled.
*
* @param[in] value - The clock source to be set, chosen from the `TMR2_Clock_Source_SelectEnum_t` enum.
*
* @return void
*
* \b Example:
* @code
* 	
* // Set Timer2 clock source to the system clock (FOSC)
* TMR2_Set_Clock_Source(TMR2_CLOCK_SOURCE_FOSC);
* 	
* @endcode
*
* \b Notes:
* - Ensure Timer2 is disabled before changing the clock source.
* - The clock source determines how Timer2 increments, so choose the appropriate source based on the application?s timing requirements.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Set_Clock_Source(TMR2_Clock_Source_SelectEnum_t value)
{
  T2CLKCONbits.CS = value;
}

/******************************************************************************
* Function : TMR2_Set_Output_Postscaler()
*//** 
* \b Description:
*
* This function sets the output postscaler for Timer2. The postscaler determines how many Timer2 
* overflows occur before an interrupt or a change is reflected in the output. The postscaler can 
* be used to extend the range of Timer2 by reducing the frequency of overflow events.
*
* The function modifies the `T2CONbits.OUTPS` bits to configure the postscaler. The available postscaler 
* rates are defined in the `TMR2_PostScaler_SelectEnum_t` enum and can include values like 1:1, 1:2, 1:4, etc.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized but can be running when the postscaler is changed.
*
* POST-CONDITION: 
*    - Timer2 will use the selected output postscaler for its overflow behavior.
*
* @param[in] value - The desired postscaler value, chosen from the `TMR2_PostScaler_SelectEnum_t` enum.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Set Timer2 output postscaler to 1:4
* TMR2_Set_Output_Postscaler(TMR2_POSTSCALER_1_4);
* 	
* @endcode
*
* \b Notes:
* - The postscaler affects how often Timer2 overflows before an interrupt is generated or the output changes.
* - The postscaler does not affect the internal counting of Timer2, only the overflow events.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Set_Output_Postscaler(TMR2_PostScaler_SelectEnum_t value)
{  
  T2CONbits.OUTPS = value;          
}

/******************************************************************************
* Function : TMR2_Set_Mode()
*//** 
* \b Description:
*
* This function sets the operational mode for Timer2. Timer2 can operate in various modes 
* such as free-running, monostable, or other modes, depending on the configuration of the 
* `T2HLTbits.MODE` register. Each mode configures Timer2?s behavior for different timing 
* applications, such as PWM generation, timing delays, or one-shot timers.
*
* The available modes are defined in the `TMR2_Mode_SelectEnum_t` enum, and can include 
* free-running, monostable, retriggerable, and more.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized but can be running when the mode is changed.
*
* POST-CONDITION: 
*    - Timer2 will operate in the selected mode based on the configuration.
*
* @param[in] value - The desired mode for Timer2, selected from the `TMR2_Mode_SelectEnum_t` enum.
*
* @return void	
*
* \b Example:
* @code
* 	
* // Set Timer2 to free-running mode
* TMR2_Set_Mode(TMR2_MODE_FREE_RUNNING);
* 	
* @endcode
*
* \b Notes:
* - Timer2 can be reconfigured for different modes depending on the application's requirements.
* - Ensure that the mode is suitable for the timing or control application being implemented.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Set_Mode(TMR2_Mode_SelectEnum_t value)
{
  T2HLTbits.MODE = value;
}

/******************************************************************************
* Function : TMR2_Get_8bit_Value()
*//** 
* \b Description:
*
* This function retrieves the current 8-bit value from the Timer2 counter. Timer2 is an 8-bit timer, 
* and this function returns the current value stored in the `TMR2` register. This value represents 
* the current state of the timer and can be used to track time-based operations in your application.
*
* PRE-CONDITION:  
*    - Timer2 must be enabled and running to get an accurate value.
*
* POST-CONDITION: 
*    - The current 8-bit value from Timer2 is returned.
*
* @param[in] None
*
* @return uint8_t
*    - The current 8-bit value of the Timer2 counter.
*
* \b Example:
* @code
* 	
* // Get the current 8-bit value from Timer2
* uint8_t timer_value = TMR2_Get_8bit_Value();
* 	
* @endcode
*
* \b Notes:
* - Timer2 must be running for the value to update, otherwise, the returned value may not reflect actual timing events.
* - Timer2 is an 8-bit timer, so this function returns an 8-bit value.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t TMR2_Get_8bit_Value(void)
{
  return TMR2;
}

/******************************************************************************
* Function : TMR2_Clear_Interrupt_Flag()
*//** 
* \b Description:
*
* This function clears the Timer2 interrupt flag (`TMR2IF`) in the `PIR4` register. 
* The interrupt flag is set when Timer2 overflows, signaling that an interrupt event 
* has occurred. Clearing the interrupt flag ensures that Timer2 can generate new interrupts 
* for subsequent overflow events.
*
* This function is typically used inside an interrupt service routine (ISR) after 
* the Timer2 interrupt has been handled to reset the flag for future interrupts.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized and running.
*    - Timer2 must have generated an interrupt, setting the `TMR2IF` flag.
*
* POST-CONDITION: 
*    - The Timer2 interrupt flag (`TMR2IF`) is cleared, allowing Timer2 to generate further interrupts.
*
* @param[in] None
*
* @return void		
*
* \b Example:
* @code
* 	
* // Clear the Timer2 interrupt flag after handling the interrupt
* TMR2_Clear_Interrupt_Flag();
* 	
* @endcode
*
* \b Notes:
* - This function should be called after handling a Timer2 interrupt to reset the flag 
*   and allow new interrupts to occur.
* - If the flag is not cleared, Timer2 will not generate additional interrupts.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Clear_Interrupt_Flag(void)        
{  
  PIR4bits.TMR2IF = 0;
}

/******************************************************************************
* Function : TMR2_Enable_Interrupt()
*//** 
* \b Description:
*
* This function enables or disables the Timer2 interrupt. When enabled, Timer2 can generate 
* an interrupt when it overflows, allowing the program to respond to the event via an 
* interrupt service routine (ISR). Disabling the interrupt will prevent Timer2 from 
* generating interrupts, but the timer will continue counting.
*
* The function modifies the `TMR2IE` bit in the `PIE4` register to control the interrupt.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized.
*    - Global and peripheral interrupts must be enabled separately for the Timer2 interrupt 
*      to be processed correctly.
*
* POST-CONDITION: 
*    - Timer2 interrupt is either enabled or disabled, based on the input parameter.
*
* @param[in] setState - The desired interrupt state: `ENABLED` to enable the Timer2 interrupt, 
*                       or `DISABLED` to disable it.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Enable the Timer2 interrupt
* TMR2_Enable_Interrupt(ENABLED);
*
* // Disable the Timer2 interrupt
* TMR2_Enable_Interrupt(DISABLED);
* 	
* @endcode
*
* \b Notes:
* - Ensure global and peripheral interrupts are configured appropriately for the Timer2 interrupt 
*   to work as expected.
* - Disabling the interrupt will not stop Timer2 from counting, but it will prevent interrupt generation.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR2_Enable_Interrupt(LogicEnum_t setState)
{
    PIE4bits.TMR2IE = setState;
}

/******************************************************************************
* Function : TMR2_Interrupt_Flag_Set()
*//** 
* \b Description:
*
* This function checks whether the Timer2 interrupt flag (`TMR2IF`) is set, indicating 
* that Timer2 has overflowed and an interrupt event has occurred. The function returns 
* `ENABLED` if the interrupt flag is set and `DISABLED` if the flag is clear.
*
* This function is typically used to check the interrupt status in polling mode or 
* before executing any interrupt-related tasks.
*
* PRE-CONDITION:  
*    - Timer2 must be initialized and running.
*    - The Timer2 interrupt flag (`TMR2IF`) should be monitored either in an interrupt service 
*      routine (ISR) or in polling mode.
*
* POST-CONDITION: 
*    - Returns the status of the Timer2 interrupt flag (`TMR2IF`), either set or clear.
*
* @param[in] None
*
* @return LogicEnum_t
*    - `ENABLED` if the Timer2 interrupt flag is set, indicating an interrupt has occurred.
*    - `DISABLED` if the Timer2 interrupt flag is clear.		
*
* \b Example:
* @code
* 	
* // Check if the Timer2 interrupt flag is set
* if (TMR2_Interrupt_Flag_Set() == ENABLED) {
*     // Handle Timer2 interrupt event
* }
* 	
* @endcode
*
* \b Notes:
* - If the flag is set, it means Timer2 has overflowed and an interrupt has been triggered.
* - The interrupt flag must be cleared after handling the interrupt using `TMR2_Clear_Interrupt_Flag()`. 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
LogicEnum_t TMR2_Interrupt_Flag_Set(void)
{
  return PIR4bits.TMR2IF;
}

/*** End of File **************************************************************/