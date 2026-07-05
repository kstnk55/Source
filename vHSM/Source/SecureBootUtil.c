/**
 * @file SecureBootUtil.c
 * @brief Public header: SecureBootUtil.h
 * @details Overview: Provides utility functions for SecureBoot operations
 */
/********************************************************************************************/
/* File Name        : SecureBootUtil.c                                                      */
/* Date             : 2021/03/26                                                            */
/* Author           : Y.Watanabe                                                            */
/* Description      : SecureBoot utility file                                               */
/* File Version     : 0001                                                                  */
/*------------------------------------------------------------------------------------------*/
/* Revision History                                                                         */
/* No       Date            Revised by      Function Name                                   */
/* 0001     2021/03/26      Y.Watanabe      New                                             */
/********************************************************************************************/

/********************************************************************************************/
/*                          Include File Section                                            */
/********************************************************************************************/
#include "SecureBootUtil.h"

# include "vstdlib.h"
/********************************************************************************************/
/*                          Macro Definition Section                                        */
/********************************************************************************************/

/**
 * @def SB_SW_GNR_PRGRM_CMAC
 * @value FALSE
 * @resolution -
 * @brief Flag to enable/disable test-only CMAC programming generation (FALSE for normal operation, TRUE for test only)
 */
#define SB_SW_GNR_PRGRM_CMAC	(FALSE)		/* FALSE or TRUE(test only) */

/**
 * @def SB_REG_ICUM_PEFLPRG0ACK
 * @value 0x00000000UL
 * @resolution -
 * @brief CPU (PE) Flash Programming Request Acknowledge Register address (0xff1f0028H)
 */
#define SB_REG_ICUM_PEFLPRG0ACK	(0x00000000UL)	/* CPU (PE) Flash Programming Request Acknowledge Register 0(ff1f0028 H) */
													/*	2bit:FENTDUPACKA0	Automatic response setting for Data Flash Bank A/B programming requests		*/
													/*			If this bit is set to 0, the FENTDUPACK0 bit can be set.								*/
													/*		 ->	0: No automatic response is set for programming requests.								*/
													/*			1: An automatic response is set for programming requests.								*/
													/*	1bit:FENTDUPACK0	Acknowledgement of Data Flash Bank A/B programming requests					*/
													/*		 ->	0: Programming requests are disabled.													*/
													/*			1: Programming requests are enabled.													*/
													/*	0bit:FENTCUPACK0	Acknowledge of Code Flash programming requests								*/
													/*		 ->	0: Programming requests are disabled.													*/
													/*			1: Programming requests are enabled.													*/

/**
 * @def SB_REG_INT_CFLASH
 * @value 0x00C5U
 * @resolution -
 * @brief Code flash programming request for CPU (PE) interrupt enable register value (0xffffb2ccH)
 */
#define SB_REG_INT_CFLASH		(0x00C5U)		/* INTFICUIF0CFRQPE : Code flash programming request for CPU (PE) interrupt enable(ffffb2cc H) */

/**
 * @def SB_REG_INT_DFLASH
 * @value 0x00C5U
 * @resolution -
 * @brief Data flash programming request for CPU (PE) interrupt enable register value (0xffffb2ceH)
 */
#define SB_REG_INT_DFLASH		(0x00C5U)		/* INTFICUIF0DFRQPE : Data flash programming request for CPU (PE) interrupt enable(ffffb2ce H) */
													/* EI Level Interrupt Control Registers 358                                                                     */
													/* EI Level Interrupt Control Registers 359                                                                     */
													/*	15	EICTn	This bit indicates the type of an interrupt detection. This bit is read only.                   */
													/*		 ->	0: Detection with an edge                                                                           */
													/*			1: Detection of the level                                                                           */
													/*			When writing in 8-bit or 16-bit units, write the value after a reset.                               */
													/*	14, 13	-	Reserved                                                                                        */
													/*			These bits are always read as 0. The write value should always be 0.                                */
													/*	12	EIRFn	Interrupt Request Flag                                                                          */
													/*			Operation varies with the interrupt input interface.                                                */
													/*		 ->	0: No interrupt request (Initial value)                                                             */
													/*			1: Interrupt request present                                                                        */
													/*	11 to 8	-	Reserved                                                                                        */
													/*			These bits are always read as 0. The write value should always be 0.                                */
													/*	7	EIMKn	Interrupt Mask                                                                                  */
													/*		 ->	0: Interrupt processing is enabled.                                                                 */
													/*			1: Interrupt processing is disabled. (Initial value)                                                */
													/*	6	EITBn	Interrupt Vector Method Select                                                                  */
													/*			0: Direct vector method                                                                             */
													/*		 ->	1: Table reference method                                                                           */
													/*	5, 4	-	Reserved                                                                                        */
													/*			These bits are always read as 0. The write value should always be 0.                                */
													/*	3 to 0	EIPn	These bits specify 16 interrupt priority levels (0: highest priority, 15: lowest priority). */

/**
 * @def SB_TM_ICUM_ACT_LOOP
 * @value 0x00FFU
 * @resolution -
 * @brief ICU-M wait counter maximum value for polling operations
 */
#define SB_TM_ICUM_ACT_LOOP		(0x00FFU)		/* ICU-M wait counter */

/**
 * @def SB_CHK_ICUM_ACT_STS
 * @value 0x80000000UL
 * @resolution -
 * @brief Bit mask for checking ICU-M system initialization state
 */
#define SB_CHK_ICUM_ACT_STS		(0x80000000UL)	/* State in which the ICU-M system is initializing */

/**
 * @def SB_CHK_ICUMIF_ACT_STS
 * @value 0x0000F800UL
 * @resolution -
 * @brief Bit mask for checking ICUMIF startup status
 */
#define SB_CHK_ICUMIF_ACT_STS	(0x0000F800UL)	/* ICUMIF Startup status */

/**
 * @def SB_TABLE_DISABLE
 * @value 0U
 * @resolution -
 * @brief ICU-M Service Request Table status: Disabled
 */
#define SB_TABLE_DISABLE		(0U)

/**
 * @def SB_TABLE_ENABLE
 * @value 1U
 * @resolution -
 * @brief ICU-M Service Request Table status: Enabled
 */
#define SB_TABLE_ENABLE			(1U)

/**
 * @def SB_TABLE_END
 * @value 2U
 * @resolution -
 * @brief ICU-M Service Request Table status: End of table marker
 */
#define SB_TABLE_END			(2U)

/**
 * @def SB_SIZE_RDBF_START_CODE
 * @value 1U
 * @resolution -
 * @brief Size of start code in DataFlash read buffer (in bytes)
 */
#define SB_SIZE_RDBF_START_CODE	(1U)			/* start code */

/**
 * @def SB_SIZE_B64_1CHNK
 * @value 4U
 * @resolution -
 * @brief Size of one Base64 encoding chunk (4 bytes)
 */
#define SB_SIZE_B64_1CHNK		(4U)

/**
 * @def SB_SIZE_ASN1_1CHNK
 * @value 3U
 * @resolution -
 * @brief Size of one ASN.1 decoded chunk (3 bytes)
 */
#define SB_SIZE_ASN1_1CHNK		(3U)

/**
 * @def SB_B64_INVVAL
 * @value 0xFFU
 * @resolution -
 * @brief Invalid Base64 character marker
 */
#define SB_B64_INVVAL			(0xFFU)

/**
 * @def SB_B64_CRLF
 * @value 0xFEU
 * @resolution -
 * @brief Carriage Return/Line Feed marker in Base64 processing
 */
#define SB_B64_CRLF				(0xFEU)

/**
 * @def SB_B64_INIVAL
 * @value 0x00U
 * @resolution -
 * @brief Initial value for Base64 processing
 */
#define SB_B64_INIVAL			(0x00U)

/**
 * @def SB_ASN1_INIVAL
 * @value 0x00U
 * @resolution -
 * @brief Initial value for ASN.1 processing
 */
#define SB_ASN1_INIVAL			(0x00U)

/**
 * @def SB_BITSFT_2
 * @value 2U
 * @resolution -
 * @brief Bit shift value (2 bits) for Base64 decoding operations
 */
#define SB_BITSFT_2				(2U)

/**
 * @def SB_BITSFT_4
 * @value 4U
 * @resolution -
 * @brief Bit shift value (4 bits) for Base64 decoding operations
 */
#define SB_BITSFT_4				(4U)

/**
 * @def SB_BITSFT_6
 * @value 6U
 * @resolution -
 * @brief Bit shift value (6 bits) for Base64 decoding operations
 */
#define SB_BITSFT_6				(6U)

/**
 * @def SB_OFS_PEM_HEADER
 * @value 28U
 * @resolution -
 * @brief Offset to PEM header in certificate data
 */
#define SB_OFS_PEM_HEADER		(28U)

/**
 * @def SB_OFS_PEM_FOOTER
 * @value 28U
 * @resolution -
 * @brief Offset to PEM footer in certificate data
 */
#define SB_OFS_PEM_FOOTER		(28U)

/**
 * @def SB_OFS_ASN1_HEADER
 * @value 33U
 * @resolution -
 * @brief Offset to ASN.1 header in decoded certificate data
 */
#define SB_OFS_ASN1_HEADER		(33U)

/**
 * @def SB_OFS_ASN1_MOD_TO_EXP
 * @value 2U
 * @resolution -
 * @brief Offset from modulus to exponent in ASN.1 structure
 */
#define SB_OFS_ASN1_MOD_TO_EXP	(2U)

/**
 * @def SB_ASCII_CR
 * @value 0x0DU
 * @resolution -
 * @brief ASCII value of Carriage Return character
 */
#define SB_ASCII_CR				(0x0DU)

/**
 * @def SB_ASCII_LF
 * @value 0x0AU
 * @resolution -
 * @brief ASCII value of Line Feed character
 */
#define SB_ASCII_LF				(0x0AU)

/**
 * @def SB_TRY_SKIP_CRLF_MAX
 * @value 3U
 * @resolution -
 * @brief Maximum number of attempts to skip CRLF sequences during parsing
 */
#define SB_TRY_SKIP_CRLF_MAX	(3U)

/**
 * @def SB_SIZE_PEM_HEADER
 * @value 26U
 * @resolution -
 * @brief Size of PEM header in bytes
 */
#define SB_SIZE_PEM_HEADER		   (26U)

/**
 * @def SB_SIZE_PEM_FOOTER
 * @value 24U
 * @resolution -
 * @brief Size of PEM footer in bytes
 */
#define SB_SIZE_PEM_FOOTER		   (24U)

/**
 * @def SB_SIZE_EC_PEM_MAXIMUM
 * @value 236U
 * @resolution -
 * @brief Maximum size of an ECDSA public key in PEM format (in bytes)
 */
#define SB_SIZE_EC_PEM_MAXIMUM     (236U)

/**
 * @def SB_ASN1_TAG_SEQUENCE
 * @value 0x30U
 * @resolution -
 * @brief ASN.1 tag value for SEQUENCE type
 */
#define SB_ASN1_TAG_SEQUENCE       (0x30U)

/**
 * @def SB_ASN1_TAG_BIT_STR
 * @value 0x03U
 * @resolution -
 * @brief ASN.1 tag value for BIT STRING type
 */
#define SB_ASN1_TAG_BIT_STR        (0x03U)

/**
 * @def SB_ASN1_TAG_INTERGER
 * @value 0x02U
 * @resolution -
 * @brief ASN.1 tag value for INTEGER type
 */
#define SB_ASN1_TAG_INTERGER       (0x02U)

/**
 * @def SB_SIZE_ASN1_TAG_LENGTH
 * @value 0x02U
 * @resolution -
 * @brief Size of ASN.1 tag and length fields (in bytes)
 */
#define SB_SIZE_ASN1_TAG_LENGTH    (0x02U)

/**
 * @def SB_SIZE_ASN1_TAG_LEN_MAX
 * @value 0x03U
 * @resolution -
 * @brief Maximum number of bytes for ASN.1 length field (assumption)
 */
#define SB_SIZE_ASN1_TAG_LEN_MAX   (0x03U) // assumption the number of length byte maximum is 3 bytes

/**
 * @def SB_SIZE_ASN1_PK_PADDING
 * @value 0x01U
 * @resolution -
 * @brief Size of ASN.1 public key padding field (in bytes)
 */
#define SB_SIZE_ASN1_PK_PADDING    (0x01U)

/**
 * @def SB_SIZE_ASN1_PK_FORMAT
 * @value 0x01U
 * @resolution -
 * @brief Size of ASN.1 public key format field (in bytes)
 */
#define SB_SIZE_ASN1_PK_FORMAT     (0x01U)

/**
 * @def SB_ASN1_PK_UNCOMPRESSED
 * @value 0x04U
 * @resolution -
 * @brief ASN.1 public key format value for uncompressed format
 */
#define SB_ASN1_PK_UNCOMPRESSED    (0x04U)

/**
 * @def SB_ASN1_LENGTH_FORM_MASK
 * @value 0x80U
 * @resolution -
 * @brief Bit mask for extracting ASN.1 length form indicator (short or long)
 */
#define SB_ASN1_LENGTH_FORM_MASK   (0x80U)

/**
 * @def SB_ASN1_LENGTH_MASK
 * @value 0x7FU
 * @resolution -
 * @brief Bit mask for extracting ASN.1 length value
 */
#define SB_ASN1_LENGTH_MASK        (0x7FU)

/**
 * @def SB_ASN1_GET_LENGTH_FORM
 * @value (x & SB_ASN1_LENGTH_FORM_MASK)
 * @resolution -
 * @brief Macro to extract ASN.1 length form (short/long) from length byte
 */
#define SB_ASN1_GET_LENGTH_FORM(x) (x & SB_ASN1_LENGTH_FORM_MASK)

/**
 * @def SB_ASN1_GET_BYTE_LENGTH
 * @value (x & SB_ASN1_LENGTH_MASK)
 * @resolution -
 * @brief Macro to extract number of bytes in ASN.1 length field from first length byte
 */
#define SB_ASN1_GET_BYTE_LENGTH(x) (x & SB_ASN1_LENGTH_MASK)

/**
 * @def SB_ASN1_JUMP_TO_VALUE_OF_TAG
 * @value Complex macro with multiple operations
 * @resolution -
 * @brief Macro to advance a position pointer past ASN.1 tag and length fields to the value portion
 */
#define SB_ASN1_JUMP_TO_VALUE_OF_TAG(n, pos, ret, idx, padding) {\
	n = nuhSBGetLengthTlv(pos, ret); \
	idx = idx + n + padding + SB_SIZE_ASN1_TAG_LENGTH; \
}

/**
 * @def SB_ASN1_JUMP_TO_NEXT_TAG
 * @value Complex macro with multiple operations
 * @resolution -
 * @brief Macro to advance a position pointer from current tag to the next tag in ASN.1 structure
 */
#define SB_ASN1_JUMP_TO_NEXT_TAG(n, pos, ret, idx, padding) {\
	n = nuhSBGetLengthTlv(pos, ret); \
	idx = idx + n + *(ret) + padding + SB_SIZE_ASN1_TAG_LENGTH; \
}
/********************************************************************************************/
/*                          Type Definition Section                                         */
/********************************************************************************************/

/********************************************************************************************/
/*                          Enumeration Type Definition Section                             */
/********************************************************************************************/

/********************************************************************************************/
/*                          Structure/Union Type Definition Section                         */
/********************************************************************************************/

/********************************************************************************************/
/*                          Global Variable Definition Section                              */
/********************************************************************************************/

/********************************************************************************************/
/*                          Static Variable Definition Section                              */
/********************************************************************************************/

/********************************************************************************************/
/*                          Static Prototype Definition Section                             */
/********************************************************************************************/
/* 公開鍵登録関数 */
static uint8 nubSBSrRegDbgPrtPK(const uint8* aubData_p);
// static void nvdSBClearPK(void);
/* PEM変換処理関数 */
// static uint8 nubSBSrGetPKfrmPEM(const uint8* aubPem_p, const uint16 auhPemSiz,
	// const uint16 auhModSiz, uint8* aubModulus_p, uint8* aubPubExp_p);
static uint8 nubSBSrB64toDec(char asbChar);
static uint8 nuhSBGetLengthTlv(const uint8* aubPem_p, uint16* auhLength_p);

static uint8 nuhSBCheckNextTagValid(const uint8* aubAsn_p, const uint16 auhPos,
	const uint16 auhBoud, const uint8 aubExpect);

/********************************************************************************************/
/*                          Prototype Definition Section                                    */
/********************************************************************************************/

/********************************************************************************************/
/*                          Table Definition Section                                        */
/********************************************************************************************/

/********************************************************************************************/
/* Function Name    : nubSBSrRegDbgPrtPK                                                    */
/* Date             : 2022/02/18                                                            */
/* Author           : S.Kikuchi                                                             */
/* Description      :                                                                       */
/* Argument Code    :                                                                       */
/* Return Code      :                                                                       */
/*------------------------------------------------------------------------------------------*/
/* Revision History                                                                         */
/* No       Date            Revised by      Explanation                                     */
/********************************************************************************************/
// static uint8 nubSBSrRegDbgPrtPK(const uint8 *aubPK_p)
// {
// 	uint8 aubResult = SB_RTN_NG;

// 	if (NULL_PTR != aubPK_p)
// 	{
// 		/* PEMからModulus, Public Exponentを取り出し */
// 		aubResult = nubSBSrGetPKfrmPEM(aubPK_p, SB_SIZE_PEM_3072, SB_SIZE_PK_LEN_3072, &wubPKModulus_a[0U], &wubPKPubExp_a[0U]);
// 		if (SB_RTN_OK == aubResult)
// 		{
// 			/* SERVICE_03_PK_IMPORT */
// 			aubResult = wubSBSrRegPK(&wubPKModulus_a[0U], &wubPKPubExp_a[0U], NULL_PTR,
// 				SB_SIZE_PK_LEN_3072, SB_SIZE_PUBEXP, SB_SIZE_0, SB_KEYID_RSG_PUB_0, SB_SRV_FLG_EN);
// 		}
// 		else
// 		{
// 			/* 取り出し失敗 */
// 			// wvdSBUartSndMsg("[SBoot]RgDPK.CnvNG.%u\r\n", aubResult);
// 		}
// 	}
// 	else
// 	{
// 		/* Null pointer */
// 		aubResult = SB_RTN_NG;
// 		// wvdSBUartSndMsg("[SBoot]RgDPK.nul\r\n");
// 	}

// 	return aubResult;
// }

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubPem_p |Pointer to buffer containing PEM-encoded public key data |
 * |const uint16 |auhPemSiz |Size of the PEM data buffer in bytes |
 * |const uint16 |auhModSiz |Expected size of the modulus in bytes |
 * |uint8* |aubModulus_p |Pointer to buffer where extracted modulus will be stored |
 * |uint8* |aubPubExp_p |Pointer to buffer where extracted public exponent will be stored |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Operation result (SB_RTN_OK: success, SB_RTN_NG: failure due to invalid parameters or PEM format) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |aubModulus_p |Filled with the extracted modulus value from the PEM-encoded key |
 * |uint8* |aubPubExp_p |Filled with the extracted public exponent value from the PEM-encoded key |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Local variable to store the function's return status |
 * |uint8 |aubCnvBuf_a[SB_SIZE_B64_1CHNK] |Buffer for storing Base64 decoded values (4 bytes) |
 * |uint8 |aubInd |Loop counter for Base64 decoding and ASN.1 parsing |
 * |uint8 |aubIndSkpCRLF |Loop counter for skipping CRLF characters in PEM data |
 * |uint8 |aubContinue |Flag to control the main processing loop (TRUE: continue, FALSE: stop) |
 * |uint16 |auhOfsPem |Current offset position in the PEM data buffer |
 * |uint16 |auhOfsASN1 |Current offset position in the decoded ASN.1 data |
 * |uint16 |auhOfsCpyMod |Current offset for copying modulus data to output buffer |
 * |uint16 |auhOfsCpyExp |Current offset for copying public exponent data to output buffer |
 * |uint16 |auhBodyPartEnd |Offset marking the end of the PEM body section (excluding footer) |
 * |uint8 |aubCpyTmp_a[SB_SIZE_ASN1_1CHNK] |Temporary buffer for storing decoded ASN.1 data (3 bytes) |
 * |uint8 |i |General purpose loop counter |
 * @brief Function to extract RSA public key components (modulus and exponent) from PEM-encoded data
 * @note This function processes a PEM-encoded RSA public key
 */
/* author S.Kikuchi */
/* date 2022/02/18 */
/************************************************************************************************/
uint8 nubSBSrGetPKfrmPEM(const uint8* aubPem_p, const uint16 auhPemSiz,
	const uint16 auhModSiz, uint8* aubModulus_p, uint8* aubPubExp_p)
{
	uint8 aubResult = SB_RTN_OK;
	uint8 aubCnvBuf_a[SB_SIZE_B64_1CHNK] = { SB_B64_INIVAL };
	uint8 aubInd;
	uint8 aubIndSkpCRLF;
	uint8 aubContinue = TRUE;
	uint16 auhOfsPem = SB_OFS_PEM_HEADER;
	uint16 auhOfsASN1 = 0U;
	uint16 auhOfsCpyMod = 0U;
	uint16 auhOfsCpyExp = 0U;
	uint16 auhBodyPartEnd;
	uint8 aubCpyTmp_a[SB_SIZE_ASN1_1CHNK];
	uint8 i;

	if ((NULL_PTR != aubPem_p) && (NULL_PTR != aubModulus_p) && (NULL_PTR != aubPubExp_p) && (auhPemSiz >= SB_SIZE_PEM_2048))
	{
		/* 変換対象はPEMの本体部分のみ。ヘッダとフッタは含まない */
		auhBodyPartEnd = auhPemSiz - SB_OFS_PEM_FOOTER;
		while (TRUE == aubContinue)
		{
			for (i = 0U; i < sizeof(aubCnvBuf_a); ++i)
			{
				aubCnvBuf_a[i] = SB_B64_INIVAL;
			}
			for (aubInd = 0U; aubInd < SB_SIZE_B64_1CHNK; ++aubInd)
			{
				/* PEMから本来のデータに変換。改行コード(CRLF)は無視する */
				for (aubIndSkpCRLF = 0U; aubIndSkpCRLF < SB_TRY_SKIP_CRLF_MAX; ++aubIndSkpCRLF)
				{
					/* 変換対象範囲チェック */
					if (auhOfsPem < auhBodyPartEnd)
					{
						/* 1ByteずつBase64から本来の値に変換 */
						//wvdSBUartSndMsg("[SBoot]B64.%u.%02X\r\n", auhOfsPem, aubPem_p[auhOfsPem]);
						aubCnvBuf_a[aubInd] = nubSBSrB64toDec((char)aubPem_p[auhOfsPem++]);
						if (SB_B64_CRLF != aubCnvBuf_a[aubInd])
						{
							aubIndSkpCRLF = SB_TRY_SKIP_CRLF_MAX;
						}
						else
						{
							/* CRLFならば再取得 */
						}
					}
					else
					{
						/* サイズ超過 */
						aubIndSkpCRLF = SB_TRY_SKIP_CRLF_MAX;
					}
				}
			}

			if ((aubCnvBuf_a[0U] < SB_B64_CRLF) && (aubCnvBuf_a[1U] < SB_B64_CRLF) && (aubCnvBuf_a[2U] < SB_B64_CRLF) && (aubCnvBuf_a[3U] < SB_B64_CRLF))
			{
				/* ビットシフトして一時バッファに格納 */
				aubCpyTmp_a[0U] = (uint8)(aubCnvBuf_a[0U] << SB_BITSFT_2) + (uint8)(aubCnvBuf_a[1U] >> SB_BITSFT_4);
				aubCpyTmp_a[1U] = (uint8)(aubCnvBuf_a[1U] << SB_BITSFT_4) + (uint8)(aubCnvBuf_a[2U] >> SB_BITSFT_2);
				aubCpyTmp_a[2U] = (uint8)(aubCnvBuf_a[2U] << SB_BITSFT_6) + aubCnvBuf_a[3U];

				for (aubInd = 0U; aubInd < SB_SIZE_ASN1_1CHNK; ++aubInd)
				{
					if ((auhOfsASN1 >= SB_OFS_ASN1_HEADER) && (auhOfsASN1 < (SB_OFS_ASN1_HEADER + auhModSiz)))
					{
						/* Modulus部分をコピー */
						//wvdSBUartSndMsg("[SBoot]Mod.%u.%u.%u.%02X\r\n", auhOfsPem, auhOfsASN1, auhOfsCpyMod, aubCpyTmp_a[aubInd]);
						aubModulus_p[auhOfsCpyMod++] = aubCpyTmp_a[aubInd];
					}
					else if ((auhOfsASN1 >= (SB_OFS_ASN1_HEADER + auhModSiz + SB_OFS_ASN1_MOD_TO_EXP)) && (auhOfsASN1 < (SB_OFS_ASN1_HEADER + auhModSiz + SB_OFS_ASN1_MOD_TO_EXP + SB_SIZE_PUBEXP)))
					{
						/* Public Exponent部分をコピー */
						//wvdSBUartSndMsg("[SBoot]Exp.%u.%u.%u.%02X\r\n", auhOfsPem, auhOfsASN1, auhOfsCpyExp, aubCpyTmp_a[aubInd]);
						aubPubExp_p[auhOfsCpyExp++] = aubCpyTmp_a[aubInd];
					}
					else
					{
						/* Modulus, Public Exponent以外の部分は無視 */
					}
					++auhOfsASN1;
				}

				/* データ本体部分の終端ならばLoopを抜ける */
				if (auhOfsPem >= auhBodyPartEnd)
				{
					aubContinue = FALSE;
				}
				else
				{
					/* Next Loop */
				}
			}
			else
			{
				/* PEMに非サポートの値が含まれていた */
				aubResult = SB_RTN_NG;
				aubContinue = FALSE;
				// wvdSBUartSndMsg("[SBoot]PkPem.IvVl.%u.%u.%u.%u.%u\r\n", aubCnvBuf_a[0U], aubCnvBuf_a[1U], aubCnvBuf_a[2U], aubCnvBuf_a[3U], auhOfsPem);
			}
		}
	}
	else
	{
		/* 引数異常 */
		aubResult = SB_RTN_NG;
		// wvdSBUartSndMsg("[SBoot]PkPem.argNG.%u.%u.%u.%u\r\n", (NULL_PTR != aubPem_p) ? TRUE : FALSE,
		// 	(NULL_PTR != aubModulus_p) ? TRUE : FALSE, (NULL_PTR != aubPubExp_p) ? TRUE : FALSE, auhPemSiz);
	}

	return aubResult;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |char |asbChar |Base64 character to be converted to its decimal value |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubRet |Decimal value of the Base64 character (0-63 for valid characters, SB_B64_CRLF for CR/LF, 0xFF for invalid characters) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubRet |Local variable to store the function's return value, initialized with 0xFF (invalid character marker) |
 * @brief Function to convert a Base64 character to its corresponding 6-bit decimal value
 * @note This function performs Base64 character to decimal value conversion following the standard Base64 encoding
 */
/* author S.Kikuchi */
/* date 2022/02/18 */
/************************************************************************************************/
static uint8 nubSBSrB64toDec(char asbChar)
{
	uint8 aubRet = 0xFFU;

	switch ((int)asbChar)
	{
	case 'A':
		aubRet = 0U;
		break;
	case 'B':
		aubRet = 1U;
		break;
	case 'C':
		aubRet = 2U;
		break;
	case 'D':
		aubRet = 3U;
		break;
	case 'E':
		aubRet = 4U;
		break;
	case 'F':
		aubRet = 5U;
		break;
	case 'G':
		aubRet = 6U;
		break;
	case 'H':
		aubRet = 7U;
		break;
	case 'I':
		aubRet = 8U;
		break;
	case 'J':
		aubRet = 9U;
		break;
	case 'K':
		aubRet = 10U;
		break;
	case 'L':
		aubRet = 11U;
		break;
	case 'M':
		aubRet = 12U;
		break;
	case 'N':
		aubRet = 13U;
		break;
	case 'O':
		aubRet = 14U;
		break;
	case 'P':
		aubRet = 15U;
		break;
	case 'Q':
		aubRet = 16U;
		break;
	case 'R':
		aubRet = 17U;
		break;
	case 'S':
		aubRet = 18U;
		break;
	case 'T':
		aubRet = 19U;
		break;
	case 'U':
		aubRet = 20U;
		break;
	case 'V':
		aubRet = 21U;
		break;
	case 'W':
		aubRet = 22U;
		break;
	case 'X':
		aubRet = 23U;
		break;
	case 'Y':
		aubRet = 24U;
		break;
	case 'Z':
		aubRet = 25U;
		break;
	case 'a':
		aubRet = 26U;
		break;
	case 'b':
		aubRet = 27U;
		break;
	case 'c':
		aubRet = 28U;
		break;
	case 'd':
		aubRet = 29U;
		break;
	case 'e':
		aubRet = 30U;
		break;
	case 'f':
		aubRet = 31U;
		break;
	case 'g':
		aubRet = 32U;
		break;
	case 'h':
		aubRet = 33U;
		break;
	case 'i':
		aubRet = 34U;
		break;
	case 'j':
		aubRet = 35U;
		break;
	case 'k':
		aubRet = 36U;
		break;
	case 'l':
		aubRet = 37U;
		break;
	case 'm':
		aubRet = 38U;
		break;
	case 'n':
		aubRet = 39U;
		break;
	case 'o':
		aubRet = 40U;
		break;
	case 'p':
		aubRet = 41U;
		break;
	case 'q':
		aubRet = 42U;
		break;
	case 'r':
		aubRet = 43U;
		break;
	case 's':
		aubRet = 44U;
		break;
	case 't':
		aubRet = 45U;
		break;
	case 'u':
		aubRet = 46U;
		break;
	case 'v':
		aubRet = 47U;
		break;
	case 'w':
		aubRet = 48U;
		break;
	case 'x':
		aubRet = 49U;
		break;
	case 'y':
		aubRet = 50U;
		break;
	case 'z':
		aubRet = 51U;
		break;
	case '0':
		aubRet = 52U;
		break;
	case '1':
		aubRet = 53U;
		break;
	case '2':
		aubRet = 54U;
		break;
	case '3':
		aubRet = 55U;
		break;
	case '4':
		aubRet = 56U;
		break;
	case '5':
		aubRet = 57U;
		break;
	case '6':
		aubRet = 58U;
		break;
	case '7':
		aubRet = 59U;
		break;
	case '8':
		aubRet = 60U;
		break;
	case '9':
		aubRet = 61U;
		break;
	case '+':
		aubRet = 62U;
		break;
	case '/':
		aubRet = 63U;
		break;
	case '=':
		aubRet = 0U;
		break;
	case (int)SB_ASCII_CR:
	case (int)SB_ASCII_LF:
		aubRet = SB_B64_CRLF;
		break;
	default:
		// wvdSBUartSndMsg("[SBoot]CnvB64.NF.%u\r\n", (uint8)asbChar);
		break;
	}
	return aubRet;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubPem_p |Pointer to ASN.1 TLV structure data |
 * |uint16* |auhLength_p |Pointer to store the extracted length value |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubNumByteLength |Number of bytes used to encode the length field (0 for short form, 1-127 for long form) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16* |auhLength_p |Updated with the actual length value extracted from the TLV structure |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8 |aubOfsByteLength |Offset to the length byte in the TLV structure (constant value 1) |
 * |uint8 |aubNumByteLength |Number of bytes used to encode the length field |
 * |uint8 |aubIdx |Loop counter for parsing multi-byte length fields |
 * |uint16 |auhLegthRet |Accumulated length value parsed from the length field |
 * @brief Function to parse the length field in an ASN.1 Tag-Length-Value (TLV) structure
 * @note This function extracts the length field from an ASN.1 TLV structure, handling both short and long
 */
/* author FPT */
/* date 2024/07/30 */
/************************************************************************************************/
static uint8 nuhSBGetLengthTlv(const uint8* aubPem_p, uint16* auhLength_p)
{
	const uint8 aubOfsByteLength = 1u;
	uint8 aubNumByteLength;
	uint8 aubIdx;
	uint16 auhLegthRet = 0u;

	if (0u != SB_ASN1_GET_LENGTH_FORM(aubPem_p[aubOfsByteLength]))
	{
		// Long form
		// x & 0x7F --> number byte of length: x
		aubNumByteLength = SB_ASN1_GET_BYTE_LENGTH(aubPem_p[aubOfsByteLength]);
		for (aubIdx = (0u + SB_SIZE_ASN1_TAG_LENGTH); aubIdx < (aubNumByteLength + SB_SIZE_ASN1_TAG_LENGTH); ++aubIdx)
		{
			auhLegthRet = ((uint32)auhLegthRet << 8u) + (uint32)aubPem_p[aubIdx];
		}
	}
	else
	{
		// Short form
		aubNumByteLength = 0u;
		auhLegthRet = (uint32)aubPem_p[aubOfsByteLength];
	}

	*auhLength_p = auhLegthRet;
	return aubNumByteLength;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubAsn_p |Pointer to ASN.1 data buffer |
 * |const uint16 |auhPos |Current position index where the tag should be checked |
 * |const uint16 |auhBoud |Upper bound limit for the position index |
 * |const uint8 |aubExpect |Expected tag value to be found at the specified position |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Validation result (SB_RTN_OK: tag is valid and matches expected value, SB_RTN_NG: tag is invalid or out of bounds) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Local variable to store the function's validation result |
 * @brief Function to validate the next tag in an ASN.1 structure
 * @note This function validates a tag in an ASN.1
 */
/* author FPT */
/* date 2024/08/22 */
/************************************************************************************************/
static uint8 nuhSBCheckNextTagValid(const uint8* aubAsn_p, const uint16 auhPos,
	const uint16 auhBoud, const uint8 aubExpect)
{
	uint8 aubResult;

	if (auhPos > auhBoud)
	{
		// The index of tag is out of range
		aubResult = SB_RTN_NG;
	}
	else
	{
		if (aubAsn_p[auhPos] == aubExpect)
		{
			aubResult = SB_RTN_OK;
		}
		else
		{
			// Incorrect tag
			aubResult = SB_RTN_NG;
		}
	}

	return aubResult;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubPem_p |Pointer to buffer containing PEM-encoded ECDSA public key data |
 * |const uint16 |auhPemSiz |Size of the PEM data buffer in bytes |
 * |uint8* |aubPubKey_p |Pointer to buffer where extracted uncompressed public key will be stored |
 * |uint16* |auhKeySize |Pointer to variable for storing the extracted key size |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Operation result (SB_RTN_OK: success, SB_RTN_NG: failure due to invalid parameters or PEM format) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |aubPubKey_p |Filled with the extracted uncompressed ECDSA public key data |
 * |uint16* |auhKeySize |Updated with the actual size of the extracted public key in bytes |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const char |asbHeaderPattern[SB_SIZE_PEM_HEADER] |String containing the PEM header pattern for public key |
 * |const char |asbFooterPattern[SB_SIZE_PEM_FOOTER] |String containing the PEM footer pattern for public key |
 * |uint8 |aubResult |Local variable to store the function's return status |
 * |uint8 |auhCntB64Char |Counter for Base64 characters processed in current chunk |
 * |uint8 |aubBase64Decoded[SB_SIZE_B64_1CHNK] |Buffer for storing intermediate Base64 decoded values |
 * |uint8 |aubPemDecoded[SB_SIZE_EC_PEM_MAXIMUM] |Buffer for storing complete decoded PEM data |
 * |uint16 |auhIdx |Loop counter for traversing the PEM data buffer |
 * |uint16 |auhIdxDecode |Index for current position in the decoded data buffer |
 * |uint16 |auhPemStartPos |Position index for the start of PEM body (after header) |
 * |uint16 |auhPemEndPos |Position index for the end of PEM body (before footer) |
 * |uint16 |auhCntB64Padding |Counter for Base64 padding characters ('=') |
 * @brief Function to extract an uncompressed ECDSA public key from PEM-encoded data
 * @note This function processes a PEM-encoded ECDSA public key and extracts the uncompressed public key
 */
/* author FPT */
/* date 2024/07/30 */
/************************************************************************************************/
uint8 nubSBSrGetEcPKfrmPEM(const uint8* aubPem_p, const uint16 auhPemSiz,
	uint8* aubPubKey_p, uint16* auhKeySize)
{
	const char asbHeaderPattern[SB_SIZE_PEM_HEADER] = "-----BEGIN PUBLIC KEY-----";
	const char asbFooterPattern[SB_SIZE_PEM_FOOTER] = "-----END PUBLIC KEY-----";
	uint8 aubResult = SB_RTN_NG;
	uint8 auhCntB64Char;
	uint8 aubBase64Decoded[SB_SIZE_B64_1CHNK] = { SB_ASN1_INIVAL };
	uint8 aubPemDecoded[SB_SIZE_EC_PEM_MAXIMUM] = { SB_ASN1_INIVAL };
	uint16 auhIdx;
	uint16 auhIdxDecode;
	uint16 auhPemStartPos;
	uint16 auhPemEndPos;
	uint16 auhCntB64Padding = 0u;

	// Input parameters check
	if ((NULL_PTR != aubPem_p) && (0u != auhPemSiz) && (NULL_PTR != aubPubKey_p) && (NULL_PTR != auhKeySize) && (auhPemSiz > SB_SIZE_PEM_HEADER))
	{
		// Find PEM header
		auhPemStartPos = 0u;
		for (auhIdx = 0u; auhIdx <= (auhPemSiz - SB_SIZE_PEM_HEADER); ++auhIdx)
		{
			if (0 == (VStdLib_MemCmp(asbHeaderPattern, &aubPem_p[auhIdx], SB_SIZE_PEM_HEADER)))
			{
				auhPemStartPos = auhIdx + SB_SIZE_PEM_HEADER;
				auhIdx = auhPemStartPos;
				if ((aubPem_p[auhIdx] == (uint8)SB_ASCII_CR) || (aubPem_p[auhIdx] == (uint8)SB_ASCII_LF))
				{
					auhPemStartPos = auhPemStartPos + 1u;
				}
				auhIdx = auhIdx + 1u;
				if ((aubPem_p[auhIdx] == (uint8)SB_ASCII_CR) || (aubPem_p[auhIdx] == (uint8)SB_ASCII_LF))
				{
					auhPemStartPos = auhPemStartPos + 1u;
				}
				auhIdx = auhPemSiz; // Exit
			}
		}

		// Find PEM footer
		auhPemEndPos = 0u;
		for (auhIdx = 0u; auhIdx <= (auhPemSiz - SB_SIZE_PEM_FOOTER); auhIdx++)
		{
			if (0 == (VStdLib_MemCmp(asbFooterPattern, &aubPem_p[auhIdx], SB_SIZE_PEM_FOOTER)))
			{
				auhPemEndPos = auhIdx;
				auhIdx = (uint16)auhPemEndPos - 1u;
				if ((aubPem_p[auhIdx] == (uint8)SB_ASCII_CR) || (aubPem_p[auhIdx] == (uint8)SB_ASCII_LF))
				{
					auhPemEndPos--;
				}
				auhIdx = auhIdx - 1u;
				if ((aubPem_p[auhIdx] == (uint8)SB_ASCII_CR) || (aubPem_p[auhIdx] == (uint8)SB_ASCII_LF))
				{
					auhPemEndPos--;
				}
				auhIdx = auhPemSiz; // Exit
			}
		}
		// Base64 decode and get the public key.
		if ((0u != auhPemStartPos) && (0u != auhPemEndPos) && (auhPemStartPos < auhPemEndPos))
		{
			// Decode Base64
			auhIdxDecode = 0u;
			auhCntB64Char = 0u;
			for (auhIdx = auhPemStartPos; auhIdx < auhPemEndPos; ++auhIdx)
			{
				// Ignore CRLF and shift the array
				if ((aubPem_p[auhIdx] == (uint8)SB_ASCII_CR) || (aubPem_p[auhIdx] == (uint8)SB_ASCII_LF))
				{
					// Ignore
				}
				else
				{
					aubBase64Decoded[auhCntB64Char] = nubSBSrB64toDec((char)aubPem_p[auhIdx]);
					auhCntB64Char++;
				}
				// Convert Base64 to binary (4 Base64 chars -> 3 bytes)
				if (SB_SIZE_B64_1CHNK == auhCntB64Char)
				{
					aubPemDecoded[auhIdxDecode] = (uint8)(aubBase64Decoded[0u] << SB_BITSFT_2) + (uint8)(aubBase64Decoded[1u] >> SB_BITSFT_4);
					aubPemDecoded[++auhIdxDecode] = (uint8)(aubBase64Decoded[1u] << SB_BITSFT_4) + (uint8)(aubBase64Decoded[2u] >> SB_BITSFT_2);
					aubPemDecoded[++auhIdxDecode] = (uint8)(aubBase64Decoded[2u] << SB_BITSFT_6) + (uint8)(aubBase64Decoded[3u]);
					auhCntB64Char = 0u;
					auhIdxDecode = auhIdxDecode + 1u;
				}
				if ((uint8)'=' == aubPem_p[auhIdx])
				{
					auhCntB64Padding++;
				}
			}

			/*
			Format ASN.1 for ECDSA public key
			SubjectPublicKeyInfo ::= SEQUENCE
			{
				AlgorithmIdentifier :: SEQUENCE
				{
					algorithm			OID
					parameters			OID
				}
				subjectPublicKey	BIT STRING
			}
			*/
			// Check the tag length of ASN.1
			aubResult = nubSBSrGetEcPKfrmDER(aubPemDecoded, auhIdxDecode - auhCntB64Padding, aubPubKey_p, auhKeySize);
		}
	}

	return aubResult;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubDer_p |Pointer to buffer containing DER-encoded ASN.1 RSA public key data |
 * |const uint16 |auhDerSiz |Size of the DER data buffer in bytes |
 * |uint8* |aubModulus_p |Pointer to buffer where extracted modulus will be stored |
 * |uint16* |auhModSiz_p |Pointer to variable for storing the extracted modulus size |
 * |uint8* |aubPubExp_p |Pointer to buffer where extracted public exponent will be stored |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Operation result (SB_RTN_OK: success, SB_RTN_NG: failure due to invalid parameters or ASN.1 format) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |aubModulus_p |Filled with the extracted RSA modulus value from the DER-encoded key |
 * |uint16* |auhModSiz_p |Updated with the actual size of the extracted modulus in bytes |
 * |uint8* |aubPubExp_p |Filled with the extracted RSA public exponent value from the DER-encoded key |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Local variable to store the function's return status |
 * |uint8 |aubNumByteLength |Number of bytes used to encode ASN.1 length fields during parsing |
 * |uint16 |auhIdxParser |Current position index while traversing the DER data structure |
 * |uint16 |auwAsn1SizeCons |Size value extracted from the current ASN.1 length field |
 * @brief Function to extract RSA public key components (modulus and exponent) from DER-encoded ASN.1 data
 * @note This function parses a DER-encoded RSA public key in ASN.1 format to extract the modulus and public exponent
 */
/* author FPT */
/* date 2024/07/30 */
/************************************************************************************************/
uint8 nubSBSrGetRsaPKfrmDER(const uint8* aubDer_p, const uint16 auhDerSiz,
	uint8* aubModulus_p, uint16* auhModSiz_p, uint8* aubPubExp_p)
{
	uint8 aubResult = SB_RTN_NG;
	uint8 aubNumByteLength;
	uint16 auhIdxParser = 0u;
	uint16 auwAsn1SizeCons = 0u;

	if ((NULL_PTR != aubDer_p) && (NULL_PTR != aubModulus_p) && (NULL_PTR != aubPubExp_p) && (0u != auhDerSiz) && (NULL_PTR != auhModSiz_p))
	{
		/*
		Format ASN.1 for RSA public key
			SubjectPublicKeyInfo ::= SEQUENCE
			{
				AlgorithmIdentifier :: SEQUENCE
				{
					algorithm			OID
					parameters			OID
				}
				subjectPublicKey	:: BIT STRING
				{
					:: SEQUENCE
					{
						modulus			INTEGER
						exponent		INTEGER
					}
				}
			}
		*/
		// Check the tag length of ASN.1
		if ((SB_ASN1_TAG_SEQUENCE == aubDer_p[auhIdxParser]) && ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
		{
			// Adjust to sequence algorithm ident
			SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);
			if ( (auhDerSiz == (uint16)(auwAsn1SizeCons + SB_SIZE_ASN1_TAG_LENGTH + aubNumByteLength)) &&
				 (nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_SEQUENCE) == SB_RTN_OK) &&
				 ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz) )
			{
				//Skip to SubjectPublicKey
				SB_ASN1_JUMP_TO_NEXT_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);

				if ((nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_BIT_STR) == SB_RTN_OK) &&
					((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
				{
					// Skip to sub sequence public key
					SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, SB_SIZE_ASN1_PK_PADDING);
					if ( (nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)(SB_ASN1_TAG_SEQUENCE)) == SB_RTN_OK) &&
						 ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz) )
					{
						// Skip to modulus public key constructed
						SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);
						if ((nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_INTERGER) == SB_RTN_OK) &&
							((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
						{
							// Skip to modulus public key value
							SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);
							*auhModSiz_p = auwAsn1SizeCons - SB_SIZE_ASN1_PK_PADDING;
							if ((auhIdxParser + auwAsn1SizeCons) < auhDerSiz)
							{
								VStdLib_MemCpy(aubModulus_p, &aubDer_p[auhIdxParser + SB_SIZE_ASN1_PK_PADDING], *auhModSiz_p);

								// Get the exponent
								auhIdxParser = auhIdxParser + auwAsn1SizeCons;
								if ( (nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_INTERGER) == SB_RTN_OK) &&
									 ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz) )
								{
									SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);
									if ((auhIdxParser + auwAsn1SizeCons) <= auhDerSiz)
									{
										VStdLib_MemCpy(aubPubExp_p, &aubDer_p[auhIdxParser], auwAsn1SizeCons);
										aubResult = SB_RTN_OK;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return aubResult;
}

/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |aubDer_p |Pointer to buffer containing DER-encoded ASN.1 EC public key data |
 * |const uint16 |auhDerSiz |Size of the DER data buffer in bytes |
 * |uint8* |aubPubKey_p |Pointer to buffer where extracted EC public key will be stored |
 * |uint16* |auhKeySize |Pointer to variable for storing the extracted key size |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Operation result (SB_RTN_OK: success, SB_RTN_NG: failure due to invalid parameters or ASN.1 format) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |aubPubKey_p |Filled with the extracted elliptic curve public key data (uncompressed format without format byte) |
 * |uint16* |auhKeySize |Updated with the actual size of the extracted public key in bytes |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |aubResult |Local variable to store the function's return status |
 * |uint8 |aubNumByteLength |Number of bytes used to encode ASN.1 length fields during parsing |
 * |uint16 |auhIdxParser |Current position index while traversing the DER data structure |
 * |uint16 |auwAsn1SizeCons |Size value extracted from the current ASN.1 length field |
 * @brief Function to extract an elliptic curve public key from DER-encoded ASN.1 data
 * @note This function parses a DER-encoded EC public key in ASN.1 format to extract the uncompressed public key 
 */
/* author FPT */
/* date 2024/07/30 */
/************************************************************************************************/
uint8 nubSBSrGetEcPKfrmDER(const uint8* aubDer_p, const uint16 auhDerSiz,
	uint8* aubPubKey_p, uint16* auhKeySize)
{
	uint8 aubResult = SB_RTN_NG;
	uint8 aubNumByteLength;
	uint16 auhIdxParser = 0u;
	uint16 auwAsn1SizeCons = 0u;

	if ((NULL_PTR != aubDer_p) && (0u != auhDerSiz) && (NULL_PTR != aubPubKey_p) && (NULL_PTR != auhKeySize))
	{
		/*
		Format ASN.1 for ECDSA public key
			SubjectPublicKeyInfo ::= SEQUENCE
			{
				AlgorithmIdentifier :: SEQUENCE
				{
					algorithm			OID
					parameters			OID
				}
				subjectPublicKey	BIT STRING
			}
		*/
		// Check the tag length of ASN.1
		if ((SB_ASN1_TAG_SEQUENCE == aubDer_p[auhIdxParser]) && ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
		{
			// Adjust to sequence algorithm ident
			SB_ASN1_JUMP_TO_VALUE_OF_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);
			if ( (auhDerSiz == (uint16)(auwAsn1SizeCons + SB_SIZE_ASN1_TAG_LENGTH + aubNumByteLength)) &&
				 (nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_SEQUENCE) == SB_RTN_OK) &&
				 ((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz) )
			{
				//Skip to SubjectPublicKey
				SB_ASN1_JUMP_TO_NEXT_TAG(aubNumByteLength, &aubDer_p[auhIdxParser], &auwAsn1SizeCons, auhIdxParser, 0u);

				if ((nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_TAG_BIT_STR) == SB_RTN_OK) &&
					((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
				{
					// Size the public key not contain padding byte and key form byte
					aubNumByteLength = nuhSBGetLengthTlv(&aubDer_p[auhIdxParser], &auwAsn1SizeCons);
					*auhKeySize = auwAsn1SizeCons - SB_SIZE_ASN1_PK_PADDING - SB_SIZE_ASN1_PK_FORMAT;
					auhIdxParser = auhIdxParser + aubNumByteLength + SB_SIZE_ASN1_TAG_LENGTH + SB_SIZE_ASN1_PK_PADDING;
					if ((nuhSBCheckNextTagValid(aubDer_p, auhIdxParser, auhDerSiz, (uint8)SB_ASN1_PK_UNCOMPRESSED) == SB_RTN_OK) &&
						((auhIdxParser + SB_SIZE_ASN1_TAG_LEN_MAX) < auhDerSiz))
					{
						// Get the public key.
						auhIdxParser = (auhIdxParser + SB_SIZE_ASN1_PK_FORMAT); // behind format type is public key data
						if (((((auhIdxParser + auwAsn1SizeCons) - SB_SIZE_ASN1_PK_PADDING) - SB_SIZE_ASN1_PK_FORMAT)) <= auhDerSiz)
						{
							VStdLib_MemCpy(aubPubKey_p, &aubDer_p[auhIdxParser], (auwAsn1SizeCons - SB_SIZE_ASN1_PK_PADDING - SB_SIZE_ASN1_PK_FORMAT));
							aubResult = SB_RTN_OK;
						}
					}
				}
			}
		}
	}

	return aubResult;
}
