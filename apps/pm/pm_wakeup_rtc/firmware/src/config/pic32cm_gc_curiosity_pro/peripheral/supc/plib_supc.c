/*******************************************************************************
  Supply Controller(SUPC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_supc.c

  Summary
    SUPC PLIB Implementation File.

  Description
    This file defines the interface to the SUPC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "device.h"
#include "plib_supc.h"
#include "interrupts.h"


void SUPC_Initialize( void )
{
    /* Configure BOR */
    SUPC_REGS->SUPC_BOR = SUPC_BOR_DCBORPSEL(0x1U) | SUPC_BOR_BORFILT(0x0U);

    /* Configure VREF */
    SUPC_REGS->SUPC_VREFCTRL = SUPC_VREFCTRL_LPSTDBY(0x1U) | SUPC_VREFCTRL_LPHIB(0x1U);

    /* Configure BKOUT */
    SUPC_REGS->SUPC_BKOUT = SUPC_BKOUT_TGLOM0(0x0U) | SUPC_BKOUT_TGLOM1(0x0U);

    /* Configure VREG */
    SUPC_REGS->SUPC_VREGCTRL = (SUPC_REGS->SUPC_VREGCTRL & SUPC_VREGCTRL_AVREGEN_Msk) | SUPC_VREGCTRL_VREGOUT(0x0U) | SUPC_VREGCTRL_AVREGSTDBY(0x1U);
}

void SUPC_SetOutputPin( SUPC_OUTPIN pin )
{
    if (pin == SUPC_OUTPIN_OUT0)
    {
        SUPC_REGS->SUPC_BKOUT |= SUPC_BKOUT_SET0_Msk;
    }
    else
    {
        SUPC_REGS->SUPC_BKOUT |= SUPC_BKOUT_SET1_Msk;
    }
}

void SUPC_ClearOutputPin( SUPC_OUTPIN pin )
{
    if (pin == SUPC_OUTPIN_OUT0)
    {
        SUPC_REGS->SUPC_BKOUT |= SUPC_BKOUT_CLR0_Msk;
    }
    else
    {
        SUPC_REGS->SUPC_BKOUT |= SUPC_BKOUT_CLR1_Msk;
    }
}

