/****************************************************************************
* Title                 :   Serial1 Functions - Enhanced Universal Synchronous
*                           Asynchronous Receiver Transmitter
* Filename              :   eusart1.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.2
* Compiler              :   XC8 
* Target                :   Microchip PIC16F series
* Copyright             :   � 2024 Jamie Starling
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
 * Implement support for additional baud rates based on varying clock speeds.
 * Add error handling for overrun or framing errors.
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
***** Includes
*******************************************************************************/
#include "serial1.h"
#include "../pps/pps.h"
#include <string.h>

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
    .IsTransmitBufferReady = &SERIAL1_IsTXBufferEmpty
};


/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : SERIAL1_Init()
*//** 
* \b Description:
*
* Initializes the SERIAL1 module with the selected baud rate configuration.
 * This function configures the baud rate, input/output pins, and enables the
 * transmitter and receiver based on the settings in the configuration array.
*  
* PRE-CONDITION:  None
*
* POST-CONDITION: The selected baud rate and settings are applied to SERIAL1.
*
* @param[in] SerialBaudEnum_t : From ESUART Lookup Table
*
* @return 		
*
* \b Example:
* @code
* 	
* SERIAL1_Init(BAUD_9600);  //Configures ESUART1 for 9600 Baud
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void SERIAL1_Init(SerialBaudEnum_t BaudSelect)
{  
 
  SP1BRG = SERIAL1_Config[BaudSelect].SP1BRG_Value;
  BAUD1CONbits.BRG16 = SERIAL1_Config[BaudSelect].BRG16_Enable;
  TX1STAbits.SYNC = SERIAL1_Config[BaudSelect].SYNC_Enable;
  TX1STAbits.BRGH = SERIAL1_Config[BaudSelect].BRGH_Enable;
  
  GPIO_SetDirection(_CORE16F_SERIAL1_INPUT_PIN,INPUT);  //Set as input -> Serial In
  
  PPS_MapOutput(_CORE16F_SERIAL1_OUTPUT_PIN,PPSOUT_TX1_CK1);  //Map TX to ->Serial Out
    
  RC1STAbits.CREN = SERIAL1_Config[BaudSelect].CREN_Enable;
  TX1STAbits.TXEN = SERIAL1_Config[BaudSelect].TXEN_Enable;
  RC1STAbits.SPEN = SERIAL1_Config[BaudSelect].SPEN_Enable;     
  
}

/******************************************************************************
* Function : SERIAL1_WriteByte()
*//** 
* \b Description:
*
* Writes a byte of data to the SERIAL1 transmit shift register (TSR).
* 
 * This function waits until the TSR buffer has space available and then writes
 * a byte of data for transmission over the SERIAL1 serial port. It blocks execution
 * until the buffer is ready.
*  
* PRE-CONDITION:  SERIAL1 module must be properly configured and initialized
* 
*
* POST-CONDITION: The byte is written to the TSR buffer for transmission.
*
* @param[in] SerialData  The byte of data to transmit.
*
* @return 		
*
* \b Example:
* @code
* 	
* SERIAL1_WriteByte('A');  / Transmit character 'A'
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void SERIAL1_WriteByte(uint8_t SerialData)
{
    while (!PIR3bits.TX1IF){}
    TX1REG = SerialData;     
}

/******************************************************************************
* Function : SERIAL1_WriteString()
*//** 
* \b Description:
*
* Writes a string of data to the SERIAL1 transmit buffer (TSR).
* This function will block if the buffer is full, waiting until the buffer
* has space to accept new data. The function writes one byte at a time
*  
* PRE-CONDITION:  SERIAL1 module must be properly configured and initialized
* 
*
* POST-CONDITION: 
*
* @param[in] *StringData - buffer of data	
*
* @return 		
*
* \b Example:
* @code
* SERIAL1_WriteString("Hello, world!");  // Send a string of data	
*
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
void SERIAL1_WriteString(char *StringData)
{
    uint8_t counter = 0;
    size_t length = strlen(StringData);
    
    // Loop through the string and transmit each character
    while (counter < length){        
        SERIAL1_WriteByte(StringData[counter]); // Send each byte individually
        counter++;       
    }
}

/******************************************************************************
* Function : SERIAL1_HasReceiveData()
*//** 
* \b Description:
*
* Checks the state of ESUART FIFO Buffer for any received data.  
* 
* 
* PRE-CONDITION: SERIAL1 module must be properly configured and initialized 
* 
* POST-CONDITION: None
*
* @param[in] : None	
*
* @return : TRUE if Data present, Otherwise FALSE.		
*
* \b Example:
* @code
* 	
* bool status = SERIAL1_HasReceiveData(); //Checks the status for any received data
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>

*******************************************************************************/
LogicEnum_t SERIAL1_HasReceiveData(void)
{
    uint8_t RCBufferStatus = PIR3bits.RC1IF;    
    return RCBufferStatus;
}

/******************************************************************************
* Function : SERIAL1_IsTSREmpty()
*//** 
* \b Description:
*
* Returns the status of the transmit buffer TSR.
* 0 - TSR Full
* 1 - TSR Empty
* 
* PRE-CONDITION:  SERIAL1 module must be properly configured and initialized 
*
* POST-CONDITION: None
*
* @param[in] : None
*
* @return : TRUE If Empty / Other wise false.
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

*******************************************************************************/
LogicEnum_t SERIAL1_IsTSREmpty(void)
{
    uint8_t TXStatus = TX1STAbits.TRMT;
    return TXStatus;
}
/*** End of File **************************************************************/

/******************************************************************************
* Function : SERIAL1_GetReceivedData()
*//** 
* \b Description:
*
* Returns the data in the serial receive buffer
* 
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
*
* @return  uint8_t of received data		
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

*******************************************************************************/
uint8_t SERIAL1_GetReceivedData(void)
{
    return RC1REG; 
}

/******************************************************************************
* Function : SERIAL1_IsTXBufferEmpty()
*//** 
* \b Description:
*
* Return 1 if the TX Buffer is empty
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

*******************************************************************************/
LogicEnum_t SERIAL1_IsTXBufferEmpty(void)
{
    uint8_t TXBuffer_Status = PIR3bits.TX1IF;    
    return TXBuffer_Status;
}


/*** End of File **************************************************************/