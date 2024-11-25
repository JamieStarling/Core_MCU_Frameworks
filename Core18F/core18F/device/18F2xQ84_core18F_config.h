/****************************************************************************
* Title                 :   Config Settings
* Filename              :   18F2xQ84_config.h
* Author                :   Jamie Starling
* Origin Date           :   2024/08/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   PIC18F2xQ84
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
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/
#ifndef _CORE18_18F2XQ84_CONFIG_H
#define _CORE18_18F2XQ84_CONFIG_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../core18F.h"

/******************************************************************************
* Configuration for ISR
*******************************************************************************/
#define _CORE18F_ISR_BASE_ADDRESS 0x000008
#define _CORE18F_ENABLE_LOW_PRIORITY_INTERRUPTS TRUE
#define _CORE18F_ENABLE_INTERRUPT_PRIORITY TRUE


/******************************************************************************
*************Configuration - Core8 HAL Enable
*******************************************************************************/

/******************************************************************************
* Enable GPIO Config - GPIO_Init* 
*******************************************************************************/
//#define _CORE18F_HAL_GPIO_CONFIG_ENABLE

/******************************************************************************
* Enable Core MCU - GPIO Analog Functions
*******************************************************************************/
#define _CORE18F_HAL_GPIO_ANALOG_ENABLE


/******************************************************************************
* Enable TMR0 Functions
* System Timer Uses TMR0 - Don't need to enable if using the system timer
*******************************************************************************/
//#define _CORE18F_HAL_TMR0_ENABLE

/******************************************************************************
* Enable TMR1 Functions
*******************************************************************************/
//#define _CORE18F_HAL_TMR1_ENABLE

/******************************************************************************
* Enable TMR2 Functions
* If using PWM TMR2 is automatically enabled. 
*******************************************************************************/
//#define _CORE18F_HAL_TMR2_ENABLE


/******************************************************************************
* Enable Core MCU - SERIAL1 Functions
* Provides support for the Enhanced Universal Synchronous Asynchronous Receiver Transmitter (SERIAL1)
* for serial communication.
*******************************************************************************/
#define _CORE18F_HAL_SERIAL1_ENABLE
//#define _CORE18F_HAL_SERIAL1_ISR_ENABLE


/******************************************************************************
* Enable Core MCU - PWM Functions
*******************************************************************************/
#define _CORE18F_HAL_PWM_ENABLE   //Enable PWM Features

/*PWM1*/
#define _CORE18F_HAL_PWM1_ENABLE
/*PWM2*/
//#define _CORE18F_HAL_PWM2_ENABLE
/*PWM3*/
//#define _CORE18F_HAL_PWM3_ENABLE


/******************************************************************************
* Enable Core8 - I2C Functions
*******************************************************************************/
#define _CORE18F_HAL_I2C_ENABLE

/******************************************************************************
* Enable Core8 - One Wire Functions
*******************************************************************************/
#define _CORE18F_HAL_ONE_WIRE_ENABLE





/******************************************************************************
* Configuration for GPIO
*******************************************************************************/
#ifdef _CORE18F_HAL_GPIO_CONFIG_ENABLE
typedef struct
{
    GPIO_Ports_t PortPin; /** < The I/ O pin*/
    PinDirectionEnum_t Mode; /** < OUTPUT or INPUT*/
    LogicEnum_t PinLevel; /** < HIGH or LOW*/
}GPIO_Config_t;


/*GPIO Configuration Table*/
/*PortPin, Mode, Initial PinLevel*/
const GPIO_Config_t GPIO_Config[]=
{        
    {PORTA_0,OUTPUT,LOW},
    {PORTA_1,OUTPUT,LOW},
    {PORTA_2,OUTPUT,LOW},
    {PORTA_3,INPUT,NA},    //PortA3 can only be input
    {PORTA_4,OUTPUT,LOW},
    {PORTA_5,OUTPUT,LOW},
};

/******************************************************************************
* Configuration for SERIAL1
*******************************************************************************/
#endif //_CORE18F_HAL_GPIO_CONFIG_ENABLE

#ifdef _CORE18F_HAL_SERIAL1_ENABLE

#define _CORE18F_SERIAL1_INPUT_PIN PORTC_7
#define _CORE18F_SERIAL1_OUTPUT_PIN PORTC_6
//#define _CORE18F_SERIAL1_PPSOUT_REGISTER 

typedef enum
{
    BAUD_9600,
    BAUD_19200,
    BAUD_57600 
}SerialBaudEnum_t;

typedef struct
{
  uint8_t ESUART_Mode;  
  uint16_t BRG_Value;         //Desired Baud Rate Value
  LogicEnum_t BRGS_Enable;    //Desired Baud Rate Multiplier
  LogicEnum_t RXEN_Enable;    //Receive Enable Control
  LogicEnum_t TXEN_Enable;    //Transmit Enable Control
  LogicEnum_t SPEN_Enable;    //Serial Port Enable
}SERIAL1_Config_t;


/*UART Config for 64Mhz*/
#if _XTAL_FREQ == 64000000
const SERIAL1_Config_t SERIAL1_Config[]=
{        
    {0b0000,0x682,ENABLED,ENABLED,ENABLED,ENABLED},  //9600Baud @64Mhz
    {0b0000,0x340,ENABLED,ENABLED,ENABLED,ENABLED},  //19200Baud @64Mhz
    {0b0000,0x115,ENABLED,ENABLED,ENABLED,ENABLED}  //57600Baud @64Mhz
};
#endif /*UART Config for 64Mhz*/

#endif //Main SERIAL1 Config

/******************************************************************************
* Configuration for PWM
*******************************************************************************/

typedef enum
{
    PWM_8bit,
    PWM_10bit 
}PWM_ConfigEnum_t;

typedef struct
{
    uint8_t PR2_Value; 
    uint8_t T2_Prescale_Value; 
}PWM_Config_t;

/*PWM Config for 64Mhz*/
#if _XTAL_FREQ == 64000000
const PWM_Config_t PWM_Config[]=
{        
    {65,0b00},  //64Mhz 8bit PWM
    {255,0b00}   //64Mhz 10bit PWM
};
#endif /*PWM Config for 64Mhz*/
/******************************************************************************
***** Configuration for I2C
*******************************************************************************/
#define I2C1_CLOCK_PIN PORTC_3
#define I2C1_DATA_PIN PORTC_4


/******************************************************************************
***** Configuration for One Wire
*******************************************************************************/
/*PORTC.0*/
#ifdef _CORE18F_HAL_ONE_WIRE_ENABLE
#define OW_DIRECTION_REGISTER TRISBbits.TRISB0
#define OW_PINDRIVER_REGISTER LATBbits.LATB0
#define OW_PINREAD_REGISTER PORTBbits.RB0
#define OW_PINANALOG_REGISTER ANSELBbits.ANSELB0
#endif



#endif /*_CORE18_18F2XQ84_CONFIG_H*/

/*** End of File **************************************************************/
