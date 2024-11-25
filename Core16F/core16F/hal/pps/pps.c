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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0      Jamie Starling  Initial Version
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
* Description: Maps a Peripheral Pin Select (PPS) device to a specified output pin, allowing 
*   peripherals like UART, SPI, or PWM to be assigned to different output pins.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to map the peripheral to (e.g., PORTC_4).
*   - PPS_Device (PPSOutputPeripheralEnum_t): The peripheral to map (e.g., PPSOUT_TX1_CK1).
*
*******************************************************************************/
void PPS_MapOutput(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device)
{   
   GPIO_SetDirection(PortPin,OUTPUT);
   *(GPIO_Register_LU[PortPin].pps_output_reg) = PPS_Device;   
}

/******************************************************************************
* Function : PPS_MapBiDirection()
* Description: Maps a Peripheral Pin Select (PPS) device to a specified GPIO pin for 
* bi-directional communication. Configures both input and output registers 
* for peripherals requiring both directions (e.g., I2C, SPI).
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to map (e.g., PORTC_4).
*   - PPS_Device (PPSOutputPeripheralEnum_t): The peripheral to map (e.g., PPSOUT_TX1_CK1).
*   - regPPC_Input_ptr (volatile uint8_t*): Pointer to the PPS input register for mapping.
*
*******************************************************************************/
void PPS_MapBiDirection(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device, volatile uint8_t *regPPC_Input_ptr)
{   
   *(GPIO_Register_LU[PortPin].pps_output_reg) = PPS_Device;
   
    // Check if regPPC_Input_ptr is valid before setting input mapping
    if (regPPC_Input_ptr != NULL)
    {
        *regPPC_Input_ptr = (GPIO_Register_LU[PortPin].pps_inputpin);
    }
}

/******************************************************************************
* Function : PPS_MapInput()
* Description: Maps a GPIO pin to a specified Peripheral Pin Select (PPS) input peripheral,
* allowing the pin to act as an input for peripherals like UART RX or SPI MISO.
*
* Parameters:
*   - PortPin (GPIO_Ports_t): The GPIO pin to map (e.g., PORTC_4).
*   - regPPC_Input_ptr (volatile uint8_t*): Pointer to the PPS input register.
*
*
*******************************************************************************/
void PPS_MapInput(GPIO_Ports_t PortPin, volatile uint8_t *regPPC_Input_ptr)
{
    // Check if regPPC_Input_ptr is valid 
    if (regPPC_Input_ptr != NULL)
    {
        *regPPC_Input_ptr = (GPIO_Register_LU[PortPin].pps_inputpin);
    }
}


/*** End of File **************************************************************/
