/****************************************************************************
* Title                 :   Core18F System Timer Functions
* Filename              :   isr_core18F_system_timer.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
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

/*************** TODO *********************************************************
 * * 
 * 
 * 
*****************************************************************************/


/***************  CHANGE LIST *************************************************
*
*    Date    Version   Author         Description 
*  
*  
*
*****************************************************************************/

#ifndef _CORE18_SYSTEM_TIMER_H
#define _CORE18_SYSTEM_TIMER_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void ISR_CORE18F_SYSTEM_TIMER_Init(void);
void ISR_CORE18F_SYSTEM_TIMER_ISR(void);
uint32_t ISR_CORE18F_SYSTEM_TIMER_GetMillis(void);

#endif /*_CORE18_SYSTEM_TIMER_H*/

/*** End of File **************************************************************/