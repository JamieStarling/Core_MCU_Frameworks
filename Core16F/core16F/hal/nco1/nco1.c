/****************************************************************************
* Title                 :   NCO1 HAL 
* Filename              :   nco1.c
* Author                :   Jamie Starling
* Origin Date           :   2024/11/08
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


/*************** CHANGE LOG ***************************************************
*
*    Date    Version   Author         Description 
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "nco1.h"

/******************************************************************************
***** NCO1 Interface
*******************************************************************************/
const NCO1_Interface_t NCO1 = {
//  .Initialize = &NULL
};


/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Functions
*******************************************************************************/
void NCO1_Init(GPIO_Ports_t PortPin, uint32_t nco_increment_value)
{
  
  
  PPS_MapOutput(PortPin,PPSOUT_PWM3OUT);
  //Set pin and map output - NCO1OUT
  
  NCO1CONbits.N1PFM = 0; // operates in Fixed Duty Cycle mode, divide by 2
  NCO1CLKbits.N1CKS = 0b000; //FOSC for the clock source
  NCO1INC = (uint24_t)nco_increment_value;    
}

/*Enables or Disables NCO Output*/
void NCO1_Enable(LogicEnum_t setState)
{
  NCO1CONbits.N1EN = setState;
}


/*** End of File **************************************************************/
