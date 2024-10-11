/****************************************************************************
* Title                 :   Core8 GPIO Functions
* Filename              :   i2c.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
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
 * -MASTER_I2C1_Init(), Make configurable
 * -Add Timeout to wait functions. 
 * 
 * 
*****************************************************************************/


/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/08/15  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "i2c1.h"


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MASTER_I2C1_Reset(void);
void I2C1_Clear_Interrupt(void);
bool I2C1_IsBusy(void);
bool I2C1_Wait_Until_Complete(void);
/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : MASTER_I2C1_Init()
*//** 
* \b Description:
*
* This function initializes the I2C1 module in master mode for communication on 
* the I2C bus. It sets the appropriate I2C pins, configures the I2C clock speed, 
* and enables the I2C1 module. The function uses the Peripheral Pin Select (PPS) 
* system to map the I2C data (SDA) and clock (SCL) lines to the specified GPIO pins.
*
* The function also sets the I2C clock frequency using the `SSP1ADD` register, 
* configures the I2C control and status registers, and ensures that the I2C1 module 
* is ready for communication with I2C slave devices.
*
* PRE-CONDITION:  
*    - The SDA and SCL lines must be connected to the appropriate I2C devices and 
*      pulled high with resistors (typically 4.7k? or 10k?).
*
* POST-CONDITION: 
*    - The I2C1 module is initialized and ready for communication in master mode.
*
* @param[in] None	
*
* @return None	
*
* \b Example:
* @code
* // Initialize the I2C1 module in master mode
* MASTER_I2C1_Init();	
*
* 	
* @endcode
*
* \b Notes:
* - The I2C clock speed is set by the `SSP1ADD` register, which divides the system clock. 
*   In this case, `SSP1ADD` is set to 0x4F, corresponding to a clock speed suitable 
*   for standard I2C operation 100Kbits.
* - The function maps the SDA and SCL pins using the PPS system and configures them 
*   as inputs to allow proper I2C communication.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void MASTER_I2C1_Init(void)
{
  GPIO_SetDirection(I2C1_CLOCK_PIN,INPUT);
  GPIO_SetDirection(I2C1_DATA_PIN,INPUT);  
 
  PPS_MapBiDirection(I2C1_CLOCK_PIN,PPSOUT_SCK1_SCL1,&SSP1CLKPPS);
  PPS_MapBiDirection(I2C1_DATA_PIN,PPSOUT_SDO1_SDA1,&SSP1DATPPS);
    
  /* CKE disabled; SMP Standard Speed;  */
  SSP1STAT = 0x80;
  /* SSPM FOSC/4_SSPxADD_I2C; CKP disabled; SSPEN disabled; SSPOV no_overflow; WCOL no_collision;  */
  SSP1CON1 = 0x8;
  /* SEN disabled; RSEN disabled; PEN disabled; RCEN disabled; ACKEN disabled; ACKDT acknowledge; GCEN disabled;  */
  SSP1CON2 = 0x0;
  /* DHEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; BOEN disabled; SCIE disabled; PCIE disabled;  */
  SSP1CON3 = 0x0;
  SSP1CON1bits.SSPM = 0b1000;
  /* SSPADD 79;  */
  SSP1ADD = 0x4F;    
  SSP1CON1bits.SSPEN = 1;
  MASTER_I2C1_Reset();
}


/******************************************************************************
* Function : MASTER_I2C1_Reset()
*//** 
* \b Description:
*
* This function resets the I2C1 module in master mode. It disables the I2C1 module, 
* clears any overflows or write collisions, and flushes the buffer. It also clears 
* the MSSP1 interrupt flag to ensure the I2C bus is reset to a known state.
*
* After performing these actions, the function re-enables the I2C1 module to allow 
* it to resume normal operation.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized using `MASTER_I2C1_Init()` before calling this function.
*    - The function should be called to recover from error states such as bus collision or buffer overflow.
*
* POST-CONDITION: 
*    - The I2C1 module is reset and re-enabled, and the I2C bus is ready for normal operation.
*
* @param[in] None	
*
* @return None	
*
* \b Example:
* @code
* 	
* // Reset the I2C1 module in case of error
* MASTER_I2C1_Reset();
* 	
* @endcode
*
* \b Notes:
* - This function is typically used when there is an I2C bus error, such as a collision or overflow, 
*   and the I2C module needs to be reset to recover.
* - The function flushes the buffer and clears the necessary flags to ensure a clean state.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void MASTER_I2C1_Reset(void)
{
  char temp;
  SSP1CON1bits.SSPEN = 0;
  temp = SSP1BUF;
  SSP1CON1bits.WCOL = 0;  
  I2C1_Clear_Interrupt();  //Clear SSP1IF
  __delay_ms(25);
  SSP1CON1bits.SSPEN = 1;
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Start_Bit_BLOCKING()
*//** 
* \b Description:
*
* This function sends a **start condition** on the I2C bus using the I2C1 module in master mode.
* The start condition is used to indicate the beginning of communication on the I2C bus, 
* signaling that the master is about to initiate a data transfer with a slave device.
*
* The function is **blocking**, meaning it waits until the start condition is complete 
* by checking the `SSP1IF` flag (MSSP1 interrupt flag). It clears the interrupt flag before 
* and after the start condition to ensure a clean I2C operation.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and configured as a master using `MASTER_I2C1_Init()`.
*
* POST-CONDITION: 
*    - A start condition is successfully sent on the I2C bus, allowing the master to proceed 
*      with sending an address or data to a slave device.
*
* @param[in] None	
*
* @return None	
*
* \b Example:
* @code
* 	
* // Send a start condition on the I2C bus
* MASTER_I2C1_Send_Start_Bit_BLOCKING();
* 	
* @endcode
*
* \b Notes:
* - The function is blocking, meaning it waits until the start condition is fully transmitted 
*   before proceeding with further operations.
* - After the start condition, the master can proceed with sending an address using 
*   `MASTER_I2C1_Send_Address_BLOCKING()` or other data transmission functions. 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void MASTER_I2C1_Send_Start_Bit_BLOCKING(void)
{
  //sends start bit, waits to complete by checking IF flag
   I2C1_Clear_Interrupt();  //Clear SSP1IF  
   SSP1CON2bits.SEN = 1;
   I2C1_Wait_Until_Complete(); //wait until complete
   I2C1_Clear_Interrupt();  //Clear SSP1IF      
}


/******************************************************************************
* Function : MASTER_I2C1_Send_Address_BLOCKING()
*//** 
* \b Description:
*
* This function sends a 7-bit slave address on the I2C bus, followed by a read or write bit.
* It is used to initiate communication with a specific slave device on the I2C bus after the 
* start condition has been transmitted. The function waits for the transmission to complete 
* before proceeding, making it **blocking**.
*
* The slave address is shifted left by 1 bit, and the read/write bit is appended to the 
* least significant bit (LSB). The function checks for acknowledgment (ACK) from the 
* slave device and returns a status indicating whether the address was acknowledged.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized using `MASTER_I2C1_Init()`.
*    - A start condition must be sent using `MASTER_I2C1_Send_Start_Bit_BLOCKING()` 
*      before calling this function.
*
* POST-CONDITION: 
*    - The slave address is transmitted on the I2C bus, and the function returns the 
*      status indicating whether the address was acknowledged by the slave.
*
* @param[in] address - The 7-bit I2C slave address to be transmitted.
* @param[in] address_mode - A value of type `I2C_Address_Mode_Enum_t` that specifies 
*                           whether the address is followed by a read (`I2C_ADDRESS_READ_MODE`) 
*                           or a write (`I2C_ADDRESS_WRITE_MODE`) operation.
*
* \return I2C_Status_Enum_t
*    - `I2C_ADDRESS_VALID_WRITE` if the address was acknowledged in write mode.
*    - `I2C_ADDRESS_VALID_READ` if the address was acknowledged in read mode.
*    - `I2C_ADDRESS_INVALID` if the address was not acknowledged by the slave device.		
*
* \b Example:
* @code
* 	
* // Send a write address to the slave with address 0x27
* I2C_Status_Enum_t status = MASTER_I2C1_Send_Address_BLOCKING(0x27, I2C_ADDRESS_WRITE_MODE);
*
* // Check if the address was acknowledged
* if (status == I2C_ADDRESS_VALID_WRITE) {
*     // Proceed with data transmission
* }
* 	
* @endcode
*
* \b Notes:
* - The function waits for the transmission to complete and checks for the slave?s acknowledgment.
* - After the address is successfully transmitted and acknowledged, data can be sent or received 
*   depending on the operation mode (read/write).
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
I2C_Status_Enum_t MASTER_I2C1_Send_Address_BLOCKING(uint8_t address, I2C_Address_Mode_Enum_t address_mode)
{
  if (address_mode) //Set if we are receiving data
    {
      SSP1BUF = (uint8_t)(address << 1 | 1);  
    }
  else
    {
     SSP1BUF = (uint8_t)(address << 1);   
    }
  
  I2C1_Wait_Until_Complete(); //Wait until complete
  I2C1_Clear_Interrupt();  //Clear SSP1IF
  
  //return true if address is ACKed other wise false
  if (!SSP1CON2bits.ACKSTAT && address_mode == I2C_ADDRESS_WRITE_MODE)
    {return I2C_ADDRESS_VALID_WRITE;}
  
  if (!SSP1CON2bits.ACKSTAT && address_mode == I2C_ADDRESS_READ_MODE)
    {return I2C_ADDRESS_VALID_READ;}
    
  else{return I2C_ADDRESS_INVALID;}  
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Stop_BLOCKING()
*//** 
* \b Description:
*
* This function sends a **stop condition** on the I2C bus using the I2C1 module in master mode.
* A stop condition signals the end of communication with the slave device and releases 
* the I2C bus, allowing other devices to initiate communication.
*
* The function is **blocking**, meaning it waits for the stop condition to complete by 
* checking the MSSP1 interrupt flag (`SSP1IF`). It ensures that the stop condition is 
* fully transmitted before continuing with further operations.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and configured as a master using `MASTER_I2C1_Init()`.
*    - The master must have initiated a start condition and completed data transmission 
*      or reception with the slave before calling this function.
*
* POST-CONDITION: 
*    - A stop condition is sent on the I2C bus, and the I2C bus is released for other devices.
*
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* 	
* // Send a stop condition on the I2C bus after communication is complete
* MASTER_I2C1_Send_Stop_BLOCKING();
* 	
* @endcode
*
* \b Notes:
* - This function is blocking, meaning it waits until the stop condition is fully transmitted 
*   before returning control to the calling function.
* - The stop condition signals the completion of communication on the I2C bus and is typically 
*   sent after addressing and data transmission.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void MASTER_I2C1_Send_Stop_BLOCKING(void)
{
   SSP1CON2bits.PEN = 1;
   I2C1_Wait_Until_Complete(); //wait until complete
   I2C1_Clear_Interrupt();  //Clear SSP1IF  
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Byte_BLOCKING()
*//** 
* \b Description:
*
* This function sends a single byte of data on the I2C bus using the I2C1 module in master mode.
* The function waits until the transmission is complete by checking the MSSP1 interrupt flag (`SSP1IF`), 
* making it **blocking**. Once the byte is transmitted, the function checks for an acknowledgment (ACK) 
* from the slave device.
*
* The function returns a status code indicating whether the byte was acknowledged by the slave. 
* An acknowledgment means the slave device received the byte, while no acknowledgment (NACK) indicates 
* that the slave did not acknowledge the data.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and configured as a master using `MASTER_I2C1_Init()`.
*    - A start condition and a valid slave address should be sent before calling this function.
*
* POST-CONDITION: 
*    - The byte is transmitted on the I2C bus, and the function returns whether the slave acknowledged the byte.
*
* @param[in] data - The byte of data to be transmitted to the slave.
*
* @return I2C_Status_Enum_t
*    - `I2C_ACK_RECEIVED` if the byte was acknowledged by the slave.
*    - `I2C_NO_ACK_RECEIVED` if the byte was not acknowledged by the slave.		
*
* \b Example:
* @code
* 	
* // Send a byte of data (0x56) to the slave device
* I2C_Status_Enum_t status = MASTER_I2C1_Send_Byte_BLOCKING(0x56);
*
* // Check if the byte was acknowledged
* if (status == I2C_ACK_RECEIVED) {
*     // The slave acknowledged the byte
* } else {
*     // No acknowledgment received from the slave
* }
* 	
* @endcode
*
* \b Notes:
* - The function is blocking, meaning it waits for the byte transmission to complete and checks the acknowledgment before returning.
* - Use this function in I2C communication to send individual bytes of data to a slave device.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
I2C_Status_Enum_t MASTER_I2C1_Send_Byte_BLOCKING(uint8_t data)
{
  SSP1BUF = data;  
  I2C1_Wait_Until_Complete(); //wait until complete
  I2C1_Clear_Interrupt();  //Clear SSP1IF
  //return true if data is ACKed other wise false
  if (!SSP1CON2bits.ACKSTAT){return I2C_ACK_RECEIVED;}
  else{return I2C_NO_ACK_RECEIVED;}    
}

/******************************************************************************
* Function : MASTER_I2C1_Send_DataBlock_BLOCKING()
*//** 
* \b Description:
*
* This function sends a block of data (an array of bytes) on the I2C bus using the I2C1 module in master mode.
* It transmits each byte in the data block sequentially and waits for the transmission of each byte to complete 
* by checking the MSSP1 interrupt flag (`SSP1IF`), making it **blocking**. For each byte, the function also 
* checks for an acknowledgment (ACK) from the slave device.
*
* The function continues to send the data block until all bytes are transmitted or until a byte is not acknowledged 
* by the slave. The function returns the status indicating whether the entire data block was successfully transmitted.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized using `MASTER_I2C1_Init()`.
*    - A start condition and a valid slave address must be sent before calling this function.
*
* POST-CONDITION: 
*    - The block of data is transmitted on the I2C bus, and the function returns the transmission status based on 
*      whether all bytes were acknowledged by the slave.
*
* @param[in] datablock - A pointer to the data block (array of bytes) to be transmitted.
* @param[in] data_length - The number of bytes to be transmitted from the data block.
*
* @return I2C_Status_Enum_t
*    - `I2C_ACK_RECEIVED` if the entire block was acknowledged by the slave.
*    - `I2C_NO_ACK_RECEIVED` if a byte in the block was not acknowledged by the sla		
*
* \b Example:
* @code
* // Data block to be sent
* uint8_t data[] = {0x10, 0x20, 0x30, 0x40};
* 
* // Send the data block to the slave
* I2C_Status_Enum_t status = MASTER_I2C1_Send_DataBlock_BLOCKING(data, sizeof(data));
*
* // Check if the entire block was acknowledged
* if (status == I2C_ACK_RECEIVED) {
*     // All bytes were successfully acknowledged by the slave
* } else {
*     // One or more bytes were not acknowledged by the slave
* }	
*
* 	
* @endcode
*
* \b Notes:
* - The function is blocking and waits for the transmission of each byte to complete before sending the next byte.
* - The function stops transmission if any byte is not acknowledged by the slave.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
I2C_Status_Enum_t MASTER_I2C1_Send_DataBlock_BLOCKING(uint8_t *datablock, uint8_t data_length)
{
  uint8_t counter = 0;
  I2C_Status_Enum_t transmit_status = I2C_ACK_RECEIVED;
  while (counter < data_length && transmit_status == I2C_ACK_RECEIVED) // Loop through the datablock and transmit each byte if and ACK is not received abort.
  {        
    transmit_status = MASTER_I2C1_Send_Byte_BLOCKING(datablock[counter]); // Send each byte individually
    counter++;       
   }
  
  return transmit_status;
}

/******************************************************************************
* Function : MASTER_I2C1_Receive_Byte_BLOCKING()
*//** 
* \b Description:
*
* This function receives a single byte of data from the I2C bus using the I2C1 module in master mode.
* It enters receive mode by setting the Receive Enable bit (`RCEN`) and waits for the reception to complete 
* by checking the MSSP1 interrupt flag (`SSP1IF`), making it a **blocking** function. Once the byte is received, 
* the function returns the byte to the caller.
*
* The function also generates an acknowledgment (ACK) after receiving the byte to indicate to the slave device 
* that more data can be sent, unless otherwise specified in subsequent operations.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and configured as a master using `MASTER_I2C1_Init()`.
*    - A start condition and a valid slave address must be sent, requesting data from the slave device.
*
* POST-CONDITION: 
*    - A byte of data is received from the I2C bus, and an acknowledgment is generated.
*
* @param[in] 	None
*
* @return uint8_t
*    - The byte of data received from the slave device.		
*
* \b Example:
* @code
* 	
* // Receive a byte of data from the slave
* uint8_t receivedByte = MASTER_I2C1_Receive_Byte_BLOCKING();
* 	
* @endcode
*
* \b Notes:
* - This function is blocking, meaning it waits for the reception of the byte to complete before returning.
* - After receiving the byte, an acknowledgment is automatically generated to indicate readiness for more data.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t MASTER_I2C1_Receive_Byte_BLOCKING(void)
{
  uint8_t I2C_Data;  
  I2C1_Clear_Interrupt();  //Clear SSP1IF  
  SSP1CON2bits.RCEN = 1; //Enter Receive Mode
  I2C1_Wait_Until_Complete(); //wait until complete
  I2C_Data = SSP1BUF;  
  SSP1CON2bits.ACKDT = 0;
  SSP1CON2bits.ACKEN = 1;
  I2C1_Wait_Until_Complete(); //wait until complete
  I2C1_Clear_Interrupt();  //Clear SSP1IF 
  SSP1CON2bits.RCEN = 0; //Exit Receive Mode
  return I2C_Data;
}

/******************************************************************************
* Function : MASTER_I2C1_Receive_DataBlock_BLOCKING()
*//** 
* \b Description:
*
* This function receives a block of data (an array of bytes) from a slave device on the I2C bus using the I2C1 module in master mode.
* It repeatedly receives each byte of data and waits for the reception to complete for each byte by checking the MSSP1 interrupt flag (`SSP1IF`), 
* making it a **blocking** function. The received data is stored in the provided data block (array).
*
* After each byte is received, an acknowledgment (ACK) is sent to the slave to indicate readiness to receive the next byte.
* The function continues until the specified number of bytes has been received.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and configured as a master using `MASTER_I2C1_Init()`.
*    - A start condition and a valid slave address must be sent, requesting data from the slave device.
*
* POST-CONDITION: 
*    - The specified number of bytes is received from the I2C bus, and the data block is populated with the received bytes.
*
* @param[in] datablock - A pointer to the array where the received data will be stored.
* @param[in] data_length - The number of bytes to be received from the slave device.
*
* @return I2C_Status_Enum_t
*    - `I2C_OK` if the entire data block was successfully received.
*
* \b Example:
* @code
* 	
* // Buffer to store the received data
* uint8_t receivedData[5];
* 
* // Receive 5 bytes of data from the slave device
* I2C_Status_Enum_t status = MASTER_I2C1_Receive_DataBlock_BLOCKING(receivedData, 5);
*
* // Check if data was successfully received
* if (status == I2C_OK) {
*     // Process the received data
* }
* 	
* @endcode
*
* \b Notes:
* - This function is blocking, meaning it waits for the reception of each byte to complete before moving to the next byte.
* - After receiving each byte, an acknowledgment (ACK) is automatically generated to indicate readiness for the next byte.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
I2C_Status_Enum_t MASTER_I2C1_Receive_DataBlock_BLOCKING(uint8_t *datablock, uint8_t data_length)
{
  uint8_t counter = 0;
  while (counter < data_length) // Loop through the datablock and transmit each byte
  {        
    datablock[counter] = MASTER_I2C1_Receive_Byte_BLOCKING(); // Send each byte individually
    counter++;       
   }
  
  return  I2C_OK;
}


/******************************************************************************
* Function : I2C1_Clear_Interrupt()
*//** 
* \b Description:
*
* This function clears the MSSP1 interrupt flag (`SSP1IF`) for the I2C1 module. 
* The MSSP1 interrupt flag is set when an I2C event occurs, such as the completion 
* of data transmission or reception. Clearing this flag ensures that the I2C1 module 
* is ready for the next I2C operation.
*
* This function is typically called after completing a data transmission or reception, 
* or after sending a start or stop condition, to acknowledge that the interrupt event 
* has been handled.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized and in use for I2C communication.
*
* POST-CONDITION: 
*    - The MSSP1 interrupt flag is cleared, allowing the I2C1 module to proceed with the next operation.
*
* @param[in] 	None
*
* @return 	None	
*
* \b Example:
* @code
* 	
* // Clear the interrupt flag after completing an I2C operation
* I2C1_Clear_Interrupt();
* 	
* @endcode
*
* \b Notes:
* - This function should be called after completing any I2C operation (start, stop, data transmission, reception) 
*   that sets the MSSP1 interrupt flag.
* - Failing to clear the MSSP1 interrupt flag may result in the I2C1 module not recognizing subsequent I2C events.
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void I2C1_Clear_Interrupt(void)
{
  PIR3bits.SSP1IF = 0;
}

/******************************************************************************
* Function : I2C1_IsBusy()
*//** 
* \b Description:
*
* This function checks whether the I2C1 module (MSSP1) is currently busy with an I2C operation.
* It returns `TRUE` if the MSSP1 interrupt flag (`SSP1IF`) is not set, indicating that the module 
* is still processing a previous operation, such as data transmission, reception, or sending 
* a start/stop condition.
*
* The function is typically used in blocking functions where the code needs to wait for the I2C1 
* module to finish the current operation before proceeding to the next step.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized using `MASTER_I2C1_Init()`.
*
* POST-CONDITION: 
*    - Returns whether the I2C1 module is busy processing an I2C operation.
*
* @param[in] 	None
*
* @return bool
*    - `TRUE` if the I2C1 module is busy (MSSP1 interrupt flag is not set).
*    - `FALSE` if the I2C1 module is idle (MSSP1 interrupt flag is set).		
*
* \b Example:
* @code
* 	
* // Wait until the I2C1 module is not busy
* while (I2C1_IsBusy()) {
*     // Busy waiting, perform other tasks or wait
* }
* 	
* @endcode
*
* \b Notes:
* - This function is generally used in conjunction with other I2C operations (e.g., start, stop, transmit, receive) 
*   to ensure that each operation completes before proceeding to the next.
* - The function checks the MSSP1 interrupt flag, which is cleared once an I2C operation is complete.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
bool I2C1_IsBusy(void)
{
  if(!PIR3bits.SSP1IF){return TRUE;}
  else{return FALSE;}
}

/******************************************************************************
* Function : I2C1_IsBusy()
*//** 
* \b Description:
*
* This function blocks the execution of the program until the I2C1 module (MSSP1) 
* completes the current I2C operation. It continuously checks if the I2C1 module is busy 
* by calling `I2C1_IsBusy()` and waits until the module becomes idle.
*
* This function ensures that the current I2C operation, such as data transmission, reception, 
* or sending a start/stop condition, is fully completed before proceeding with the next task.
*
* PRE-CONDITION:  
*    - The I2C1 module must be initialized using `MASTER_I2C1_Init()`.
*    - An I2C operation (e.g., start, stop, transmit, or receive) must be in progress.
*
* POST-CONDITION: 
*    - The I2C1 module is idle, meaning the current I2C operation has completed.
*
* @param[in] 	None
*
* @return bool
*    - Always returns `TRUE` once the operation is complete.		
*
* \b Example:
* @code
* 	
* // Wait until the I2C1 operation is complete
* I2C1__Wait_Until_Complete();
*
* // Proceed with the next operation after completion
* 	
* @endcode
*
* \b Notes:
* - This function is blocking, meaning it waits until the I2C operation is complete before allowing further execution.
* - It is typically used after sending or receiving data, or after sending a start or stop condition, to ensure the I2C1 module is ready.
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
bool I2C1_Wait_Until_Complete(void)
{
    while (I2C1_IsBusy()){} //wait until complete
    return TRUE;
}


/******************************************************************************/
/***** Test Code *****/
/******************************************************************************/
void MASTER_I2C1_Test_BLOCKING(void)
{
  I2C_Status_Enum_t I2C_Status;
  I2C_Send_State_Enum_t I2C_Send_State = I2C_SEND_START_BIT;
  uint8_t I2C_data[] = {10, 20, 30, 40, 50};

  MASTER_I2C1_Send_Start_Bit_BLOCKING();
  I2C_Send_State = I2C_SEND_ADDRESS;  
  I2C_Status = MASTER_I2C1_Send_Address_BLOCKING(0x27,I2C_ADDRESS_READ_MODE);
  
  if(I2C_Status == I2C_ADDRESS_VALID_WRITE){I2C_Send_State = I2C_SEND_DATA;}
  if(I2C_Status == I2C_ADDRESS_VALID_READ){I2C_Send_State = I2C_READ_DATA;}
  
  if(I2C_Send_State==I2C_SEND_DATA)
    {
     I2C_Status = MASTER_I2C1_Send_DataBlock_BLOCKING(I2C_data,sizeof(I2C_data));
     //I2C_Status = MASTER_I2C1_Send_Byte_BLOCKING(0x56); 
     if(I2C_Status == I2C_ACK_RECEIVED)
       {I2C_Send_State = I2C_SEND_STOP_BIT;}
    }
  
  if(I2C_Send_State==I2C_READ_DATA)
    {
      I2C_data[0] = MASTER_I2C1_Receive_Byte_BLOCKING();
    }
  
  MASTER_I2C1_Send_Stop_BLOCKING();           
}




/*** End of File **************************************************************/
