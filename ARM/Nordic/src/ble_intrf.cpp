/*--------------------------------------------------------------------------
File   : ble_intrf.cpp

Author : Hoang Nguyen Hoan          Feb. 6, 2017

Desc   : Implementation allow the creation of generic serial interface of
		 a custom Bluetooth Smart service with multiple user defined
		 characteristics.

Copyright (c) 2017, I-SYST inc., all rights reserved

Permission to use, copy, modify, and distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright
notice and this permission notice appear in all copies, and none of the
names : I-SYST or its contributors may be used to endorse or
promote products derived from this software without specific prior written
permission.

For info or contributing contact : hnhoan at i-syst dot com

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------
Modified by          Date              Description

----------------------------------------------------------------------------*/
#include <string.h>

#include "cfifo.h"
#include "ble_intrf.h"
#include "ble_app.h"

#define NRFBLEINTRF_PACKET_SIZE		NRF_BLE_MAX_MTU_SIZE
#define NRFBLEINTRF_CFIFO_SIZE		CFIFO_TOTAL_MEMSIZE(NRFBLEINTRF_PACKET_SIZE << 1, 1)

static uint8_t s_nRFBleRxFifoMem[NRFBLEINTRF_CFIFO_SIZE];
static uint8_t s_nRFBleTxFifoMem[NRFBLEINTRF_CFIFO_SIZE];
//static uint8_t s_BleInrfWrBuffer[NRFBLEINTRF_PACKET_SIZE];
//static int s_BleIntrfWrBufferLen = 0;
static volatile bool s_bBleIntrfTxReady = true;

/**
 * @brief - Disable
 * 		Turn off the interface.  If this is a physical interface, provide a
 * way to turn off for energy saving. Make sure the turn off procedure can
 * be turned back on without going through the full init sequence
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return None
 */
void BleIntrfDisable(DEVINTRF *pDevIntrf)
{
	// TODO:
}

/**
 * @brief - Enable
 * 		Turn on the interface.
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return None
 */
void BleIntrfEnable(DEVINTRF *pDevIntrf)
{
	// TODO:
}

/**
 * @brief - GetRate
 * 		Get data rate of the interface in Hertz.  This is not a clock frequency
 * but rather the transfer frequency (number of transfers per second). It has meaning base on the
 * implementation as bits/sec or bytes/sec or whatever the case
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return Transfer rate per second
 */
int BleIntrfGetRate(DEVINTRF *pDevIntrf)
{
	return 0;	// BLE has no rate
}

/**
 * @brief - SetRate
 * 		Set data rate of the interface in Hertz.  This is not a clock frequency
 * but rather the transfer frequency (number of transfers per second). It has meaning base on the
 * implementation as bits/sec or bytes/sec or whatever the case
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 * 		Rate 	  : Data rate to be set in Hertz (transfer per second)
 *
 * @return 	Actual transfer rate per second set.  It is the real capable rate
 * 			closes to rate being requested.
 */
int BleIntrfSetRate(DEVINTRF *pDevIntrf, int Rate)
{
	return 0; // BLE has no rate
}

/**
 * @brief - StartRx
 * 		Prepare start condition to receive data with subsequence RxData.
 * This can be in case such as start condition for I2C or Chip Select for
 * SPI or precondition for DMA transfer or whatever requires it or not
 * This function must check & set the busy state for re-entrancy
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 * 		DevAddr   : The device selection id scheme
 *
 * @return 	true - Success
 * 			false - failed.
 */
bool BleIntrfStartRx(DEVINTRF *pDevIntrf, int DevAddr)
{
	return true;
}

/**
 * @brief - RxData
 * 		Receive data into pBuff passed in parameter.  Assuming StartRx was
 * called prior calling this function to get the actual data
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 * 		pBuff 	  : Pointer to memory area to receive data.
 * 		BuffLen   : Length of buffer memory in bytes
 *
 * @return	Number of bytes read
 */
int BleIntrfRxData(DEVINTRF *pDevIntrf, uint8_t *pBuff, int BuffLen)
{
	BLEINTRF *intrf = (BLEINTRF*)pDevIntrf->pDevData;
	int cnt = 0;

	while (BuffLen > 0)
	{
		int l = BuffLen;
		uint8_t *p = CFifoGetMultiple(intrf->hRxFifo, &l);
		if (p == NULL)
			break;
		memcpy(pBuff, p, l);
		BuffLen -= l;
		pBuff += l;
		cnt += l;
	}

	return cnt;
}

/**
 * @brief - StopRx
 * 		Completion of read data phase. Do require post processing
 * after data has been received via RxData
 * This function must clear the busy state for re-entrancy
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return	None
 */
void BleIntrfStopRx(DEVINTRF *pSerDev)
{
	// TODO:
}

/**
 * @brief - StartTx
 * 		Prepare start condition to transfer data with subsequence TxData.
 * This can be in case such as start condition for I2C or Chip Select for
 * SPI or precondition for DMA transfer or whatever requires it or not
 * This function must check & set the busy state for re-entrancy
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 * 		DevAddr   : The device selection id scheme
 *
 * @return 	true - Success
 * 			false - failed
 */
bool BleIntrfStartTx(DEVINTRF *pDevIntrf, int DevAddr)
{
	return true;
}

/**
 * @brief - TxData
 * 		Transfer data from pData passed in parameter.  Assuming StartTx was
 * called prior calling this function to send the actual data
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 * 		pData 	: Pointer to memory area of data to send.
 * 		DataLen : Length of data memory in bytes
 *
 * @return	Number of bytes sent
 */
int BleIntrfTxData(DEVINTRF *pDevIntrf, uint8_t *pData, int DataLen)
{
	BLEINTRF *intrf = (BLEINTRF*)pDevIntrf->pDevData;
	int cnt = 0;

	while (DataLen > 0)
	{
		int l = DataLen;
		uint8_t *p = CFifoPutMultiple(intrf->hTxFifo, &l);
		if (p == NULL)
			break;
		memcpy(p, pData, l);
		DataLen -= l;
		pData += l;
		cnt += l;
	}

	if (s_bBleIntrfTxReady == true)
	{
		s_bBleIntrfTxReady = false;
		int l = NRFBLEINTRF_PACKET_SIZE;
		uint8_t *p = CFifoGetMultiple(intrf->hTxFifo, &l);
		if (p != NULL)
		{
			uint32_t res = BleSrvcCharNotify(intrf->pBleSrv, intrf->TxCharIdx, p, l);
#if (NRF_SD_BLE_API_VERSION <= 3)
			if (res != BLE_ERROR_NO_TX_PACKETS)
#else
			if (res != NRF_ERROR_RESOURCES)
#endif
			{
				s_bBleIntrfTxReady = true;
			}
		}
	}

	return cnt;
}

/**
 * @brief - StopTx
 * 		Completion of sending data via TxData.  Do require post processing
 * after all data was transmitted via TxData.
 * This function must clear the busy state for re-entrancy
 *
 * @param
 * 		pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return	None
 */
void BleIntrfStopTx(DEVINTRF *pDevIntrf)
{

}

/**
 * @brief - Reset
 *      This function perform a reset of interface.  Must provide empty
 * function of not used.
 *
 * @param
 *      pDevIntrf : Pointer to an instance of the Device Interface
 *
 * @return  None
 */
void BleIntrfReset(DEVINTRF *pDevIntrf)
{

}

void BleIntrfRxWrCB(BLESRVC *pBleSvc, uint8_t *pData, int Offset, int Len)
{
	BLEINTRF *intrf = (BLEINTRF*)pBleSvc->pContext;

	do {
		int l = Len;
		uint8_t *p = CFifoPutMultiple(intrf->hRxFifo, &l);
		if (p == NULL)
			break;
		//int l = min(intrf->PacketSize, Len);
		memcpy(p, pData, l);
		Len -= l;
		pData += l;
	} while (Len > 0);

	if (CFifoUsed(intrf->hRxFifo) > 0 && intrf->DevIntrf.EvtCB != NULL)
	{
		intrf->DevIntrf.EvtCB(&intrf->DevIntrf, DEVINTRF_EVT_RX_DATA, NULL, 0);
	}
}

bool BleIntrfInit(BLEINTRF *pBleIntrf, const BLEINTRF_CFG *pCfg)
{
	if (pBleIntrf == NULL || pCfg == NULL)
		return false;

	if (pCfg->PacketSize <= 0 || pCfg->pRxFifoMem == NULL || pCfg->pTxFifoMem == NULL)
	{
		pBleIntrf->PacketSize = NRFBLEINTRF_PACKET_SIZE;
		pBleIntrf->hRxFifo = CFifoInit(s_nRFBleRxFifoMem, NRFBLEINTRF_CFIFO_SIZE, pBleIntrf->PacketSize, true);
		pBleIntrf->hTxFifo = CFifoInit(s_nRFBleTxFifoMem, NRFBLEINTRF_CFIFO_SIZE, pBleIntrf->PacketSize, true);
	}
	else
	{
		pBleIntrf->PacketSize = pCfg->PacketSize;
		pBleIntrf->hRxFifo = CFifoInit(pCfg->pRxFifoMem, pCfg->RxFifoMemSize, pCfg->PacketSize, true);
		pBleIntrf->hTxFifo = CFifoInit(pCfg->pTxFifoMem, pCfg->TxFifoMemSize, pCfg->PacketSize, true);
	}

	pBleIntrf->DevIntrf.pDevData = (void*)pBleIntrf;
	pBleIntrf->pBleSrv = pCfg->pBleSrv;
	pBleIntrf->pBleSrv->pContext = pBleIntrf;

	pBleIntrf->RxCharIdx = pCfg->RxCharIdx;
	pBleIntrf->TxCharIdx = pCfg->TxCharIdx;

	pBleIntrf->pBleSrv->pCharArray[pBleIntrf->RxCharIdx].WrCB = BleIntrfRxWrCB;

	pBleIntrf->DevIntrf.Enable = BleIntrfEnable;
	pBleIntrf->DevIntrf.Disable = BleIntrfDisable;
	pBleIntrf->DevIntrf.GetRate = BleIntrfGetRate;
	pBleIntrf->DevIntrf.SetRate = BleIntrfSetRate;
	pBleIntrf->DevIntrf.StartRx = BleIntrfStartRx;
	pBleIntrf->DevIntrf.RxData = BleIntrfRxData;
	pBleIntrf->DevIntrf.StopRx = BleIntrfStopRx;
	pBleIntrf->DevIntrf.StartTx = BleIntrfStartTx;
	pBleIntrf->DevIntrf.TxData = BleIntrfTxData;
	pBleIntrf->DevIntrf.StopTx = BleIntrfStopTx;
	pBleIntrf->DevIntrf.Busy = false;
	pBleIntrf->DevIntrf.MaxRetry = 0;
	pBleIntrf->DevIntrf.EvtCB = pCfg->EvtCB;

	return true;
}

bool BleIntrf::Init(const BLEINTRF_CFG &Cfg)
{
	return BleIntrfInit(&vBleIntrf, &Cfg);
}

