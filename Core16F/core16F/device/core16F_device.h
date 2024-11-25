/****************************************************************************
* Title                 :   Core16F Target Devices
* Filename              :   core16_device.h
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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/04/25  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

#ifndef _CORE16F_DEVICE_H
#define _CORE16F_DEVICE_H

/******************************************************************************
* Includes
*******************************************************************************/
#include "../core16F.h"

// Check if the device defined is PIC16F15313 and include its configuration files
#if defined(_CORE16F_SYSTEM_DEVICE_16F15313) 
    #include "16F15313_configBits.h"        // Configuration bits for the PIC16F15313
    #include "16F15313_core16F_config.h"    // Core configuration specific to the PIC16F15313
    #include "16F15313_LU.h"                // Lookup table for registers and peripherals of the PIC16F15313

// Check if the device defined is part of the PIC16F1532X series and include respective configuration files
#elif defined(_CORE16F_SYSTEM_DEVICE_16F1532X) 
    #include "16F1532x_configBits.h"        // Configuration bits for the PIC16F1532X series
    #include "16F1532x_core16F_config.h"    // Core configuration specific to the PIC16F1532X series
    #include "16F1532x_LU.h"                // Lookup table for registers and peripherals of the PIC16F1532X series
#else
    #error "Unsupported device: Please ensure the correct device is defined."
#endif


#endif /*_CORE16F_DEVICE_H*/
/*** End of File **************************************************************/
