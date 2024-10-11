/****************************************************************************
* Title                 :   One Wire HAL
* Filename              :   one_wire.h
* Author                :   Jamie Starling
* Origin Date           :   2024/08/20
* Version               :   1.0.0
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
 * * 
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

#ifndef _CORE18F_ONE_WIRE_H
#define _CORE18F_ONE_WIRE_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
* Configuration
*******************************************************************************/
#define OW_DIRECTION_REGISTER TRISAbits.TRISA0
#define OW_PINDRIVER_REGISTER LATAbits.LATA0
#define OW_PINREAD_REGISTER PORTAbits.RA0
#define OW_PINANALOG_REGISTER ANSELAbits.ANSA0

/*ONE WIRE RESET TIMINGS*/
#define ONE_WIRE_RESET_DELAY_US 480
#define ONE_WIRE_RESET_DELAY_DRIVE_HIGH_US 70
#define ONE_WIRE_RESET_DELAY_READ_US 410

/*ONE WIRE WRITE TIMINGS*/
#define ONE_WIRE_WRITE_BIT_1_DELAY_DRIVE_LOW_US 6
#define ONE_WIRE_WRITE_BIT_1_DELAY_DRIVE_HIGH_US 64
#define ONE_WIRE_WRITE_BIT_0_DELAY_DRIVE_LOW_US 60
#define ONE_WIRE_WRITE_BIT_0_DELAY_DRIVE_HIGH_US 10

/*ONE WIRE READ TIMINGS*/
#define ONE_READ_BIT_DELAY_DRIVE_LOW_US 5
#define ONE_READ_BIT_DELAY_DRIVE_HIGH_US 2
#define ONE_READ_BIT_DELAY_END_US 45
/******************************************************************************
* Function Prototypes
*******************************************************************************/
void ONE_WIRE_Init(void);
LogicEnum_t ONE_WIRE_Reset(void);
void ONE_WIRE_Write_Byte(uint8_t data);
uint8_t ONE_WIRE_Read_Byte(void);
uint8_t ONE_WIRE_Read_Bit(void);

#endif /*_CORE18F_ONE_WIRE_H*/

/*** End of File **************************************************************/
