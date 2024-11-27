/****************************************************************************
* Title                 :   GPIO Analog Functions
* Filename              :   gpio_analog.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.3
* Compiler              :   XC8
* Target                :   Microchip PIC16F series 
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

/******************************************************************************
* Includes
*******************************************************************************/
#include "gpio_analog.h"

/******************************************************************************
***** Analog Interface
*******************************************************************************/
const GPIO_Analog_Interface_t GPIO_Analog = {
  .Initialize = &GPIO_Analog_Init,
  .SelectChannel = &GPIO_Analog_SelectChannel,
  .PinSet = &GPIO_Analog_SetPortPin,
  .ReadChannel =  &GPIO_Analog_ReadChannel
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : GPIO_Analog_Init()
* Description: Initializes the ADC for a specified analog channel, sets the conversion 
* clock based on the system clock, and enables the ADC module.
*
* Parameters:
*   - Channel (AnalogChannelSelectEnum_t): The analog channel to initialize 
*     (e.g., ANA0, ANA1).

*******************************************************************************/
void GPIO_Analog_Init(AnalogChannelSelectEnum_t Channel)
{
    //ADC Conversion Clock Select bits  - 
    #if _XTAL_FREQ == 1000000    
    ADCON1bits.ADCS = 0b00000000;       //1 MHz 2.0us FOSC/2    
    #elif _XTAL_FREQ == 2000000    
    ADCON1bits.ADCS = 0b00000100;       //2 MHz 2.0us FOSC/4    
    #elif _XTAL_FREQ == 4000000    
    //ADCON1bits.ADCS = 0b00000100;     //4 MHz 1.0us FOSC/4    
    ADCON1bits.ADCS = 0b00000001;       //4 MHz 2.0us FOSC/8  
    #elif _XTAL_FREQ == 8000000
    //ADCON1bits.ADCS = 0b00000001;     //8 MHz 1.0us FOSC/8
    ADCON1bits.ADCS = 0b00000101;       //8 MHz 2.0us FOSC/16 
    #elif _XTAL_FREQ == 16000000
     //ADCON1bits.ADCS = 0b00000101;    //16 MHz 1.0us FOSC/16
    ADCON1bits.ADCS = 0b00000010;       //16 MHz 2.0us FOSC/32
    #elif _XTAL_FREQ == 20000000    
    //ADCON1bits.ADCS = 0b00000010;     //20 MHz 1.6us FOSC/32
    ADCON1bits.ADCS = 0b00000110;       //20 MHz 3.2us FOSC/64
    #elif _XTAL_FREQ == 32000000
    //ADCON1bits.ADCS = 0b00000010;     //32 MHz 1.0us FOSC/32
    ADCON1bits.ADCS = 0b00000110;       //32 MHz 2.0us FOSC/64  
    #else
    #error "Unsupported _XTAL_FREQ value for Analog Conversion. Please check the frequency settings."
    #endif
    
   //Set Channel - 
   ADCON0bits.CHS = Channel;
   ADCON1bits.ADFM = 1; //ADRESH holds the High Value
           
   ADCON0bits.ADON = 1;
}

/******************************************************************************
* Function : GPIO_Analog_SelectChannel()
* Description:Selects an analog channel for ADC conversions by setting the channel select 
*   bits (CHS) in the ADCON0 register.
*
* Parameters:
*   - Channel (AnalogChannelSelectEnum_t): The analog channel to select 
*     (e.g., ANA0, ANA1).

*******************************************************************************/
void GPIO_Analog_SelectChannel(AnalogChannelSelectEnum_t Channel)
{
    ADCON0bits.CHS = Channel;    
}

/******************************************************************************
* Function : GPIO_Analog_SetPortPin()
* Description:Configures a GPIO pin for analog input and initializes the ADC with the 
* specified analog channel.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to configure (e.g., PORTA_0, PORTC_1).
*   - Channel (AnalogChannelSelectEnum_t): The analog channel to associate with 
*     the pin (e.g., ANA0, ANA1).
*******************************************************************************/
void GPIO_Analog_SetPortPin(GPIO_Ports_t PortPin, AnalogChannelSelectEnum_t Channel)
{   
   GPIO.ModeSet(PortPin,ANALOG);
   GPIO_Analog_Init(Channel);
}

/******************************************************************************
* Function : GPIO_Analog_ReadChannel()
* Description:Starts an ADC conversion on the selected channel, waits for it to complete, 
* and returns the 10-bit conversion result.
*
* Parameters:
*   - None
*
* Returns:
*   - uint16_t: The 10-bit ADC conversion result.
*******************************************************************************/
uint16_t GPIO_Analog_ReadChannel(void)
{
   uint16_t adc_result; 
   ADCON0bits.GOnDONE = 1;  //Start the conversion
    
   while (ADCON0bits.GOnDONE == 1){}   
       
   adc_result = CORE.Make16(ADRESH,ADRESL);    
   return adc_result;    //Verify that this returns 10bit result    
}


/*** End of File **************************************************************/
