/****************************************************************************
* Title                 :   GPIO Analog Functions
* Filename              :   gpio_analog.h
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
*
*****************************************************************************/


#ifndef _CORE16F_GPIO_ANALOG_H
#define _CORE16F_GPIO_ANALOG_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core16F.h"


/******************************************************************************
***** Analog Interface
*******************************************************************************/
typedef struct {
  void (*Initialize)(AnalogChannelSelectEnum_t Channel);   
  void (*SelectChannel)(AnalogChannelSelectEnum_t Channel);
  void (*PinSet)(GPIO_Ports_t PortPin, AnalogChannelSelectEnum_t Channel);
  uint16_t (*ReadChannel)(void);
}GPIO_Analog_Interface_t;

extern const GPIO_Analog_Interface_t GPIO_Analog;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void GPIO_Analog_Init(AnalogChannelSelectEnum_t Channel);
void GPIO_Analog_SelectChannel(AnalogChannelSelectEnum_t Channel);
void GPIO_Analog_SetPortPin(GPIO_Ports_t PortPin, AnalogChannelSelectEnum_t Channel);
uint16_t GPIO_Analog_ReadChannel();

#endif /*_CORE16F_GPIO_ANALOG_H*/


/*** End of File **************************************************************/
