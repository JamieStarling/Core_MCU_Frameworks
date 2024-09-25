/****************************************************************************
* Title                 :   One Wire HAL
* Filename              :   one_wire.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/20
* Version               :   1.0.1
* Compiler              :   XC8 
* Target                :   Microchip PIC16F series 
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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/08/20  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "one_wire.h"

/******************************************************************************
***** ONE WIRE Interface
*******************************************************************************/
const One_Wire_Interface_t ONE_WIRE = {
  .Initialize = &ONE_WIRE_Init,
  .Reset = &ONE_WIRE_Reset,
  .WriteByte =  &ONE_WIRE_Write_Byte,  
  .ReadByte =  &ONE_WIRE_Read_Byte,
  .ReadBit = &ONE_WIRE_Read_Bit
};

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void ONE_WIRE_Drive_Low(void);
void ONE_WIRE_Drive_High(void);
uint8_t ONE_WIRE_Read(void);
void ONE_WIRE_Write_Bit(uint8_t write_bit);
uint8_t ONE_WIRE_Read_Bit(void);

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : ONE_WIRE_Init()
*//** 
* \b Description:
*
* This function initializes the one-wire bus for communication. It configures 
* the one-wire pin by disabling the analog function (if applicable) and setting 
* the pin as an input to prepare it for one-wire communication. This is typically 
* the first step before sending or receiving data on the one-wire bus.
*
* The one-wire pin is defined in the configuration as `OW_DIRECTION_REGISTER`, 
* `OW_PINANALOG_REGISTER`, etc., and is associated with a specific microcontroller pin.
*
* PRE-CONDITION:  
*    - The microcontroller's pin to be used for one-wire communication must be 
*      correctly connected to the one-wire bus and defined in the configuration.
*
* POST-CONDITION: 
*    - The one-wire pin is set as an input, and its analog function (if enabled) 
*      is disabled to allow for digital communication on the bus.
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* 	
* // Initialize the one-wire bus
* ONE_WIRE_Init();
* 	
* @endcode
*
* \b Notes:
* - The one-wire bus must be initialized before performing any read or write operations.
* - This function configures the pin for digital input by disabling the analog feature.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void ONE_WIRE_Init(void)
{
  OW_PINANALOG_REGISTER = 0;  //turn off analog  
  OW_DIRECTION_REGISTER = 1;  //set pin as input
}


/******************************************************************************
* Function : ONE_WIRE_Reset()
*//** 
* \b Description:
*
* This function sends a **reset pulse** on the one-wire bus and waits for a **presence pulse**
* from any devices connected to the bus. The reset pulse is used to signal the start of communication
* and to synchronize with slave devices. The function drives the bus low for the required reset time,
* then releases the bus and waits for a response.
*
* The function returns a status indicating whether any devices are present on the bus. If a device 
* responds with a presence pulse, the function returns `DEVICE_PRESENT`. If no devices respond, 
* the function returns `NO_DEVICE`.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*    - The one-wire bus must be connected to at least one slave device.
*
* POST-CONDITION: 
*    - A reset pulse is sent, and the function waits for a presence pulse from the slave device(s).
*
* @param[in] None
*
* @return LogicEnum_t
*    - `DEVICE_PRESENT` if one or more devices responded with a presence pulse.
*    - `NO_DEVICE` if no devices responded to the reset pulse.		
*
* \b Example:
* @code
* 	
* // Send a reset pulse and check for devices on the one-wire bus
* LogicEnum_t status = ONE_WIRE_Reset();
*
* if (status == DEVICE_PRESENT) {
*     // One or more devices are present on the bus
* } else {
*     // No devices found on the bus
* }
* 	
* @endcode
*
* \b Notes:
* - The reset pulse ensures that all devices on the one-wire bus are synchronized and ready for communication.
* - Devices on the bus respond with a presence pulse, signaling that they are ready for communication.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
LogicEnum_t ONE_WIRE_Reset(void)
{
    
  ONE_WIRE_Drive_Low(); 
  __delay_us(ONE_WIRE_RESET_DELAY_US); // wait for 480us+

  ONE_WIRE_Drive_High();    
  __delay_us(ONE_WIRE_RESET_DELAY_DRIVE_HIGH_US);

  uint8_t response = ONE_WIRE_Read();
  __delay_us(ONE_WIRE_RESET_DELAY_READ_US); 

  ONE_WIRE_Drive_High(); 
  
  if (response == 0) {return NO_DEVICE;}
  return DEVICE_PRESENT;  
}

/******************************************************************************
* Function : ONE_WIRE_Drive_Low()
*//** 
* \b Description:
*
* This function drives the one-wire bus **low** by setting the one-wire pin as an output and 
* pulling it to a low logic level (0V). This is typically used to initiate communication 
* on the one-wire bus, such as sending a reset pulse or writing data bits.
*
* The function sets the direction register to output (`OW_DIRECTION_REGISTER = 0`) and sets the 
* pin driver to low (`OW_PINDRIVER_REGISTER = 0`), pulling the bus to ground.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*
* POST-CONDITION: 
*    - The one-wire pin is driven low, pulling the bus to ground.
*
* @param[in] None
*
* @return None		
*
* \b Example:
* @code
* 	
* // Drive the one-wire bus low
* ONE_WIRE_Drive_Low();
* 	
* @endcode
*
* \b Notes:
* - This function is typically followed by a delay to ensure the bus stays low for the required 
*   time before being released or driven high.
* - Driving the bus low is a fundamental operation for one-wire communication, used in reset pulses, 
*   writing bits, and other bus operations.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void ONE_WIRE_Drive_Low(void)
{
  OW_DIRECTION_REGISTER = 0;
  OW_PINDRIVER_REGISTER = 0;  
}

/******************************************************************************
* Function : ONE_WIRE_Drive_High()
*//** 
* \b Description:
*
* This function drives the one-wire bus **high** by setting the one-wire pin as an output and 
* pulling it to a high logic level (typically 5V or 3.3V). This is typically used after 
* driving the bus low, such as when completing a reset pulse or after writing data bits.
*
* The function sets the direction register to output (`OW_DIRECTION_REGISTER = 0`) and sets the 
* pin driver to high (`OW_PINDRIVER_REGISTER = 1`), releasing the bus to a high logic level.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*
* POST-CONDITION: 
*    - The one-wire pin is driven high, pulling the bus to a high logic level.
*
* @param[in] None	
*
* @return None	
*
* \b Example:
* @code
* 	
* // Drive the one-wire bus high
* ONE_WIRE_Drive_High();
* 	
* @endcode
*
* \b Notes:
* - This function is typically called after driving the bus low, to release the bus and allow 
*   the pull-up resistor or connected devices to maintain a high logic level.
* - Driving the bus high is a fundamental part of one-wire communication, used in reset pulses, 
*   writing bits, and other bus operations.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void ONE_WIRE_Drive_High(void)
{
  OW_DIRECTION_REGISTER = 0;
  OW_PINDRIVER_REGISTER = 1;  
}

/******************************************************************************
* Function : ONE_WIRE_Read()
*//** 
* \b Description:
*
* This function reads the current logic level of the one-wire bus. It sets the one-wire 
* pin as an input and reads the pin state, returning `1` if the bus is high (logic 1) 
* or `0` if the bus is low (logic 0). This is typically used to check for the presence 
* of a device on the bus or to read bits from a slave device during data transmission.
*
* The function sets the direction register to input (`OW_DIRECTION_REGISTER = 1`) 
* and reads the pin state using the `OW_PINREAD_REGISTER`.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*    - The bus should be in a state where it is expected to be read, typically after 
*      a delay following a low pulse.
*
* POST-CONDITION: 
*    - The logic level of the one-wire bus is read and returned as `1` (high) or `0` (low).
*
* @param[in] None
*
* @return uint8_t
*    - `1` if the one-wire bus is high (logic 1).
*    - `0` if the one-wire bus is low (logic 0).
*
* \b Example:
* @code
* 	
* // Read the current state of the one-wire bus
* uint8_t bus_state = ONE_WIRE_Read();
*
* if (bus_state == 1) {
*     // Bus is high
* } else {
*     // Bus is low
* }
* 	
* @endcode
*
* \b Notes:
* - This function is commonly used during one-wire communication to check the state of the bus.
* - Ensure that the pin is correctly configured as an input before reading the bus state.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t ONE_WIRE_Read(void)
{
  uint8_t one_wire_data = 0;
  
  OW_DIRECTION_REGISTER = 1;
  
  //if (HIGH == GPIO_ReadPortPin(PORTA_0)){one_wire_data = 1;}
  if (OW_PINREAD_REGISTER){one_wire_data = 1;}
  else {one_wire_data = 0;}
  return one_wire_data;  
}

/******************************************************************************
* Function : ONE_WIRE_Write_Bit()
*//** 
* \b Description:
*
* <DESCRIPTION>
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
void ONE_WIRE_Write_Bit(uint8_t write_bit)
{
  if (write_bit)  //Write 1 to buss
    {
      ONE_WIRE_Drive_Low();
      __delay_us(ONE_WIRE_WRITE_BIT_1_DELAY_DRIVE_LOW_US);
      ONE_WIRE_Drive_High();
      __delay_us(ONE_WIRE_WRITE_BIT_1_DELAY_DRIVE_HIGH_US);      
    }
  else  //Write 0 to buss
    {
       ONE_WIRE_Drive_Low();
       __delay_us(ONE_WIRE_WRITE_BIT_0_DELAY_DRIVE_LOW_US);
       ONE_WIRE_Drive_High();
       __delay_us(ONE_WIRE_WRITE_BIT_0_DELAY_DRIVE_HIGH_US);      
    }
}

/******************************************************************************
* Function : ONE_WIRE_Read_Bit()
*//** 
* \b Description:
*
* This function writes a single bit (either 0 or 1) to the one-wire bus. The bit is written 
* according to the one-wire protocol, where writing a `1` involves pulling the bus low for 
* a short period followed by releasing it, and writing a `0` involves pulling the bus low for 
* a longer period. The function controls the timing of the pulse based on the value of the bit.
*
* A `1` is written by driving the bus low for a shorter time (`6µs`) and then releasing the bus.
* A `0` is written by driving the bus low for a longer time (`60µs`), then releasing the bus.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*
* POST-CONDITION: 
*    - The specified bit (`0` or `1`) is written to the one-wire bus.
*
* @param[in] write_bit - The bit to be written to the one-wire bus (either `0` or `1`).
*
* @return void
*
* \b Example:
* @code
* 	
* // Write a '1' bit to the one-wire bus
* ONE_WIRE_Write_Bit(1);
*
* // Write a '0' bit to the one-wire bus
* ONE_WIRE_Write_Bit(0);
* 	
* @endcode
*
* - The timing for writing bits is critical and follows the one-wire protocol specifications.
* - Writing a bit involves pulling the bus low for a specific amount of time and then releasing it.
* - Ensure that the one-wire bus is ready for writing before calling this function.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t ONE_WIRE_Read_Bit(void)
{
  uint8_t one_wire_data = 0;
  //reading a bit 
  ONE_WIRE_Drive_Low();
  __delay_us(ONE_READ_BIT_DELAY_DRIVE_LOW_US);
  //ONE_WIRE_High();
  OW_DIRECTION_REGISTER = 1;
  __delay_us(ONE_READ_BIT_DELAY_DRIVE_HIGH_US);
  
  one_wire_data = ONE_WIRE_Read();
  
   __delay_us(ONE_READ_BIT_DELAY_END_US);
   return one_wire_data;
}

/******************************************************************************
* Function : ONE_WIRE_Write_Byte()
*//** 
* \b Description:
*
* This function writes a full byte of data to the one-wire bus by sending each bit 
* sequentially, starting with the least significant bit (LSB). It calls the 
* `ONE_WIRE_Write_Bit()` function to transmit each bit, ensuring that the correct 
* timing and protocol are followed for one-wire communication.
*
* The byte is shifted right after each bit is written, so the next bit can be sent. 
* This process continues for all 8 bits of the byte, sending the LSB first and the 
* most significant bit (MSB) last.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*
* POST-CONDITION: 
*    - The full byte of data is written to the one-wire bus, one bit at a time.
*
* @param[in] data - The byte of data to be transmitted to the one-wire bus.
*
* @return void		
*
* \b Example:
* @code
* 	
* // Write the byte 0xA5 (binary: 10100101) to the one-wire bus
* ONE_WIRE_Write_Byte(0xA5);
* 	
* @endcode
*
* \b Notes:
* - This function sends the least significant bit (LSB) first, followed by the remaining bits.
* - Ensure that the one-wire bus is ready for communication before calling this function.
* - The function internally calls `ONE_WIRE_Write_Bit()` for each bit in the byte.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void ONE_WIRE_Write_Byte(uint8_t data)
{
  uint8_t loop_counter;
  
  for (loop_counter = 0; loop_counter < 8; loop_counter++)
    {
      ONE_WIRE_Write_Bit(data & 0x01); //Sending LS-bit first
      data >>= 1; // shift the data byte for the next bit to send
    }
  
}

/******************************************************************************
* Function : ONE_WIRE_Read_Byte()
*//** 
* \b Description:
*
* This function reads a full byte of data from the one-wire bus by receiving each bit 
* sequentially, starting with the least significant bit (LSB). It calls the 
* `ONE_WIRE_Read_Bit()` function to receive each bit and assembles them into a byte.
*
* The function shifts the received byte right after each bit is read, preparing it for the 
* next bit to be inserted. This process continues for all 8 bits of the byte, reading 
* the LSB first and the most significant bit (MSB) last.
*
* PRE-CONDITION:  
*    - The one-wire bus must be initialized using `ONE_WIRE_Init()`.
*    - A start condition or previous operation must have been performed to signal the start of communication.
*
* POST-CONDITION: 
*    - A full byte of data is read from the one-wire bus, one bit at a time.
*
* @param[in] None
*
* @return uint8_t
*    - The byte of data received from the one-wire bus.		
*
* \b Example:
* @code
* 	
* // Read a byte of data from the one-wire bus
* uint8_t received_data = ONE_WIRE_Read_Byte();
*
* // Process the received data
* 	
* @endcode
*
* \b Notes:
* - This function reads the least significant bit (LSB) first, followed by the remaining bits.
* - Ensure that the one-wire bus is in a state where it can receive data before calling this function.
* - The function internally calls `ONE_WIRE_Read_Bit()` for each bit in the byte.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t ONE_WIRE_Read_Byte(void)
{
  uint8_t loop_counter, result = 0;
  
  for (loop_counter = 0; loop_counter < 8; loop_counter++)
	{		
		result >>= 1; 				// shift the result to get it ready for the next bit to receive
		if (ONE_WIRE_Read_Bit()){result |= 0x80;} // if result is one, then set MS-bit						
	}
	return result;  
}


/*** End of File **************************************************************/
