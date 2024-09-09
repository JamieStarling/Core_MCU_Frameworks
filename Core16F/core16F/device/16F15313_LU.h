/****************************************************************************
* Title                 :   Register Lookup Table for PIC16F15313
* Filename              :   16F15313_LU.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   Microchip PIC16F15313
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

#ifndef _CORE16F_16F15313_LU_H
#define _CORE16F_16F15313_LU_H
/******************************************************************************
***** Includes
*******************************************************************************/
#include "../core16F.h"

/******************************************************************************
* Defines
*******************************************************************************/
/******************************************************************************
****** Constants: Timer0
*******************************************************************************/

/******************************************************************************
 * \brief Timer0 Post-Scaler Select Enum
 * 
 * This enum selects the post-scaler value for Timer0 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR0_POST_SCALE_1_1 = 0b0000,
  TMR0_POST_SCALE_1_2 = 0b0001,
  TMR0_POST_SCALE_1_3 = 0b0010,
  TMR0_POST_SCALE_1_4 = 0b0011,
  TMR0_POST_SCALE_1_5 = 0b0100,
  TMR0_POST_SCALE_1_6 = 0b0101,
  TMR0_POST_SCALE_1_7 = 0b0110,
  TMR0_POST_SCALE_1_8 = 0b0111,
  TMR0_POST_SCALE_1_9 = 0b1000,
  TMR0_POST_SCALE_1_10 = 0b1001,
  TMR0_POST_SCALE_1_11 = 0b1010,
  TMR0_POST_SCALE_1_12 = 0b1011,
  TMR0_POST_SCALE_1_13 = 0b1100,
  TMR0_POST_SCALE_1_14 = 0b1101,
  TMR0_POST_SCALE_1_15 = 0b1110,
  TMR0_POST_SCALE_1_16 = 0b1111  
}TMR0_PostScaler_SelectEnum_t;


/******************************************************************************
 * \brief Timer0 Clock Source Select Enum
 * 
 * This enum selects the clock source value for Timer0 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR0_LC1_OUT = 0b111,  
  TMR0_MFINTOSC = 0b101,
  TMR0_LFINTOSC = 0b100,
  TMR0_HFINTOSC = 0b011,
  TMR0_FOSC_D4 = 0b010,
  TMR0_T0CKIPPS_INV = 0b001,
  TMR0_T0CKIPPS_NINV = 0b000
}TMR0_Clock_Source_SelectEnum_t;


/******************************************************************************
 * \brief Timer0 Pre-Scaler Select Enum
 * 
 * This enum selects the Pre-Scaler value for Timer0 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR0_PRESCALER_1_32768 = 0b1111,
  TMR0_PRESCALER_1_16384 = 0b1110,
  TMR0_PRESCALER_1_8192 = 0b1101,
  TMR0_PRESCALER_1_4096 = 0b1100,
  TMR0_PRESCALER_1_2048 = 0b1011,
  TMR0_PRESCALER_1_1024 = 0b1010,
  TMR0_PRESCALER_1_512 = 0b1001,
  TMR0_PRESCALER_1_256 = 0b1000,
  TMR0_PRESCALER_1_128 = 0b0111,
  TMR0_PRESCALER_1_64 = 0b0110,
  TMR0_PRESCALER_1_32 = 0b0101,
  TMR0_PRESCALER_1_16 = 0b0100,
  TMR0_PRESCALER_1_8 = 0b0011,
  TMR0_PRESCALER_1_4 = 0b0010,
  TMR0_PRESCALER_1_2 = 0b0001,
  TMR0_PRESCALER_1_1 = 0b0000
}TMR0_PreScaler_SelectEnum_t;

/******************************************************************************
****** Constants: Timer1
*******************************************************************************/
/******************************************************************************
 * \brief Timer1 Pre-Scaler Select Enum
 * 
 * This enum selects the Pre-Scaler value for Timer1 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR1_PRESCALER_1_8 = 0b11,
  TMR1_PRESCALER_1_4 = 0b10,
  TMR1_PRESCALER_1_2 = 0b01,
  TMR1_PRESCALER_1_1 = 0b00
}TMR1_PreScaler_SelectEnum_t;


/******************************************************************************
 * \brief Timer1 Clock Source Select Enum
 * 
 * This enum selects the clock source value for Timer1 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR1_LC4_OUT = 0b1101,
  TMR1_LC3_OUT = 0b1100,
  TMR1_LC2_OUT = 0b1011,
  TMR1_LC1_OUT = 0b1010,
  TMR1_TMR0_OVERFLOW_OUT = 0b1001,
  TMR1_CLKR_OUT = 0b1000,
  TMR1_MFINTOSC_32KHZ = 0b0110,
  TMR1_MFINTOSC_500KHZ = 0b0101,
  TMR1_LFINTOSC = 0b0100,
  TMR1_HFINTOSC = 0b0011,
  TMR1_FOSC = 0b0010,
  TMR1_FOSC_D4 = 0b0001,
  TMR1_T1CKIPPS = 0b0000
}TMR1_Clock_Source_SelectEnum_t;


/******************************************************************************
****** Constants: Timer2
*******************************************************************************/

/******************************************************************************
 * \brief Timer2 Pre-Scaler Select Enum
 * 
 * This enum selects the Pre-Scaler value for Timer2 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR2_PRESCALER_1_128 = 0b111,
  TMR2_PRESCALER_1_64 = 0b110,
  TMR2_PRESCALER_1_32 = 0b101,
  TMR2_PRESCALER_1_16 = 0b100,
  TMR2_PRESCALER_1_8 = 0b011,
  TMR2_PRESCALER_1_4 = 0b010,
  TMR2_PRESCALER_1_2 = 0b001,
  TMR2_PRESCALER_1_1 = 0b000
}TMR2_PreScaler_SelectEnum_t;


/******************************************************************************
 * \brief Timer2 Mode Select Enum
 * 
 * This enum selects the mode value for Timer2 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR2_FREE_RUN_PERIOD_PULSE_SOFTWARE_GATE =            0b00000,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_ACTIVE_HIGH =     0b00001,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_ACTIVE_LOW =      0b00010,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_RESET =           0b00011,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_RESET_RISING =    0b00100,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_RESET_FALLING =   0b00101,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_RESET_LOW =       0b00110,
  TMR2_FREE_RUN_PERIOD_PULSE_HARDWARE_RESET_HIGH =      0b00111,
  TMR2_ONE_SHOT_SOFTWARE_START =                        0b01000,
  TMR2_ONE_SHOT_EDGE_TRIGGERED_START_RISING =           0b01001,
  TMR2_ONE_SHOT_EDGE_TRIGGERED_START_FALLING =          0b01010,
  TMR2_ONE_SHOT_EDGE_TRIGGERED_START_ANY =              0b01011,  
  TMR2_ONE_SHOT_EDGE_TRIGGERED_HW_RESET_RISING =        0b01100,  
  TMR2_ONE_SHOT_EDGE_TRIGGERED_HW_RESET_FALLING =       0b01101,
  TMR2_ONE_SHOT_EDGE_TRIGGERED_HW_RESET_LOW =           0b01110,
  TMR2_ONE_SHOT_EDGE_TRIGGERED_HW_RESET_HIGH =          0b01111,
  TMR2_MONOSTABLE_RISING_START =                        0b10001,  
  TMR2_MONOSTABLE_FALLING_START =                       0b10010,
  TMR2_MONOSTABLE_ANY_START =                           0b10011,
  TMR2_ONESHOT_LEVEL_TRIGGER_HW_RESET_HIGH_LOW  =       0b10110,
  TMR2_ONESHOT_LEVEL_TRIGGER_HW_RESET_LOW_HIGH  =       0b10111,  
}TMR2_Mode_SelectEnum_t;

/******************************************************************************
 * \brief Timer2 Clock Source Select Enum
 * 
 * This enum selects the clock source value for Timer2 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR2_LC4_OUT = 0b1110,
  TMR2_LC3_OUT = 0b1101,
  TMR2_LC2_OUT = 0b1100,
  TMR2_LC1_OUT = 0b1011,
  TMR2_ZCD1_OUT = 0b1010,
  TMR2_NCO1_OUT = 0b1001,
  TMR2_CLKR_OUT = 0b1000,
  TMR2_MFINTOSC_32KHZ = 0b0110,
  TMR2_MFINTOSC_500KHZ = 0b0101,
  TMR2_LFINTOSC = 0b0100,
  TMR2_HFINTOSC = 0b0011,
  TMR2_FOSC = 0b0010,
  TMR2_FOSC_D4 = 0b0001,
  TMR2_T1CKIPPS = 0b0000
}TMR2_Clock_Source_SelectEnum_t;

/******************************************************************************
 * \brief Timer2 Post-Scaler Select Enum
 * 
 * This enum selects the post-scaler value for Timer2 on the PIC16F1532x devices.
 *******************************************************************************/
typedef enum
{
  TMR2_POST_SCALE_1_1 = 0b0000,
  TMR2_POST_SCALE_1_2 = 0b0001,
  TMR2_POST_SCALE_1_3 = 0b0010,
  TMR2_POST_SCALE_1_4 = 0b0011,
  TMR2_POST_SCALE_1_5 = 0b0100,
  TMR2_POST_SCALE_1_6 = 0b0101,
  TMR2_POST_SCALE_1_7 = 0b0110,
  TMR2_POST_SCALE_1_8 = 0b0111,
  TMR2_POST_SCALE_1_9 = 0b1000,
  TMR2_POST_SCALE_1_10 = 0b1001,
  TMR2_POST_SCALE_1_11 = 0b1010,
  TMR2_POST_SCALE_1_12 = 0b1011,
  TMR2_POST_SCALE_1_13 = 0b1100,
  TMR2_POST_SCALE_1_14 = 0b1101,
  TMR2_POST_SCALE_1_15 = 0b1110,
  TMR2_POST_SCALE_1_16 = 0b1111  
}TMR2_PostScaler_SelectEnum_t;

/******************************************************************************
****** Constants: I/O Pin Direction
*******************************************************************************/

/******************************************************************************
 * \brief Defines the Max IO Pin Count on the Device
 * 
 * Used for reading the GPIO Configuration Table.
 *******************************************************************************/
#define _CORE16F_MAX_GPIO_PORTPIN_COUNT 6

/******************************************************************************
 * \brief Defines the IO Pin Direction on the Device
 * 
 * Used for setting the IO Pin Direction. 
 *******************************************************************************/
typedef enum
{
    OUTPUT = 0x0U,	
    INPUT = 0x1U,
    INPUT_W_PULLUP = 0x2U,
    ANALOG = 0x3U,
    OPEN_DRAIN = 0x4U
}PinDirectionEnum_t;


/******************************************************************************
***** Digital Lookup Tables
*******************************************************************************/

/******************************************************************************
 * \brief Port Pin Table Lookup
 * 
 * Maps Port Pin to a value for later lookup.
 *******************************************************************************/
typedef enum
{    
    PORTA_0,
    PORTA_1,
    PORTA_2,
    PORTA_3,
    PORTA_4,
    PORTA_5,
    MAX_IOPINS
}GPIO_Ports_t;


/******************************************************************************
 * \brief GPIO Pin Mask Lookup
 * 
 * This lookup table provides the bitmask for each GPIO pin on the device.
 * The table is used to configure the individual bits in the port registers.
 *******************************************************************************/
const unsigned char GPIO_PinBitMask_LU[] = 
{
    0b00000001U,    //RA.0
    0b00000010U,    //RA.1
    0b00000100U,    //RA.2
    0b00001000U,    //RA.3
    0b00010000U,    //RA.4
    0b00100000U,    //RA.5
};

/******************************************************************************
 * \brief GPIO Direction Register Lookup
 * 
 * This table contains pointers to the GPIO direction registers (TRISx) for each pin.
 * It is used to set the direction of the GPIO ports.
 *******************************************************************************/
volatile unsigned char *const GPIO_DirectionRegister_LU[] =
{
    &TRISA, //RA.0
    &TRISA, //RA.1
    &TRISA, //RA.2
    &TRISA, //RA.3
    &TRISA, //RA.3
    &TRISA, //RA.5
};

/******************************************************************************
 * \brief GPIO Write Register Lookup Table
 * 
This table contains pointers to the GPIO write registers (LATx) for each pin.
 * It is used to write to the output latches of the GPIO ports.
 *******************************************************************************/
volatile unsigned char *const GPIO_WriteRegister_LU[] =
{
    &LATA,  //RA.0
    &LATA,  //RA.1
    &LATA,  //RA.2
    &LATA,  //RA.3
    &LATA,  //RA.4
    &LATA,  //RA.5
};

/******************************************************************************
 * \brief GPIO Read Register Lookup
 * 
 * This table contains pointers to the GPIO read registers (PORTx) for each pin.
 * It is used to read from the GPIO ports.
 *******************************************************************************/
volatile unsigned char *const GPIO_ReadRegister_LU[] =
{
    &PORTA, //RA.0
    &PORTA, //RA.1
    &PORTA, //RA.2
    &PORTA, //RA.3
    &PORTA, //RA.4
    &PORTA, //RA.5
};

/******************************************************************************
 * \brief GPIO Weak Pull-up Register Lookup
 * 
 * This table contains pointers to the GPIO Weak Pull-up registers (WPUx) for each pin.
 * It is used to set Weak-Up on each pin.
 *******************************************************************************/
volatile unsigned char *const GPIO_WPURegister_LU[] =
{
    &WPUA,  //RA.0
    &WPUA,  //RA.1
    &WPUA,  //RA.2
    &WPUA,  //RA.3
    &WPUA,  //RA.4
    &WPUA,  //RA.5
};

/******************************************************************************
 * \brief GPIO Open Drain Control Register Lookup
 * 
 * This table contains pointers to the GPIO Open Drain registers (ODCONx) for each pin.
 * It is used to enable/disable open drain control for each pin.
 *******************************************************************************/
volatile unsigned char *const GPIO_ODCONRegister_LU[] =
{
    &ODCONA,  //RA.0
    &ODCONA,  //RA.1
    &ODCONA,  //RA.2
    &ODCONA,  //RA.3
    &ODCONA,  //RA.4
    &ODCONA   //RA.5     
};

/******************************************************************************
***** Analog Lookup Tables
*******************************************************************************/

/******************************************************************************
 * \brief GPIO Analog Register Lookup
 * 
 * This table contains pointers to the GPIO Analog Registers (ANSELx) for each pin.
 * It is used to enable/disable analog input for each pin.
 *******************************************************************************/
volatile unsigned char *const GPIO_AnalogRegister_LU[] =
{
    &ANSELA,    //RA.0
    &ANSELA,    //RA.1
    &ANSELA,    //RA.2
    &ANSELA,    //RA.3
    &ANSELA,    //RA.4
    &ANSELA,    //RA.5    
};



/******************************************************************************
 * \brief Analog Channel Select Enum
 * 
 * This enum defines the analog channels available for selection on the device.
 *******************************************************************************/
typedef enum
{
    AN0 = 0b000000,			    
    AN1 = 0b000001, 
    AN2 = 0b000010,
    AN3 = 0b000011,
    AN4 = 0b000100,
    AN5 = 0b000101,
    AVSS = 0b111011,
    TEMPERATURE_SENSOR = 0b111100,
    DAC1_OUTPUT = 0b111101,
    FVR_BUFFER1 = 0b111110,
    FVR_BUFFER2 = 0b111111,
}AnalogChannelSelectEnum_t;



/******************************************************************************
***** PPS Output Signal Routing Options Lookup Tables
*******************************************************************************/

/******************************************************************************
 * \brief PPS Peripheral Output Enum
 * 
 * This enum defines the PPS Peripheral Output available for selection on the device.
 *******************************************************************************/
typedef enum
{
    PPSOUT_CLKR = 0x1BU,			    
    PPSOUT_NCO1OUT = 0x1AU, 
    PPSOUT_TMR0 = 0x19U,
    PPSOUT_SDO1_SDA1 = 0x16U,
    PPSOUT_SCK1_SCL1 = 0x15U,    
    PPSOUT_C1OUT = 0x13U,
    PPSOUT_DT1 = 0x10U,
    PPSOUT_TX1_CK1 = 0x0FU,
    PPSOUT_PWM6OUT = 0x0EU,
    PPSOUT_PWM5OUT = 0x0DU,
    PPSOUT_PWM4OUT = 0x0CU,
    PPSOUT_PWM3OUT = 0x0BU,
    PPSOUT_CCP2 = 0x0AU,
    PPSOUT_CCP1 = 0x09U,
    PPSOUT_CWG1D = 0x08U,
    PPSOUT_CWG1C = 0x07U,
    PPSOUT_CWG1B = 0x06U,
    PPSOUT_CWG1A = 0x05U,
    PPSOUT_CLC4OUT = 0x04U,
    PPSOUT_CLC3OUT = 0x03U,
    PPSOUT_CLC2OUT = 0x02U,
    PPSOUT_CLC1OUT = 0x01U,           
}PPSOutputPeripheralEnum_t;

/******************************************************************************
 * \brief PPS Pin Lookup
 * 
 * This table defines the PPS PIN to Input Peripheral
 *******************************************************************************/
const unsigned char PPS_InputPin_LU[] = 
{
    0x00,    //RA.0
    0x01,    //RA.1
    0x02,    //RA.2
    0x03,    //RA.3
    0x04,    //RA.4
    0x05    //RA.5
};

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
};


#endif /*_CORE16F_16F15313_LU_H*/

/*** End of File **************************************************************/
