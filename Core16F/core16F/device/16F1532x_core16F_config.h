/****************************************************************************
* Title                 :   Config Settings for PIC16F15323/4/5
* Filename              :   16F1532x_config.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
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

/*************** TODO *********************************************************
 * ()Add Configuration for 57600 Baud for Esuart1  
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
#ifndef _CORE16F_16F1532X_CONFIG_H
#define _CORE16F_16F1532X_CONFIG_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../core16F.h"

/******************************************************************************
* Configuration for GPIO
*******************************************************************************/
#ifdef _CORE16F_HAL_GPIO_CONFIG_ENABLE

/******************************************************************************
 * \brief GPIO Configuration Structure
 * 
 * This structure holds the configuration for each GPIO pin, including its pin number,
 * input/output mode, and initial pin level.
 *******************************************************************************/
typedef struct
{
    GPIO_Ports_t PortPin; /** < The I/ O pin*/
    PinDirectionEnum_t Mode; /** < OUTPUT or INPUT*/
    LogicEnum_t PinLevel; /** < HIGH or LOW*/
}GPIO_Config_t;


/******************************************************************************
 * \brief GPIO Configuration Table
 * 
 * PortPin, Mode, Initial PinLevel
 *******************************************************************************/
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
***** Configuration for EUSART1
*******************************************************************************/

#ifdef _CORE16F_HAL_EUSART1_ENABLE
#define _CORE16F_EUSART1_INPUT_PIN PORTC_5      //Defines the EUSART Input Pin
#define _CORE16F_EUSART1_OUTPUT_PIN PORTC_4     //Defines the EUSART Ouput Pin

/******************************************************************************
 * \brief Baud Rate Selection Enum
 * 
 ********************************************************************************/
typedef enum
{
    BAUD_9600,
    BAUD_57600 
}SerialBaudEnum_t;

/******************************************************************************
 * \brief EUSART1 Configuration Structure
 * 
 * This structure defines the settings for the EUSART1 module, such as baud rate and control options.
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
}EUSART1_Config_t;

/******************************************************************************
 * \brief EUSART1 Configuration Lookup Table
 * 
 ********************************************************************************/
/*Config for 32Mhz*/
#if _XTAL_FREQ == 32000000
const EUSART1_Config_t EUSART1_Config[]=
{        
    {832,ENABLED,DISABLED,ENABLED,ENABLED,ENABLED,ENABLED}  //9600Baud @32Mhz
};
#endif

#endif //_CORE16F_HAL_EUSART1_ENABLE



/******************************************************************************
***** Configuration for PWM
*******************************************************************************/

/******************************************************************************
 * \brief PWM Enum 
 * 
 ******************************************************************************/
typedef enum
{
    PWM_8bit,
    PWM_10bit 
}PWM_ConfigEnum_t;

/******************************************************************************
 * \brief PWM Configuration Structure
 * 
* This structure defines the settings for PWM, including the period register value and prescale setting.
 ******************************************************************************/
typedef struct
{
    uint8_t PR2_Value; 
    uint8_t T2_Prescale_Value; 
}PWM_Config_t;

/******************************************************************************
 * \brief PWM Configuration Table
 * 
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



#endif /*_CORE16F_16F1532X_CONFIG_H*/

/*** End of File **************************************************************/
