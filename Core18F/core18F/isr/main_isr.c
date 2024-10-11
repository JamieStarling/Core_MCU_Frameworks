/****************************************************************************
* Title                 :   Main ISR Function
* Filename              :   main_isr.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/25
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
*
*******************************************************************************/
/** @file %<%NAME%>%.%<%EXTENSION%>%
 *  @brief <TBD>
 * 
 *  <DESCRIPTION> 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "../core18F.h"

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : core18_isr_routine()
*//** 
* \b Description:
*
* Interrupt Routine - add any ISR code here to be processed
*  
* PRE-CONDITION:  
* PRE-CONDITION: 
*
* POST-CONDITION: 
*
* @param[in] 	
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
void __interrupt(irq(TMR0), base(_CORE18F_ISR_BASE_ADDRESS)) TMR0_ISR(void)
{
#ifdef _CORE18F_SYSTEM_TIMER_ENABLE
    ISR_CORE18F_SYSTEM_TIMER_ISR();  //Core8 System Timer
#endif
}
    
void __interrupt(irq(default), base(_CORE18F_ISR_BASE_ADDRESS)) DEFAULT_ISR(void)
{
 // Unhandled interrupts go here
}
   



/*** End of File **************************************************************/

