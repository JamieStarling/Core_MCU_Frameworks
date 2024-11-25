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
* Interrupt State Status
*******************************************************************************/
typedef enum
{
  MAIN_RUNNING = 0b00,
  LOW_ISR_RUNNING = 0b01,
  HIGH_ISR_RUNNING = 0b10,
  BOTH_ISR_RUNNING = 0b11  
}ISR_Interrupt_StateEnum_t;


/******************************************************************************
****** Lookup : GPIO 
*******************************************************************************/
/*Defines the Max IO Pin Count on the Device
* Used for reading the GPIO Configuration Table*/
#define _CORE18_MAX_GPIO_PORTPIN_COUNT 25

/******************************************************************************
* Port Pin Table Lookup Maps Port Pin Name to a value for later lookup.
******************************************************************************/
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

/******************************************************************************
* GPIO Register Lookup
*******************************************************************************/
typedef struct {
    volatile unsigned char *direction_reg;  // Pointer to the TRIS register for direction control (input/output)
    volatile unsigned char *write_reg;      // Pointer to the LAT register for writing output levels
    volatile unsigned char *read_reg;       // Pointer to the PORT register for reading pin levels
    volatile unsigned char *wpu_reg;        // Pointer to the Weak Pull-Up register
    volatile unsigned char *analog_reg;     // Pointer to the ANSEL register for analog/digital configuration
    volatile unsigned char *odcon_reg;      // Pointer to the open-drain configuration register
    volatile unsigned char pinmask;         // Bitmask for the specific pin in the register
    volatile unsigned char pps_inputpin;    // PPS input value for the pin
    volatile unsigned char *pps_output_reg; // Pointer to the PPS output configuration register
    
} GPIO_RegisterSet_t;

const GPIO_RegisterSet_t GPIO_Register_LU[] = {
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00000001U, 0x00, &RA0PPS},  // RA.0
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00000010U, 0x01, &RA1PPS},  // RA.1
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00000100U, 0x02, &RA2PPS},  // RA.2
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00001000U, 0x03, &RA3PPS},  // RA.3
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00010000U, 0x04, &RA4PPS},  // RA.4
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b00100000U, 0x05, &RA5PPS},  // RA.5
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b01000000U, 0x06, &RA6PPS},  // RA.6
    {&TRISA, &LATA, &PORTA, &WPUA, &ANSELA, &ODCONA, 0b10000000U, 0x07, &RA7PPS},  // RA.7
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00000001U, 0x08, &RB0PPS},  // RB.0
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00000010U, 0x09, &RB1PPS},  // RB.1
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00000100U, 0x0A, &RB2PPS},  // RB.2
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00001000U, 0x0B, &RB3PPS},  // RB.3
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00010000U, 0x0C, &RB4PPS},  // RB.4
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b00100000U, 0x0D, &RB5PPS},  // RB.5
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b01000000U, 0x0E, &RB6PPS},  // RB.6
    {&TRISB, &LATB, &PORTB, &WPUB, &ANSELB, &ODCONB, 0b10000000U, 0x0F, &RB7PPS},  // RB.7    
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00000001U, 0x10, &RC0PPS},  // RC.0
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00000010U, 0x11, &RC1PPS},  // RC.1
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00000100U, 0x12, &RC2PPS},  // RC.2
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00001000U, 0x13, &RC3PPS},  // RC.3
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00010000U, 0x14, &RC4PPS},  // RC.4
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b00100000U, 0x15, &RC5PPS},  // RC.5    
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b01000000U, 0x16, &RC6PPS},  // RC.6
    {&TRISC, &LATC, &PORTC, &WPUC, &ANSELC, &ODCONC, 0b10000000U, 0x17, &RC7PPS},  // RC.7
};

/******************************************************************************
***** Analog Lookup Tables
*******************************************************************************/

/******************************************************************************
*Analog Channel Select Enum -  This enum defines the analog channels available for selection on the device.
*******************************************************************************/

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
*PPS Peripheral Output Enum * This enum defines the PPS Peripheral Output available for selection on the device.
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
****** Constants: Timer0
*******************************************************************************/

/******************************************************************************
*Timer0 Post-Scaler Select Enum * This enum selects the post-scaler value for Timer0 on the PIC16F1532x devices.
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


/******************************************************************************
* Timer0 Clock Source Select Enum * This enum selects the clock source value for Timer0 on the PIC16F1532x devices.
*******************************************************************************/
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
****** Constants: Timer2
*******************************************************************************/

/******************************************************************************
* Timer2 Pre-Scaler Select Enum * This enum selects the Pre-Scaler value for Timer2 on the PIC16F1532x devices.
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
* Timer2 Mode Select Enum * This enum selects the mode value for Timer2 on the PIC16F1532x devices.
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
* Timer2 Clock Source Select Enum * This enum selects the clock source value for Timer2 on the PIC16F1532x devices.
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
* Timer2 Post-Scaler Select Enum * This enum selects the post-scaler value for Timer2 on the PIC16F1532x devices.
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





#endif /*_CORE18_18F2XQ84_LU_H*/

/*** End of File **************************************************************/
