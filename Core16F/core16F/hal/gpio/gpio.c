/****************************************************************************
* Title                 :   Core8 GPIO Digital Functions
* Filename              :   gpio.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
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
#include "gpio.h"

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
* This function configures the direction and mode of a specified GPIO pin. It allows 
* the pin to be set as an input, output, input with pull-up resistor, analog input, 
* or open-drain output.
*
* The function dynamically configures the direction, analog functionality, and pull-up 
* resistors based on the provided pin direction and pin configuration. The appropriate 
* register settings for the specified pin are updated accordingly.  
* 
* PRE-CONDITION:  None
*
* POST-CONDITION: The GPIO pin will be configured as per the specified direction (input, output, etc.). 
*
* @param[in] 	PortPin - The GPIO pin to be configured, specified by the `GPIO_Ports_t` type.
* @param[in] PinDirection - The direction and mode for the GPIO pin, specified by 
*                           the `PinDirectionEnum_t` type (INPUT, OUTPUT, INPUT_W_PULLUP, ANALOG, OPEN_DRAIN).
*
* @return None
*
* \b Example:
* @code
* 	
* GPIO_SetDirection(PORTA_0, INPUT);    //Set Port A0 as an input
* GPIO_SetDirection(PORTA_1, OUTPUT);   // Set PORTA pin 1 as an output
* GPIO_SetDirection(PORTA_2, ANALOG);	// Set PORTA pin 2 as an analog input
* GPIO_SetDirection(PORTA_4, INPUT_W_PULLUP);  / Set PORTA pin 4 as an input with pull-up resistor enabled
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void GPIO_SetDirection(GPIO_Ports_t PortPin, PinDirectionEnum_t PinDirection)
{  
   //Variables that holds the registers of the Direction, Analog and PIN BitMask.
   uint8_t *regDirection_ptr, *regAnalog_ptr, pinBitMask, *regODCON_ptr;
   
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin];
   
    //Get the register that controls the direction for the Pin
   regDirection_ptr = (uint8_t*) GPIO_DirectionRegister_LU[PortPin];    
   
   //Get the register that controls the analog for the Pin
   regAnalog_ptr = (uint8_t*) GPIO_AnalogRegister_LU[PortPin];   
          
    //If PIN is to be set as Input - Set the associated Register Bit
   if (PinDirection == INPUT)
    {
       //Set the bit in the Direction Register with OR
        *regDirection_ptr |= pinBitMask;    
        
       //Invert the Pin Mask to clear the Analog Register with AND         
        *regAnalog_ptr &= ~pinBitMask;        
    }
   
   else if (PinDirection == OUTPUT)
   //If PIN is to be set as OUTPUT - Clear the associated Register Bit  
    {
       //Invert the Mask - Clear the bit in the Direction Register and Analog Register
       *regDirection_ptr &= ~pinBitMask; 
       *regAnalog_ptr &= ~pinBitMask;        
    }  
   
   else if (PinDirection == INPUT_W_PULLUP)
   //If PIN is to be set as INPUT with PullUp 
   {
       //Set the bit in the Direction Register with OR
        *regDirection_ptr |= pinBitMask;    
        
       //Invert the Pin Mask to clear the Analog Register with AND         
        *regAnalog_ptr &= ~pinBitMask;   
        
        GPIO_EnableWPUA(PortPin);
    }

    else if (PinDirection == ANALOG)
    //If Pin is to be set as analog input
    {
        //Invert the Mask - Clear the bit in the Direction Register and Set Analog Register
        *regDirection_ptr &= ~pinBitMask;         
        *regAnalog_ptr |= pinBitMask; 
    }
   
   else if (PinDirection == OPEN_DRAIN)
   //If PIN is to be set as OPEN_DRAIN - Clear the associated Register Bit  
    {
       //Invert the Mask - Clear the bit in the Direction Register and Analog Register
       *regDirection_ptr &= ~pinBitMask; 
       *regAnalog_ptr &= ~pinBitMask;
       //Set ODCON Bit
       regODCON_ptr = (uint8_t*) GPIO_ODCONRegister_LU[PortPin];
       *regODCON_ptr |= pinBitMask;
    }  
}

/******************************************************************************
* Function : GPIO_EnableWPUA()
*//** 
* \b Description:
* Local Function
* This function enables the weak pull-up resistor for a specified GPIO pin. 
* Weak pull-up resistors are used to ensure that input pins are pulled to a high 
* logic level (1) when no active driver is connected to the pin. This helps avoid 
* floating inputs, which can cause erratic behavior in the system.
* 
* The function works by setting the corresponding weak pull-up register bit for 
* the given GPIO pin. 
* 
* PRE-CONDITION: Called from GPIO_SetDirection when INPUT_W_PULLUP is Parm 
*
* POST-CONDITION: The weak pull-up resistor will be enabled for the specified GPIO pin.
*
* @param[in] 	
*
* @return 		
*
* \b Example:
* @code
* GPIO_SetDirection(PORTA_0, INPUT_W_PULLUP); 	// Set PORTA pin 0 as an input with pull-up enabled
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

* <hr>
*******************************************************************************/
void GPIO_EnableWPUA (GPIO_Ports_t PortPin)
{
   //var that holds the register of the WeakPull Up and PIN BitMask.
   uint8_t *regWPU_ptr, pinBitMask;
   
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin];
   
    //Get the register that controls the direction for the Pin
   regWPU_ptr = (uint8_t*) GPIO_WPURegister_LU[PortPin];   
    
   //Set the bit in the WPU with OR
        *regWPU_ptr |= pinBitMask;           
}	

/******************************************************************************
* Function : GPIO_WritePortPin()
*//** 
* \b Description:
*
* This function sets the logic level (HIGH or LOW) of a specified GPIO pin. 
* It is typically used to control the output state of a pin that has been 
* configured as an output using the `GPIO_SetDirection()` function.  
* 
* The function writes to the port latch register to set the pin either HIGH 
* (logic 1) or LOW (logic 0) depending on the `PinLevel` argument.
*
* **Usage Notes:**
* - Before calling this function, the target pin must be configured as an OUTPUT 
*   using the `GPIO_SetDirection()` function.
* - This function should only be used for GPIO pins configured as digital outputs.
* - Calling this function on a pin that is not configured as an output will not work 
*   as intended and may result in undefined behavior.
* 
* 
* PRE-CONDITION:  The target GPIO pin must be configured as an output using `GPIO_SetDirection()`.
*
* POST-CONDITION: The logic level (HIGH or LOW) will be applied to the specified GPIO pin.
*
* @param[in] PortPin - The GPIO pin to set the logic level for, specified by the 
*                      `GPIO_Ports_t` type (e.g., PORTA_0, PORTC_1).
* @param[in] PinLevel - The logic level to apply to the pin, specified by 
*                       `LogicEnum_t` (HIGH or LOW).
*	
*
* @return None
*
* \b Example:
* @code
* 	
* GPIO_WritePortPin (PORTA_0,HIGH);  //Turns on Pin A.0
* GPIO_WritePortPin (PORTA_0,LOW);  //Turns off Pin A.0
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void GPIO_WritePortPin (GPIO_Ports_t PortPin, LogicEnum_t PinLevel)
{    
   //var that holds the registers of the Port Write and PIN BitMask.
   uint8_t *regPortWrite_ptr, pinBitMask;
   
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin];
   
   //Get the Port Write Register
   regPortWrite_ptr = (uint8_t*) GPIO_WriteRegister_LU[PortPin]; 
   
    
    //If PIN is to be set HIGH
    if (PinLevel == HIGH)
    {
        //Set the bit in the Latch Register with OR
        *regPortWrite_ptr |= pinBitMask;        
    }
    //Everything else - LOW
    else
    {      
       //Invert the Mask - Clear the bit in the Latch Register with AND
       *regPortWrite_ptr &= ~pinBitMask;         
    }  
}

/******************************************************************************
* Function : GPIO_ReadPortPin()
*//** 
* \b Description:
*
* This function reads the current logic level (HIGH or LOW) from a specified GPIO pin.
* It is typically used to read the state of a pin that has been configured as an input 
* using the `GPIO_SetDirection()` function.
*
* The function checks the pin's value in the port register and returns either a 
* HIGH (logic 1) or LOW (logic 0) value.
* 
* \b Notes:
* - Calling this function on a pin that is not configured as an input may lead to 
*   undefined behavior.
* - Ensure the pin is properly configured as a digital input before reading its value.
* 
* PRE-CONDITION:  The target GPIO pin must be configured as an input using `GPIO_SetDirection()`
*
* POST-CONDITION: The logic level (HIGH or LOW) of the pin is returned.
*
* @param[in] PortPin - The GPIO pin to read the logic level from, specified by the 
*                      `GPIO_Ports_t` type (e.g., PORTA_0, PORTC_1).	
*
* @return LogicEnum_t
*    - HIGH (logic 1) if the pin is at a high voltage level.
*    - LOW (logic 0) if the pin is at a low voltage level.		
*
* \b Example:
* @code
* 	
* LogicEnum_t pinState = GPIO_ReadPortPin(PORTA_0); // Read the logic level of PORTA pin 0
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/

LogicEnum_t GPIO_ReadPortPin(GPIO_Ports_t PortPin)
{        
   //var that holds the registers of the Port Read and PIN BitMask.
   uint8_t *regPortRead_ptr, pinBitMask;
   
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin];
   
   //Get the Port Write Register
   regPortRead_ptr = (uint8_t*) GPIO_ReadRegister_LU[PortPin];
    
   if ((*regPortRead_ptr & pinBitMask) >> 0x00)
   {
       return HIGH;
   }
   else
   {
       return LOW;
   }   
}

/******************************************************************************
* Function : GPIO_TogglePortPin()
*//** 
* \b Description:
*
* This function toggles the logic level of a specified GPIO pin. If the pin is 
* currently HIGH (logic 1), it will be set to LOW (logic 0), and if it is currently 
* LOW (logic 0), it will be set to HIGH (logic 1). This function is typically used 
* to control devices like LEDs or other peripherals where the state needs to alternate.
*
* The function works by performing a bitwise XOR operation on the port latch register 
* to flip the current state of the pin.
*  
* PRE-CONDITION:  
*    - The target GPIO pin must be configured as an output using `GPIO_SetDirection()`.
*
* POST-CONDITION: 
*    - The logic level of the specified GPIO pin is toggled.
*
* @param[in] PortPin - The GPIO pin to toggle, specified by the `GPIO_Ports_t` type 
*                      (e.g., PORTA_0, PORTC_1).	
*
* @return 	None	
*
* \b Example:
* @code
* GPIO_TogglePortPin(PORTA_0); // Toggle the state of PORTA pin 0
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
void GPIO_TogglePortPin(GPIO_Ports_t PortPin)
{
    //var that holds the registers of the Port Write and PIN BitMask.
   uint8_t *regPortWrite_ptr, pinBitMask;
    
   //Get the BitMask of the PIN    
   pinBitMask = GPIO_PinBitMask_LU[PortPin]; 
   
   //Get the Port Write Register
   regPortWrite_ptr = (uint8_t*) GPIO_WriteRegister_LU[PortPin];
   
   //Flip the Bit with XOR
    *regPortWrite_ptr ^= pinBitMask;    
}


/******************************************************************************
* Function : GPIO_Init()
*//** 
* \b Description:
*
* This function initializes the GPIO pins based on a provided configuration table.
* The configuration table contains the settings for each pin, including the pin 
* direction (input or output) and the initial pin level (HIGH or LOW) for output pins.
* 
* This function loops through each entry in the configuration table, sets the pin 
* direction, and, if the pin is configured as an output, sets its initial level.
*
* **Usage Notes:**
* - The configuration table is defined as an array of `GPIO_Config_t` structures, 
*   which contain the pin number, direction, and initial level for each GPIO pin.
* - This function should be called during system initialization to set up all 
*   required GPIO pins.
* - GPIO_Config_t is found in the xxxx_core16F_config.h file in the device folder.
*  
* PRE-CONDITION:  
*    - The configuration table must be defined and passed to the function.
*
* POST-CONDITION: 
*    - All GPIO pins specified in the configuration table are initialized according to 
*      the settings provided.
*
* @param[in] Config - A pointer to the GPIO configuration table (`GPIO_Config_t`), which 
*                     contains the settings for each pin. 	
*
* @return 		
*
* \b Example:
* @code
* 	
* GPIO_Init(GPIO_Config); // Initialize GPIO based on the configuration
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
#ifdef _CORE16F_HAL_GPIO_CONFIG_ENABLE
void GPIO_Init(const GPIO_Config_t* Config)
{
    uint8_t Config_line = 0;
    
    for (Config_line = 0; Config_line < _CORE16F_MAX_GPIO_PORTPIN_COUNT; Config_line++)
    {
       GPIO_SetDirection(Config[Config_line].PortPin,Config[Config_line].Mode);
       
       if (Config[Config_line].Mode == OUTPUT)
       {
           GPIO_WritePortPin(Config[Config_line].PortPin,Config[Config_line].PinLevel);
       }
       
    }    
}
#endif //_CORE16F_HAL_GPIO_CONFIG_ENABLE





/*** End of File **************************************************************/



