/****************************************************************************
* Title                 :   CORE MCU Framework : PWM2 for 18F devices
* Filename              :   pwm2.h
* Author                :   Jamie Starling
* Origin Date           :   2024/11/21
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   PIC18F Family  
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
*    Date    Version   Author         Description 
*  
*****************************************************************************/

#ifndef _CORE_PWM2_H_
#define _CORE_PWM2_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
* Constants
*******************************************************************************/

/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
***** PWM Interface
*******************************************************************************/
typedef struct {
  void (*Initialize)(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config);   
  void (*Output)(LogicEnum_t setState);
  void (*DutyCycle)(uint16_t dutyValue);
}PWM2_Interface_t;

extern const PWM2_Interface_t PWM2;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void PWM2_Init(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config);
void PWM2_Output_Enable(LogicEnum_t setState);
void PWM2_Set_DutyCycle(uint16_t dutyValue);


#endif /*_CORE_PWM1_H_*/

/*** End of File **************************************************************/
