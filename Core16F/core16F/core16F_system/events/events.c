/****************************************************************************
* Title                 :   CORE MUC Event System
* Filename              :   events.c
* Author                :   Jamie Starling
* Origin Date           :   2024/10/17
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   PIC16 Family 
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

/***************  CHANGE LIST *************************************************
*
*   Date        Version     Author          Description 
*   2024/10/17  1.0.0       Jamie Starling  Initial Version
*  
*
*****************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "events.h"

/******************************************************************************
* Variables
*******************************************************************************/
CORE_TimedEvent_t EventList[MAX_EVENTS];      // Event list

/******************************************************************************
****** Functions
*******************************************************************************/
/******************************************************************************
* Function : TimedEventSystem_Init()
* Description: Initializes the Event System
*
*  - HISTORY OF CHANGES - 
*  
*******************************************************************************/
void TimedEventSystem_Init(void)
{
    for (uint8_t i = 0; i < MAX_EVENTS; i++) {
        EventList[i].active = 0;        // Mark all events as inactive
    }
}

/******************************************************************************
* Function : ScheduleEvent()
* Description: Adds an event to the List
*
* Parameters:
*
*  - HISTORY OF CHANGES - 
*  
*******************************************************************************/
uint8_t ScheduleEvent(uint32_t delay_ms, void (*callback)(void), uint32_t interval)
{
    for (uint8_t i = 0; i < MAX_EVENTS; i++) {
        if (EventList[i].active == 0) {     // Find an available slot
            EventList[i].trigger_time = ISR_CORE16F_SYSTEM_TIMER_GetMillis() + delay_ms;
            EventList[i].event_callback = callback;
            EventList[i].interval = interval;
            EventList[i].active = 1;
            return 1;  // Successfully scheduled
        }
    }
    return 0;  // No available slots
}

/******************************************************************************
* Function : CheckEvents()
* Description: Checks the Event list - Add in to Main Loop
*
*  - HISTORY OF CHANGES - 
*  
*******************************************************************************/
void CheckEvents(void)
{
    uint32_t current_time = ISR_CORE16F_SYSTEM_TIMER_GetMillis();
    
    for (uint8_t i = 0; i < MAX_EVENTS; i++) {
        if (EventList[i].active && (current_time >= EventList[i].trigger_time)) {
            // Trigger the event
            EventList[i].event_callback();
            
            // Reschedule the event if it's recurring, otherwise deactivate it
            if (EventList[i].interval > 0) {
                EventList[i].trigger_time += EventList[i].interval;  // Set next trigger time
            } else {
                EventList[i].active = 0;  // Deactivate one-time events
            }
        }
    }
}

/******************************************************************************
* Function : CancelEvent()
* Description: Removes an event from the list
*
* Parameters:
*
*  - HISTORY OF CHANGES - 
*  
*******************************************************************************/
void CancelEvent(void (*callback)(void))
{
    for (uint8_t i = 0; i < MAX_EVENTS; i++) {
        if (EventList[i].event_callback == callback) {
            EventList[i].active = 0;  // Mark as inactive
            break;
        }
    }
}


/*** End of File **************************************************************/
