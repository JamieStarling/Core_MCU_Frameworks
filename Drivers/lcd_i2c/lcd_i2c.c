/****************************************************************************
* Title                 :   LCD I2C Drivers
* Filename              :   lcd_i2c.c
* Author                :   Jamie Starling
* Origin Date           :   2024/10/15
* Version               :   1.0.0
* Compiler              :   XC8
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
*   2024/10/16  1.0.0       Jamie Starling  Initial Version
* 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "lcd_i2c.h"
#include <string.h>

/******************************************************************************
* I2C1 Interface
*******************************************************************************/
const LCD_I2C_Interface_t LCD = {
  .Initialize = &LCD_I2C_init,
  .BlackLight = &LCD_I2C_BackLight,
  .Location = &LCD_I2C_Location,
  .Clear = &LCD_I2C_Clear_Display,
  .Write_Character = &LCD_I2C_Write_Character,
  .Write_String = &LCD_I2C_Write_String
};

/******************************************************************************
* Variables 
*******************************************************************************/
LCD_DATA_ByteAccess LCD_Data;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void LCD_I2C_Check_BUS_Status(void);
LCD_I2C_Status_Enum_t LCD_I2C_Send(uint8_t address, bool RS, uint8_t data);
LCD_I2C_Status_Enum_t LCD_I2C_Check_Address(uint8_t address);
LCD_I2C_Status_Enum_t LCD_I2C_Start_LCD_Init_4bitMode(uint8_t address);
LCD_I2C_Status_Enum_t LCD_Send_I2C_Data(uint8_t address,uint8_t en_value);
/******************************************************************************
* Functions
*******************************************************************************/

/*Init Function - Called First*/
LCD_I2C_Status_Enum_t LCD_I2C_init(uint8_t address)
{
  LCD_I2C_Status_Enum_t I2C_Status;  
  LCD_Data.byte = 0x00;
  I2C1_MASTER.Initialize(); //Initialize I2C 
  I2C_Status = LCD_I2C_Check_Address(address);  
  I2C_Status = LCD_I2C_Start_LCD_Init_4bitMode(address);
  LCD.BlackLight(0x3f,ON);  
  return I2C_Status;  
}


/*Init Function - Place LCD in 4 bit mode*/
LCD_I2C_Status_Enum_t LCD_I2C_Start_LCD_Init_4bitMode(uint8_t address)
{
  LCD_I2C_Status_Enum_t I2C_Status; 
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(_LCD_CMD_4bit_Mode_1));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(_LCD_CMD_4bit_Mode_1));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(_LCD_CMD_4bit_Mode_2));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(_LCD_CMD_4bit_Mode_2));
  CORE.Delay_MS(10);
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(_LCD_CMD_Function_Set));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(_LCD_CMD_Function_Set)); 
  CORE.Delay_MS(10);
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(_LCD_CMD_Display_Set));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(_LCD_CMD_Display_Set)); 
  CORE.Delay_MS(10);  
  I2C_Status = LCD_I2C_Clear_Display(address);
  return I2C_Status;
}


/*Function to call to send data to LCD - RS is 0 if sending command*/
LCD_I2C_Status_Enum_t LCD_I2C_Send(uint8_t address, bool RS, uint8_t data)
{
  I2C1_Status_Enum_t I2C_Status;
  LCD_Data.bits.LCD_DATA = data;
  LCD_Data.bits.RS = RS;  //Set RS 
  
  // First pass with EN Low
  if (LCD_Send_I2C_Data(address,0) != LCD_I2C_OK) { return LCD_I2C_GENERIC_ERROR; }

  // Second pass with EN High
  if (LCD_Send_I2C_Data(address,1) != LCD_I2C_OK) { return LCD_I2C_GENERIC_ERROR; }

  // Third pass with EN Low again
  if (LCD_Send_I2C_Data(address,0) != LCD_I2C_OK) { return LCD_I2C_GENERIC_ERROR; }
  
  return LCD_I2C_OK;  
}


// Helper function to send the data and handle I2C status - Takes care of EN timing
LCD_I2C_Status_Enum_t LCD_Send_I2C_Data(uint8_t address,uint8_t en_value)
{
  I2C1_Status_Enum_t I2C_Status;  
  LCD_Data.bits.EN = en_value;  // Set EN
  LCD_I2C_Check_BUS_Status();
  I2C1_MASTER.WriteStart();  // Send Start Bit
  I2C_Status = I2C1_MASTER.WriteAddress(address, I2C_ADDRESS_WRITE_MODE);
  if (I2C_Status != I2C_ADDRESS_VALID_WRITE) { return LCD_I2C_INVALID_ADDRESS; }
  I2C_Status = I2C1_MASTER.WriteByte(LCD_Data.byte);
  I2C1_MASTER.WriteStop();
  if (I2C_Status != I2C_ACK_RECEIVED) { return LCD_I2C_GENERIC_ERROR; }
  return LCD_I2C_OK;
  }



/*Checks to see if the LCD address is correct*/
LCD_I2C_Status_Enum_t LCD_I2C_Check_Address(uint8_t address)
{
  I2C1_Status_Enum_t I2C_Status;
  LCD_I2C_Check_BUS_Status();
  I2C1_MASTER.WriteStart();  //Send Start Bit
  I2C_Status = I2C1_MASTER.WriteAddress(address,I2C_ADDRESS_WRITE_MODE);
  if (I2C_Status != I2C_ADDRESS_VALID_WRITE){return LCD_I2C_INVALID_ADDRESS;}
  I2C_Status = I2C1_MASTER.WriteByte(LCD_Data.byte);
  I2C1_MASTER.WriteStop();
  if (I2C_Status != I2C_ACK_RECEIVED){return LCD_I2C_GENERIC_ERROR;}
  return LCD_I2C_OK;  
}

/*Checks the I2C Bus and Resets if needed*/
void LCD_I2C_Check_BUS_Status(void)
{
  I2C1_Bus_Status_Enum_t I2C_Status;
  I2C_Status = I2C1_MASTER.Bus_Status();
  if (I2C_Status != I2C_BUS_OK){I2C1_MASTER.Reset();}  
}

/*Turns Backligt on Off*/
LCD_I2C_Status_Enum_t LCD_I2C_BackLight(uint8_t address, LogicEnum_t set_light)
{
  I2C1_Status_Enum_t I2C_Status;
  if (set_light == ON){LCD_Data.bits.BackLight = 1;}
  if (set_light == OFF){LCD_Data.bits.BackLight = 0;}  
  LCD_I2C_Check_BUS_Status();
  if (LCD_Send_I2C_Data(address,0) != LCD_I2C_OK) { return LCD_I2C_GENERIC_ERROR;}  
  return LCD_I2C_OK;  
}

/*Set Cursor Position*/
LCD_I2C_Status_Enum_t LCD_I2C_Location(uint8_t address, uint8_t row, uint8_t column)
{
  uint8_t location_data;
  LCD_I2C_Status_Enum_t I2C_Status;
  
  switch (row) {
        case 0: location_data = _LCD_LINE_1 + column; break;  // Line 1
        case 1: location_data = _LCD_LINE_2 + column; break;  // Line 2
        case 2: location_data = _LCD_LINE_3 + column; break;  // Line 3 (for 4-line displays)
        case 3: location_data = _LCD_LINE_4 + column; break;  // Line 4 (for 4-line displays)
        default: return LCD_I2C_GENERIC_ERROR;  // Invalid row
    }
  
  location_data = (0x80 | location_data);
  
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(location_data));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(location_data));
  
  return I2C_Status;  
}


/*Clear Display*/
LCD_I2C_Status_Enum_t LCD_I2C_Clear_Display(uint8_t address)
{
  LCD_I2C_Status_Enum_t I2C_Status;
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.High4(_LCD_CMD_CLEAR));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE_UTILS.Low4(_LCD_CMD_CLEAR));  
  return I2C_Status;
}

/*Writes a Character to the Display*/
LCD_I2C_Status_Enum_t LCD_I2C_Write_Character(uint8_t address, uint8_t character)
{
  LCD_I2C_Status_Enum_t I2C_Status;
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_DATA,CORE_UTILS.High4(character));
  I2C_Status = LCD_I2C_Send(address,_LCD_RS_DATA,CORE_UTILS.Low4(character));
  return I2C_Status;
}

/*Writes a String to the Display*/
LCD_I2C_Status_Enum_t LCD_I2C_Write_String(uint8_t address, char *StringData)
{
    uint8_t counter = 0;
    size_t length = strlen(StringData);
    LCD_I2C_Status_Enum_t I2C_Status;
    
    // Loop through the string and print each character
    while (counter < length){        
        I2C_Status = LCD_I2C_Write_Character(address,StringData[counter]); // Write each byte individually
        counter++;       
    }
    return I2C_Status;
}


/*** End of File **************************************************************/
