/****************************************************************************
* Title                 :   PPS Peripheral Pin Select functions
* Filename              :   pps.c
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
 * Provide Input Mapping
 * 
 * 
*****************************************************************************/

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0      Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "pps.h"
#include "../gpio/gpio.h"


/******************************************************************************
* PPS Interface
*******************************************************************************/
const PPS_Interface_t PPS = {
  .MapOutput = &PPS_MapOutput,
  .MapBiDirection = &PPS_MapBiDirection,
  .MapInput = &PPS_MapInput
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : PPS_MapOutput()
*//** 
* \b Description:
*
* This function maps a Peripheral Pin Select (PPS) device to a specified output pin.
* It allows peripheral modules such as UART, SPI, or PWM to be dynamically mapped to 
* different output pins using the PPS system available on PIC16F series microcontrollers.
*
* The function first configures the specified pin as an output, and then it assigns 
* the selected peripheral device to that pin through the PPS register.
*  
*
* POST-CONDITION: 
*    - The specified GPIO pin will act as the output for the selected PPS peripheral.
* 
* @param[in] PortPin - The GPIO pin to map the peripheral to, specified by the 
*                      `GPIO_Ports_t` type (e.g., PORTC_4, PORTA_1).
* @param[in] PPS_Device - The peripheral to map to the pin, specified by 
*                         `PPSOutputPeripheralEnum_t` (e.g., PPSOUT_TX1_CK1 for UART TX). 	
*
* @return None
*
* \b Example:
* @code
* 
* // Map the UART TX1 output to PORTC pin 4
* PPS_MapOutput(PORTC_4, PPSOUT_TX1_CK1);
* 	
* @endcode
*
* \b Notes:
* - This function maps a peripheral to an output pin. For bi-directional pins, use `PPS_MapBiDirection()`.
* - Ensure that the correct PPS configuration registers are unlocked if needed for your device.
*
* <br><b> - HISTORY OF CHANGES - </b>
* 
* 
* <hr>
*******************************************************************************/
void PPS_MapOutput(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device)
{
   //var that holds the registers of the PPC,
   uint8_t *regPPC_ptr;
   
   //Get the register that controls the PPC
   regPPC_ptr = (uint8_t*) PPS_OutputRegister_LU[PortPin]; 
   
   GPIO_SetDirection(PortPin,OUTPUT);
   
   *regPPC_ptr = PPS_Device;    
}

/******************************************************************************
* Function : PPS_MapBiDirection()
*//** 
* \b Description:
*
* This function maps a Peripheral Pin Select (PPS) device to a specified GPIO pin for 
* bi-directional communication. It allows peripheral modules that require both input 
* and output functionality, such as SPI (MISO/MOSI), or I2C (SDA/SCL), 
* to be dynamically mapped to a GPIO pin using the PPS system on PIC16F series 
* microcontrollers.
*
* The function configures the specified GPIO pin for output and then maps both the 
* input and output registers to the respective peripheral device.
*  
*
* POST-CONDITION: 
*    - The specified GPIO pin will be configured for bi-directional communication 
*      with the selected PPS peripheral.
*
* @param[in] PortPin - The GPIO pin to map for bi-directional communication, specified 
*                      by the `GPIO_Ports_t` type (e.g., PORTC_4, PORTA_1).
* @param[in] PPS_Device - The peripheral to map to the pin, specified by 
*                         `PPSOutputPeripheralEnum_t` (e.g., PPSOUT_TX1_CK1 for UART TX).
* @param[in] regPPC_Input_ptr - A pointer to the PPS input register where the input 
*                               side of the bi-directional pin will be mapped.	
*
* @return None
*
* \b Example:
* @code
* 
* 	
* @endcode
*
* \b Notes:
* - This function handles both input and output mapping for peripherals requiring 
*   bi-directional communication, such as I2C, or SPI.
* - Ensure that the PPS input register pointer is provided correctly for the desired pin.
* - This function should be used for peripherals that need both input and output 
*   functionality (e.g., I2C, SPI MISO/MOSI).
*
* <br><b> - HISTORY OF CHANGES - </b>
* 
* 
* <hr>
*******************************************************************************/
void PPS_MapBiDirection(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device, volatile uint8_t *regPPC_Input_ptr)
{
   //var that holds the registers of the PPC,
   uint8_t *regPPC_ptr;
   
   //Get the register that controls the PPC
   regPPC_ptr = (uint8_t*) PPS_OutputRegister_LU[PortPin];    
   
   *regPPC_ptr = PPS_Device;
   
   // Check if regPPC_Input_ptr is valid before dereferencing
    if (regPPC_Input_ptr != NULL)
    {
        *regPPC_Input_ptr = PPS_InputPin_LU[PortPin];
    }
}

/******************************************************************************
* Function : PPS_MapInput()
*//** 
* \b Description:
*
* This function maps a GPIO pin to a specific Peripheral Pin Select (PPS) input 
* peripheral on PIC16F series microcontrollers. It allows peripheral modules 
* (e.g., UART RX, SPI MISO) to be dynamically mapped to a particular input pin 
* through the PPS system.
*
* The function maps the input register of the specified peripheral to the given 
* GPIO pin, enabling that pin to act as the input for the peripheral.
*  
*
* POST-CONDITION: 
*    - The specified GPIO pin will be mapped as the input to the selected peripheral.
*
* @param[in] PortPin - The GPIO pin to map as the input, specified by the `GPIO_Ports_t` type 
*                      (e.g., PORTC_4, PORTA_1).
* @param[in] regPPC_Input_ptr - A pointer to the PPS input register where the peripheral input 
*                               will be mapped.	
*
* @return None
*
* \b Example:
* @code
* 
* 	
* @endcode
*
* \b Notes:
* - This function only handles input pin mapping. For output or bi-directional mappings, 
*   use `PPS_MapOutput()` or `PPS_MapBiDirection()`.
* - Ensure the correct PPS input register pointer is provided for the desired pin.
*
* <br><b> - HISTORY OF CHANGES - </b>
* 
* 
* <hr>
*******************************************************************************/
void PPS_MapInput(GPIO_Ports_t PortPin, volatile uint8_t *regPPC_Input_ptr)
{
  // Check if regPPC_Input_ptr is valid before dereferencing
    if (regPPC_Input_ptr != NULL)
    {
        *regPPC_Input_ptr = PPS_InputPin_LU[PortPin];
    }
}


/*** End of File **************************************************************/
