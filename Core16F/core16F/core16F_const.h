/****************************************************************************
* Title                 :   Core8 Constants
* Filename              :   core16_const.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.1
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
#define _CORE_POINTER_REGISTER_SIZE uint8_t

/***Constants: Logic Values***/
/*LogicEnum_t defines common logic values for use in the Core8 framework. 
* This enum provides standard definitions for enabled/disabled states, boolean values,
* pin states, and common control settings.*/
typedef enum
{   DISABLED        = 0x0U,	
    ENABLED         = 0x1U,	
    FALSE           = 0x0U,		
    TRUE            = 0x1U,
    OFF             = 0x0U,
    ON              = 0x1U,
    LOW             = 0x0U,			    
    HIGH            = 0x1U, 
    NA              = 0x0U,  //Does not apply / Not Used
    CLEAR           = 0x0U,
    SET             = 0x1U,
    NO_DEVICE       = 0x0U,
    DEVICE_PRESENT  = 0x1U,
}LogicEnum_t;


/******************************************************************************
 *Defines the IO Pin Direction on the Device* 
 * Used for setting the IO Pin Direction. 
 *******************************************************************************/
typedef enum
{
    OUTPUT          = 0x0U,	
    INPUT           = 0x1U,
    INPUT_W_PULLUP  = 0x2U,
    ANALOG          = 0x3U,
    OPEN_DRAIN      = 0x4U
}PinDirectionEnum_t;


/******************************************************************************
*********Typedefs
*******************************************************************************/
typedef bool boolean;       //Alias for the standard `bool` type, for use in logical conditions.
typedef uint8_t byte;       //Alias for the standard `uint8_t`, representing an 8-bit unsigned value.
typedef unsigned int word;  //Alias for `unsigned int`, representing a 16-bit unsigned value.

#endif /*_CORE16F_SYSTEM_CONST_H_*/

/*** End of File **************************************************************/
