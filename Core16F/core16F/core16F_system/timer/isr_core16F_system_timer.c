/****************************************************************************
* Title                 :   Core8 System Timer Functions
* Filename              :   isr_core16_system_timer.c
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
* Add configurations to handle different clock speeds (e.g., 16 MHz, 8 MHz).
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
#include "isr_core16F_system_timer.h"

/******************************************************************************
***** Constants
*******************************************************************************/
#define _CORE16F_SYSTEM_TIMER_MILLIS_INC 1  //Defines the time that each interrupt repersents.

/******************************************************************************
***** Variables
*******************************************************************************/
volatile uint32_t CORE16F_SYSTEM_TIMER_Overflow_Count = 0;
volatile uint32_t CORE16F_SYSTEM_TIMER_Millis = 0;

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : ISR_CORE16F_SYSTEM_TIMER_Init()
*//** 
* \b Description:
*
* Initializes the system timer to generate 1ms ticks.
* 
* This function configures the system timer (TMR0) to generate interrupts
* every 1ms at 32 MHz clock speed. It sets the clock source, prescaler, 
* enables interrupts, and starts the timer.
*  
* PRE-CONDITION: None 
*
* POST-CONDITION:
     * TMR0 is set to generate a 1ms timer
     * Peripheral and Global Interrupts are enabled
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* ISR_CORE16F_SYSTEM_TIMER_Init();  // Initialize the system timer
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
*******************************************************************************/
void ISR_CORE16F_SYSTEM_TIMER_Init(void)
{
    TMR0_Set_16bit_Mode(DISABLED);  //Disable 16 Bit timer    
    
    //Timing for ~1ms at 32Mhz
    TMR0_Set_Clock_Source(TMR0_FOSC_D4); //Source Select FOSC/4
    TMR0_Set_Prescaler_Rate(TMR0_PRESCALER_1_32); //Prescaler Rate 1:32
    
    TMR0_Enable_Interrupt(ENABLED);
    TMR0_Clear_Interrupt_Flag();       
    
    ISR_Peripheral_Interrupt(ENABLED);
    ISR_Global_Interrupt(ENABLED);
    TMR0_Enable(ENABLED);
}

/******************************************************************************
* Function : ISR_CORE16F_SYSTEM_TIMER_ISR()
*//** 
* \b Description:
*
* Interrupt function that increments the timer values - add to ISR code  
* 
* PRE-CONDITION:  System timer must be initialized using `ISR_CORE16F_SYSTEM_TIMER_Init`.
* PRE-CONDITION:  Global and peripheral interrupts must be enabled.
*
* POST-CONDITION: The interrupt flag is cleared, and the millisecond counter is updated.
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* This code is added to the Main ISR Function. 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void ISR_CORE16F_SYSTEM_TIMER_ISR(void)
{
    if (TMR0_Interrupt_Flag_Set()){
            TMR0_Clear_Interrupt_Flag();
            uint32_t time = CORE16F_SYSTEM_TIMER_Millis;
            time += _CORE16F_SYSTEM_TIMER_MILLIS_INC;
            CORE16F_SYSTEM_TIMER_Millis = time;
            CORE16F_SYSTEM_TIMER_Overflow_Count++;
        }    
} // END ISR_CORE16F_SYSTEM_TIMER_ISR

/******************************************************************************
* Function : ISR_CORE16F_SYSTEM_TIMER_GetMillis()
*//** 
* \b Description:
*
* This function returns the number of milliseconds that have passed since the 
* system timer was initialized. It reads the global `CORE16F_SYSTEM_TIMER_Millis` 
* variable, which is updated in the system timer ISR to track elapsed time in milliseconds.
*
* This function disables global interrupts momentarily to avoid inconsistencies when 
* reading the timer variable, then re-enables them once the value is safely retrieved.
*
* PRE-CONDITION:  The system timer must be initialized using `ISR_CORE16F_SYSTEM_TIMER_Init()`.
* PRE-CONDITION:  The system timer ISR (`ISR_CORE16F_SYSTEM_TIMER_ISR`) must be running.
*
* POST-CONDITION: Returns the total elapsed time in milliseconds since the system timer was started.
*
* @param[in] 	
*
* @return :  uint32_t: The number of milliseconds elapsed since the system timer was initialized.	
*
* \b Example:
* @code
* 	
* uint32_t current_time = ISR_CORE16F_SYSTEM_TIMER_GetMillis();
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
uint32_t ISR_CORE16F_SYSTEM_TIMER_GetMillis(void)
{
    uint32_t time;
	
	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	
    ISR_Global_Interrupt(DISABLED);
    time = CORE16F_SYSTEM_TIMER_Millis;
    ISR_Global_Interrupt(ENABLED);	
    return time;
}


/*** End of File **************************************************************/
