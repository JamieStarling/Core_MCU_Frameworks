/****************************************************************************
* Title                 :    Timer1 Functions
* Filename              :   tmr1.h
* Author                :   Jamie Starling
* Origin Date           :   2024/09/08
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

/*************** TODO *********************************************************
 * * 
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

#ifndef _CORE18F_TMR1_H
#define _CORE18F_TMR1_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TMR1_Enable(LogicEnum_t setState);
void TMR1_16bit_ReadWrite_Mode(LogicEnum_t setState);
void TMR1_Set_Prescaler_Rate(TMR1_PreScaler_SelectEnum_t value);
void TMR1_Set_Clock_Source(TMR1_Clock_Source_SelectEnum_t value);
uint8_t TMR1_Get_8bit_Value(void);
uint16_t TMR1_Get_16bit_Value(void);
void TMR1_Clear_Interrupt_Flag(void);
void TMR1_Enable_Interrupt(LogicEnum_t setState);
LogicEnum_t TMR1_Interrupt_Flag_Set(void);


#endif /*_CORE18F_TMR1_H*/

/*** End of File **************************************************************/
