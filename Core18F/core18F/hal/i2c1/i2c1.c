/****************************************************************************
* Title                 :   Core MCU I2C1 Functions
* Filename              :   i2c.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
* Version               :   1.0.4
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
*   2024/08/15  1.0.0       Jamie Starling  Initial Version
*  
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
I2C1_Status_Enum_t I2C1_Wait_Until_Complete(void);
void MASTER_I2C1_Send_Stop(void);
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
    GPIO.ModeSet(I2C1_CLOCK_PIN,OPEN_DRAIN);
    GPIO.ModeSet(I2C1_DATA_PIN,OPEN_DRAIN);  
    GPIO.PinWrite(I2C1_CLOCK_PIN,HIGH);
    GPIO.PinWrite(I2C1_DATA_PIN,HIGH);    
 
    PPS_MapBiDirection(I2C1_CLOCK_PIN,PPSOUT_I2C1_SCL,&I2C1SCLPPS);
    PPS_MapBiDirection(I2C1_DATA_PIN,PPSOUT_I2C1_SDA,&I2C1SDAPPS); 
    
    I2C1CON0 = 0x4; //I2C Host mode, 7-bit address 
    I2C1CON1 = 0x80; //ACKCNT Not Acknowledge;     
    I2C1CON2bits.SDAHT = 0b10; //SDAHT 30 ns hold time;
    I2C1CON2bits.ABD = 0; //Address Buffer 
  
    I2C1CLK = 0x0; //CLK Fosc/4
    I2C1PIR = 0x0; //Clear Interrupt Flags  
    I2C1PIE = 0x0; //Disable all I2C1 Interrupts  
    I2C1ERR = 0x0; //Clear All Errors
    /* Clear Byte Count registers */
    I2C1CNTL = 0x0;
    I2C1CNTH = 0x0;  
    I2C1BAUD = 0x1F; // Set BAUD 31 - 100Khz
   
    I2C1BTOC = 0x0; /* BTOC TMR2 post scaled output;  */     
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
    I2C1CON0bits.EN = 0;  //Disable I2C  
    I2C1STAT1bits.CLRBF = 1; //Clears Buffers
    I2C1STAT1bits.TXWE = 0; //Clear Transmit Write Error
    I2C1STAT1bits.RXRE = 0; //Clear Receive Write Error  
    __delay_ms(25);
    I2C1CON0bits.EN = 1; //Enable I2C
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
  uint8_t i2c_count_compare;
  I2C1CNTL = i2c_bytecount;  //Load the data byte count 
  I2C1ADB1 = (uint8_t)(i2c_address << 1);   //Load the Address Register 
  if (!(i2c_bytecount == 0)){I2C1TXB = datablock[0];} 
  
  I2C1CON0bits.S = SET; //Set the Start Bit  
  
  //No data - used for address check
  if (i2c_bytecount == 0){    
    //while(!I2C1PIRbits.CNTIF){}  //Wait for completion
    if (I2C1_Wait_Until_Complete() == I2C_TIMEOUT){
        MASTER_I2C1_Send_Stop();
        return I2C_TIMEOUT;
    }  
    if(I2C1CON1bits.ACKSTAT){return I2C_ADDRESS_INVALID;} //Check for ACK on address  
    return I2C_OK;
    }
  
  for (uint8_t i2c_bytecounter = 1; i2c_bytecounter < i2c_bytecount; i2c_bytecounter++){    
    while (!PIR7bits.I2C1TXIF){}
    i2c_count_compare = I2C1CNTL;
    I2C1TXB = datablock[i2c_bytecounter];   
    while(I2C1CNTL == i2c_count_compare && I2C1STAT0bits.MMA){return I2C_NACK_RECEIVED;}    
    }
  
  //while(!I2C1PIRbits.CNTIF){}  //Wait for completion  
  if (I2C1_Wait_Until_Complete() == I2C_TIMEOUT){
        MASTER_I2C1_Send_Stop();
        return I2C_TIMEOUT;
    }  
  if(I2C1CON1bits.ACKSTAT){return I2C_NACK_RECEIVED;} //Check for ACK  
  return I2C_OK;
    
}

/******************************************************************************
* Function : I2C1_Clear_Interrupts()
* 
*******************************************************************************/
void I2C1_Clear_Interrupts(void)
{
  I2C1PIR = 0;
  I2C1STAT1bits.CLRBF = 1;
}

/******************************************************************************
* Function : MASTER_I2C1_ReadData()
* 
*******************************************************************************/
I2C1_Status_Enum_t MASTER_I2C1_ReadData(uint8_t i2c_address,uint8_t i2c_bytecount_send, uint8_t *datablock_send, uint8_t i2c_bytecount_receive, uint8_t *datablock_receive)
{
  return 0;
}

/******************************************************************************
* Function : I2C1_Wait_Until_Complete()
* Description: Waits for the I2C1 module to complete its current operation. Returns a 
* status indicating whether the operation finished successfully or timed out.
*
*
* Returns:
*   - I2C1_Status_Enum_t: `I2C_OK` if the operation completes, `I2C_TIMEOUT` if it times out.
*******************************************************************************/
I2C1_Status_Enum_t I2C1_Wait_Until_Complete(void)
{
  uint8_t timeout_counter = _I2C1_BUS_TIMEOUT_VALUE; 
  
  while (!I2C1PIRbits.CNTIF && timeout_counter-- > 0){} //wait until complete or time out    
  return (timeout_counter == 0) ? I2C_TIMEOUT : I2C_OK;
}

/******************************************************************************
* Function :  MASTER_I2C1_Send_Stop()
* 
*******************************************************************************/
void MASTER_I2C1_Send_Stop(void)
{
  I2C1CON1bits.P = SET;
}













/*** End of File **************************************************************/
