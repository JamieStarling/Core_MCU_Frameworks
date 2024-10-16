/****************************************************************************
* Title                 :   DS18B20 Driver
* Filename              :   ds18b20.c
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

/*************** TODO *********************************************************
 * 
 * 
 * 
*****************************************************************************/


/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*
*   2024/10/11  1.0.0       Jamie Starling  Initial Version 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "ds18b20.h"

/******************************************************************************
* Interface
*******************************************************************************/
const DS18B20_Interface_t DS18B20 = {
  .Initialize = &DS18B20_Init,
  .Read = &DS18B20_Get_TemperatureC,
  .Present = &DS18B20_Present,
  .ReadRaw = &DS18B20_Get_TemperatureRAW,
  .GetResolution = &DS18B20_Return_Resolution,
};



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
DS18B20_Status_t DS18B20_Status = {.previous_crc_status = DS18B20_STATUS_CRC_FAILED};

/******************************************************************************
* Function Prototypes
*******************************************************************************/
uint8_t DS18B20_Compute_CRC(uint8_t *data, uint8_t len);
bool DS18B20_Start_Conversion(void);
uint8_t DS18B20_Read_ScratchPad(void);
void DS18B20_Handle_CRC_Fail(void);
void DS18B20_Update_Status(uint8_t *ds_data);
void DS18B20_Read_ROM(uint8_t *ds_data, uint8_t *ds_crc_value);
void DS18B20_Read_ScratchPad_Data(uint8_t *ds_data, uint8_t *ds_crc_value);
void DS18B20_Update_ScratchPad_Status(uint8_t *ds_data);
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
  bool device_status;
  device_status = ONE_WIRE.Reset();
  if (device_status == DEVICE_PRESENT){return true;}
 else{return false;}    
}

/*DS18B20_Init*/
uint8_t DS18B20_Init(void)
{
  uint8_t receivedCRC;
  uint8_t computed_crc_value;
  uint8_t ds_data[_DS18B20_ROM_SIZE];
  
  ONE_WIRE_Init();
  __delay_us(20);
  
  if (DS18B20_Check_Present()){
      DS18B20_Status.is_present = TRUE;
      DS18B20_Read_ROM(ds_data, &receivedCRC);
      
      computed_crc_value = DS18B20_Compute_CRC(ds_data, sizeof(ds_data));
      
      /*If CRC is ok, Store data and return OK*/
      if (computed_crc_value == receivedCRC){
            DS18B20_Update_Status(ds_data);
            return DS18B20_STATUS_OK;
        }
      /*If CRC check failed, Handle Failed Event*/
      else {
            DS18B20_Handle_CRC_Fail();
            return DS18B20_STATUS_CRC_FAILED;
        }
    }/*End of If DS Present Logic*/
  
  /*If DS is not present we fail and send back no_device*/  
    DS18B20_Status.is_present = FALSE;
    return DS18B20_STATUS_NO_DEVICE;   
}


/*DS18B20_Read_ROM - Used during presents check to get ROM Data*/
void DS18B20_Read_ROM(uint8_t *ds_data, uint8_t *ds_crc_value)
{
    ONE_WIRE.WriteByte(_DS18B20_READ_ROM_COMMAND);
    for (uint8_t i = 0; i < _DS18B20_ROM_SIZE; i++) {
        ds_data[i] = ONE_WIRE.ReadByte();
    }
    *ds_crc_value = ONE_WIRE.ReadByte();
}

/*DS18B20_Update_Status - Used during presents check to update status*/
void DS18B20_Update_Status(uint8_t *ds_data)
{
    DS18B20_Status.family_code = ds_data[0];
    for (uint8_t i = 0; i < 6; i++) {
        DS18B20_Status.serial_number[i] = ds_data[i + 1];
    }
    DS18B20_Status.previous_crc_status = DS18B20_STATUS_OK;
}

/*DS18B20_Handle_CRC_Fail - Used when the CRC fails*/
void DS18B20_Handle_CRC_Fail(void)
{
    DS18B20_Status.crc_fail_count++;
    DS18B20_Status.previous_crc_status = DS18B20_STATUS_CRC_FAILED;
}

/*DS18B20_Compute_CRC - Computes the CRC*/
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

/*DS18B20_Read_Temperature*/
uint8_t DS18B20_Read_Temperature(void)
{             
    // Start the conversion process
    if (!DS18B20_Start_Conversion()) {
        return DS18B20_STATUS_TEMPERATURE_CONVERSION_FAILED;  // Failed to start conversion
    }
  
    // Try to read scratchpad data, retrying up to MAX_RETRY_COUNT times
    uint8_t retry_count = 0;
    while (DS18B20_Read_ScratchPad() == DS18B20_STATUS_CRC_FAILED && retry_count < _DS18B20_MAX_RETRY_COUNT) {        
        __delay_ms(_DS18B20_RETRY_DELAY_MS);  // Short delay before retry
        retry_count++;
    }
  
    // Check if scratchpad data was read successfully
    if (retry_count >= _DS18B20_MAX_RETRY_COUNT) {
        return DS18B20_STATUS_CRC_FAILED;  // Failed to read scratchpad data
    }
  
    // Update temperature values
    DS18B20_Status.raw_previous_temperature_value = DS18B20_Status.raw_current_temperature_value;
    DS18B20_Status.raw_current_temperature_value = (DS18B20_Status.temperature_msb << 8) | DS18B20_Status.temperature_lsb;
    
    // Calculate the temperature in Celsius
    DS18B20_Status.temperature_in_c = (float)(DS18B20_Status.raw_current_temperature_value * _DS18B20_TEMPERATURE_RESOLUTION_12bit);

    return DS18B20_STATUS_OK;  // Temperature read successfully
    
}

float DS18B20_Get_TemperatureC(void){
  if (DS18B20_Read_Temperature() == DS18B20_STATUS_OK){
      return DS18B20_Status.temperature_in_c;
    }
  else{
      return _DS18B20_INVALID_TEMPERATURE;
    }
}

int16_t DS18B20_Get_TemperatureRAW(void){
 if (DS18B20_Read_Temperature() == DS18B20_STATUS_OK){
      return DS18B20_Status.raw_current_temperature_value;
    }
  else{
      return _DS18B20_INVALID_TEMPERATURE;
    }
}


/*DS18B20_Start_Converstion*/
bool DS18B20_Start_Conversion(void)
{
  if (DS18B20_Check_Present())  
    {
       ONE_WIRE.WriteByte(_DS18B20_SKIP_ROM_COMMAND);
       ONE_WIRE.WriteByte(_DS18B20_CONVERT_COMMAND);
       //Wait until conversion is complete
       __delay_ms(_DS18B20_CONVERSION_DELAY_MS);
       return true;
    }
  return false;
}

uint8_t DS18B20_Read_ScratchPad(void)
{
    uint8_t receivedCRC;
    uint8_t computed_crc_value;
    uint8_t scratchpadData[_DS18B20_SCRATCHPAD_DATA_SIZE];

    if (DS18B20_Check_Present()){  
        
        DS18B20_Read_ScratchPad_Data(scratchpadData, &receivedCRC);
        computed_crc_value =  DS18B20_Compute_CRC(scratchpadData, sizeof(scratchpadData));
            
        if (computed_crc_value == receivedCRC) {
            DS18B20_Update_ScratchPad_Status(scratchpadData);
            return DS18B20_STATUS_OK;
        }
        else {
            DS18B20_Handle_CRC_Fail();
            return DS18B20_STATUS_CRC_FAILED;
        }
    }
    return DS18B20_STATUS_CRC_FAILED;
}


/*Return true If DS18b20 is present*/
bool DS18B20_Present(void)
{
  if (DS18B20_Status.is_present == TRUE){return true;}
  else{return false;}
}

/*Reads DS18b20 scratch pad data - Tempature etc*/
void DS18B20_Read_ScratchPad_Data(uint8_t *ds_data, uint8_t *ds_crc_value)
{
    ONE_WIRE.WriteByte(_DS18B20_SKIP_ROM_COMMAND);
    ONE_WIRE.WriteByte(_DS18B20_READ_SCRATCHPAD);
    for (uint8_t i = 0; i < _DS18B20_SCRATCHPAD_DATA_SIZE; i++) {
        ds_data[i] = ONE_WIRE.ReadByte();
    }
    *ds_crc_value = ONE_WIRE.ReadByte();
}

void DS18B20_Update_ScratchPad_Status(uint8_t *ds_data)
{
    DS18B20_Status.previous_crc_status = DS18B20_STATUS_OK;
    DS18B20_Status.configuration_value = ds_data[4];
    DS18B20_Status.temperature_lsb = ds_data[0];
    DS18B20_Status.temperature_msb = ds_data[1];
}

DS18B20_StatusEnum_t DS18B20_Return_Resolution(void)
{
  switch (DS18B20_Status.configuration_value) {
    case _DS18B20_9BIT_RESOLUTION:
      return DS18B20_RESOLUTION_9BIT;
    case _DS18B20_10BIT_RESOLUTION:
      return DS18B20_RESOLUTION_10BIT;
    case _DS18B20_11BIT_RESOLUTION:
      return DS18B20_RESOLUTION_11BIT;
    case _DS18B20_12BIT_RESOLUTION:
      return DS18B20_RESOLUTION_12BIT;
    default:
      return DS18B20_ERROR_GENERIC;      
    }     
}


/*** End of File **************************************************************/
