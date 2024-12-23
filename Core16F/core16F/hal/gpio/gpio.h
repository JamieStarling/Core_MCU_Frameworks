/****************************************************************************
* Title                 :   Core MCU GPIO Functions
* Filename              :   gpio.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.1
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

#ifndef _CORE16F_GPIO_H
#define _CORE16F_GPIO_H
/******************************************************************************
***** Includes
*******************************************************************************/
#include "../../core16F.h"

/******************************************************************************
***** GPIO Interface
*******************************************************************************/
typedef struct {
  void (*ModeSet)(GPIO_Ports_t PortPin, PinDirectionEnum_t PinDirection);   
  void (*PinWrite)(GPIO_Ports_t PortPin, LogicEnum_t PinLevel);
  void (*PinToggle)(GPIO_Ports_t PortPin);
  LogicEnum_t (*PinRead)(GPIO_Ports_t PortPin);
  
    #ifdef _CORE16F_HAL_GPIO_CONFIG_ENABLE
    void (*Configure)(const GPIO_Config_t* Config);
    #endif

}GPIO_Interface_t;

extern const GPIO_Interface_t GPIO;

/******************************************************************************
***** Function Prototypes
*******************************************************************************/
void GPIO_SetDirection(GPIO_Ports_t PortPin, PinDirectionEnum_t PinDirection);
void GPIO_WritePortPin (GPIO_Ports_t PortPin, LogicEnum_t PinLevel);
void GPIO_TogglePortPin(GPIO_Ports_t PortPin);
LogicEnum_t GPIO_ReadPortPin(GPIO_Ports_t PortPin);

#ifdef _CORE16F_HAL_GPIO_CONFIG_ENABLE
void GPIO_Init(const GPIO_Config_t* Config);
#endif

#endif /*_CORE16F_GPIO_H*/

/*** End of File **************************************************************/
