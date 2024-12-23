/****************************************************************************
* Title                 :   Core8 Framework - Main ISR Function
* Filename              :   main_isr.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   Microchip PIC16F series 
* Copyright             :   � 2024 Jamie Starling
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
***** Includes
*******************************************************************************/
#include "../core16F.h"

/******************************************************************************
****** Functions
*******************************************************************************/
/******************************************************************************
* Function : core16F_isr_routine()
* Description: Main interrupt service routine (ISR) for the Core MCU framework, handling 
* system interrupts. Processes system timer interrupts and can be expanded 
* to include additional interrupt handlers as needed.
*
*******************************************************************************/
void __interrupt () core16F_isr_routine (void) {
    
#ifdef _CORE16F_SYSTEM_TIMER_ENABLE
    ISR_CORE16F_SYSTEM_TIMER_ISR();  // Handle Core16F system timer interrupt
#endif    
}


/*** End of File **************************************************************/

