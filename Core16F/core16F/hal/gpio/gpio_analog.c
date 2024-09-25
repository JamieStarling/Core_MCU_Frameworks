/****************************************************************************
* Title                 :   GPIO Analog Functions
* Filename              :   gpio_analog.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.1
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
*//** 
* \b Description:
*
* This function initializes the analog-to-digital conversion (ADC) functionality 
* for a specified analog channel on the microcontroller. It configures the conversion 
* timing based on the system clock frequency and sets the specified analog channel for 
* conversion.
*
* The function sets the conversion clock (ADCS), enables the ADC, and configures the 
* analog result formatting to store the result in the high byte of the result register.
*  
* PRE-CONDITION:  
*    - The pin should be configured as an analog input using `GPIO_SetDirection()`, 
*      or the `GPIO_Analog_SetPortPin()` function should be used to configure the pin as analog.
*
* POST-CONDITION: 
*    - The specified analog channel is initialized, and the ADC module is ready to perform conversions.
*
* @param[in] Channel - The analog channel to initialize, specified by 
*                      `AnalogChannelSelectEnum_t` (e.g., ANA0, ANA1).
*
* @return 		void
*
* \b Example:
* @code
* 	
* GPIO_Analog_Init(ANA0); // Initialize and configure analog channel ANA0
* 	
* @endcode
*
* \b Notes:
* - The conversion clock timing is automatically configured based on the system clock 
*   (_XTAL_FREQ). Different clock speeds are supported.
* - The function enables the ADC module and sets the desired analog channel for conversion.
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void GPIO_Analog_Init(AnalogChannelSelectEnum_t Channel)
{
    //ADC Conversion Clock Select bits  - 
    #if _XTAL_FREQ == 1000000
    //1 MHz 2.0us FOSC/2
     ADCON1bits.ADCS = 0b00000000;
    #endif /*_XTAL_FREQ == 1000000*/
    
    #if _XTAL_FREQ == 2000000
    //2 MHz 2.0us FOSC/4
     ADCON1bits.ADCS = 0b00000100;
    #endif /*_XTAL_FREQ == 2000000*/
    
    #if _XTAL_FREQ == 4000000
    //4 MHz 1.0us FOSC/4
    //ADCON1bits.ADCS = 0b00000100;    
    
    //4 MHz 2.0us FOSC/8
    ADCON1bits.ADCS = 0b00000001;     
    #endif /*_XTAL_FREQ == 4000000*/
   
    #if _XTAL_FREQ == 8000000
    //8 MHz 1.0us FOSC/8
    //ADCON1bits.ADCS = 0b00000001;    
    
    //8 MHz 2.0us FOSC/16
    ADCON1bits.ADCS = 0b00000101;     
    #endif  /*_XTAL_FREQ == 8000000*/
           
    #if _XTAL_FREQ == 16000000
    //16 MHz 1.0us FOSC/16
    //ADCON1bits.ADCS = 0b00000101;    
    
    //16 MHz 2.0us FOSC/32
    ADCON1bits.ADCS = 0b00000010;     
    #endif /*_XTAL_FREQ == 16000000*/        

   #if _XTAL_FREQ == 20000000
    //20 MHz 1.6us FOSC/32
    //ADCON1bits.ADCS = 0b00000010;    
    
    //20 MHz 3.2us FOSC/64
    ADCON1bits.ADCS = 0b00000110;     
    #endif /*_XTAL_FREQ == 16000000*/      
    
    #if _XTAL_FREQ == 32000000
    //32 MHz 1.0us FOSC/32
    //ADCON1bits.ADCS = 0b00000010;    
    
    //32 MHz 2.0us FOSC/64
    ADCON1bits.ADCS = 0b00000110;     
    #endif /*_XTAL_FREQ == 16000000*/    
    
    //Set Channel - 
   ADCON0bits.CHS = Channel;
   ADCON1bits.ADFM = 1; //ADRESH holds the High Value
           
   ADCON0bits.ADON = 1;
}

/******************************************************************************
* Function : GPIO_Analog_SelectChannel()
*//** 
* \b Description:
*
* This function selects an analog channel for the ADC (Analog-to-Digital Converter)
* to perform conversions on. The selected channel is configured for subsequent
* ADC readings. 
*
* The function modifies the ADC channel select bits (CHS) in the ADCON0 register
* to point to the desired analog channel.
*
* PRE-CONDITION:  
*    - The pin associated with the analog channel must be configured as an analog input 
*      using `GPIO_SetDirection()` or `GPIO_Analog_SetPortPin()`.
*    - The ADC module must be initialized using `GPIO_Analog_Init()` before selecting channels.
*
* POST-CONDITION: 
*    - The specified analog channel is selected for ADC conversions.
*
* @param[in] Channel - The analog channel to select, specified by 
*                      `AnalogChannelSelectEnum_t` (e.g., ANA0, ANA1, etc.).
*
*
* @return 		void
*
* \b Example:
* @code
* 	
* GPIO_Analog_SelectChannel(ANA0); //Selects analog channel ANA0
* 	
* @endcode
*
* \b Notes:
* - The ADC must be initialized before selecting a channel.
* - The selected channel will be used for future ADC conversions until another channel is selected.
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void GPIO_Analog_SelectChannel(AnalogChannelSelectEnum_t Channel)
{
    ADCON0bits.CHS = Channel;    
}

/******************************************************************************
* Function : GPIO_Analog_SetPortPin()
*//** 
* \b Description:
*
* This function configures a specific GPIO pin to be used for analog input in the 
* Analog-to-Digital Converter (ADC). It modifies the direction and analog register 
* settings for the specified pin and initializes the ADC to use the selected analog 
* channel.
*
* The function sets the pin as an analog input and enables the corresponding analog 
* channel. After setting the pin direction, it calls `GPIO_Analog_Init()` to configure 
* the ADC for proper operation.
*
* PRE-CONDITION:  
*    - The ADC module must be initialized with the proper conversion timing using `GPIO_Analog_Init()`.
*
* POST-CONDITION: 
*    - The GPIO pin is configured for analog input, and the selected analog channel 
*      is ready for ADC conversions.
*
* @param[in] PortPin - The GPIO pin to configure for analog input, specified by 
*                      `GPIO_Ports_t` (e.g., PORTA_0, PORTC_1).
* @param[in] Channel - The analog channel to associate with the GPIO pin, specified by 
*                      `AnalogChannelSelectEnum_t` (e.g., ANA0, ANA1, etc.).
*
* @return None		
*
* \b Example:
* @code
* 	
* GPIO_Analog_SetPortPin(PORTA_0, ANA0);  / Set PORTA pin 0 as an analog input sets ADC to channel ANA0
* 	
* @endcode
*
* \b Notes:
* - This function sets the pin direction as analog input and initializes the analog channel.
* - After calling this function, the selected GPIO pin will be configured for ADC conversion.
*
* <br><b> - HISTORY OF CHANGES - </b>

* <hr>
*******************************************************************************/
void GPIO_Analog_SetPortPin(GPIO_Ports_t PortPin, AnalogChannelSelectEnum_t Channel)
{
  //var that holds the registers of the Direction, Analog and PIN BitMask.
   uint8_t *regDirection_ptr, *regAnalog_ptr, pinBitMask;
   
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin];
   
    //Get the register that controls the direction for the Pin
   regDirection_ptr = (uint8_t*) GPIO_DirectionRegister_LU[PortPin];    
   
   //Get the register that controls the analog for the Pin
   regAnalog_ptr = (uint8_t*) GPIO_AnalogRegister_LU[PortPin];
   
   *regDirection_ptr &= ~pinBitMask; 
   *regAnalog_ptr |= pinBitMask;
   
   GPIO_Analog_Init(Channel);
}

/******************************************************************************
* Function : GPIO_Analog_ReadChannel()
*//** 
* \b Description:
*
* This function starts an analog-to-digital conversion (ADC) on the selected 
* analog channel and waits for the conversion to complete. Once the conversion 
* is done, it returns the 10-bit result of the ADC conversion.
*
* The function initiates the ADC by setting the `GOnDONE` bit in the ADCON0 register,
* waits for the conversion to complete, and then reads the result from the ADC result
* registers (ADRESH and ADRESL). The 10-bit result is returned to the caller.
*
* PRE-CONDITION:  
*    - The pin and analog channel must be configured for analog input using 
*      `GPIO_Analog_SetPortPin()` and `GPIO_Analog_Init()`.
*
* POST-CONDITION: 
*    - The ADC result is returned as a 10-bit value representing the analog input.
*
* @param[in] None
*
* @return uint16_t
*    - The 10-bit result of the ADC conversion.
*
* \b Example:
* @code
* // Set up the pin and analog channel
* GPIO_Analog_SetPortPin(PORTA_0, ANA0);
* GPIO_Analog_Init(ANA0);
*
* // Read the analog value from channel ANA0
* uint16_t adcValue = GPIO_Analog_ReadChannel(); 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
* <hr>
*******************************************************************************/
uint16_t GPIO_Analog_ReadChannel()
{
   
    ADCON0bits.GOnDONE = 1;  //Start the conversion
    
    while (ADCON0bits.GOnDONE == 1){
        NOP();
    }
    
    uint16_t adc_result;
    
    adc_result = CORE16F_Make_16(ADRESH,ADRESL);
    
    //adc_result = (uint16_t)(ADRESH<<8) | (uint16_t) ADRESL;
    
    return adc_result;    //Verify that this returns 10bit result
    
}


/*** End of File **************************************************************/
