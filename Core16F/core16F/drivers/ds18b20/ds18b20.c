/****************************************************************************
* Title                 :   <TITLE>
* Filename              :   %<%NAME%>%.%<%EXTENSION%>%
* Author                :   Jamie Starling
* Origin Date           :   %<%DATE%>%, %<%TIME%>%
* Version               :   1.0.0
* Compiler              :    
* Target                :    
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
 * 
 * 
 * 
*****************************************************************************/


/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*
*******************************************************************************/
/** @file %<%NAME%>%.%<%EXTENSION%>%
 *  @brief <TBD>
 * 
 *  <DESCRIPTION> 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "ds18b20.h"

/******************************************************************************
* Constants
*******************************************************************************/


/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
#define _DS18B20_READ_ROM_COMMAND 0x33
#define _DS18B20_SKIP_ROM_COMMAND 0xCC
#define _DS18B20_CONVERT_COMMAND 0x44
#define _DS18B20_READ_SCRATCHPAD 0xBE


/******************************************************************************
* Variables
*******************************************************************************/
typedef struct {
    uint8_t is_present;
    uint8_t crc_fail_count;
    uint8_t family_code;
    uint8_t serial_number[6];
    int16_t raw_previous_temperature_value;
    int16_t raw_current_temperature_value;
    uint8_t previous_crc_status;
    uint8_t configuration_value;
    uint8_t temperature_lsb;
    uint8_t temperature_msb;
    float temperature_in_c;
    
}DS18B20_Status_t;
DS18B20_Status_t DS18B20_Status = {.previous_crc_status = DS_CRC_FAILED};

/******************************************************************************
* Function Prototypes
*******************************************************************************/
uint8_t DS18B20_Compute_CRC(uint8_t *data, uint8_t len);
bool DS18B20_Start_Converstion(void);
uint8_t DS18B20_Read_ScratchPad(void);
/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : DS18B20_Check_Present
*//** 
* \b Description: 
* Checks for the presents of the DS18B20 on the One Wire Bus - Returns True if online
*
* <DESCRIPTION>
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
*  
* <hr>
*******************************************************************************/
bool DS18B20_Check_Present(void)
{
  uint8_t present_check = 0;
  present_check = ONE_WIRE_Reset();
  return present_check;
}

uint8_t DS18B20_Init(void)
{
  uint8_t ds_crc_value;
  uint8_t computed_crc_value;
  uint8_t ds_data[7];
  ONE_WIRE_Init();
  __delay_us(20);
  if (!DS18B20_Check_Present())  //DS18B20 will send a low pulse if present
    {
      DS18B20_Status.is_present = TRUE;
      ONE_WIRE_Write_Byte(_DS18B20_READ_ROM_COMMAND);
      ds_data[0] = ONE_WIRE_Read_Byte(); //Family
      ds_data[1] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_data[2] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_data[3] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_data[4] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_data[5] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_data[6] = ONE_WIRE_Read_Byte(); //Serial Number
      ds_crc_value = ONE_WIRE_Read_Byte(); //Crc
      
      computed_crc_value =  DS18B20_Compute_CRC(ds_data, sizeof(ds_data));
      
      if (computed_crc_value == ds_crc_value)
        {
          DS18B20_Status.is_present = TRUE;
          DS18B20_Status.family_code = ds_data[0];
          DS18B20_Status.serial_number[0] = ds_data[1];
          DS18B20_Status.serial_number[1] = ds_data[2];
          DS18B20_Status.serial_number[2] = ds_data[3];                 
          DS18B20_Status.serial_number[3] = ds_data[4];
          DS18B20_Status.serial_number[4] = ds_data[5];
          DS18B20_Status.serial_number[5] = ds_data[6];          
          DS18B20_Status.previous_crc_status = DS_OK;
          return DS_OK;
        }      
      else{
          DS18B20_Status.crc_fail_count++;
          DS18B20_Status.previous_crc_status =  DS_CRC_FAILED;
          return DS_CRC_FAILED;
        }      
    }
  
  DS18B20_Status.is_present = FALSE;
  return DS_NO_DEVICE;  
}

uint8_t DS18B20_Compute_CRC(uint8_t *data, uint8_t len)
{
  uint8_t computed_crc = 0;
  
   while (len--) {
        uint8_t byte = *data++;
        computed_crc ^= byte;
        
        for (uint8_t i = 0; i < 8; i++) {
            if (computed_crc & 0x01) {
                computed_crc = (computed_crc >> 1) ^ 0x8C;  // Polynomial is 0x31 (0x8C when shifted by 1 bit)
            } else {
                computed_crc >>= 1;
            }
        }
    }
    
    return computed_crc;  
}


uint8_t DS18B20_Get_Temperature(void)
{
    bool conversion_status;
    uint8_t read_scratchpad_status = DS_CRC_FAILED;
  
    conversion_status = DS18B20_Start_Converstion(); 
            
    if(conversion_status)
      {
        while(read_scratchpad_status == DS_CRC_FAILED){
            read_scratchpad_status = DS18B20_Read_ScratchPad();
          }
        
        // Combine the MSB and LSB into a signed 16-bit integer
        DS18B20_Status.raw_previous_temperature_value = DS18B20_Status.raw_current_temperature_value;
        DS18B20_Status.raw_current_temperature_value = (DS18B20_Status.temperature_msb << 8) | DS18B20_Status.temperature_lsb;
        DS18B20_Status.temperature_in_c = (float)(DS18B20_Status.raw_current_temperature_value * .0625);
        return DS_OK;
      }
    
    return DS_TEMPERATURE_CONVERSION_FAILED;       
}


bool DS18B20_Start_Converstion(void)
{
  if (!DS18B20_Check_Present())  //DS18B20 will send a low pulse if present
    {
       ONE_WIRE_Write_Byte(_DS18B20_SKIP_ROM_COMMAND);
       ONE_WIRE_Write_Byte(_DS18B20_CONVERT_COMMAND);
       //Wait until conversion is complete
       __delay_ms(1000);
       return TRUE;
    }
  return FALSE;
}

uint8_t DS18B20_Read_ScratchPad(void)
{
    uint8_t ds_crc_value;
    uint8_t computed_crc_value;
    uint8_t ds_data[8];

    if (!DS18B20_Check_Present()){  //DS18B20 will send a low pulse if present
       
            ONE_WIRE_Write_Byte(_DS18B20_SKIP_ROM_COMMAND);
            ONE_WIRE_Write_Byte(_DS18B20_READ_SCRATCHPAD);
            ds_data[0] = ONE_WIRE_Read_Byte(); 
            ds_data[1] = ONE_WIRE_Read_Byte(); 
            ds_data[2] = ONE_WIRE_Read_Byte(); 
            ds_data[3] = ONE_WIRE_Read_Byte(); 
            ds_data[4] = ONE_WIRE_Read_Byte(); 
            ds_data[5] = ONE_WIRE_Read_Byte(); 
            ds_data[6] = ONE_WIRE_Read_Byte(); 
            ds_data[7] = ONE_WIRE_Read_Byte();                      
            ds_crc_value = ONE_WIRE_Read_Byte(); //CRC
            
            computed_crc_value =  DS18B20_Compute_CRC(ds_data, sizeof(ds_data));
            
            if (computed_crc_value == ds_crc_value){           
                DS18B20_Status.previous_crc_status = DS_OK;
                DS18B20_Status.configuration_value = ds_data[4];
                DS18B20_Status.temperature_lsb = ds_data[0];
                DS18B20_Status.temperature_msb = ds_data[1];
                return DS_OK;
              }
            
            else{       
                DS18B20_Status.crc_fail_count++;
                DS18B20_Status.previous_crc_status =  DS_CRC_FAILED;
                return DS_CRC_FAILED;
              }           
      }
    return DS_NO_DEVICE;
}



/*** End of File **************************************************************/
