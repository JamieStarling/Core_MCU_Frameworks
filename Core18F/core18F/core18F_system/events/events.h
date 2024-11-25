/****************************************************************************
* Title                 :   CORE MCU Event System
* Filename              :   events.h
* Author                :   Jamie Starling
* Origin Date           :   2024/10/17
* Version               :   1.0.0
* Compiler              :   XC8 
* Target                :   PIC18 Family 
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

#ifndef _CORE18F_SYSTEM_EVENTS_H
#define _CORE18F_SYSTEM_EVENTS_H
/******************************************************************************
* Includes
*******************************************************************************/
#include "../../core18F.h"

/******************************************************************************
* Configuration
*******************************************************************************/
#define MAX_EVENTS 5                  // Maximum number of scheduled events

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct {
    uint32_t trigger_time;              // Time in milliseconds when the event should trigger
    void (*event_callback)(void);       // Function pointer to the event handler
    uint32_t interval;                  // Interval for recurring events (0 for one-time events)
    uint8_t active;                     // Flag to indicate if the event is active
} CORE_TimedEvent_t;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TimedEventSystem_Init(void);
uint8_t ScheduleEvent(uint32_t delay_ms, void (*callback)(void), uint32_t interval);
void CheckEvents(void);
void CancelEvent(void (*callback)(void));

#endif /*_H_*/

/*** End of File **************************************************************/
