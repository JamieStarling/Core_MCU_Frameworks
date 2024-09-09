/****************************************************************************
* Title                 :   Core8 Constants
* Filename              :   core16_const.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
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

/*************** TODO *********************************************************
 *  
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

#ifndef _CORE16F_SYSTEM_CONST_H_
#define _CORE16F_SYSTEM_CONST_H_

/******************************************************************************
********* Constants
*******************************************************************************/
/*Sets the Pointer Register Size - Set accordingly depending on target CPU*/
#define _PointerRegisterSize uint8_t

/***Constants: Logic Values***/
/*LogicEnum_t defines common logic values for use in the Core8 framework. 
* This enum provides standard definitions for enabled/disabled states, boolean values,
* pin states, and common control settings.*/
typedef enum
{   DISABLED = 0U,	
    ENABLED = 1U,	
    FALSE = 0U,		
    TRUE = 1U,
    OFF = 0U,
    ON = 1U,
    LOW = 0x0U,			    
    HIGH = 0x1U, 
    NA = 0x0U,  //Does not apply / Not Used
    CLEAR = 0U,
    SET = 1U,
    NO_DEVICE = 0U,
    DEVICE_PRESENT = 1U,
}LogicEnum_t;


/******************************************************************************
*********Typedefs
*******************************************************************************/
typedef bool boolean;       //Alias for the standard `bool` type, for use in logical conditions.
typedef uint8_t byte;       //Alias for the standard `uint8_t`, representing an 8-bit unsigned value.
typedef unsigned int word;  //Alias for `unsigned int`, representing a 16-bit unsigned value.

#endif /*_CORE16F_SYSTEM_CONST_H_*/

/*** End of File **************************************************************/
