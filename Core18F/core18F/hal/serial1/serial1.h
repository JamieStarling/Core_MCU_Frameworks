/****************************************************************************
* Title                 :   SERIAL1 Functions - Enhanced Universal Synchronous
*                           Asynchronous Receiver Transmitter
* Filename              :   serial1.h
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

/*************** TODO *********************************************************
 * * 
 * 
 * 
*****************************************************************************/

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

#ifndef _CORE18F_SERIAL1_H
#define _CORE18F_SERIAL1_H
/******************************************************************************
***** Includes
*******************************************************************************/
#include "../../core18F.h"
/******************************************************************************
***** SERIAL1 Interface
*******************************************************************************/
typedef struct {
  void (*Initialize)(SerialBaudEnum_t BaudSelect); 
  void (*WriteByte)(uint8_t SerialData);
  void (*WriteString)(char *StringData);
  LogicEnum_t (*IsDataAvailable)(void);
  LogicEnum_t (*IsTransmitComplete)(void);
  uint8_t (*ReadByte)(void);
  LogicEnum_t (*IsTransmitBufferReady)(void);  
}SERIAL1_Interface_t;

extern const SERIAL1_Interface_t SERIAL1;


/******************************************************************************
* Function Prototypes
*******************************************************************************/

void SERIAL1_Init(SerialBaudEnum_t BaudSelect);
void SERIAL1_WriteByte(uint8_t SerialData);
void SERIAL1_WriteString(char *StringData);
LogicEnum_t SERIAL1_HasReceiveData(void);
LogicEnum_t SERIAL1_IsTSREmpty(void);
uint8_t SERIAL1_GetReceivedData(void);
LogicEnum_t SERIAL1_IsTXBufferEmpty(void);

#endif /*_CORE18F_SERIAL1_H*/

/*** End of File **************************************************************/
