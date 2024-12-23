/****************************************************************************
* Title                 :   Blink LED Delay Based on POT Analog Value
* Filename              :   blink_led_pot.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/24
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :    
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
* Includes
*******************************************************************************/
#include "core16F/core16F.h" //Include Core MCU Functions


/******************************************************************************
* Functions
*******************************************************************************/
void main(void)
{
  /*Setup*/
  /*Initialize for the Core8 System   */
  CORE.Initialize(); //
  
  /*Set PORTA.0 to Output*/
  GPIO.ModeSet(PORTA_0,OUTPUT);
  
 /*Set PORTA.1 to Analog and Maps ANA1 Channel - Initializes Analog*/
  GPIO_Analog.PinSet(PORTA_1,ANA1); //  

 
  while(1) //Program loop
    {      
      uint16_t POT_Value;
      GPIO.PinToggle(PORTA_0); //Toggles LED on PORTA_0
      POT_Value = GPIO_Analog.ReadChannel(); //Reads Value from Pot
      CORE.Delay_MS(POT_Value);    //Delay based on reading from the Analog     
    }
}




/*** End of File **************************************************************/
