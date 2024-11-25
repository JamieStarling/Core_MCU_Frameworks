/****************************************************************************
* Title                 :   PWM3 Functions
* Filename              :   pwm3.c
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
#include "pwm3.h"
#include "../pps/pps.h"
#include "../tmr2/tmr2.h"

/******************************************************************************
***** PWM Interface
*******************************************************************************/
const PWM3_Interface_t PWM3 = {
  .Initialize = &PWM3_Init,
  .Output = &PWM3_Output_Enable,
  .DutyCycle = &PWM3_Set_DutyCycle  
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : PWM3_Init(PortPin)
* Description: Initializes the PWM3 module on the specified GPIO pin for Pulse Width Modulation (PWM) output.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin for PWM output (e.g., PORTC_5).
*   - PWM_Config_Select (PWM_ConfigEnum_t): The PWM configuration to use (e.g., PWM_8bit).
*
*******************************************************************************/
void PWM3_Init(GPIO_Ports_t PortPin,PWM_ConfigEnum_t PWM_Config_Select)
{     
  PPS_MapOutput(PortPin,PPSOUT_PWM3OUT);
  
  PR2 = PWM_Config[PWM_Config_Select].PR2_Value;
  TMR2_Set_Clock_Source(TMR2_FOSC_D4); // Set Timer2 clock source to FOSC/4
  TMR2_Set_Prescaler_Rate(PWM_Config[PWM_Config_Select].T2_Prescale_Value);  // Set Timer2 prescaler
  TMR2_Enable(ENABLED);  // Enable Timer2
   
  PWM3CONbits.PWM3OUT = 0x01;  // Enable PWM output
  PWM3CONbits.PWM3EN = 0x01;  // Enable PWM       
}

/******************************************************************************
* Function : PWM3_Output_Enable()
* Description:Enables or disables the PWM3 output on the selected GPIO pin by modifying 
*   the PWM3 output enable bit.
*
* Parameters:
*   - setState (LogicEnum_t): ENABLED to enable the output, DISABLED to disable it.
*
* 
*******************************************************************************/
void PWM3_Output_Enable(LogicEnum_t setState)
{
  PWM3CONbits.PWM3OUT = (setState == ENABLED) ? 0x01 : 0x00;  
}


/******************************************************************************
* Function : PWM3_Set_DutyCycle()
* Description: Description:
*   Sets the duty cycle for the PWM3 output by writing a 10-bit value to the 
*   duty cycle registers (PWM3DCL and PWM3DCH).
*
* Parameters:
*   - dutyValue (uint16_t): The 10-bit duty cycle value, where 0 represents 0% 
*     duty cycle and the maximum value represents 100% duty cycle.
*
*******************************************************************************/
void PWM3_Set_DutyCycle(uint16_t dutyValue)
{
    //2 LSB's of dutyValue
    PWM3DCL = (uint8_t)(dutyValue << 6);
    //8 MSB's of dutyValue
    PWM3DCH = (uint8_t)(dutyValue >> 2);
    
}


/*** End of File **************************************************************/
