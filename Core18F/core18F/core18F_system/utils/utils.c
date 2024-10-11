/****************************************************************************
* Title                 :   Core MCU Framework Generic Utilities
* Filename              :   utils.c
* Author                :   Jamie Starling
* Origin Date           :   2024/08/15
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
 * 
 * 
 * 
*****************************************************************************/

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
* Function : CORE18F_Make_16
*//** 
* \b Description:
*
* Combines two 8-bit values into a single 16-bit value.
 * This function takes two 8-bit values (a high byte and a low byte) and 
 * combines them into a 16-bit value, with the high byte in the upper 8 bits
 * and the low byte in the lower 8 bits.
*  
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param[in] high_byte  The high 8 bits of the resulting 16-bit value.	
  @param[in] low_byte   The low 8 bits of the resulting 16-bit value.
*
* @return  A 16-bit value constructed from the high and low bytes. 		
*
* \b Example:
* @code
* 	
* uint16_t result = CORE18F_Make_16(0x12, 0x34); // Result will be 0x1234.
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/

uint16_t CORE18F_Make_16(uint8_t high_byte, uint8_t low_byte)
{
  // Combine the high byte and low byte into a 16-bit value
  uint16_t combined_value = ((uint16_t)high_byte << 8) | low_byte;
  
  // Return the combined result
  return combined_value;
}
/*** End of File **************************************************************/
