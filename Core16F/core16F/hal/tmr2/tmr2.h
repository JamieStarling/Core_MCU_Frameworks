/****************************************************************************
* Title                 :   Timer 2 Functions
* Filename              :   tmr2.h
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
 * * 
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

#ifndef _CORE16F_TMR2_H
#define _CORE16F_TMR2_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core16F.h"

/******************************************************************************
***** TMR2 Interface
*******************************************************************************/
typedef struct {
  void (*Enable)(LogicEnum_t setState);
  void (*Set_OutputPostscaler)(TMR2_PostScaler_SelectEnum_t value);
  void (*Set_ClockSource)(TMR2_Clock_Source_SelectEnum_t value);  
  void (*Set_PrescalerRate)(TMR2_PreScaler_SelectEnum_t value);
  uint8_t (*Read_8bitValue)(void);  
  void (*Clear_InterruptFlag)(void);
  void (*Set_InterruptEnable)(LogicEnum_t setState);
  LogicEnum_t (*IsInterruptFlagSet)(void);
}TMR2_Interface_t;

extern const TMR2_Interface_t TIMER2;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TMR2_Enable(LogicEnum_t setState);
void TMR2_Set_Prescaler_Rate(TMR2_PreScaler_SelectEnum_t value);
void TMR2_Set_Clock_Source(TMR2_Clock_Source_SelectEnum_t value);
void TMR2_Set_Output_Postscaler(TMR2_PostScaler_SelectEnum_t value);
uint8_t TMR2_Get_8bit_Value(void);
void TMR2_Clear_Interrupt_Flag(void);
void TMR2_Enable_Interrupt(LogicEnum_t setState);
LogicEnum_t TMR2_Interrupt_Flag_Set(void);

#endif /*_CORE16F_TMR2_H*/

/*** End of File **************************************************************/
