/****************************************************************************
* Title                 :   RGB LED Driver (4 Pin LEDs)
* Filename              :   led_rgb.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/26
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

/*************** TODO *********************************************************
 * 
 * 
 * 
*****************************************************************************/


/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "led_rgb.h"

/******************************************************************************
* Constants
*******************************************************************************/


/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : LED_RGB_Init()
*//** 
* \b Description:
*
* Init for the RGB LED - Call First
*  
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
*
* @return 		
*
* \b Example:
* @code
* 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void LED_RGB_Init(void)
{  
   LED_RGB_RED_PWM_CHANNEL_INIT(LED_RGB_RED_PWM_CHANNEL_PIN,PWM32Mhz_8bit);
   LED_RGB_GREEN_PWM_CHANNEL_INIT(LED_RGB_GREEN_PWM_CHANNEL_PIN,PWM32Mhz_8bit);
   LED_RGB_BLUE_PWM_CHANNEL_INIT(LED_RGB_BLUE_PWM_CHANNEL_PIN,PWM32Mhz_8bit);  
}


/******************************************************************************
* Function : LED_RGB_Write_Value()
*//** 
* \b Description:
*
* Writes a RGB value to the PWM channels used for the RGB LED
*  
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
*
* @return 		
*
* \b Example:
* @code
* 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void LED_RGB_Write_Value(uint8_t red,uint8_t green,uint8_t blue)
{
  LED_RGB_RED_PWM_DUTYSET(red);
  LED_RGB_GREEN_PWM_DUTYSET(green);
  LED_RGB_BLUE_PWM_DUTYSET(blue);
}

/******************************************************************************
* Function : LED_RGB_Write_Color()
*//** 
* \b Description:
*
* Writes a Color value to the PWM channels based on a color lookup 
*  
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
*
* @return 		
*
* \b Example:
* @code
* 	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void LED_RGB_Write_Color(LED_RGB_Color_Values_t RGB_Color)
{
  LED_RGB_Write_Value(LED_RGB_COLOR[RGB_Color].RedValue,
                      LED_RGB_COLOR[RGB_Color].GreenValue,
                      LED_RGB_COLOR[RGB_Color].BlueValue);
}

/*** End of File **************************************************************/
