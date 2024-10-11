/****************************************************************************
* Title                 :   Register Lookup Table for PIC18F2xQ84
* Filename              :   18F2xQ84_LU.h
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

/*************** TODO *********************************************************
 * * 
 * 
 * 
*****************************************************************************/


/***************  CHANGE LIST *************************************************
*
*    Date    Version   Author         Description 
*  
*  
*
*****************************************************************************/

#ifndef _CORE18_18F2XQ84_LU_H
#define _CORE18_18F2XQ84_LU_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../core18F.h"


/******************************************************************************
* Constants: Interrupt State Status
*******************************************************************************/
typedef enum
{
  MAIN_RUNNING = 0b00,
  LOW_ISR_RUNNING = 0b01,
  HIGH_ISR_RUNNING = 0b10,
  BOTH_ISR_RUNNING = 0b11  
}ISR_Interrupt_StateEnum_t;


/******************************************************************************
* Constants: Timer0
*******************************************************************************/
typedef enum
{
  POST_SCALE_1_1 = 0b0000,
  POST_SCALE_1_2 = 0b0001,
  POST_SCALE_1_3 = 0b0010,
  POST_SCALE_1_4 = 0b0011,
  POST_SCALE_1_5 = 0b0100,
  POST_SCALE_1_6 = 0b0101,
  POST_SCALE_1_7 = 0b0110,
  POST_SCALE_1_8 = 0b0111,
  POST_SCALE_1_9 = 0b1000,
  POST_SCALE_1_10 = 0b1001,
  POST_SCALE_1_11 = 0b1010,
  POST_SCALE_1_12 = 0b1011,
  POST_SCALE_1_13 = 0b1100,
  POST_SCALE_1_14 = 0b1101,
  POST_SCALE_1_15 = 0b1110,
  POST_SCALE_1_16 = 0b1111  
}TMR0_PostScaler_SelectEnum_t;


typedef enum
{
  CLC1_OUT = 0b111,
  SOSC = 0b110,
  MFINTOSC = 0b101,
  LFINTOSC = 0b100,
  HFINTOSC = 0b011,
  FOSC_D4 = 0b010,
  T0CKIPPS_INV = 0b001,
  T0CKIPPS_NINV = 0b000
}TMR0_Clock_Source_SelectEnum_t;


typedef enum
{
  PRESCALER_1_32768 = 0b1111,
  PRESCALER_1_16384 = 0b1110,
  PRESCALER_1_8192 = 0b1101,
  PRESCALER_1_4096 = 0b1100,
  PRESCALER_1_2048 = 0b1011,
  PRESCALER_1_1024 = 0b1010,
  PRESCALER_1_512 = 0b1001,
  PRESCALER_1_256 = 0b1000,
  PRESCALER_1_128 = 0b0111,
  PRESCALER_1_64 = 0b0110,
  PRESCALER_1_32 = 0b0101,
  PRESCALER_1_16 = 0b0100,
  PRESCALER_1_8 = 0b0011,
  PRESCALER_1_4 = 0b0010,
  PRESCALER_1_2 = 0b0001,
  PRESCALER_1_1 = 0b0000
}TMR0_PreScaler_SelectEnum_t;


/******************************************************************************
* Constants: I/O Pin Direction
*******************************************************************************/

/*Defines the Max IO Pin Count on the Device
* Used for reading the GPIO Configuration Table*/
#define _CORE18_MAX_GPIO_PORTPIN_COUNT 25

typedef enum
{
    OUTPUT = 0x0U,	
    INPUT = 0x1U,
    INPUT_W_PULLUP = 0x2U,
    ANALOG = 0x3U,
    OPEN_DRAIN = 0x4U
}PinDirectionEnum_t;

/******************************************************************************
* Digital Lookup Tables
*******************************************************************************/

//Port Pin Table Lookup
typedef enum
{    
    PORTA_0,
    PORTA_1,
    PORTA_2,
    PORTA_3,
    PORTA_4,
    PORTA_5,
    PORTA_6,
    PORTA_7,
    PORTB_0,
    PORTB_1,
    PORTB_2,
    PORTB_3,
    PORTB_4,
    PORTB_5,
    PORTB_6,
    PORTB_7,
    PORTC_0,
    PORTC_1,
    PORTC_2,
    PORTC_3,
    PORTC_4,
    PORTC_5,
    PORTC_6,
    PORTC_7,
    PORTE_3,
    MAX_IOPINS
}GPIO_Ports_t;


/*GPIO Pin Mask Lookup**/
const unsigned char GPIO_PinBitMask_LU[] = 
{
    0b00000001U,    //RA.0
    0b00000010U,    //RA.1
    0b00000100U,    //RA.2
    0b00001000U,    //RA.3
    0b00010000U,    //RA.4
    0b00100000U,    //RA.5
    0b01000000U,    //RA.6
    0b10000000U,    //RA.7
    0b00000001U,    //RB.0
    0b00000010U,    //RB.1
    0b00000100U,    //RB.2
    0b00001000U,    //RB.3
    0b00010000U,    //RB.4
    0b00100000U,    //RB.5
    0b01000000U,    //RB.6
    0b10000000U,    //RB.7
    0b00000001U,    //RC.0
    0b00000010U,    //RC.1
    0b00000100U,    //RC.2
    0b00001000U,    //RC.3
    0b00010000U,    //RC.4
    0b00100000U,    //RC.5
    0b01000000U,    //RC.6
    0b10000000U,    //RC.7
    0b00001000U,    //RE.3    
};

/*GPIO Direction Register Lookup**/
volatile unsigned char *const GPIO_DirectionRegister_LU[] =
{
    &TRISA, //RA.0
    &TRISA, //RA.1
    &TRISA, //RA.2
    &TRISA, //RA.3
    &TRISA, //RA.3
    &TRISA, //RA.5
    &TRISA, //RA.6
    &TRISA, //RA.7
    &TRISB, //RB.0
    &TRISB, //RB.1
    &TRISB, //RB.2
    &TRISB, //RB.3
    &TRISB, //RB.4
    &TRISB, //RB.5
    &TRISB, //RB.6
    &TRISB, //RB.7    
    &TRISC, //RC.0
    &TRISC, //RC.1
    &TRISC, //RC.2
    &TRISC, //RC.3
    &TRISC, //RC.3
    &TRISC, //RC.5
    &TRISC, //RC.6
    &TRISC, //RC.7
    &TRISE, //RE.3
};

/*GPIO Digital Write Register Lookup**/
volatile unsigned char *const GPIO_WriteRegister_LU[] =
{
    &LATA,  //RA.0
    &LATA,  //RA.1
    &LATA,  //RA.2
    &LATA,  //RA.3
    &LATA,  //RA.4
    &LATA,  //RA.5
    &LATA,  //RA.6
    &LATA,  //RA.7
    &LATB,  //RB.0
    &LATB,  //RB.1
    &LATB,  //RB.2
    &LATB,  //RB.3
    &LATB,  //RB.4
    &LATB,  //RB.5
    &LATB,  //RB.6
    &LATB,  //RB.7    
    &LATC,  //RC.0
    &LATC,  //RC.1
    &LATC,  //RC.2
    &LATC,  //RC.3
    &LATC,  //RC.4
    &LATC,  //RC.5
    &LATC,  //RC.6
    &LATC,  //RC.7
    //&LATE,  //RE.3
};

/*GPIO Read Register Lookup**/
volatile unsigned char *const GPIO_ReadRegister_LU[] =
{
    &PORTA, //RA.0
    &PORTA, //RA.1
    &PORTA, //RA.2
    &PORTA, //RA.3
    &PORTA, //RA.4
    &PORTA, //RA.5
    &PORTA, //RA.6
    &PORTA, //RA.7
    &PORTB, //RB.0
    &PORTB, //RB.1
    &PORTB, //RB.2
    &PORTB, //RB.3
    &PORTB, //RB.4
    &PORTB, //RB.5
    &PORTB, //RB.6
    &PORTB, //RB.7    
    &PORTC, //RC.0
    &PORTC, //RC.1
    &PORTC, //RC.2
    &PORTC, //RC.3
    &PORTC, //RC.4
    &PORTC, //RC.5
    &PORTC, //RC.6
    &PORTC, //RC.7
    &PORTE, //RE.3
    
};

/*GPIO Weak Pull-up Register Lookup**/
volatile unsigned char *const GPIO_WPURegister_LU[] =
{
    &WPUA,  //RA.0
    &WPUA,  //RA.1
    &WPUA,  //RA.2
    &WPUA,  //RA.3
    &WPUA,  //RA.4
    &WPUA,  //RA.5
    &WPUA,  //RA.6
    &WPUA,  //RA.7
    &WPUB,  //RB.0
    &WPUB,  //RB.1
    &WPUB,  //RB.2
    &WPUB,  //RB.3
    &WPUB,  //RB.4
    &WPUB,  //RB.5
    &WPUB,  //RB.6
    &WPUB,  //RB.7    
    &WPUC,  //RC.0
    &WPUC,  //RC.1
    &WPUC,  //RC.2
    &WPUC,  //RC.3
    &WPUC,  //RC.4
    &WPUC,  //RC.5
    &WPUC,  //RC.6
    &WPUC,  //RC.7
    //&WPUE,  //RE.3
};

/*GPIO Open Drain Control Register Lookup**/
volatile unsigned char *const GPIO_ODCONRegister_LU[] =
{
    &ODCONA,  //RA.0
    &ODCONA,  //RA.1
    &ODCONA,  //RA.2
    &ODCONA,  //RA.3
    &ODCONA,  //RA.4
    &ODCONA,  //RA.5
    &ODCONA,  //RA.6
    &ODCONA,  //RA.7
    &ODCONB,  //RB.0
    &ODCONB,  //RB.1
    &ODCONB,  //RB.2
    &ODCONB,  //RB.3
    &ODCONB,  //RB.4
    &ODCONB,  //RB.5
    &ODCONB,  //RB.6
    &ODCONB,  //RB.7    
    &ODCONC,  //RC.0
    &ODCONC,  //RC.1
    &ODCONC,  //RC.2
    &ODCONC,  //RC.3
    &ODCONC,  //RC.4
    &ODCONC,  //RC.5
    &ODCONC,  //RC.6
    &ODCONC,  //RC.7    
};


/******************************************************************************
* Analog Lookup Tables
*******************************************************************************/

/*GPIO Analog Register Lookup**/
volatile unsigned char *const GPIO_AnalogRegister_LU[] =
{
    &ANSELA,    //RA.0
    &ANSELA,    //RA.1
    &ANSELA,    //RA.2
    &ANSELA,    //RA.3
    &ANSELA,    //RA.4
    &ANSELA,    //RA.5
    &ANSELA,    //RA.6
    &ANSELA,    //RA.7
    &ANSELB,    //RB.0
    &ANSELB,    //RB.1
    &ANSELB,    //RB.2
    &ANSELB,    //RB.3
    &ANSELB,    //RB.4
    &ANSELB,    //RB.5
    &ANSELB,    //RB.6
    &ANSELB,    //RB.7    
    &ANSELC,    //RC.0
    &ANSELC,    //RC.1
    &ANSELC,    //RC.2
    &ANSELC,    //RC.3
    &ANSELC,    //RC.4
    &ANSELC,    //RC.5    
    &ANSELC,    //RC.6
    &ANSELC,    //RC.7
    //&ANSELE,    //RE.1
    
};


#ifdef _CORE18F_HAL_GPIO_ANALOG_ENABLE
/**Constants: Analog Channel Select */
typedef enum
{
    ANA0 = 0b000000,			    
    ANA1 = 0b000001, 
    ANA2 = 0b000010,
    ANA3 = 0b000011,
    ANA4 = 0b000100,
    ANA5 = 0b000101,
    ANA6 = 0b000110,
    ANA7 = 0b000111,
    ANB0 = 0b001000,
    ANB1 = 0b001001,
    ANB2 = 0b001010,
    ANB3 = 0b001011,
    ANB4 = 0b001100,
    ANB5 = 0b001101,
    ANB6 = 0b001110,
    ANB7 = 0b001111,
    ANC0 = 0b010000,
    ANC1 = 0b010001,
    ANC2 = 0b010010,
    ANC3 = 0b010011,
    ANC4 = 0b010100,
    ANC5 = 0b010101,
    ANC6 = 0b010110,
    ANC7 = 0b010111,
    AVSS = 0b111011,
    TEMPERATURE_SENSOR = 0b111100,
    DAC1_OUTPUT = 0b111101,
    FVR_BUFFER1 = 0b111110,
    FVR_BUFFER2 = 0b111111,
}AnalogChannelSelectEnum_t;
#endif //Anlog LU


/******************************************************************************
* PPS Output Signal Routing Options Lookup Tables
*******************************************************************************/

typedef enum
{
    PSSOUT_LATxy            = 0x00U,
    PPSOUT_CLC1OUT          = 0x01U,      
    PPSOUT_CLC2OUT          = 0x02U,
    PPSOUT_CLC3OUT          = 0x03U,
    PPSOUT_CLC4OUT          = 0x04U,
    PPSOUT_CLC5OUT          = 0x05U,
    PPSOUT_CLC6OUT          = 0x06U,
    PPSOUT_CLC7OUT          = 0x07U,
    PPSOUT_CLC8OUT          = 0x08U,
    PPSOUT_CWG1A            = 0x09U,
    PPSOUT_CWG1B            = 0x0AU,
    PPSOUT_CWG1C            = 0x0BU,
    PPSOUT_CWG1D            = 0x0CU,
    PPSOUT_CWG2A            = 0x0DU,
    PPSOUT_CWG2B            = 0x0EU,
    PPSOUT_CWG2C            = 0x0FU,
    PPSOUT_CWG2D            = 0x10U,
    PPSOUT_CWG3A            = 0x11U,
    PPSOUT_CWG3B            = 0x12U,
    PPSOUT_CWG3C            = 0x13U,
    PPSOUT_CWG3D            = 0x14U,
    PPSOUT_CCP1             = 0x15U,
    PPSOUT_CCP2             = 0x16U,
    PPSOUT_CCP3             = 0x17U,
    PPSOUT_PWM1S1P1_OUT     = 0x18U,
    PPSOUT_PWM1S1P2_OUT     = 0x19U,
    PPSOUT_PWM2S1P1_OUT     = 0x1AU,
    PPSOUT_PWM2S1P2_OUT     = 0x1BU,
    PPSOUT_PWM3S1P1_OUT     = 0x1CU,
    PPSOUT_PWM3S1P2_OUT     = 0x1DU,
    PPSOUT_PWM4S1P1_OUT     = 0x1EU,
    PPSOUT_PWM4S1P2_OUT     = 0x1FU,
    PPSOUT_UART1_TX         = 0x20U,
    PPSOUT_UART1_TXDE       = 0x21U,
    PPSOUT_UART1_RTS        = 0x22U,
    PPSOUT_UART2_TX         = 0x23U,
    PPSOUT_UART2_TXDE       = 0x24U,
    PPSOUT_UART2_RTS        = 0x25U,  
    PPSOUT_UART3_TX         = 0x26U,
    PPSOUT_UART3_TXDE       = 0x27U,
    PPSOUT_UART3_RTS        = 0x28U,
    PPSOUT_UART4_TX         = 0x29U,
    PPSOUT_UART4_TXDE       = 0x2AU, 
    PPSOUT_UART4_RTS        = 0x2BU,
    PPSOUT_UART5_TX         = 0x2CU,
    PPSOUT_UART5_TXDE       = 0x2DU,
    PPSOUT_UART5_RTS        = 0x2EU,
    PPSOUT_C1OUT            = 0x2FU,
    PPSOUT_C2OUT            = 0x30U,
    PPSOUT_SPI1_SCK         = 0x31U,
    PPSOUT_SPI1_SDO         = 0x32U,
    PPSOUT_SPI1_SS          = 0x33U,
    PPSOUT_SPI2_SCK         = 0x34U,
    PPSOUT_SPI2_SDO         = 0x35U,
    PPSOUT_SPI2_SS          = 0x36U,
    PPSOUT_I2C1_SCL         = 0x37U,
    PPSOUT_I2C1_SDA         = 0x38U,
    PPSOUT_TMR0             = 0x39U,
    PPSOUT_TU16A            = 0x3AU,
    PPSOUT_TU16B            = 0x3BU,
    PPSOUT_NCO1             = 0x3FU,
    PPSOUT_NCO2             = 0x40U,
    PPSOUT_NCO3             = 0x41U,
    PPSOUT_CLKR             = 0x42U,
    PPSOUT_DSM1             = 0x43U,
    PPSOUT_ADGRDA           = 0x44U,
    PPSOUT_ADGRDB           = 0x45U,
    PPSOUT_CANTX            = 0x46U
}PPSOutputPeripheralEnum_t;

/******************************************************************************
 * \brief PPS Output Register Lookup
 * 
 * This table defines the PPS output register.
 *******************************************************************************/
_PointerRegisterSize volatile * const PPS_OutputRegister_LU[] =
{
    (_PointerRegisterSize*) &RA0PPS,    //RA.0
    (_PointerRegisterSize*) &RA1PPS,    //RA.1    
    (_PointerRegisterSize*) &RA2PPS,    //RA.2
    (_PointerRegisterSize*) &RA3PPS,    //RA.3
    (_PointerRegisterSize*) &RA4PPS,    //RA.4
    (_PointerRegisterSize*) &RA5PPS,    //RA.5
    (_PointerRegisterSize*) &RA6PPS,    //RA.6
    (_PointerRegisterSize*) &RA7PPS,    //RA.7
    (_PointerRegisterSize*) &RB0PPS,    //RB.0
    (_PointerRegisterSize*) &RB1PPS,    //RB.1    
    (_PointerRegisterSize*) &RB2PPS,    //RB.2
    (_PointerRegisterSize*) &RB3PPS,    //RB.3
    (_PointerRegisterSize*) &RB4PPS,    //RB.4
    (_PointerRegisterSize*) &RB5PPS,    //RB.5
    (_PointerRegisterSize*) &RB6PPS,    //RB.6
    (_PointerRegisterSize*) &RB7PPS,    //RB.7    
    (_PointerRegisterSize*) &RC0PPS,    //RC.0
    (_PointerRegisterSize*) &RC1PPS,    //RC.1    
    (_PointerRegisterSize*) &RC2PPS,    //RC.2
    (_PointerRegisterSize*) &RC3PPS,    //RC.3
    (_PointerRegisterSize*) &RC4PPS,    //RC.4
    (_PointerRegisterSize*) &RC5PPS,    //RC.5
    (_PointerRegisterSize*) &RC6PPS,    //RC.6
    (_PointerRegisterSize*) &RC7PPS,    //RC.7
};

/******************************************************************************
 * \brief PPS Pin Lookup
 * 
 * This table defines the PPS PIN to Input Peripheral
 *******************************************************************************/
const unsigned char PPS_InputPin_LU[] = 
{
    0b000000,  //RA.0
    0b000001,  //RA.1
    0b000010,  //RA.2
    0b000011,  //RA.3
    0b000100,  //RA.4
    0b000101,  //RA.5
    0b000110,  //RA.6      
    0b000111,  //RA.7
    0b001000,  //RB.0
    0b001001,  //RB.1
    0b001010,  //RB.2
    0b001011,  //RB.3
    0b001100,  //RB.4
    0b001101,  //RB.5
    0b001110,  //RB.6      
    0b001111,  //RB.7
    0b010000,  //RC.0
    0b010001,  //RC.1
    0b010010,  //RC.2
    0b010011,  //RC.3
    0b010100,  //RC.4
    0b010101,  //RC.5
    0b010110,  //RC.6      
    0b010111,  //RC.7    
};


#endif /*_CORE18_18F2XQ84_LU_H*/

/*** End of File **************************************************************/
