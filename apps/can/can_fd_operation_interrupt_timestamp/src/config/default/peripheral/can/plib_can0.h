/*******************************************************************************
  CAN Peripheral Library Interface Header File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_can0.h

  Summary:
    CAN PLIB interface declarations.

  Description:
    The CAN plib provides a simple interface to manage the CAN modules on
    Microchip microcontrollers. This file defines the interface declarations
    for the CAN plib.

  Remarks:
    None.

*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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
//DOM-IGNORE-END

#ifndef PLIB_CAN0_H
#define PLIB_CAN0_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

/*
 * This section lists the other files that are included in this file.
 */
#include <stdbool.h>
#include <string.h>

#include "device.h"
#include "plib_can_common.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
#define CAN0_CLOCK_FREQUENCY    36000000U

/* CAN0 Message RAM Configuration Size */
#define CAN0_RX_FIFO0_ELEMENT_SIZE       72U
#define CAN0_RX_FIFO0_SIZE               72U
#define CAN0_RX_FIFO1_ELEMENT_SIZE       72U
#define CAN0_RX_FIFO1_SIZE               72U
#define CAN0_RX_BUFFER_ELEMENT_SIZE      72U
#define CAN0_RX_BUFFER_SIZE              72U
#define CAN0_TX_FIFO_BUFFER_ELEMENT_SIZE 72U
#define CAN0_TX_FIFO_BUFFER_SIZE         72U
#define CAN0_TX_EVENT_FIFO_SIZE          8U
#define CAN0_STD_MSG_ID_FILTER_SIZE      8U
#define CAN0_EXT_MSG_ID_FILTER_SIZE      16U

/* CAN0_MESSAGE_RAM_CONFIG_SIZE to be used by application or driver
   for allocating buffer from non-cached contiguous memory */
#define CAN0_MESSAGE_RAM_CONFIG_SIZE     320U

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
void CAN0_Initialize(void);
bool CAN0_MessageTransmitFifo(uint8_t numberOfMessage, CAN_TX_BUFFER *txBuffer);
uint8_t CAN0_TxFifoFreeLevelGet(void);
bool CAN0_TxBufferIsBusy(uint8_t bufferNumber);
bool CAN0_TxEventFifoRead(uint8_t numberOfTxEvent, CAN_TX_EVENT_FIFO *txEventFifo);
bool CAN0_MessageReceive(uint8_t bufferNumber, CAN_RX_BUFFER *rxBuffer);
bool CAN0_MessageReceiveFifo(CAN_RX_FIFO_NUM rxFifoNum, uint8_t numberOfMessage, CAN_RX_BUFFER *rxBuffer);
CAN_ERROR CAN0_ErrorGet(void);
void CAN0_ErrorCountGet(uint8_t *txErrorCount, uint8_t *rxErrorCount);
void CAN0_MessageRAMConfigSet(uint8_t *msgRAMConfigBaseAddress);
bool CAN0_StandardFilterElementSet(uint8_t filterNumber, can_mram_sidfe_registers_t *stdMsgIDFilterElement);
bool CAN0_StandardFilterElementGet(uint8_t filterNumber, can_mram_sidfe_registers_t *stdMsgIDFilterElement);
bool CAN0_ExtendedFilterElementSet(uint8_t filterNumber, can_mram_xidfe_registers_t *extMsgIDFilterElement);
bool CAN0_ExtendedFilterElementGet(uint8_t filterNumber, can_mram_xidfe_registers_t *extMsgIDFilterElement);
void CAN0_SleepModeEnter(void);
void CAN0_SleepModeExit(void);
bool CAN0_BitTimingCalculationGet(CAN_BIT_TIMING_SETUP *setup, CAN_BIT_TIMING *bitTiming);
bool CAN0_BitTimingSet(CAN_BIT_TIMING *bitTiming);
void CAN0_TxFifoCallbackRegister(CAN_TX_FIFO_CALLBACK callback, uintptr_t contextHandle);
void CAN0_TxEventFifoCallbackRegister(CAN_TX_EVENT_FIFO_CALLBACK callback, uintptr_t contextHandle);
void CAN0_RxBuffersCallbackRegister(CAN_TXRX_BUFFERS_CALLBACK callback, uintptr_t contextHandle);
void CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_NUM rxFifoNum, CAN_RX_FIFO_CALLBACK callback, uintptr_t contextHandle);
void CAN0_CallbackRegister(CAN_CALLBACK callback, uintptr_t contextHandle);
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
// DOM-IGNORE-END

#endif // PLIB_CAN0_H

/*******************************************************************************
 End of File
*/
