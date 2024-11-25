/****************************************************************************
* Title                 :   Core16F System Init Functions
* Filename              :   core16F_init.c
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
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "core16F.h"

/******************************************************************************
***** CORE System Interface
*******************************************************************************/
const CORE16F_System_Interface_t CORE = {
    .Initialize = &CORE16F_init,
    
    #ifdef _CORE16F_SYSTEM_INCLUDE_DELAYS_ENABLE
        .Delay_MS = &CORE16F_Delay_BlockingMS,
    #endif /*_CORE16F_SYSTEM_INCLUDE_DELAYS_ENABLE*/
    
    #ifdef _CORE16F_SYSTEM_EVENTS_ENABLE
        .Events_Initialize = &TimedEventSystem_Init,
        .Events_Add = &ScheduleEvent,
        .Events_Check = &CheckEvents,
        .Events_Remove = &CancelEvent,
    #endif

    .Make16 = &CORE_Make_16,
    .Low4 = &CORE_Return_4bit_Low,
    .High4 = &CORE_Return_4bit_High,
    .Set_Bit = &CORE_Set_Bit,
    .Clear_Bit = &CORE_Clear_Bit,
    .FloatToString =&CORE_floatToString,
    .IntToString = &CORE_intToString,
};

/******************************************************************************
****** Functions
*******************************************************************************/
/******************************************************************************
* Function : CORE16F_init()
* Description: Initializes the Core16F system for PIC16F MCUs, setting up timers and 
* events if they are enabled in the configuration.
* 
*******************************************************************************/
void CORE16F_init(void)
{
    #ifdef _CORE16F_SYSTEM_TIMER_ENABLE
        ISR_CORE16F_SYSTEM_TIMER_Init();    // Initializes Timer ISR for system timing
    
    #ifdef _CORE16F_SYSTEM_EVENTS_ENABLE
        CORE.Events_Initialize();        // Initializes Core 16F Event System
    #endif //_CORE16F_SYSTEM_EVENTS_ENABLE
    #endif //_CORE16F_SYSTEM_TIMER_ENABLE
}

/*** End of File **************************************************************/
