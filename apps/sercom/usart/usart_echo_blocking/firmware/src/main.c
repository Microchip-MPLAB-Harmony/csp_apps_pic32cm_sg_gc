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

#define RX_BUFFER_SIZE 256
#define LED_ON    LED0_Clear
#define LED_OFF   LED0_Set


static char messageStart[] = "**** USART Line Echo Demo: Blocking Transfer without the interrupt ****\r\n\
**** Type a line of characters and press the Enter key. **** \r\n\
**** Entered line will be echoed back, and the LED is toggled. ****\r\n";
static char newline[] = "\r\n";
static char errorMessage[] = "\r\n**** USART error has occurred ****\r\n";
static char receiveBuffer[RX_BUFFER_SIZE] = {};
static char data = 0;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    uint16_t rxCounter=0;
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    /* Send start message */
    SERCOM4_USART_Write(&messageStart[0], sizeof(messageStart));
    
    while ( true )
    {
        /* Check if there is a received character */
        if(SERCOM4_USART_ReceiverIsReady() == true)
        {
            if(SERCOM4_USART_ErrorGet() == USART_ERROR_NONE)
            {
                SERCOM4_USART_Read(&data, 1);

                if((data == '\n') || (data == '\r'))
                {
                    SERCOM4_USART_Write(&newline[0],sizeof(newline));
                    SERCOM4_USART_Write(&receiveBuffer[0],rxCounter);
                    SERCOM4_USART_Write(&newline[0],sizeof(newline));
                    rxCounter = 0;
                    LED_Toggle();
                }
                else
                {
                    receiveBuffer[rxCounter++] = data;
                }
            }
            else
            {
                SERCOM4_USART_Write(&errorMessage[0],sizeof(errorMessage));
            }
        }
    }



    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}




/*******************************************************************************
 End of File
*/

