/****************************************************************************
* Title                 :   Core MCU System Timer Functions
* Filename              :   isr_core18F_system_timer.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.1
* Compiler              :   XC8
* Target                :   Microchip PIC18F series  
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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0   Jamie Starling  Initial Version
*   2024/10/28  1.0.1   Jamie Starling  Optimized ISR Function
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "isr_core18F_system_timer.h"

/******************************************************************************
* Constants
*******************************************************************************/
#define _CORE18F_SYSTEM_TIMER_MILLIS_INC 1

/******************************************************************************
* Variables
*******************************************************************************/
//volatile uint32_t CORE18F_SYSTEM_TIMER_Overflow_Count = 0;
volatile uint32_t CORE18F_SYSTEM_TIMER_Millis = 0;


/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : ISR_CORE18F_SYSTEM_TIMER_Init()
* Description: Initializes Timer0 to generate 1ms ticks at 32MHz, setting up the timer 
* mode, clock source, prescaler, and enabling interrupts.
*
*******************************************************************************/
void ISR_CORE18F_SYSTEM_TIMER_Init(void)
{
    //Using TMR0  
    //Disable 16 Bit timer
    TMR0_Set_16bit_Mode(DISABLED);
    TMR0_Set_Output_Postscaler(POST_SCALE_1_1);
    
    //Timing for ~1ms at 64Mhz
    TMR0_Set_Clock_Source(FOSC_D4); //Clocl Source Select FOSC/4
    TMR0_Set_Prescaler_Rate(PRESCALER_1_64); //Prescaler Rate 1:64    
    
    TMR0_Clear_Interrupt_Flag();
    TMR0_Enable_Interrupt(ENABLED);    
    
    ISR_Enable_System_Default();
    
    TMR0_Enable(ENABLED); //Enable TMR0
}

/******************************************************************************
* Function : ISR_CORE18F_SYSTEM_TIMER_ISR()
* Description: Interrupt Service Routine for Timer0 that increments the millisecond counter
* whenever the Timer0 overflow flag is set. 
*
* - HISTORY OF CHANGES - 
* 2024/10/28 1.0.1 Optimized ISR Function
*******************************************************************************/
void ISR_CORE18F_SYSTEM_TIMER_ISR(void)
{   
  PIR3bits.TMR0IF = 0; //Clear Timer0 Interrupt Flag
  CORE18F_SYSTEM_TIMER_Millis += _CORE18F_SYSTEM_TIMER_MILLIS_INC;
 }   


/******************************************************************************
* Function : ISR_CORE18F_SYSTEM_TIMER_GetMillis()
* Description: Returns the number of milliseconds elapsed since the system timer was 
* initialized. Disables global interrupts momentarily to ensure a consistent 
* read of the `CORE16F_SYSTEM_TIMER_Millis` variable.
*
* Returns:
*   - (uint32_t): The elapsed time in milliseconds.
*******************************************************************************/
uint32_t ISR_CORE18F_SYSTEM_TIMER_GetMillis(void)
{
    uint32_t time;
	
    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
	
    ISR_Global_Interrupt(DISABLED);
    time = CORE18F_SYSTEM_TIMER_Millis;
    ISR_Global_Interrupt(ENABLED);
	
    return time;
}


/*** End of File **************************************************************/
