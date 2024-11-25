/****************************************************************************
* Title                 :   LCD I2C Drivers
* Filename              :   lcd_i2c.c
* Author                :   Jamie Starling
* Origin Date           :   2024/10/15
* Version               :   1.0.2
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

/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*   2024/10/16  1.0.0   Jamie Starling  Initial Version
*   2024/10/26  1.0.1   Jamie Starling  Various Timing Fixes after Initialize and Clear 
*   2024/11/03  1.0.2   Jamie Starling  Changed to use new I2C API 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "lcd_i2c.h"

/******************************************************************************
* I2C1 Interface
*******************************************************************************/
const LCD_I2C_Interface_t LCD = {
  .Initialize = &LCD_I2C_init,
  .BlackLight = &LCD_I2C_BackLight,
  .Location = &LCD_I2C_Location,
  .Clear = &LCD_I2C_Clear_Display,
  .Write_Character = &LCD_I2C_Write_Character,
  .Write = &LCD_I2C_Write_String          
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
/******************************************************************************
* Functions
*******************************************************************************/

/******************************************************************************
* Function : LCD_I2C_init()
* Description: Initializes the I2C communication for an LCD module at a given address. 
* It sets up the LCD data structure, initializes the I2C module, checks the address, 
* and starts the LCD in 4-bit mode.
*
* @param address - The I2C address of the LCD.
* @return LCD_I2C_Status_Enum_t - Status of the initialization.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_init(uint8_t address)
{  
  //Clear the LCD Data Structure
  LCD_Data.byte = 0x00;
  
  //Initialize I2C 
  I2C1_MASTER.Initialize(); 
  
  // Check if the provided I2C address is valid
  if (I2C1_MASTER.WriteData(address,0,&LCD_Data.byte) != I2C_OK){return LCD_I2C_INVALID_ADDRESS;}  
  
  // Start LCD initialization in 4-bit mode and check for errors
  if (LCD_I2C_Start_LCD_Init_4bitMode(address) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}  
  
  // Initial delay to allow LCD setup
  __delay_ms(_LCD_INIT_DELAY_MS);  
  
  return LCD_I2C_OK;  
}


/******************************************************************************
* Function : LCD_I2C_Start_LCD_Init_4bitMode()
* Description: Initializes the LCD module in 4-bit mode using the I2C interface.
* Sends the initialization sequence commands to configure the LCD.
*
* @param address - The I2C address of the LCD.
* @return LCD_I2C_Status_Enum_t - Status of the initialization.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Start_LCD_Init_4bitMode(uint8_t address)
{
    LCD_I2C_Status_Enum_t LCD_Status; 
    
    // Send the first part of the 4-bit initialization sequence
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_4bit_Mode_1));  
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_4bit_Mode_1));
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    // Send the second part of the 4-bit initialization sequence
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_4bit_Mode_2));
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_4bit_Mode_2));
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    // Delay to allow the LCD to process the command
    __delay_ms(_LCD_INIT_DELAY_MS);
    
    // Set function mode
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_Function_Set));
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_Function_Set)); 
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    // Delay to allow the LCD to process the command
    __delay_ms(_LCD_INIT_DELAY_MS);
  
    // Set display mode
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_Display_Set));
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_Display_Set)); 
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    // Delay to allow the LCD to process the command
    __delay_ms(_LCD_INIT_DELAY_MS); 
    
    // Clear the display
    LCD_Status = LCD_I2C_Clear_Display(address);
    if (LCD_Status != LCD_I2C_OK) {return LCD_Status;}
    
    return LCD_I2C_OK;
}


/******************************************************************************
* Function : LCD_I2C_Send()
* Description: Sends data or a command to the LCD over I2C. The RS bit determines if the data
* is a command (RS = 0) or data (RS = 1).
*
* @param address - The I2C address of the LCD.
* @param RS - Boolean value; true for data, false for command.
* @param data - The data byte to send.
*
* @return LCD_I2C_Status_Enum_t - Status of the transmission.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Send(uint8_t address, bool RS, uint8_t data)
{  
  LCD_Data.bits.LCD_DATA = data;
  LCD_Data.bits.RS = RS;  //Set RS 
  
  // First pass with EN Low 
  __delay_us(_LCD_DATA_DELAY_US);
  LCD_Data.bits.EN = LOW;
  if (I2C1_MASTER.WriteData(address,1,&LCD_Data.byte) != I2C_OK){ return LCD_I2C_GENERIC_ERROR; }

  // Second pass with EN High
   __delay_us(_LCD_DATA_DELAY_US);
  LCD_Data.bits.EN = HIGH;
  if (I2C1_MASTER.WriteData(address,1,&LCD_Data.byte) != I2C_OK) { return LCD_I2C_GENERIC_ERROR; }

  // Third pass with EN Low again
   __delay_us(_LCD_DATA_DELAY_US);
  LCD_Data.bits.EN = LOW;
  if (I2C1_MASTER.WriteData(address,1,&LCD_Data.byte) != I2C_OK) { return LCD_I2C_GENERIC_ERROR; }  
  return LCD_I2C_OK;  
}

/******************************************************************************
* Function : LCD_I2C_BackLight()
* Description: Controls the LCD backlight state (on or off).
*
* @param address - The I2C address of the LCD.
* @param set_light - The desired state of the backlight (ON or OFF).
* 
* @return LCD_I2C_Status_Enum_t - Status of the transmission.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_BackLight(uint8_t address, LogicEnum_t set_light)
{  
  // Set backlight bit based on the input state
  LCD_Data.bits.BackLight = (set_light == ON) ? 1 : 0;    
  LCD_Data.bits.LCD_DATA = 0x00;  // Clear data bits if not needed for backlight control
  
  // Write to the LCD and check for errors
  if (I2C1_MASTER.WriteData(address,1,&LCD_Data.byte) != I2C_OK){return LCD_I2C_GENERIC_ERROR;}    
  return LCD_I2C_OK;  
}

/******************************************************************************
* Function : LCD_I2C_Location()
* Description: Sets the cursor position on the LCD display.
*
* @param address - The I2C address of the LCD.
* @param row - The row number (0-based index).
* @param column - The column number (0-based index).
*
*  @return LCD_I2C_Status_Enum_t - Status of the transmission.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Location(uint8_t address, uint8_t row, uint8_t column)
{
  uint8_t location_data;  
  
  // Determine the starting address based on the row
  switch (row) {
        case 0: location_data = _LCD_LINE_1 + column; break;  // Line 1
        case 1: location_data = _LCD_LINE_2 + column; break;  // Line 2
        case 2: location_data = _LCD_LINE_3 + column; break;  // Line 3 (for 4-line displays)
        case 3: location_data = _LCD_LINE_4 + column; break;  // Line 4 (for 4-line displays)
        default: return LCD_I2C_GENERIC_ERROR;  // Invalid row
    }
  
  // Combine with the command for setting the DDRAM address
  location_data = (0x80 | location_data);
  
  if(LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(location_data)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  if(LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(location_data)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(location_data));
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(location_data));
  
  return LCD_I2C_OK;  
}

/******************************************************************************
* Function : LCD_I2C_Clear_Display()
* Description: Clears the LCD display and resets the cursor to the home position.
*
* @param address - The I2C address of the LCD.
* @return LCD_I2C_Status_Enum_t - Status of the operation.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Clear_Display(uint8_t address)
{
  if(LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_CLEAR)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  if(LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_CLEAR)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.High4(_LCD_CMD_CLEAR));
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_CMD,CORE.Low4(_LCD_CMD_CLEAR));  
  
  // Delay for the LCD to process the clear command
  __delay_ms(_LCD_CLEAR_DELAY_MS); 
  
  // Return success if both commands succeeded
  return LCD_I2C_OK;
}

/******************************************************************************
* Function : LCD_I2C_Write_Character()
* Description: Writes a character to the LCD display.
*
* @param address - The I2C address of the LCD.
* @param character - The ASCII character to write to the display.
* 
* @return LCD_I2C_Status_Enum_t - Status of the operation.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Write_Character(uint8_t address, uint8_t character)
{
  if(LCD_I2C_Send(address,_LCD_RS_DATA,CORE.High4(character)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  if(LCD_I2C_Send(address,_LCD_RS_DATA,CORE.Low4(character)) != LCD_I2C_OK){return LCD_I2C_GENERIC_ERROR;}
  
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_DATA,CORE.High4(character));
  //LCD_Status = LCD_I2C_Send(address,_LCD_RS_DATA,CORE.Low4(character));
  
  return LCD_I2C_OK;
}

/******************************************************************************
* Function : LCD_I2C_Write_String()
* Description: Writes a string to the LCD display.
*
* @param address - The I2C address of the LCD.
* @param StringData - The null-terminated string to display.
* 
* @return LCD_I2C_Status_Enum_t - Status of the last character written.
*******************************************************************************/
LCD_I2C_Status_Enum_t LCD_I2C_Write_String(uint8_t address, char *StringData)
{
  LCD_I2C_Status_Enum_t LCD_Status = LCD_I2C_OK;
    
  // Loop through the string until the null terminator is reached
  for (uint8_t i = 0; StringData[i] != '\0'; i++) {
    LCD_Status = LCD_I2C_Write_Character(address, StringData[i]);
        
    // If any write operation fails, return immediately
    if (LCD_Status != LCD_I2C_OK) {
        return LCD_Status;
        }
    }
return LCD_Status;  // Return the last status (OK if all characters succeed)
}



/*** End of File **************************************************************/
