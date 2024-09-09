/****************************************************************************
* Title                 :   Core8 Framework - Main ISR Function
* Filename              :   main_isr.c
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
***** Includes
*******************************************************************************/
#include "../core16F.h"

/******************************************************************************
****** Functions
*******************************************************************************/
/******************************************************************************
* Function : core16F_isr_routine()
*//** 
* \b Description:
*
* This function serves as the main interrupt service routine (ISR) for the Core8 
* framework, handling all the system interrupts. It is designed to process different 
* ISR events, such as system timers, by checking the appropriate interrupt flags 
* and servicing them accordingly. Custom ISR code can also be added here based on 
* specific interrupt sources.
* 
* The function currently calls the system timer ISR handler (`ISR_CORE16F_SYSTEM_TIMER_ISR`) 
* when the system timer is enabled. Additional handlers for other interrupts (e.g., 
* peripheral interrupts) can be added as needed.  
*
* **Usage Notes:**
* - Developers can add custom ISR handling code to process other interrupt events.
* - It is important to check and clear the corresponding interrupt flags within the ISR 
*   to avoid retriggering of the same interrupt.
*  
* PRE-CONDITION:  Global interrupts must be enabled.
* PRE-CONDITION:  Interrupt sources, such as timers or peripherals, must be configured and enabled 
*      in the system.
*
* POST-CONDITION: Interrupt flags for handled interrupts must be cleared to avoid retriggering.
*
* @param[in] 	None
*
* @return 	None	
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void __interrupt () core16F_isr_routine (void) {
    
#ifdef _CORE16F_SYSTEM_TIMER_ENABLE
    ISR_CORE16F_SYSTEM_TIMER_ISR();  //Core8 System Timer
#endif    
}


/*** End of File **************************************************************/

