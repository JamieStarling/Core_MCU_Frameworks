/****************************************************************************
* Title                 :   PPS Peripheral Pin Select functions
* Filename              :   pps.h
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
* Version               :   1.0.0
* Compiler              :   XC8
* Target                :   Microchip PIC16F series
* Copyright             :   © 2024 Jamie Starling
* All Rights Reserved
*
* 
* Purpose : Functions to for mapping The Peripheral Pin Select (PPS) module
*  (PPS) module connects peripheral inputs and outputs to the device I/O pins
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
 * * 
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

#ifndef _CORE16F_PPS_H
#define _CORE16F_PPS_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core16F.h"


/******************************************************************************
* Function Prototypes
*******************************************************************************/

void PPS_MapOutput(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device);
void PPS_MapBiDirection(GPIO_Ports_t PortPin, PPSOutputPeripheralEnum_t PPS_Device, volatile uint8_t *regPPC_Input_ptr);
void PPS_MapInput(GPIO_Ports_t PortPin, volatile uint8_t *regPPC_Input_ptr);

#endif /*_CORE16F_PPS_H*/

/*** End of File **************************************************************/
