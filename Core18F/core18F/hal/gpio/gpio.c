/****************************************************************************
* Title                 :   Core MCU GPIO Digital Functions
* Filename              :   gpio.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   Microchip PIC18F series 
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
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "gpio.h"

/******************************************************************************
* Interface
*******************************************************************************/
const GPIO_Interface_t GPIO = {
  .ModeSet = &GPIO_SetDirection,
  .PinWrite = &GPIO_WritePortPin,
  .PinToggle = &GPIO_TogglePortPin,
  .PinRead =  &GPIO_ReadPortPin
};

/******************************************************************************
***** Local Function Prototypes
*******************************************************************************/
void GPIO_EnableWPUA (GPIO_Ports_t PortPin);

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : GPIO_SetDirection()
*//** 
* \b Description:
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to configure.
*   - PinDirection (PinDirectionEnum_t): The desired pin direction or mode.
* 
*- HISTORY OF CHANGES -
* 1.0.3 Corrected ANALOG Direction Set
* 1.0.4 Replaced multiple if-else blocks with switch statement
*******************************************************************************/
void GPIO_SetDirection(GPIO_Ports_t PortPin, PinDirectionEnum_t PinDirection)
{           
  switch (PinDirection) {
    case INPUT:      //If PIN is to be set as Input - Set the associated Register Bit
        *(GPIO_Register_LU[PortPin].direction_reg) |= (GPIO_Register_LU[PortPin].pinmask);    //Set the bit in the Direction Register with OR       
        *(GPIO_Register_LU[PortPin].analog_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);     //Invert the Pin Mask to clear the Analog Register with AND                
        break;
       
    case OUTPUT:    //If PIN is to be set as OUTPUT - Clear the associated Register Bit  
        *(GPIO_Register_LU[PortPin].direction_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);  //Invert the Mask - Clear the bit in the Direction Register and Analog Register
        *(GPIO_Register_LU[PortPin].analog_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);
        break;
    
    case INPUT_W_PULLUP:   //If PIN is to be set as INPUT with PullUp 
       *(GPIO_Register_LU[PortPin].direction_reg) |= (GPIO_Register_LU[PortPin].pinmask);   //Set the bit in the Direction Register with OR
       *(GPIO_Register_LU[PortPin].analog_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);     //Invert the Pin Mask to clear the Analog Register with AND  
       GPIO_EnableWPUA(PortPin);
       break;
       
    case ANALOG: //If Pin is to be set as analog input
       *(GPIO_Register_LU[PortPin].direction_reg) |= (GPIO_Register_LU[PortPin].pinmask);  //Set the bit in the Direction Register with OR Along with Analog  
       *(GPIO_Register_LU[PortPin].analog_reg) |= (GPIO_Register_LU[PortPin].pinmask);
       break;
       
    case OPEN_DRAIN: //If PIN is to be set as OPEN_DRAIN - Clear the associated Register Bit
       *(GPIO_Register_LU[PortPin].direction_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);  //Invert the Mask - Clear the bit in the Direction Register and Analog Register
       *(GPIO_Register_LU[PortPin].analog_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);       
       *(GPIO_Register_LU[PortPin].odcon_reg) |= (GPIO_Register_LU[PortPin].pinmask);
       break;
       
    default:
        break;      
    }     
}

/******************************************************************************
* Function : GPIO_EnableWPUA()
* Description: Enables the weak pull-up resistor for a specified GPIO pin by setting the 
* appropriate bit in the weak pull-up register.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to enable the pull-up for.
*******************************************************************************/
void GPIO_EnableWPUA (GPIO_Ports_t PortPin)
{      
   *(GPIO_Register_LU[PortPin].wpu_reg) |= (GPIO_Register_LU[PortPin].pinmask); //Set the bit in the WPU with OR          
}	

/******************************************************************************
* Function : GPIO_WritePortPin()
*//** 
* \b Description:
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to set (e.g., PORTA_0, PORTC_1).
*   - PinLevel (LogicEnum_t): The logic level to apply (HIGH or LOW).
*
*******************************************************************************/
void GPIO_WritePortPin (GPIO_Ports_t PortPin, LogicEnum_t PinLevel)
{    
   if (PinLevel == HIGH) //If PIN is to be set HIGH
    {
       *(GPIO_Register_LU[PortPin].write_reg) |= (GPIO_Register_LU[PortPin].pinmask);  //Set the bit in the Latch Register with OR
    }    
   else //Everything else set- LOW
    {
       *(GPIO_Register_LU[PortPin].write_reg) &= ~(GPIO_Register_LU[PortPin].pinmask);  //Invert the Mask - Clear the bit in the Latch Register with AND       
    }  
}

/******************************************************************************
* Function : GPIO_ReadPortPin()
*//** 
* \b Description:
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to read (e.g., PORTA_0, PORTC_1).
*
* Returns:
*   - LogicEnum_t: HIGH (logic 1) if the pin is high, LOW (logic 0) if the pin is low.
*******************************************************************************/
LogicEnum_t GPIO_ReadPortPin(GPIO_Ports_t PortPin)
{     
   return (*(GPIO_Register_LU[PortPin].read_reg) & (GPIO_Register_LU[PortPin].pinmask)) ? HIGH : LOW;   
}

/******************************************************************************
* Function : GPIO_TogglePortPin()
* Description:Toggles the logic level of a specified GPIO pin. If the pin is HIGH, it will
* be set to LOW, and if it is LOW, it will be set to HIGH.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to toggle (e.g., PORTA_0, PORTC_1).
*******************************************************************************/
void GPIO_TogglePortPin(GPIO_Ports_t PortPin)
{    
   *(GPIO_Register_LU[PortPin].write_reg) ^= (GPIO_Register_LU[PortPin].pinmask);    //Flip the Bit with XOR
}

/******************************************************************************
* Function : GPIO_Init()
* Description: Initializes GPIO pins based on a provided configuration table, setting each 
* pin's direction and initial level as specified.
*
* Parameters:
*   - Config (const GPIO_Config_t*): Pointer to the GPIO configuration table, 
*     which contains settings for each pin.
*******************************************************************************/
#ifdef _CORE18F_HAL_GPIO_CONFIG_ENABLE
void GPIO_Init(const GPIO_Config_t* Config)
{
    uint8_t Config_line = 0;
    
    for (Config_line = 0; Config_line < _CORE18F_MAX_GPIO_PORTPIN_COUNT; Config_line++)
    {
       GPIO_SetDirection(Config[Config_line].PortPin,Config[Config_line].Mode);
       
       if (Config[Config_line].Mode == OUTPUT)
       {
           GPIO_WritePortPin(Config[Config_line].PortPin,Config[Config_line].PinLevel);
       }
       
    }    
}
#endif //_CORE18F_HAL_GPIO_CONFIG_ENABLE





/*** End of File **************************************************************/



