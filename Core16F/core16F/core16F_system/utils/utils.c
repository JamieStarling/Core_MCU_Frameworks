/****************************************************************************
* Title                 :   Core MCU Framework Generic Utilities
* Filename              :   utils.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
* Version               :   1.0.2
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
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "utils.h"

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : CORE_Make_16
* Description: Combines two 8-bit values into a single 16-bit value, placing the high 
* byte in the upper 8 bits and the low byte in the lower 8 bits.
*
* Parameters:
*   - high_byte (uint8_t): The 8-bit value for the upper half of the result.
*   - low_byte (uint8_t): The 8-bit value for the lower half of the result.
*
* Returns:
*   - (uint16_t): The combined 16-bit value.
*  
*******************************************************************************/

uint16_t CORE_Make_16(uint8_t high_byte, uint8_t low_byte)
{
  // Combine the high byte and low byte into a 16-bit value
  uint16_t combined_value = ((uint16_t)high_byte << 8) | low_byte;
  
  // Return the combined result
  return combined_value;
}

/******************************************************************************
* Function : CORE_Return_4bit_Low
* Description: Extracts and returns the lower 4 bits (low nibble) of an 8-bit value.
*
* Parameters:
*   - byte (uint8_t): The 8-bit input value.
*
* Returns:
*   - (uint8_t): The lower 4 bits of the input.
*******************************************************************************/
uint8_t CORE_Return_4bit_Low(uint8_t byte)
{
  // Extract the lower 4 bits (mask with 0x0F)
    return (byte & 0x0F);
}

/******************************************************************************
* Function : CORE_Return_4bit_High
* Description: Extracts and returns the upper 4 bits (high nibble) of an 8-bit value.
*
* Parameters:
*   - byte (uint8_t): The 8-bit input value.
*
* Returns:
*   - (uint8_t): The upper 4 bits of the input, right-aligned.
*  
*******************************************************************************/
uint8_t CORE_Return_4bit_High(uint8_t byte)
{
  // Extract the lower 4 bits (mask with 0x0F)
    return ((byte >> 4) & 0x0F);
}

/******************************************************************************
* Function : CORE_Set_Bit
* Description: Sets a specific bit in an 8-bit value.
*
* Parameters:
*   - byte: The original 8-bit value.
*   - bit_position: The position of the bit to set (0-7).
*
* Returns:
*   - The modified 8-bit value with the specified bit set.
*******************************************************************************/
uint8_t CORE_Set_Bit(uint8_t byte, uint8_t bit_position)
{
    return byte | (uint8_t)(1 << bit_position);
}

/******************************************************************************
* Function : CORE_Clear_Bit
* Description: Clears a specific bit in an 8-bit value.
* Parameters:
*   - byte: The original 8-bit value.
*   - bit_position: The position of the bit to clear (0-7).
* Returns:
*   - The modified 8-bit value with the specified bit cleared.
*******************************************************************************/
uint8_t CORE_Clear_Bit(uint8_t byte, uint8_t bit_position)
{
    return byte & ~(uint8_t)(1 << bit_position);
}


/******************************************************************************
* Function : CORE_floatToString
* Description: Converts a floating-point number to a string representation with a specified 
* number of decimal places. The function handles both positive and negative 
* numbers and formats the output as a null-terminated string.
* 
* Parameters:
* - float number: The floating-point number to convert.
* - char* buffer: A pointer to the character array to store the resulting string.
* - uint8_t decimalPlaces: The number of decimal places to include in the output.
*******************************************************************************/
void CORE_floatToString(float number, char* buffer, uint8_t decimalPlaces)
{
    int32_t integerPart = (int32_t)number;
    int32_t decimalPart;
    uint8_t i = 0;
    bool isNegative = false;

    // Handle negative numbers
    if (number < 0) {
        isNegative = true;
        number = -number;
        integerPart = -integerPart;
    }

    // Extract integer part
    do {
        buffer[i++] = (integerPart % 10) + '0';
        integerPart /= 10;
    } while (integerPart > 0);

    // Add negative sign if necessary
    if (isNegative) {
        buffer[i++] = '-';
    }

    // Reverse the integer part
    for (uint8_t j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    // Add decimal point
    buffer[i++] = '.';

    // Extract decimal part
    number -= (int32_t)number;
    for (uint8_t j = 0; j < decimalPlaces; j++) {
        number *= 10;
    }
    decimalPart = (int32_t)number;

    // Convert decimal part to string
    for (uint8_t j = 0; j < decimalPlaces; j++) {
        buffer[i + decimalPlaces - j - 1] = (decimalPart % 10) + '0';
        decimalPart /= 10;
    }

    // Null-terminate the string
    buffer[i + decimalPlaces] = '\0';
}

/****************************************************************************** 
* Function : CORE_intToString 
* Description: Converts an integer number to a string representation. The function handles 
* both positive and negative numbers and formats the output as a null-terminated 
* string.
*
* Parameters:
* - int32_t number: The integer number to convert.
* - char* buffer: A pointer to the character array to store the resulting string.
*******************************************************************************/
void CORE_intToString(int32_t number, char* buffer)
{
    uint8_t i = 0;
    bool isNegative = false;

    // Handle negative numbers
    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    // Extract digits and store them in the buffer
    do {
        buffer[i++] = (number % 10) + '0';
        number /= 10;
    } while (number > 0);

    // Add negative sign if necessary
    if (isNegative) {
        buffer[i++] = '-';
    }

    // Reverse the buffer to get the correct order
    for (uint8_t j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    // Null-terminate the string
    buffer[i] = '\0';
}

/*** End of File **************************************************************/
