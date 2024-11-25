/****************************************************************************
* Title                 :   Serial1 Functions - Enhanced Universal Synchronous
*                           Asynchronous Receiver Transmitter
* Filename              :   serial1.c
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
*
*****************************************************************************/

/******************************************************************************
***** Includes
*******************************************************************************/
#include "serial1.h"
#include "../pps/pps.h"
//#include <string.h>

/******************************************************************************
***** SERIAL1 Interface
*******************************************************************************/
const SERIAL1_Interface_t SERIAL1 = {
    .Initialize = &SERIAL1_Init,
    .WriteByte = &SERIAL1_WriteByte,
    .WriteString = &SERIAL1_WriteString,
    .IsDataAvailable = &SERIAL1_HasReceiveData,
    .IsTransmitComplete = &SERIAL1_IsTSREmpty,
    .ReadByte = &SERIAL1_GetReceivedData,
    .IsTransmitBufferReady = &SERIAL1_IsTXBufferEmpty,
    .IsError = &SERIAL1_IsError,
    .ClearErrors = &SERIAL1_Clear_Error,
};

/******************************************************************************
* Function Prototypes
*******************************************************************************/
SERIAL1_Status_Enum_t SERIAL1_Wait_Until_TXBufferFree(void);

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : SERIAL1_Init()
* Description: Initializes the SERIAL1 module with the selected baud rate and configuration 
* settings. Configures the baud rate registers, input/output pins, and enables 
* the transmitter and receiver.
*
* Parameters:
*   - BaudSelect (SerialBaudEnum_t): The baud rate configuration from the SERIAL1 
*     lookup table (e.g., BAUD_9600).
*******************************************************************************/
void SERIAL1_Init(SerialBaudEnum_t BaudSelect)
{  
 
  U1CON0bits.MODE = SERIAL1_Config[BaudSelect].ESUART_Mode; //Asynchronous 8-bit UART mode
  U1BRG = SERIAL1_Config[BaudSelect].BRG_Value;
   
  U1CON0bits.BRGS = SERIAL1_Config[BaudSelect].BRGS_Enable;  
  
  GPIO_SetDirection(_CORE18F_SERIAL1_INPUT_PIN,INPUT);  //Set as input -> Serial In
  
  PPS_MapOutput(_CORE18F_SERIAL1_OUTPUT_PIN,PPSOUT_UART1_TX);  //Map TX to ->Serial Out    
  
  U1CON0bits.RXEN = SERIAL1_Config[BaudSelect].RXEN_Enable; //Receive Enable
  U1CON0bits.TXEN = SERIAL1_Config[BaudSelect].TXEN_Enable; //Transmit Enable
  U1CON1bits.ON = SERIAL1_Config[BaudSelect].SPEN_Enable; //Serial Port Enable
}

/******************************************************************************
* Function : SERIAL1_WriteByte()
* Description: Writes a byte of data to the SERIAL1 transmit shift register (TSR). This 
*   function waits until the TSR buffer is ready before sending the byte.
*
* Parameters:
*   - SerialData (uint8_t): The byte of data to transmit.
*
*******************************************************************************/
SERIAL1_Status_Enum_t SERIAL1_WriteByte(uint8_t SerialData)
{
    
  if (SERIAL1_Wait_Until_TXBufferFree() != OK){return TIMEOUT;}
  U1TXB = SerialData;     
  return OK;
}

/******************************************************************************
* Function : SERIAL1_WriteString()
* Description: Writes a string to the SERIAL1 transmit buffer, sending one byte at a time. 
*   The function blocks until the buffer is ready for each byte.
*
* Parameters:
*   - StringData (char*): Pointer to the string to be transmitted.
*
*******************************************************************************/
SERIAL1_Status_Enum_t SERIAL1_WriteString(char *StringData)
{   
    SERIAL1_Status_Enum_t SendStatus;
    // Loop through the string and transmit each character
    for (; *StringData != '\0'; StringData++) {
        SendStatus = SERIAL1_WriteByte(*StringData); // Send each byte
        if (SendStatus != OK){return SendStatus;}
    }
    return OK;
}

/******************************************************************************
* Function : SERIAL1_HasReceiveData()
* Description:Checks if the SERIAL1 module has received data in its FIFO buffer.
*
*
* Returns:
*   - LogicEnum_t: TRUE if data is present, FALSE otherwise.
*******************************************************************************/
LogicEnum_t SERIAL1_HasReceiveData(void)
{
     return(!U1FIFObits.RXBE) ? TRUE : FALSE; // Return TRUE if data is present   
}

/******************************************************************************
* Function : SERIAL1_IsTSREmpty()
* Description: Checks if the transmit shift register (TSR) of the SERIAL1 module is empty.
*
* Returns:
*   - LogicEnum_t: TRUE if TSR is empty, FALSE if it is full.
*
*******************************************************************************/
LogicEnum_t SERIAL1_IsTSREmpty(void)
{
    return (PIR4bits.U1TXIF) ? TRUE : FALSE; // Return TRUE if TSR is empty      
}


/******************************************************************************
* Function : SERIAL1_GetReceivedData()
* Description: Returns the byte of data currently in the SERIAL1 receive buffer.
*
* Parameters:
*   - None
*
* Returns:
*   - uint8_t: The received byte from the serial buffer.
*
*******************************************************************************/
uint8_t SERIAL1_GetReceivedData(void)
{
    return U1RXB;  // Return the received data from the buffer
}

/******************************************************************************
* Function : SERIAL1_IsTXBufferEmpty()
* Description: Checks if the SERIAL1 transmit buffer is empty.
*
* Returns:
*   - LogicEnum_t: TRUE if the TX buffer is empty, FALSE otherwise.
*
*******************************************************************************/
LogicEnum_t SERIAL1_IsTXBufferEmpty(void)
{
    return (LogicEnum_t)(U1FIFObits.TXBE);    
    
}

/******************************************************************************
* Function :  SERIAL1_Wait_Until_TXBufferFree()
*//** 
*******************************************************************************/
SERIAL1_Status_Enum_t SERIAL1_Wait_Until_TXBufferFree(void)
{
  uint16_t timeout_counter = _SERIAL1_TIMEOUT_VALUE; 
  while (!SERIAL1_IsTXBufferEmpty()&& timeout_counter-- > 0){}  
  if (timeout_counter == 0){return TIMEOUT;} 
  return OK;  
}
    

/******************************************************************************
* Function : SERIAL1_IsError()
* Description: Checks if the SERIAL1 has any errors
*
* Returns:
*   - SERIAL1_Error_Enum_t: Error Code or SERIAL1_OK
*
*******************************************************************************/
SERIAL1_Status_Enum_t SERIAL1_IsError(void)
{
  if (U1ERRIRbits.FERIF){return FRAMMING_ERROR;}
  if (U1ERRIRbits.RXFOIF){return OVERRUN_ERROR;}
  return OK;
}

/******************************************************************************
* Function : SERIAL1_Clear_Error()
* Description: Clears SERIAL1 of any errors.
*******************************************************************************/
void SERIAL1_Clear_Error(void)
{
  SERIAL1_GetReceivedData();
  U1CON0bits.RXEN = CLEAR;
  NOP();
  U1CON0bits.RXEN = SET;
}

/*** End of File **************************************************************/