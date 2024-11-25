/****************************************************************************
* Title                 :   Core MCU Framework Generic Utilities
* Filename              :   utils.h
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
* Version               :   1.0.2
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
*****************************************************************************/

#ifndef _CORE_SYSTEM_UTILS_H
#define _CORE_SYSTEM_UTILS_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"


/******************************************************************************
* Function Prototypes
*******************************************************************************/
uint16_t CORE_Make_16(uint8_t high_byte, uint8_t low_byte);
uint8_t CORE_Return_4bit_High(uint8_t byte);
uint8_t CORE_Return_4bit_Low(uint8_t byte);
uint8_t CORE_Set_Bit(uint8_t byte, uint8_t bit_position);
uint8_t CORE_Clear_Bit(uint8_t byte, uint8_t bit_position);
void CORE_floatToString(float number, char* buffer, uint8_t decimalPlaces);
void CORE_intToString(int32_t number, char* buffer);

#endif /*_CORE_SYSTEM_UTILS_H*/
/*** End of File **************************************************************/
