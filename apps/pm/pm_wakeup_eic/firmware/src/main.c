/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


#define LED_ON LED_Clear
#define LED_OFF LED_Set

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
enum
{
  IDLE_SLEEP_MODE = 'a',
  STANDBY_SLEEP_MODE = 'b',
  HIBERNATE_SLEEP_MODE = 'c',
  OFF_SLEEP_MODE ='d',
}SLEEP_MODES;

static uint8_t cmd = 0;

static void timeout (uintptr_t context)
{
    LED_Toggle();    
}

void display_menu (void)
{
    printf("\n\n\n\rSelect the low power mode to enter");
    printf("\n\ra) Idle Sleep Mode");
    printf("\n\rb) Standby Sleep Mode"); 
    printf("\n\rc) Hibernate Sleep Mode");
    printf("\n\rd) Off Sleep Mode");
    printf("\n\rEnter your choice");    
    scanf("%c", &cmd);
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    RSTC_BKUPEXIT_CAUSE reset_cause_bkup;
    RSTC_RESET_CAUSE reset_cause;
    
    /* The AT module generates an interrupt after POR reset. The application must clear
     the interrupt flag or the AT will continue to request the MCLK and prevent the device
     from entering the sleep modes.
     */
    AT_REGS->AT_anti_tamper__STAT = AT_REGS->AT_anti_tamper__STAT;
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    reset_cause_bkup = RSTC_BackupExitCauseGet();
    reset_cause = RSTC_ResetCauseGet();
    
    printf("\n\n\r----------------------------------------------");
    printf("\n\r                 LOW power demo using EIC"               );
    printf("\n\r----------------------------------------------"); 
    
    printf("\r\nreset_cause_bkup :%x\r\n",(unsigned int)reset_cause_bkup);
    printf("\r\nreset_cause :%x\r\n",(unsigned int)reset_cause);

    if((reset_cause & RSTC_RCAUSE_EXT_Msk) == RSTC_RCAUSE_EXT_Msk)
        printf("\n\n\rDevice exited from Hibernate mode\n");
    else if(reset_cause == RSTC_RCAUSE_POR_Msk)
        printf("\n\n\rDevice exited from OFF mode\n");
    
    SYSTICK_TimerCallbackSet(&timeout, (uintptr_t) NULL);
    SYSTICK_TimerStart();
    
    display_menu();
    
    while(1)
    {
        switch(cmd)
        {
            case IDLE_SLEEP_MODE:
            {
                printf("\n\rEntering IDLE SLEEP Mode");
                printf("\n\rPress SW0 to wakeup the device"); 
                SYSTICK_TimerStop();
                LED_OFF();
                PM_IdleModeEnter();
                printf("\n\rSW0 Pressed exiting Sleep mode......");
                SYSTICK_TimerStart();
                display_menu();
                break;
            }
            case STANDBY_SLEEP_MODE:
            {
                printf("\n\rEntering STANDBY SLEEP Mode");
                printf("\n\rPress SW0 to wakeup the device");   
                SYSTICK_TimerStop();
                LED_OFF();
                PM_StandbyModeEnter();
                printf("\n\rSW0 Pressed exiting Standby mode......");
                SYSTICK_TimerStart();
                display_menu();
                break;
            }
            case HIBERNATE_SLEEP_MODE:
            {
                printf("\n\rEntering HIBERNATE SLEEP Mode");
                printf("\n\rPress Reset button to wakeup the device   "); 
                SYSTICK_TimerStop();
                LED_OFF();
                PM_HibernateModeEnter();
                break;
            }
            case OFF_SLEEP_MODE:
            {
                printf("\n\rEntering OFF SLEEP Mode");
                printf("\n\rPress Reset button to wakeup the device  ");   
                SYSTICK_TimerStop();
                LED_OFF();
                PM_OffModeEnter();
                break;
            }
            default:
            {
                printf("\n\rInvalid choice");
                display_menu();
                break;
            }
        } 
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

