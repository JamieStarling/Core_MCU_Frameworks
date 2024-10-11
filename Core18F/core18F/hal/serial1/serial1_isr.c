/****************************************************************************
* Title                 :   SERIAL1 ISR Handlers
* Filename              :   serial1_isr.c
* Author                :   Jamie Starling
* Origin Date           :   2024/05/10
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
*   2024/05/10  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "serial1_isr.h"
#include "serial1.h"
#include "../../isr/isr_control.h"

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : SERIAL1_ISR_RC_Enable()
*//** 
* \b Description:
*
* Enables or disables the SERIAL1 receive interrupt.
* This function enables or disables the SERIAL1 receive interrupt (RC1IE)
* depending on the `setState` parameter. 
* 
* PRE-CONDITION: SERIAL1 module must be initialized.
* 
*
* POST-CONDITION: Interrupt for ESUART Receive is enabled or disabled
*
* @param[in] setState  LogicEnum_t value to enable (ENABLED) or disable (DISABLED) the receive ISR.
*
* @return : None
*
* \b Example:
* @code
* 	
* SERIAL1_ISR_RC_Enable(ENABLED);  //Enable ISR for ESUART1 Receive
* SERIAL1_ISR_RC_Enable(DISABLED);  //Disable ISR for ESUART1 Receive
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void SERIAL1_ISR_RC_Enable(LogicEnum_t setState)
{
  if(setState) //If ENABLED enable ISR for ESUART1 Receive
    {          
      PIE4bits.U1RXIE = 1;
      ISR_Enable_System_Default();
    }
  else //Other wise Disable ISR for ESUART1 Receive
    {
      PIE4bits.U1RXIE = 0; 
    }  
  
}


/******************************************************************************
* Function : SERIAL1_ISR_Handler_RC()
*//** 
* \b Description:
* SERIAL1 receive interrupt handler.
 * This function handles the SERIAL1 receive interrupt by calling a user-defined
 * callback function (RCIRQ_HANDLER) with the received byte as a parameter. 
*  
* PRE-CONDITION:  SERIAL1 module must be initialized.
*
* POST-CONDITION: The callback function processes the received data.
*
* @param[in] RCIRQ_HANDLER  Function pointer to the user-defined receive handler function. 	
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
void __interrupt(irq(U1RX), base(_CORE18F_ISR_BASE_ADDRESS)) SERIAL1_RC_ISR(void)
{
 // Unhandled interrupts go here
}

void SERIAL1_ISR_Handler_RC(void (*RCIRQ_HANDLER)(uint8_t))
{
    if (PIR4bits.U1RXIF) //RC1IF is cleared when receive buffer is empty
    {
        RCIRQ_HANDLER(SERIAL1_GetReceivedData());
    }
}

/******************************************************************************
* Function : SERIAL1_ISR_TX_Enable()
*//** 
* \b Description:
*
* Enables or disables the SERIAL1 transmit interrupt.
* This function enables or disables the SERIAL1 transmit interrupt (TXIE)
* based on the value of `setState`. 
* 
* The TXxIF interrupt can be enabled by setting the TXxIE interrupt enable bit
* of the PIE3 register. However, the TXxIF flag bit will be set whenever the
* TXxREG is empty, regardless of the state of TXxIE enable bit.
* To use interrupts when transmitting data, set the TXxIE bit only when there
* is more data to send. Clear the TXxIE interrupt enable bit upon writing the
* last character of the transmission to the TXxREG.
*  
* PRE-CONDITION:  SERIAL1 module must be initialized.
* 
*
* POST-CONDITION: ESUART1 TX1IF - will generate an Interrupt
*
* @param[in] : setState  LogicEnum_t value to enable (ENABLED) or disable (DISABLED) the transmit ISR.	
*
* @return : None
*
* \b Example:
* @code
* SERIAL1_ISR_TX_Enable(ENABLED);  //Enable TXIF on ESUART1
* SERIAL1_ISR_TX_Enable(DISABLED);  //Disable TXIF on ESUART1
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void SERIAL1_ISR_TX_Enable(LogicEnum_t setState)
{
  if(setState) //If ENABLED - Enable TX ISR
    {
        PIE4bits.U1TXIE = 1;
        ISR_Enable_System_Default();    
    }
  else  //Otherwise Disable ESUART1 TX ISR
    {
        PIE4bits.U1TXIE = 0;
    }
   
}

/******************************************************************************
* Function : SERIAL1_ISR_Handler_TX()
*//** 
* \b Description: SERIAL1 transmit interrupt handler.
*
* The goes into the ISR function and processes the ISR for TX IRQ 
*  
* This function handles the SERIAL1 transmit interrupt by calling a user-defined
* callback function (TXIRQ_HANDLER) whenever the transmit interrupt is triggered.
* 
* PRE-CONDITION:  SERIAL1 module must be initialized.
*
* POST-CONDITION: 
*
* @param[in] TXIRQ_HANDLER  Function pointer to the user-defined transmit handler function.	
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
void __interrupt(irq(U1TX), base(_CORE18F_ISR_BASE_ADDRESS)) SERIAL1_TX_ISR(void)
{
 // Unhandled interrupts go here
}

void SERIAL1_ISR_Handler_TX(void (*TXIRQ_HANDLER)(void))
{
   if (PIR4bits.U1TXIF) //ISR is readonly - Set when Transmit buffer is empty.
    {
        TXIRQ_HANDLER();
    }
}

/*** End of File **************************************************************/
