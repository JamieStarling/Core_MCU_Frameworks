/****************************************************************************
* Title                 :   CORE MCU Framework : PWM2 for 18F devices
* Filename              :   pwm2.c
* Author                :   Jamie Starling
* Origin Date           :   2024/11/21
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   PIC18F Family 
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
/******************************************************************************
***** NOTES
* PWM Functions uses the CCP module
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "pwm2.h"


/******************************************************************************
***** PWM Interface
*******************************************************************************/
const PWM2_Interface_t PWM2 = {
  .Initialize = &PWM2_Init,
  .Output = &PWM2_Output_Enable,
  .DutyCycle = &PWM2_Set_DutyCycle  
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : PWM2_Init(PortPin)
* Description: Initializes the PWM3 module on the specified GPIO pin for Pulse Width Modulation (PWM) output.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin for PWM output (e.g., PORTC_5).
*   - PWM_Config_Select (PWM_ConfigEnum_t): The PWM configuration to use (e.g., PWM_8bit).
*
*******************************************************************************/
void PWM2_Init(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config_Select)
{     
  PPS_MapOutput(PortPin,PPSOUT_CCP1);
  
  PR2 = PWM_Config[PWM_Config_Select].PR2_Value;
  TMR2_Set_Clock_Source(TMR2_FOSC_D4); // Set Timer2 clock source to FOSC/4
  TMR2_Set_Prescaler_Rate(PWM_Config[PWM_Config_Select].T2_Prescale_Value);  // Set Timer2 prescaler
  TMR2_Enable(ENABLED);  // Enable Timer2
   
  
  CCP2CON = 0x00; // Disable CCP2 to configure it
  CCPTMRS0bits.C2TSEL = 0b01; // TMR2 selected for CCP2  
  CCP2CONbits.MODE = 0b1100;  // Enable PWM  Mode  
  CCP2CONbits.FMT = 1; // Set Left Aligned Mode
  CCP2CONbits.EN = 1;  //Enable CCP2
}

/******************************************************************************
* Function : PWM2_Output_Enable()
* Description:Enables or disables the PWM output on the selected GPIO pin by modifying 
* the PWM output enable bit.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable the output, DISABLED to disable it.
*
* 
*******************************************************************************/
void PWM2_Output_Enable(LogicEnum_t setState)
{
   CCP2CONbits.EN = (setState == ENABLED) ? 0x01 : 0x00;  
}


/******************************************************************************
* Function : PWM2_Set_DutyCycle()
* Description: Description:
*   Sets the duty cycle for the PWM output by writing a 10-bit value to the 
*   duty cycle registers.
*
* Parameters:
*   - dutyValue (uint16_t): The 10-bit duty cycle value, where 0 represents 0% 
*     duty cycle and the maximum value represents 100% duty cycle.
*
*******************************************************************************/
void PWM2_Set_DutyCycle(uint16_t dutyValue)
{
    //2 LSB's of dutyValue
    CCPR2L = (uint8_t)(dutyValue << 6);
    //8 MSB's of dutyValue
    CCPR2H = (uint8_t)(dutyValue >> 2);   
}


/*** End of File **************************************************************/
