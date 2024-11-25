/****************************************************************************
* Title                 :   Core MCU I2C1 Functions
* Filename              :   i2c.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
* Version               :   1.0.4
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
*   Date        Version Author          Description 
*   2024/08/15  1.0.0   Jamie Starling  Initial Version
*   2024/11/03  1.0.4   Jamie Starling  Changed to Match the 18F I2C Interface
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "i2c1.h"

/******************************************************************************
* I2C1 Interface
*******************************************************************************/
const I2C1_Master_Interface_t I2C1_MASTER = {
  .Initialize = &MASTER_I2C1_Init,  
  .BusReset = &MASTER_I2C1_Reset,
  .WriteData = &MASTER_I2C1_WriteData,
  .ReadData = &MASTER_I2C1_ReadData,  
};

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void I2C1_Clear_Interrupt(void);
void MASTER_I2C1_Send_Start_Bit_BLOCKING(void);
void MASTER_I2C1_Send_Stop_BLOCKING(void);
I2C1_Status_Enum_t MASTER_I2C1_Send_Byte_BLOCKING(uint8_t data);
I2C1_Status_Enum_t I2C1_Wait_Until_Complete(void);
bool I2C1_IsBusy(void);
uint8_t MASTER_I2C1_Receive_Byte_BLOCKING(void);

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : MASTER_I2C1_Init()
* Description: This function initializes the I2C1 module in master mode for communication on 
* the I2C bus. It sets the appropriate I2C pins, configures the I2C clock speed, 
* and enables the I2C1 module. The function uses the Peripheral Pin Select (PPS) 
* system to map the I2C data (SDA) and clock (SCL) lines to the specified GPIO pins.
*
*
*******************************************************************************/
void MASTER_I2C1_Init(void)
{
  GPIO_SetDirection(I2C1_CLOCK_PIN,INPUT);
  GPIO_SetDirection(I2C1_DATA_PIN,INPUT);  
 
  PPS_MapBiDirection(I2C1_CLOCK_PIN,PPSOUT_SCK1_SCL1,&SSP1CLKPPS);
  PPS_MapBiDirection(I2C1_DATA_PIN,PPSOUT_SDO1_SDA1,&SSP1DATPPS);
    
  SSP1STAT = 0x80; /* CKE disabled; SMP Standard Speed;  */  
  SSP1CON1 = 0x8; /* SSPM FOSC/4_SSPxADD_I2C; CKP disabled; SSPEN disabled; SSPOV no_overflow; WCOL no_collision;  */  
  SSP1CON2 = 0x0; /* SEN disabled; RSEN disabled; PEN disabled; RCEN disabled; ACKEN disabled; ACKDT acknowledge; GCEN disabled;  */  
  SSP1CON3 = 0x0; /* DHEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; BOEN disabled; SCIE disabled; PCIE disabled;  */
  SSP1CON1bits.SSPM = 0b1000;  
  SSP1ADD = 0x4F;    /* SSPADD 79;  */  
  MASTER_I2C1_Reset();
}


/******************************************************************************
* Function : MASTER_I2C1_Reset()
* Description: This function resets the I2C1 module in master mode. It disables the I2C1 module, 
* clears any overflows or write collisions, and flushes the buffer. It also clears 
* the MSSP1 interrupt flag to ensure the I2C bus is reset to a known state.
*
* After performing these actions, the function re-enables the I2C1 module to allow 
* it to resume normal operation.
*
*******************************************************************************/
void MASTER_I2C1_Reset(void)
{
  char temp;
  SSP1CON1bits.SSPEN = 0;
  temp = SSP1BUF;
  SSP1CON1bits.WCOL = 0;  
  I2C1_Clear_Interrupt();  //Clear SSP1IF
  __delay_ms(_I2C1_RESET_DELAY_MS);
  SSP1CON1bits.SSPEN = 1;
}

/******************************************************************************
* Function : MASTER_I2C1_WriteData()
* Description: Writes a block of data to a specified I2C address. Sends the start condition,
* the address, and each byte in the data block. Checks for ACK after each byte
* and handles any NACKs by stopping the transmission.
*
* Parameters:
*   - i2c_address (uint8_t): The I2C address of the device to write to.
*   - i2c_bytecount (uint8_t): Number of bytes to write from the data block.
*   - datablock (uint8_t*): Pointer to the data block to be transmitted.
*
* Returns:
*   - I2C1_Status_Enum_t: Status of the write operation (e.g., I2C_OK, I2C_TIMEOUT, I2C_NACK_RECEIVED).
*
*******************************************************************************/
I2C1_Status_Enum_t MASTER_I2C1_WriteData(uint8_t i2c_address,uint8_t i2c_bytecount, uint8_t *datablock)
{
  //Check for Busy...
  
  // Send start condition
  MASTER_I2C1_Send_Start_Bit_BLOCKING(); 
 
  // Send I2C Address with R/W bit cleared (write operation)
  SSP1BUF = (uint8_t)(i2c_address << 1);  
  
  // Wait for the address to be transmitted or timeout
  if (I2C1_Wait_Until_Complete() == I2C_TIMEOUT){
      MASTER_I2C1_Send_Stop_BLOCKING();
      return I2C_TIMEOUT;
    }  
  
  I2C1_Clear_Interrupt();  // Clear interrupt flag
  
 // Check for ACK from the client
  if(SSP1CON2bits.ACKSTAT){
      MASTER_I2C1_Send_Stop_BLOCKING(); // Send Stop if NACK is received
      return I2C_ADDRESS_INVALID;
    }
  
  // If no data to send (address check only)
  if(i2c_bytecount==0){
    MASTER_I2C1_Send_Stop_BLOCKING();
    return I2C_OK;  
    }
  
  // Send each byte in the data block
  for (uint8_t i2c_bytecounter = 0; i2c_bytecounter < i2c_bytecount; i2c_bytecounter++){    
    I2C1_Status_Enum_t transmit_status;
    transmit_status = MASTER_I2C1_Send_Byte_BLOCKING(datablock[i2c_bytecounter]); // Send each byte individually
    
    // Check for NACK or other issues
    if (transmit_status != I2C_ACK_RECEIVED)
      {
        MASTER_I2C1_Send_Stop_BLOCKING();
        return I2C_NACK_RECEIVED;       
      }    
    }
  
  // Send Stop Bit after the last byte
  MASTER_I2C1_Send_Stop_BLOCKING();
  return I2C_OK;    
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Start_Bit_BLOCKING()
* Description: Sends a start condition on the I2C1 bus in master mode to indicate the 
* beginning of communication with a slave device.
*
*******************************************************************************/
void MASTER_I2C1_Send_Start_Bit_BLOCKING(void)
{
  uint8_t timeout_counter = _I2C1_BUS_TIMEOUT_VALUE; 
  SSP1CON2bits.SEN = 1;
   
   while(SSP1CON2bits.SEN && timeout_counter-- > 0){}
   I2C1_Clear_Interrupt();  //Clear SSP1IF
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Stop_BLOCKING()
* Description: This function sends a **stop condition** on the I2C bus using the I2C1 module in master mode.
* A stop condition signals the end of communication with the slave device and releases 
* the I2C bus, allowing other devices to initiate communication.
*
*******************************************************************************/
void MASTER_I2C1_Send_Stop_BLOCKING(void)
{
  uint8_t timeout_counter = _I2C1_BUS_TIMEOUT_VALUE; 
  SSP1CON2bits.PEN = 1;
  while(SSP1CON2bits.PEN && timeout_counter-- > 0){}
  I2C1_Clear_Interrupt();
}

/******************************************************************************
* Function : MASTER_I2C1_Send_Byte_BLOCKING()
* Description: Sends a single byte on the I2C1 bus in master mode and waits for the 
*   transmission to complete. Checks for an acknowledgment (ACK) from the slave 
*   device after transmission.
*
* Parameters:
*   - data (uint8_t): The byte of data to be transmitted.
*
* Returns:
*   - I2C1_Status_Enum_t: Status of the transmission (e.g., I2C_ACK_RECEIVED, 
*     I2C_NACK_RECEIVED, I2C_TIMEOUT).
*
*******************************************************************************/
I2C1_Status_Enum_t MASTER_I2C1_Send_Byte_BLOCKING(uint8_t data)
{
  SSP1BUF = data;  
  if (I2C1_Wait_Until_Complete() == I2C_TIMEOUT){return I2C_TIMEOUT;} //Wait until complete or timeout
  I2C1_Clear_Interrupt();  // Clear the interrupt flag
  
  // Check for ACK from the slave device
  return (!SSP1CON2bits.ACKSTAT) ? I2C_ACK_RECEIVED : I2C_NACK_RECEIVED;
}

/******************************************************************************
* Function : I2C1_Clear_Interrupt()
* Description: Clears the MSSP1 interrupt flag (`SSP1IF`) and the bus collision flag 
* (`BCL1IF`) for the I2C1 module to prepare for the next I2C operation.
*
*******************************************************************************/
void I2C1_Clear_Interrupt(void)
{
  PIR3bits.SSP1IF = 0;
  PIR3bits.BCL1IF = 0;
}

/******************************************************************************
* Function : I2C1_IsBusy()
* Description: Checks if the I2C1 module (MSSP1) is currently busy with an I2C operation.
*
* Returns:
*   - bool: `TRUE` if the I2C1 module is busy, `FALSE` if it is not.
* 
*******************************************************************************/
bool I2C1_IsBusy(void)
{
   return (!PIR3bits.SSP1IF) ? TRUE : FALSE;
}

/******************************************************************************
* Function : I2C1_Wait_Until_Complete()
* Description: Waits for the I2C1 module to complete its current operation. Returns a 
* status indicating whether the operation finished successfully or timed out.
*
*
* Returns:
*   - I2C1_Status_Enum_t: `I2C_OK` if the operation completes, `I2C_TIMEOUT` if it times out.
*  
*******************************************************************************/
I2C1_Status_Enum_t I2C1_Wait_Until_Complete(void)
{
  uint8_t timeout_counter = _I2C1_BUS_TIMEOUT_VALUE; 
  
  while (I2C1_IsBusy() && timeout_counter-- > 0){} //wait until complete or time out    
  return (timeout_counter == 0) ? I2C_TIMEOUT : I2C_OK;
}

/******************************************************************************
* Function : MASTER_I2C1_ReadData()
* Description:  This function reads data from an I2C device in master mode. It sends a start 
* condition, writes an address with the read bit set, transmits a series of data 
* bytes (if any), and then reads a specified number of bytes from the slave device. 
* The function handles potential NACKs and timeouts, ensuring that the I2C operation 
* completes safely or returns an error code.
*
* @param[in] i2c_address - The 7-bit address of the I2C slave device.
* @param[in] i2c_bytecount_send - Number of bytes to send to the slave device.
* @param[in] *datablock_send - Pointer to the buffer holding the data to be sent.
* @param[in] i2c_bytecount_receive - Number of bytes to read from the slave device.
* @param[out] *datablock_receive - Pointer to the buffer where received data will be stored.
*
* @return I2C1_Status_Enum_t
*    - I2C_OK: Operation completed successfully.
*    - I2C_TIMEOUT: Timeout occurred while waiting for a response.
*    - I2C_ADDRESS_INVALID: The slave device did not acknowledge the address.
*    - I2C_NACK_RECEIVED: The slave device did not acknowledge the transmitted data.
*******************************************************************************/
I2C1_Status_Enum_t MASTER_I2C1_ReadData(uint8_t i2c_address,uint8_t i2c_bytecount_send, uint8_t *datablock_send, uint8_t i2c_bytecount_receive, uint8_t *datablock_receive)
{
    
  if(I2C1_IsBusy()){return I2C_Busy;}
  
  // Send start condition
  MASTER_I2C1_Send_Start_Bit_BLOCKING(); 
 
  // Send I2C Address with R/W bit set (read operation)
  SSP1BUF = (uint8_t)(uint8_t)(i2c_address << 1 | 1);
  
  // Wait for the address to be transmitted or timeout
  if (I2C1_Wait_Until_Complete() == I2C_TIMEOUT){
      MASTER_I2C1_Send_Stop_BLOCKING();
      return I2C_TIMEOUT;
    }  
  
  I2C1_Clear_Interrupt();  // Clear interrupt flag
  
 // Check for ACK from the client
  if(SSP1CON2bits.ACKSTAT){
      MASTER_I2C1_Send_Stop_BLOCKING(); // Send Stop if NACK is received
      return I2C_ADDRESS_INVALID;
    }
  
  // Send each byte in the data block
  for (uint8_t i2c_bytecounter = 0; i2c_bytecounter < i2c_bytecount_send; i2c_bytecounter++){    
    I2C1_Status_Enum_t transmit_status;
    transmit_status = MASTER_I2C1_Send_Byte_BLOCKING(datablock_send[i2c_bytecounter]); // Send each byte individually
    
    // Check for NACK or other issues
    if (transmit_status != I2C_ACK_RECEIVED)
      {
        MASTER_I2C1_Send_Stop_BLOCKING();
        return I2C_NACK_RECEIVED;       
      }    
    }
  
  // Receive The Data
  for (uint8_t i2c_bytecounter = 0; i2c_bytecounter < i2c_bytecount_receive; i2c_bytecounter++){
        datablock_receive[i2c_bytecounter] = MASTER_I2C1_Receive_Byte_BLOCKING();
    } 
  
  // Send Stop Bit after the last byte
  MASTER_I2C1_Send_Stop_BLOCKING();
  return I2C_OK;   
}

/******************************************************************************
* Function : MASTER_I2C1_Receive_Byte_BLOCKING()
* Description: This function receives a single byte of data from an I2C slave device in 
* a blocking manner using the I2C1 module in master mode. It sets up the I2C 
* module to receive data, waits for the reception to complete, and returns the 
* received byte. The function also sends an acknowledgment (ACK) after the byte 
* is received and clears the appropriate I2C flags.
*
* @return uint8_t
*    - The byte of data received from the I2C slave device.
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





/*** End of File **************************************************************/
