/****************************************************************************
* Title                 :   PWM6 Functions
* Filename              :   pwm6.c
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
#include "pwm6.h"
#include "../pps/pps.h"
#include "../tmr2/tmr2.h"

/******************************************************************************
***** PWM Interface
*******************************************************************************/
const PWM6_Interface_t PWM6 = {
  .Initialize = &PWM6_Init,
  .Output = &PWM6_Output_Enable,
  .DutyCycle = &PWM6_Set_DutyCycle  
};


/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : PWM6_Init(PortPin)
*//** 
* \b Description:
*
* Initializes the PWM6 module on the specified GPIO pin for generating Pulse Width Modulation (PWM).
* The function configures the selected output pin using the Peripheral Pin Select (PPS) system and 
* sets up the PWM timer (Timer2) with the appropriate period and prescaler values from the configuration.
*
* The function also enables the PWM6 output and turns on the timer used for PWM signal generation.
*  
* POST-CONDITION: 
*    - The specified pin is mapped as the PWM6 output, and the PWM signal is generated 
*      with the selected duty cycle configuration.
*
* @param[in] PortPin - The GPIO pin to be configured as the PWM output, specified by 
*                      `GPIO_Ports_t` (e.g., PORTC_5, PORTA_1).
* @param[in] PWM_Config_Select - The PWM configuration to use, specified by 
*                                `PWM_ConfigEnum_t` (e.g., PWM62Mhz_8bit, PWM62Mhz_10bit).
*
* @return None 		
*
* \b Example:
* @code
* 	
* // Initialize PWM6 on PORTC pin 5 with 8-bit configuration
* PWM6_Init(PORTC_5, PWM62Mhz_8bit);
* 	
* @endcode
*
* \b Notes:
* - The function sets the appropriate PWM period and prescaler based on the configuration.
* - Use `PWM6_Set_DutyCycle()` to set the desired duty cycle after initialization.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void PWM6_Init(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config_Select)
{ 
    
  PPS_MapOutput(PortPin,PPSOUT_PWM6OUT);
  
  PR2 = PWM_Config[PWM_Config_Select].PR2_Value;
  TMR2_Set_Clock_Source(TMR2_FOSC_D4); //FOSC/4 - T2 Clock Select
  TMR2_Set_Prescaler_Rate(PWM_Config[PWM_Config_Select].T2_Prescale_Value);  //Set T2 Prescale 
  TMR2_Enable(ENABLED);  //Timer 2 on
   
  PWM6CONbits.PWM6OUT = 0x01;  //Enable PWM output
  PWM6CONbits.PWM6EN = 0x01;  //Enable PWM       
}

/******************************************************************************
* Function : PWM6_Output_Enable()
*//** 
* \b Description:
*
* This function enables or disables the PWM6 output on the selected GPIO pin.
* It controls whether the PWM signal is actively output on the pin by modifying 
* the PWM6 output enable bit in the PWM6 control register.
*
* The function is useful for temporarily turning off the PWM signal without 
* modifying the configuration of the PWM itself.
*
* PRE-CONDITION:  
*    - The PWM6 module must be initialized using `PWM6_Init()`.
*    - The GPIO pin must be configured as a PWM output.
*
* POST-CONDITION: 
*    - The PWM output on the specified GPIO pin is either enabled or disabled 
*      depending on the value of `setState`.
*
* @param[in] setState - A value of type `LogicEnum_t` to enable (ENABLED) or 
*                       disable (DISABLED) the PWM output.
*
* @return 		
*
* \b Example:
* @code
* 	
* // Enable the PWM6 output
* PWM6_Output_Enable(ENABLED);
*
* // Disable the PWM6 output
* PWM6_Output_Enable(DISABLED);
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void PWM6_Output_Enable(LogicEnum_t setState)
{
  if(setState)
    {
     PWM6CONbits.PWM6OUT = 0x01; 
    }
  else
    {
     PWM6CONbits.PWM6OUT = 0x00; 
    }
  
}


/******************************************************************************
* Function : PWM6_Set_DutyCycle()
*//** 
* \b Description:
*
* This function sets the duty cycle of the PWM6 output. The duty cycle represents 
* the proportion of time that the PWM signal stays HIGH during one complete period, 
* typically expressed as a percentage. A 50% duty cycle means the signal stays HIGH 
* for half of the period and LOW for the other half.
*
* The function takes a 10-bit value representing the desired duty cycle and writes 
* it to the PWM6 duty cycle registers (PWM6DCL and PWM6DCH). The duty cycle value 
* determines the HIGH-time of the PWM signal.
*
* The valid range for `dutyValue` depends on the PWM configuration and clock frequency:
* - At 8 MHz, the valid range is 0 - 408, with 204 representing a 50% duty cycle.
* - At 16 MHz, the valid range is 0 - 1024, with 512 representing a 50% duty cycle.
*
* PRE-CONDITION:  
*    - The PWM6 module must be initialized using `PWM6_Init()`.
*    - The desired duty cycle should be calculated and passed as a 10-bit value.
*
* POST-CONDITION: 
*    - The PWM6 output will have the specified duty cycle.
*
* @param[in] dutyValue - The 10-bit duty cycle value, where 0 represents 0% duty 
*                        cycle and the maximum value represents 100% duty cycle.
*
*
* @return void		
*
* \b Example:
* @code
* 	
* // Set the PWM6 duty cycle to 50% at 16 MHz clock
* PWM6_Set_DutyCycle(512);  // 512 is 50% duty cycle at 16 MHz
*
* // Set the PWM6 duty cycle to 75%
* PWM6_Set_DutyCycle(768);  // 768 is 75% duty cycle at 16 MHz
* 	
* @endcode
*
* \b Notes:
* - The duty cycle value is divided into two registers: PWM6DCL for the lower 2 bits, 
*   and PWM6DCH for the upper 8 bits.
* - Ensure that the value of `dutyValue` is within the valid range for your clock frequency 
*   and PWM configuration.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/

void PWM6_Set_DutyCycle(uint16_t dutyValue)
{
    //2 LSB's of dutyValue
    PWM6DCL = (uint8_t)(dutyValue << 6);
    //8 MSB's of dutyValue
    PWM6DCH = (uint8_t)(dutyValue >> 2);
    
}


/*** End of File **************************************************************/
