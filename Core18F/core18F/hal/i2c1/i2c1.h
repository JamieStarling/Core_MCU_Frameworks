/****************************************************************************
* Title                 :   I2C HAL Functions
* Filename              :   i2c.h
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
 * * 
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

#ifndef _CORE18F_I2C_H
#define _CORE18F_I2C_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
****** Configuration
*******************************************************************************/

/******************************************************************************
 * \brief I2C Return Codes
 * 
 ******************************************************************************/
typedef enum
{
 I2C_OK,
 I2C_ADDRESS_VALID_WRITE,
 I2C_ADDRESS_VALID_READ,
 I2C_ADDRESS_INVALID,
 I2C_ACK_RECEIVED,
 I2C_NO_ACK_RECEIVED,
 I2C_TIMEOUT,
}I2C_Status_Enum_t;

typedef enum
{
  I2C_SEND_START_BIT,
  I2C_SEND_ADDRESS,
  I2C_SEND_DATA,
  I2C_READ_DATA,
  I2C_SEND_STOP_BIT 
}I2C_Send_State_Enum_t;

typedef enum
{
  I2C_ADDRESS_WRITE_MODE = 0,
  I2C_ADDRESS_READ_MODE = 1  
}I2C_Address_Mode_Enum_t;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MASTER_I2C1_Init(void);
void MASTER_I2C1_Send_Start_Bit_BLOCKING(void);
I2C_Status_Enum_t MASTER_I2C1_Send_Address_BLOCKING(uint8_t address, I2C_Address_Mode_Enum_t address_mode);
void MASTER_I2C1_Send_Stop_BLOCKING(void);
I2C_Status_Enum_t MASTER_I2C1_Send_Byte_BLOCKING(uint8_t data);
I2C_Status_Enum_t MASTER_I2C1_Send_DataBlock_BLOCKING(uint8_t *datablock, uint8_t data_length);
uint8_t MASTER_I2C1_Receive_Byte_BLOCKING(void);
I2C_Status_Enum_t MASTER_I2C1_Receive_DataBlock_BLOCKING(uint8_t *datablock, uint8_t data_length);
void MASTER_I2C1_Test_BLOCKING(void);



#endif /*_CORE18F_I2C_H*/

/*** End of File **************************************************************/
