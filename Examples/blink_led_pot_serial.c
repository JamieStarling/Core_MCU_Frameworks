/****************************************************************************
* Title                 :   Blinks LED based on POT Analog Value - Outputs POT Value to Serial Port
* Filename              :   blink_led_pot_serial.c
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
  
/*Set PORTA.2 to Analog and Maps ANA2 Channel - Initializes Analog*/
  GPIO_Analog.PinSet(PORTA_1,ANA1); //  

/*Initializes Serial1 to 9600 Baud
*On the PIC16F15313 Receive is PORTA.5 : Transmit is on PORTA.4 */
  SERIAL1.Initialize(BAUD_9600);  //Initializes Serial1 - On the PIC16F15313 Receive is RA4
 
  while(1) //Program loop
    {      
      uint16_t POT_Value; 
      char SerialTransmit_Buffer[25]; 
      
      GPIO.PinToggle(PORTA_0); //Toggles LED on PORTA_0
      
      POT_Value = GPIO_Analog.ReadChannel();
      sprintf(SerialTransmit_Buffer, "POT Value : %d\n", POT_Value);
      SERIAL1.WriteString(SerialTransmit_Buffer);  
      CORE.Delay_MS(POT_Value);    //Delay based on reading from the Analog     
    }
}




/*** End of File **************************************************************/
