/*--------------------------------------------------------------------------
File   : crc.h

Author : Hoang Nguyen Hoan          Dec. 27, 2011

Desc   : CRC calculations
		 reference : http://en.wikipedia.org/wiki/Computation_of_CRC

Copyright (c) 2011, I-SYST, all rights reserved

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
#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Calculate 8 bits CRC value
 *          Polynomial : (x7 + x3 + 1) × x (left-shifted CRC-7-CCITT)
 *          0x12 = (0x09 << 1) (MSBF/normal)
 *
 * @param   pData   : Pointer to data buffer to calculate
 *          Len     : Data length in bytes
 *          SeedVal : Initial CRC seed value
 *
 * @return 8 bits CRC value
 */
uint8_t crc8_ccitt(uint8_t *pData, int Len, uint8_t SeedVal);

/**
 * @brief   Calculate 16 bits CRC value
 *          Polynomial : x16 + x15 + x2 + 1 (CRC-16-ANSI)
 *          0x8005 (MSBF/normal)
 *
 * @param   pData   : Pointer to data buffer to calculate
 *          Len     : Data length in bytes
 *          SeedVal : Initial CRC seed value
 *
 * @return 16 bits CRC value
 */
uint16_t crc16_ansi(uint8_t *pData, int Len, uint16_t SeedVal);

/**
 * @brief   Calculate 16 bits CRC value
 *          Polynomial : x16 + x12 + x5 + 1 (CRC-16-CCITT)
 *          0x1021 (MSBF/normal)
 *
 * @param	pData 	: Pointer to data buffer to calculate
 * 			Len		: Data length in bytes
 *          SeedVal : Initial CRC seed value
 *
 * @return	16 bits CRC value
 */
uint16_t crc16_ccitt(uint8_t *pData, int Len, uint16_t SeedVal);

/**
 * Calculate 8 bits CRC value
 *
 * @param	pData 	: Pointer to data buffer to calculate
 * 			Len		: Data length in bytes
 *
 * @return	32 bits CRC value
 */
uint32_t crc32(uint8_t *pData, int Len);

#ifdef __cplusplus
}
#endif

#endif // __CRC_H__
