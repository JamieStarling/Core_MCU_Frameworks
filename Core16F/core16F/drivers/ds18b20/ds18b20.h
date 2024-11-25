/****************************************************************************
* Title                 :   DS18B20 Driver
* Filename              :   ds18b20.h
* Author                :   Jamie Starling
* Origin Date           :   2024/10/10
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   PIC MCUs
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


/***************  CHANGE LIST *************************************************
*
*    Date    Version   Author         Description 
*   2024/10/11  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

#ifndef _COREMCU_DS18B20_H
#define _COREMCU_DS18B20_H

/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core_version.h"

#ifdef _CORE16_MCU
#include "../../core16F.h"
#endif

#ifdef _CORE18_MCU
#include "../../core18F.h"
#endif


/******************************************************************************
* Constants
*******************************************************************************/
#define _DS18B20_READ_ROM_COMMAND 0x33
#define _DS18B20_SKIP_ROM_COMMAND 0xCC
#define _DS18B20_CONVERT_COMMAND 0x44
#define _DS18B20_READ_SCRATCHPAD 0xBE
#define _DS18B20_INVALID_TEMPERATURE 0xFF

#define _DS18B20_MAX_RETRY_COUNT 10
#define _DS18B20_TEMPERATURE_RESOLUTION_12bit .0625

#define _DS18B20_ROM_SIZE 7
#define _DS18B20_SCRATCHPAD_DATA_SIZE 8

#define _DS18B20_9BIT_RESOLUTION 0x00
#define _DS18B20_10BIT_RESOLUTION 0x20
#define _DS18B20_11BIT_RESOLUTION 0x40
#define _DS18B20_12BIT_RESOLUTION 0x60

#define _DS18B20_CONVERSION_DELAY_MS 1000
#define _DS18B20_RETRY_DELAY_MS 20

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum
{
    DS18B20_STATUS_OK,
    DS18B20_STATUS_NO_DEVICE,
    DS18B20_STATUS_CRC_FAILED,
    DS18B20_STATUS_TEMPERATURE_CONVERSION_FAILED,
    DS18B20_ERROR_GENERIC,
    DS18B20_RESOLUTION_9BIT,
    DS18B20_RESOLUTION_10BIT,
    DS18B20_RESOLUTION_11BIT,
    DS18B20_RESOLUTION_12BIT
}DS18B20_StatusEnum_t;



/******************************************************************************
***** DS18B20 Interface
*******************************************************************************/
typedef struct {
  DS18B20_StatusEnum_t (*Initialize)(void);   
  float (*ReadC)(void);
  float (*ReadF)(void);
  int16_t (*ReadRaw)(void);
  bool (*Present)(void);
  DS18B20_StatusEnum_t(*GetResolution)(void);
  DS18B20_StatusEnum_t(*Start_Conversion)(void);
}DS18B20_Interface_t;

extern const DS18B20_Interface_t DS18B20;




/******************************************************************************
* Function Prototypes
*******************************************************************************/
DS18B20_StatusEnum_t DS18B20_Init(void);
DS18B20_StatusEnum_t DS18B20_Read_Temperature(void);
bool DS18B20_PresentStatus(void);
float DS18B20_Get_TemperatureC(void);
float DS18B20_Get_TemperatureF(void);
int16_t DS18B20_Get_TemperatureRAW(void);
DS18B20_StatusEnum_t DS18B20_Return_Resolution(void);

#endif /*_COREMCU_DS18B20_H*/

/*** End of File **************************************************************/
