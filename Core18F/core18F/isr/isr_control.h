/****************************************************************************
* Title                 :   Device ISR Control Functions
* Filename              :   isr_control.h
* Author                :   Jamie Starling  
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   
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

#ifndef _CORE18_ISR_CORE_H
#define _CORE18_ISR_CORE_H

/******************************************************************************
* Includes
*******************************************************************************/
#include "../core18F.h"


/******************************************************************************
* Function Prototypes
*******************************************************************************/

void ISR_Global_Interrupt(LogicEnum_t setstate);
void ISR_Global_Low_Priority_Interrupt(LogicEnum_t setState);
void ISR_Interrupt_Priority_Enable(LogicEnum_t setState);
ISR_Interrupt_StateEnum_t ISR_Interrupt_Status(void);
void ISR_Enable_System_Default(void);

#endif /*_CORE18_ISR_CORE_H*/

/*** End of File **************************************************************/
