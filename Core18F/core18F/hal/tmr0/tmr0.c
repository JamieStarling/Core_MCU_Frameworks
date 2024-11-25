/****************************************************************************
* Title                 :   CORE MCU Framework : TMR0 for 18F devices
* Filename              :   tmr0.c
* Author                :   Jamie Starling
* Origin Date           :   2024/04/30
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
*   2024/04/30  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
****** Includes
*******************************************************************************/
#include "tmr0.h"


/******************************************************************************
* TMR0 Interface
*******************************************************************************/
const TMR0_Interface_t TIMER0 = {
  .Enable = &TMR0_Enable,
  .Set_16bitMode = &TMR0_Set_16bit_Mode,
  .Set_OutputPostscaler = &TMR0_Set_Output_Postscaler,
  .Set_ClockSource =  &TMR0_Set_Clock_Source,
  .Set_InputAsyncMode =  &TMR0_Set_Input_Async_Mode,
  .Set_PrescalerRate =  &TMR0_Set_Prescaler_Rate,
  .Read_8bitValue =  &TMR0_Get_8bit_Value,
  .Read_16bitValue =  &TMR0_Get_16bit_Value,
  .Clear_InterruptFlag =  &TMR0_Clear_Interrupt_Flag,
  .Set_InterruptEnable =  &TMR0_Enable_Interrupt,
  .IsInterruptFlagSet =  &TMR0_Interrupt_Flag_Set
};

/******************************************************************************
***** Functions
*******************************************************************************/
/******************************************************************************
* Function : TMR0_Enable()
 * 
* \b Description:
*
* Enables or disables the TMR0 module.
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 is either Disabled or Enabled Based on Parm
*
* @param[in] : LogicEnum_t values : ENABLED/DISABLED
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Enable(ENABLED); //Enable TMR0
* TMR0_Enable(DISABLED); //Disable TMR0
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Enable(LogicEnum_t setState)
{
    T0CON0bits.EN = setState;
}

/******************************************************************************
* Function : TMR0_Set_16bit_Mode()
 * 
* \b Description:
*
* Enables or Disables TMR0 16bit mode
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 16bit mode is either Disabled or Enabled Based on Parm
*
* @param[in] : LogicEnum_t values : ENABLED/DISABLED
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Set_16bit_Mode(ENABLED); //Enable TMR0 16bit mode
* TMR0_Set_16bit_Mode(DISABLED); //Disable TMR0 16bit mode
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Set_16bit_Mode(LogicEnum_t setState)
{
    T0CON0bits.MD16 = setState;
}

/******************************************************************************
* Function : TMR0_Set_Output_Postscaler()
 * 
* \b Description:
*
* Sets the Postscaler Value for TMR0
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 Postscaler Value is set Based on Parm
*
* @param[in] : TMR0_PostScaler_SelectEnum_t values : See device lookup table
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Set_Output_Postscaler(TMR0_POST_SCALE_1_1); //Set TMR0 Postscale to 1:1
* TMR0_Set_Output_Postscaler(TMR0_POST_SCALE_1_8); //Set TMR0 Postscale to 1:8
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Set_Output_Postscaler(TMR0_PostScaler_SelectEnum_t value)
{  
    T0CON0bits.OUTPS = value;
}

/******************************************************************************
* Function : TMR0_Set_Clock_Source()
 * 
* \b Description:
*
* Sets the Clock Source for TMR0
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 ClockSource Value is set Based on Parm
*
* @param[in] : TMR0_Clock_Source_SelectEnum_t values : See device lookup table
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Set_Clock_Source(TMR0_FOSC_D4); //Set TMR0 Clock Source to FOSC/4
* TMR0_Set_Clock_Source(TMR0_HFINTOSC); //Set TMR0 Clock Source to High Speed Internal OSC
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Set_Clock_Source(TMR0_Clock_Source_SelectEnum_t value)
{
  T0CON1bits.CS = value;
}

/******************************************************************************
* Function :  TMR0_Set_Input_Async_Mode()
 * 
* \b Description:
*
* Enables or Disables TMR0 Async Mode
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 Async Mode mode is either Disabled or Enabled Based on Parm
*
* @param[in] : LogicEnum_t values : ENABLED/DISABLED
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Set_Input_Async_Mode(ENABLED); //Enable TMR0 Async Mode
* TMR0_Set_Input_Async_Mode(DISABLED); //Disable TMR0 Async Mode
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Set_Input_Async_Mode(LogicEnum_t setState)
{
    T0CON1bits.ASYNC = setState;
}

/******************************************************************************
* Function : TMR0_Set_Prescaler_Rate()
 * 
* \b Description:
*
* Sets the Prescaler Value for TMR0
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 Prescaler Value is set Based on Parm
*
* @param[in] : TMR0_PreScaler_SelectEnum_t values : See device lookup table
*
* @return : None		
*
* \b Example:
* @code
* TMR0_Set_Prescaler_Rate(PRESCALER_1_1); //Set TMR0 Prescale to 1:1
* TMR0_Set_Prescaler_Rate(PRESCALER_1_64); //Set TMR0 Prescale to 1:64
* 	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Set_Prescaler_Rate(TMR0_PreScaler_SelectEnum_t value)
{
  T0CON1bits.CKPS = value;
}

/******************************************************************************
* Function :  TMR0_Get_8bit_Value()
 * 
* \b Description:
*
* Returns TMR0 8bit value from TMR0L Register.
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: 
*
* @param[in] : none
*
* @return : uint8_t value of TMR0L Register. 		
*
* \b Example:
* @code
* uint8_t var = TMR0_Get_8bit_Value(); 
*  	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint8_t TMR0_Get_8bit_Value(void)
{
  return TMR0L;
}

/******************************************************************************
* Function :  TMR0_Get_16bit_Value()
 * 
* \b Description:
*
* Returns TMR0 16bit value from combining TMR0H and TMR0L Register.
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: 
*
* @param[in] : none
*
* @return : 16bit value from combining TMR0H and TMR0L Register. 		
*
* \b Example:
* @code
* uint16_t var = TMR0_Get_16bit_Value(); 
*  	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
uint16_t TMR0_Get_16bit_Value(void)
{
  return CORE.Make16(TMR0H,TMR0L);
}

/******************************************************************************
* Function :  TMR0_Clear_Interrupt_Flag()
* 
* \b Description:
*
* Clears TMR0 Interrupt Flag
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0IF is cleared
*
* @param[in] : none
*
* @return : none		
*
* \b Example:
* @code
* TMR0_Clear_Interrupt_Flag();
*  	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Clear_Interrupt_Flag(void)        
{  
  PIR3bits.TMR0IF = 0;
}

/******************************************************************************
* Function : TMR0_Enable_Interrupt()
* 
* \b Description:
*
* Enables or Disables TMR0 Interrupt
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: TMR0 Interrupt is enabled or disabled based on parm.
*
* @param[in] : LogicEnum_t values : ENABLED/DISABLED
*
* @return : none		
*
* \b Example:
* @code
* TMR0_Enable_Interrupt(ENABLED);
* TMR0_Enable_Interrupt(DISABLED);
*  	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
void TMR0_Enable_Interrupt(LogicEnum_t setState)
{
    PIE3bits.TMR0IE = setState;
}
      
/******************************************************************************
* Function : TMR0_Interrupt_Flag_Set()
* 
* \b Description:
*
* Returns TRUE if the TMR0 Interrupt Flag is Set.
*  
* PRE-CONDITION: _CORE18F_HAL_TMR0_ENABLE in core18F.h is defined  
*
* POST-CONDITION: 
*
* @param[in] : none
*
* @return : TRUE/FALSE		
*
* \b Example:
* @code
* bool status = TMR0_Interrupt_Flag_Set();
* *  	
* @endcode
*
* 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <hr>
*******************************************************************************/
LogicEnum_t TMR0_Interrupt_Flag_Set(void)
{
  return PIR3bits.TMR0IF;
}
/*** End of File **************************************************************/
