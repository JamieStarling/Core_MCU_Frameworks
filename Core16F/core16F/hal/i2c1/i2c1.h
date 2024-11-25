/****************************************************************************
* Title                 :   I2C HAL Functions
* Filename              :   i2c.h
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
* Version               :   1.0.3
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
*   2024/08/15  1.0.0       Jamie Starling  Initial Version
*  
*****************************************************************************/

#ifndef _CORE16F_I2C1_H
#define _CORE16F_I2C1_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core16F.h"

/******************************************************************************
* Defines
*******************************************************************************/
#define _I2C1_BUS_TIMEOUT_VALUE 250
#define _I2C1_RESET_DELAY_MS 25

/******************************************************************************
* I2C Return Codes
******************************************************************************/
typedef enum
{
    I2C_ADDRESS_INVALID,
    I2C_NACK_RECEIVED,
    I2C_ACK_RECEIVED,
    I2C_TIMEOUT,
    I2C_OK,
    I2C_Busy
}I2C1_Status_Enum_t;


/******************************************************************************
***** I2C1 Interface
*******************************************************************************/

typedef struct {
  void (*Initialize)(void);
  void (*BusReset)(void); 
  I2C1_Status_Enum_t (*WriteData)(uint8_t i2c_address,uint8_t i2c_bytecount, uint8_t *datablock);
  I2C1_Status_Enum_t (*ReadData) (uint8_t i2c_address,uint8_t i2c_bytecount_send, uint8_t *datablock_send, uint8_t i2c_bytecount_receive, uint8_t *datablock_receive);
}I2C1_Master_Interface_t;

extern const I2C1_Master_Interface_t I2C1_MASTER;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MASTER_I2C1_Init(void);
void MASTER_I2C1_Reset(void);
I2C1_Status_Enum_t MASTER_I2C1_WriteData(uint8_t i2c_address,uint8_t i2c_bytecount, uint8_t *datablock);
I2C1_Status_Enum_t MASTER_I2C1_ReadData(uint8_t i2c_address,uint8_t i2c_bytecount_send, uint8_t *datablock_send, uint8_t i2c_bytecount_receive, uint8_t *datablock_receive);





#endif /*_CORE16F_I2C1_H*/

/*** End of File **************************************************************/
