/****************************************************************************
* Title                 :   Core18F Framework Includes - For Microchip 18F processors
* Filename              :   core18F.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   Microchip PIC18F series
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
 *
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

#ifndef _CORE18F_H
#define _CORE18F_H

/******************************************************************************
********* Standard Includes
*******************************************************************************/
#include <xc.h>
#include <stdint.h>     //For standard type definitions
#include <stdbool.h>    //For Bool
#include <stdlib.h> 
#include <stdio.h>

/******************************************************************************
************ Sets Core8 Framework Processor
*******************************************************************************/
/******************************************************************************
* Sets the Core18 system device
* Available Devices:
* _CORE18_SYSTEM_DEVICE_18F2xQ84 : PIC18F26Q84, PIC18F27Q84
*******************************************************************************/
#ifdef _PIC18F26Q84_H_
#define _CORE18_SYSTEM_DEVICE_18F2xQ84
#endif

#ifdef _PIC18F27Q84_H_
#define _CORE18_SYSTEM_DEVICE_18F2xQ84
#endif

/****XTAL_FREQ****/
/*Used to calculate the delay time - Change depending on processor Speed*/
#define _XTAL_FREQ 64000000UL



/******************************************************************************
************* Configuration - Enable Disables Optional HALS and Features
*******************************************************************************/

/******************************************************************************
***** Core8 System Timer Enable
*******************************************************************************/
#define _CORE18F_SYSTEM_TIMER_ENABLE

/******************************************************************************
***** Enable Core8 System Delays based on System Timer
*******************************************************************************/
#define _CORE18F_SYSTEM_INCLUDE_DELAYS_ENABLE


/******************************************************************************
********* Start of Core8 Framework System Includes - Required
*******************************************************************************/
#include "core18F_const.h"               //Core8 System Constants
#include "device/core18F_device.h"       //Core8 Device Specifics
#include "core18F_system/utils/utils.h"  //Core8 Utililities


/******************************************************************************
********* Start of Core8 System HAL Includes - Default
*******************************************************************************/
#include "hal/gpio/gpio.h"          //Include GPIO Functions
#include "hal/pps/pps.h"            //Include PPS Functions

/******************************************************************************
********* Additional Includes - Based on Configuration 
*******************************************************************************/

//Include System Timer if Enabled
#ifdef _CORE18F_SYSTEM_TIMER_ENABLE
#include "core18F_system/timer/isr_core18F_system_timer.h"
#include "isr/isr_control.h"
#include "hal/tmr0/tmr0.h"
#endif

//Include system delay functions if Enabled
#ifdef _CORE18F_SYSTEM_INCLUDE_DELAYS_ENABLE
#include "core18F_system/delays/delays.h"
#endif

//Include GPIO Analog Functions - If Enabled
#ifdef _CORE18F_HAL_GPIO_ANALOG_ENABLE
#include "hal/gpio/gpio_analog.h"
#endif

/****TIMER 0******/
#ifdef _CORE18F_HAL_TMR0_ENABLE
#include "hal/tmr0/tmr0.h"
#endif

#ifdef _CORE18F_HAL_TMR1_ENABLE
#include "hal/tmr1/tmr1.h"
#endif

#ifdef _CORE18F_HAL_TMR2_ENABLE
#include "hal/tmr2/tmr2.h"
#endif

/******SERIAL1*********/
#ifdef _CORE18F_HAL_SERIAL1_ENABLE
#include "hal/serial1/serial1.h"
#endif

/******SERIAL1 TX ISR*********/
#ifdef _CORE18F_HAL_SERIAL1_ISR_ENABLE
#include "hal/serial1/serial1_isr.h"
#endif



/******PWM*********/
#ifdef _CORE18F_HAL_PWM3_ENABLE
#include "hal/tmr2/tmr2.h"
#include "hal/pwm3/pwm3.h"
#endif

#ifdef _CORE18F_HAL_PWM4_ENABLE
#include "hal/tmr2/tmr2.h"
#include "hal/pwm4/pwm4.h"
#endif

#ifdef _CORE18F_HAL_PWM4_ENABLE
#include "hal/tmr2/tmr2.h"
#include "hal/pwm5/pwm5.h"
#endif

#ifdef _CORE18F_HAL_PWM5_ENABLE
#include "hal/tmr2/tmr2.h"
#include "hal/pwm6/pwm6.h"
#endif

/******I2C*********/
#ifdef _CORE18F_HAL_I2C_ENABLE
#include "hal/i2c1/i2c1.h"
#endif

/******One Wire*********/
#ifdef _CORE18F_HAL_ONE_WIRE_ENABLE
#include "hal/one_wire/one_wire.h"
#endif








/******************************************************************************
***** CORE System Interface
*******************************************************************************/
typedef struct {
  void (*Initialize)(void);  
#ifdef _CORE18F_SYSTEM_INCLUDE_DELAYS_ENABLE
  void (*Delay_MS)(uint32_t timeMS);   
#endif
}CORE18F_System_Interface_t;

extern const CORE18F_System_Interface_t CORE;





/******************************************************************************
********* Function Prototypes
*******************************************************************************/
void CORE18F_init(void);

#endif /*_CORE18F_H*/

/*** End of File **************************************************************/
