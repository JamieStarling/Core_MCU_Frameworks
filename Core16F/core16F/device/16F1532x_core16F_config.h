/****************************************************************************
* Title                 :   Config Settings for PIC16F15323/4/5
* Filename              :   16F1532x_core16F_config.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.2
* Compiler              :   XC8
* Target                :   Microchip PIC16F15323/4/5
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


/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/
#ifndef _CORE16F_16F1532X_CONFIG_H
#define _CORE16F_16F1532X_CONFIG_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../core16F.h"

/******************************************************************************
* Configuration for ISR
*******************************************************************************/
#define _CORE16F_ENABLE_PERIPHERAL_INTERRUPT 

/******************************************************************************
************* Configuration - Enable Disables MCU HAL and Features
*******************************************************************************/

/*GPIO and Analog*/
//#define _CORE16F_HAL_GPIO_CONFIG_ENABLE  //Enabled GPIO to Be Set Through Lookup Table
//#define _CORE16F_HAL_GPIO_ANALOG_ENABLE  //Enable Analog Features

/*Timer Functions*/
//#define _CORE16F_HAL_TMR0_ENABLE  //System Timer Uses TMR0 - Don't need to enable if using the system timer
//#define _CORE16F_HAL_TMR1_ENABLE  //Enables TMR1
//#define _CORE16F_HAL_TMR2_ENABLE  //If using PWM TMR2 is automatically enabled.

/*SERIAL1 Functions*/
#define _CORE16F_HAL_SERIAL1_ENABLE
//#define _CORE16F_HAL_SERIAL1_ISR_ENABLE   //Enables Serial1 with interrupt support.

/*PWM*/
//#define _CORE16F_HAL_PWM_ENABLE   //Enable PWM Features
//#define _CORE16F_HAL_PWM3_ENABLE  //Enable PWM3 
//#define _CORE16F_HAL_PWM4_ENABLE  //Enable PWM4
//#define _CORE16F_HAL_PWM5_ENABLE  //Enable PWM5
//#define _CORE16F_HAL_PWM6_ENABLE  //Enable PWM6

/*I2C*/
#define _CORE16F_HAL_I2C_ENABLE

/*One Wire*/
#define _CORE16F_HAL_ONE_WIRE_ENABLE

/*NCO1*/
#define _CORE16F_HAL_NCO1_ENABLE



/******************************************************************************
* DEVICE CONFIGUATION TABLES
*******************************************************************************/

/******************************************************************************
***** Configuration for GPIO - Used only if Enabled
*******************************************************************************/
#ifdef _CORE16F_HAL_GPIO_CONFIG_ENABLE
/*GPIO Configuration Structure */
typedef struct
{
    GPIO_Ports_t PortPin; /** < The I/ O pin*/
    PinDirectionEnum_t Mode; /** < OUTPUT or INPUT*/
    LogicEnum_t PinLevel; /** < HIGH or LOW*/
}GPIO_Config_t;

/*GPIO Configuration Table */
/* PortPin, Mode, Initial PinLevel */

const GPIO_Config_t GPIO_Config[]=
{        
    {PORTA_0,OUTPUT,LOW},
    {PORTA_1,OUTPUT,LOW},
    {PORTA_2,OUTPUT,LOW},
    {PORTA_3,INPUT,NA},    //PortA3 can only be input
    {PORTA_4,OUTPUT,LOW},
    {PORTA_5,OUTPUT,LOW},
};
#endif //_CORE16F_HAL_GPIO_CONFIG_ENABLE



/******************************************************************************
***** Configuration for SERIAL1
*******************************************************************************/

#ifdef _CORE16F_HAL_SERIAL1_ENABLE
#define _CORE16F_SERIAL1_INPUT_PIN PORTC_5      //Defines the Serial Input Pin
#define _CORE16F_SERIAL1_OUTPUT_PIN PORTC_4     //Defines the Serial Ouput Pin

/******************************************************************************
 * Baud Rate Selection  
 ********************************************************************************/
typedef enum
{
    BAUD_9600,
    BAUD_19200,
    BAUD_57600 
}SerialBaudEnum_t;

/******************************************************************************
 * SERIAL1 Configuration Structure
 * This structure defines the settings for the SERIAL1 module, such as baud rate and control options.
 ********************************************************************************/
typedef struct
{
    uint16_t SP1BRG_Value; 
    LogicEnum_t BRG16_Enable; 
    LogicEnum_t SYNC_Enable;
    LogicEnum_t BRGH_Enable;
    LogicEnum_t CREN_Enable;
    LogicEnum_t TXEN_Enable;
    LogicEnum_t SPEN_Enable;
}SERIAL1_Config_t;

/******************************************************************************
 * SERIAL1 Configuration Lookup Table
 ********************************************************************************/
/*Config for 32Mhz*/
#if _XTAL_FREQ == 32000000
const SERIAL1_Config_t SERIAL1_Config[]=
{        
    {832,ENABLED,DISABLED,ENABLED,ENABLED,ENABLED,ENABLED},  //9600Baud @32Mhz
    {416,ENABLED,DISABLED,ENABLED,ENABLED,ENABLED,ENABLED},  //19200 Baud @32Mhz
    {34,DISABLED,DISABLED,ENABLED,ENABLED,ENABLED,ENABLED}  //57600 Baud @32Mhz
};
#endif
#endif //_CORE16F_HAL_SERIAL1_ENABLE


/******************************************************************************
***** Configuration for PWM
*******************************************************************************/

/******************************************************************************
* PWM LU  
******************************************************************************/
typedef enum
{
    PWM_8bit,
    PWM_10bit 
}PWM_ConfigEnum_t;

/******************************************************************************
*PWM Configuration Structure
* This structure defines the settings for PWM, including the period register value and prescale setting.
******************************************************************************/
typedef struct
{
    uint8_t PR2_Value; 
    uint8_t T2_Prescale_Value; 
}PWM_Config_t;

/******************************************************************************
* PWM Configuration Table
* This table defines the settings for PWM, including the period register value and prescale setting.
 ******************************************************************************/
/*Config for 32Mhz*/
#if _XTAL_FREQ == 32000000
const PWM_Config_t PWM_Config[]=
{        
    {65,0b00},  //32Mhz 8bit PWM
    {255,0b00}   //32Mhz 10bit PWM
};
#endif

/******************************************************************************
***** Configuration for I2C
*******************************************************************************/
#define I2C1_CLOCK_PIN PORTC_0
#define I2C1_DATA_PIN PORTC_1

/******************************************************************************
***** Configuration for One Wire
*******************************************************************************/
/*PORTC.0*/
#ifdef _CORE16F_HAL_ONE_WIRE_ENABLE
#define OW_DIRECTION_REGISTER TRISAbits.TRISA5
#define OW_PINDRIVER_REGISTER LATAbits.LATA5
#define OW_PINREAD_REGISTER PORTAbits.RA5
#define OW_PINANALOG_REGISTER ANSELAbits.ANSA5
#endif


#endif /*_CORE16F_16F1532X_CONFIG_H*/

/*** End of File **************************************************************/
