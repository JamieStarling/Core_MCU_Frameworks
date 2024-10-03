/****************************************************************************
* Title                 :    Dual Alternating LEDS
* Filename              :  alternating_leds.c
* Author                :   Jamie Starling
* Origin Date           :   2024/10/02
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
  
  GPIO.ModeSet(PORTA_0,OUTPUT);  /*Set PORTA.0 to Output*/
  GPIO.ModeSet(PORTA_1,OUTPUT);  /*Set PORTA.1 to Output*/
  
  /*Set the Initial Pattern*/
  GPIO.PinWrite(PORTA_0,ON);  /*LED on PORTA.0 ON*/
  GPIO.PinWrite(PORTA_1,OFF); /*LED on PORTA.1 OFF*/
  
  while(1) //Program loop
    {      
      CORE.Delay_MS(1000);    //One Second Delay
      GPIO.PinToggle(PORTA_0); //Toggles LED on PORTA_0
      GPIO.PinToggle(PORTA_1); //Toggles LED on PORTA_1      
    }
}




/*** End of File **************************************************************/
