/****************************************************************************
* Title                 :   CORE8 Framework : TMR0 for 16F devices
* Filename              :   tmr0.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/30
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   Microchip PIC18F series
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
*   2024/04/30  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/
#ifndef _CORE18F_TMR0_H
#define _CORE18F_TMR0_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"
/******************************************************************************
***** TMR0 Interface
*******************************************************************************/
typedef struct {
  void (*Enable)(LogicEnum_t setState);
  void (*Set_16bitMode)(LogicEnum_t setState);
  void (*Set_OutputPostscaler)(TMR0_PostScaler_SelectEnum_t value);
  void (*Set_ClockSource)(TMR0_Clock_Source_SelectEnum_t value);
  void (*Set_InputAsyncMode)(LogicEnum_t setState);
  void (*Set_PrescalerRate)(TMR0_PreScaler_SelectEnum_t value);
  uint8_t (*Read_8bitValue)(void);
  uint16_t (*Read_16bitValue)(void);
  void (*Clear_InterruptFlag)(void);
  void (*Set_InterruptEnable)(LogicEnum_t setState);
  LogicEnum_t (*IsInterruptFlagSet)(void);
}TMR0_Interface_t;

extern const TMR0_Interface_t TIMER0;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TMR0_Enable(LogicEnum_t setState);
void TMR0_Set_16bit_Mode(LogicEnum_t setState);
void TMR0_Set_Output_Postscaler(TMR0_PostScaler_SelectEnum_t value);
void TMR0_Set_Clock_Source(TMR0_Clock_Source_SelectEnum_t value);
void TMR0_Set_Input_Async_Mode(LogicEnum_t setState);
void TMR0_Set_Prescaler_Rate(TMR0_PreScaler_SelectEnum_t value);
uint8_t TMR0_Get_8bit_Value(void);
uint16_t TMR0_Get_16bit_Value(void);
void TMR0_Clear_Interrupt_Flag(void);
void TMR0_Enable_Interrupt(LogicEnum_t setState);
LogicEnum_t TMR0_Interrupt_Flag_Set(void);

#endif /*_CORE18F_TMR0_H*/

/*** End of File **************************************************************/
