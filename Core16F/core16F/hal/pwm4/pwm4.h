/****************************************************************************
* Title                 :   PWM4 Functions
* Filename              :   pwm3.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/24
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
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

#ifndef _CORE16F_PWM4_H
#define _CORE16F_PWM4_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core16F.h"

/******************************************************************************
***** PWM Interface
*******************************************************************************/
typedef struct {
  void (*Initialize)(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config);   
  void (*Output)(LogicEnum_t setState);
  void (*DutyCycle)(uint16_t dutyValue);
}PWM4_Interface_t;

extern const PWM4_Interface_t PWM4;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void PWM4_Init(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config);
void PWM4_Output_Enable(LogicEnum_t setState);
void PWM4_Set_DutyCycle(uint16_t dutyValue);

#endif /*_CORE16F_PWM4_H*/

/*** End of File **************************************************************/
