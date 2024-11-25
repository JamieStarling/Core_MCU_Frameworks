/****************************************************************************
* Title                 :   Core MCU System Timer Functions
* Filename              :   isr_core16_system_timer.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
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
*   2024/04/25  1.0.0   Jamie Starling  Initial Version
*   2024/10/28  1.0.1   Jamie Starling  Optimized ISR Function
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
//volatile uint32_t CORE16F_SYSTEM_TIMER_Overflow_Count = 0;
volatile uint32_t CORE16F_SYSTEM_TIMER_Millis = 0;

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : ISR_CORE16F_SYSTEM_TIMER_Init()
* Description: Initializes Timer0 to generate 1ms ticks at 32MHz, setting up the timer 
* mode, clock source, prescaler, and enabling interrupts.
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
* Description: Interrupt Service Routine for Timer0 that increments the millisecond counter
* whenever the Timer0 overflow flag is set. 
*
* - HISTORY OF CHANGES - 
* 2024/10/28 1.0.1 Optimized ISR Function
*******************************************************************************/
void ISR_CORE16F_SYSTEM_TIMER_ISR(void)
{
    if (PIR0bits.TMR0IF){
            PIR0bits.TMR0IF = 0;  //Clear Timer0 Interrupt Flag
            CORE16F_SYSTEM_TIMER_Millis += _CORE16F_SYSTEM_TIMER_MILLIS_INC;
        }    
} 

/******************************************************************************
* Function : ISR_CORE16F_SYSTEM_TIMER_GetMillis()
* Description: Returns the number of milliseconds elapsed since the system timer was 
* initialized. Disables global interrupts momentarily to ensure a consistent 
* read of the `CORE16F_SYSTEM_TIMER_Millis` variable.
*
* Returns:
*   - (uint32_t): The elapsed time in milliseconds.
*******************************************************************************/
uint32_t ISR_CORE16F_SYSTEM_TIMER_GetMillis(void)
{
    uint32_t time;
    
    // Disable interrupts temporarily to read the timer value safely
    ISR_Global_Interrupt(DISABLED);
    time = CORE16F_SYSTEM_TIMER_Millis;
    ISR_Global_Interrupt(ENABLED);	
    
    return time;
}


/*** End of File **************************************************************/
