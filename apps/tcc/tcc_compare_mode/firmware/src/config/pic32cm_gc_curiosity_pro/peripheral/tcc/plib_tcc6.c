/*******************************************************************************
  Timer/Counter(TCC6) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_tcc6.c

  Summary
    TCC6 PLIB Implementation File.

  Description
    This file defines the interface to the TCC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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

#include "interrupts.h"
#include "plib_tcc6.h"







// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: TCC6 Implementation
// *****************************************************************************
// *****************************************************************************

/* Initialize TCC module in Compare Mode */
void TCC6_CompareInitialize( void )
{
    /* Reset TCC */
    TCC6_REGS->TCC_CTRLA = TCC_CTRLA_SWRST_Msk;

    while((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_SWRST_Msk) == TCC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode & prescaler */
    TCC6_REGS->TCC_CTRLA = TCC_CTRLA_PRESCALER_DIV64 | TCC_CTRLA_PRESCSYNC_PRESC ;
    /* Configure waveform generation mode */
    TCC6_REGS->TCC_WAVE = TCC_WAVE_WAVEGEN_MFRQ;



    
    TCC6_REGS->TCC_PER = 10000U;
    
    TCC6_REGS->TCC_CC[0] = 2250U;
    TCC6_REGS->TCC_CC[1] = 24U;

    /* Clear all interrupt flags */
    TCC6_REGS->TCC_INTFLAG = TCC_INTFLAG_Msk;


    while((TCC6_REGS->TCC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
}

/* Enable the counter */
void TCC6_CompareStart( void )
{
    TCC6_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
}

/* Disable the counter */
void TCC6_CompareStop( void )
{
    TCC6_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
}

uint32_t TCC6_CompareFrequencyGet( void )
{
    return (uint32_t)562500;
}

void TCC6_CompareCommandSet(TCC_COMMAND command)
{
    TCC6_REGS->TCC_CTRLBSET = (uint8_t)((uint32_t)command << TCC_CTRLBSET_CMD_Pos);
    while ((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB_Msk) == TCC_SYNCBUSY_CTRLB_Msk)
    {
        /* Wait for Write Synchronization */
    }    
}

/* Get the current counter value */
uint16_t TCC6_Compare16bitCounterGet( void )
{
    /* Write command to force COUNT register read synchronization */
    TCC6_REGS->TCC_CTRLBSET |= (uint8_t)TCC_CTRLBSET_CMD_READSYNC;

    while((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB_Msk) == TCC_SYNCBUSY_CTRLB_Msk)
    {
        /* Wait for Write Synchronization */
    }

    while((TCC6_REGS->TCC_CTRLBSET & TCC_CTRLBSET_CMD_Msk) != 0U)
    {
        /* Wait for CMD to become zero */
    }

    /* Read current count value */
    return (uint16_t)TCC6_REGS->TCC_COUNT;
}

/* Configure counter value */
void TCC6_Compare16bitCounterSet( uint16_t countVal )
{
    TCC6_REGS->TCC_COUNT = countVal;

    while((TCC6_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_COUNT_Msk) == TCC_SYNCBUSY_COUNT_Msk)
    {
        /* Wait for Write Synchronization */
    }
}

/* Configure period value */
bool TCC6_Compare16bitPeriodSet( uint16_t period )
{
    bool status = false;
    if((TCC6_REGS->TCC_STATUS & TCC_STATUS_PERBUFV_Msk) == 0U)
    {
        /* Configure period value */
        TCC6_REGS->TCC_PERBUF = period;
        status = true;
    }
    return status;
}

/* Read period value */
uint16_t TCC6_Compare16bitPeriodGet( void )
{
    /* Get period value */
    return (uint16_t)TCC6_REGS->TCC_PER;
}


/* Configure duty cycle value */
bool TCC6_Compare16bitMatchSet(TCC6_CHANNEL_NUM channel, uint16_t compareValue )
{
    bool status = false;
    if ((TCC6_REGS->TCC_STATUS & (1UL << (TCC_STATUS_CCBUFV0_Pos + (uint32_t)channel))) == 0U)
    {
        /* Set new compare value for compare channel */
        TCC6_REGS->TCC_CCBUF[channel] = compareValue & 0xFFFFFFU;
        status = true;
    }
    return status;
}




uint32_t TCC6_CompareStatusGet( void )
{
    uint32_t compare_status;
    compare_status = ((TCC6_REGS->TCC_INTFLAG));
    TCC6_REGS->TCC_INTFLAG = compare_status;
    return compare_status;
}
