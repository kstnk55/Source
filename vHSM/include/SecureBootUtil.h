/**
* @file  SecureBootUtil.h
* @brief  Public header for SecureBootUtil
* @details Overview: This header file defines constants, data types, and function prototypes for the Secure Boot Utility module. It includes definitions for memory addresses, cryptographic key sizes, data buffer sizes, and utility functions for handling cryptographic keys in various formats (PEM, DER).
*/

/********************************************************************************************/
/* File Name        : SecureBootUtil.h                                                      */
/* Date             : 2021/03/26                                                            */
/* Author           : Y.Watanabe                                                            */
/* Description      : SecureBootUtil header file                                            */
/* File Version     : 0001                                                                  */
/*------------------------------------------------------------------------------------------*/
/* Revision History                                                                         */
/* No       Date            Revised by      Function Name                                   */
/* 0001     2021/03/26      Y.Watanabe      New                                             */
/********************************************************************************************/
#ifndef SECUREBOOTUTIL_H
#define SECUREBOOTUTIL_H

#include "Std_Types.h"
/********************************************************************************************/
/*                          Macro Description                                               */
/********************************************************************************************/
/* CMAC Value for program A/B */
/**
 * @def			SB_ADDR_A_CMAC_VAL
 * @value		0x001FFFD0UL
 * @resolution	-
 * @brief 		Defines the memory address where the CMAC (Cipher-based Message Authentication Code) value for application program 'A' is stored.
 */
#define SB_ADDR_A_CMAC_VAL	(0x001FFFD0UL)		/* program A */
/**
 * @def			SB_ADDR_B_CMAC_VAL
 * @value		0x0029FFD0UL
 * @resolution	-
 * @brief 		Defines the memory address where the CMAC value for application program 'B' is stored.
 */
#define SB_ADDR_B_CMAC_VAL	(0x0029FFD0UL)		/* program B */

/* ValidateProgram */
/**
 * @def			SB_SIZE_MSG_BIT
 * @value		5242496U
 * @resolution	-
 * @brief 		Defines the size of the program message to be validated in bits (5242496 bits).
 */
#define SB_SIZE_MSG_BIT		(5242496U)
/**
 * @def			SB_SIZE_MSG_BYTE
 * @value		655312U
 * @resolution	-
 * @brief 		Defines the size of the program message to be validated in bytes (655312 bytes).
 */
#define SB_SIZE_MSG_BYTE	(655312U)
/**
 * @def			SB_SIZE_CMAC_BIT
 * @value		128U
 * @resolution	-
 * @brief 		Defines the size of the CMAC tag in bits (128 bits) used for program validation.
 */
#define SB_SIZE_CMAC_BIT	(128U)
/**
 * @def			SB_SIZE_CMAC_BYTE
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the CMAC tag in bytes (16 bytes) used for program validation.
 */
#define SB_SIZE_CMAC_BYTE	(16U)
/**
 * @def			SB_SIZE_CMAC_WORD
 * @value		4U
 * @resolution	-
 * @brief 		Defines the size of the CMAC tag in 32-bit words (4 words) used for program validation.
 */
#define SB_SIZE_CMAC_WORD	(4U)

/* start code address */
/**
 * @def			SB_BLCK_START_CODE
 * @value		1533U
 * @resolution	-
 * @brief 		Defines the block number for the start code address, calculated as an offset from a base address.
 */
#define SB_BLCK_START_CODE	(1533U)
/**
 * @def			SB_VADR_START_CODE
 * @value		0x00017F40UL
 * @resolution	-
 * @brief 		Defines the virtual start code address within the memory map.
 */
#define SB_VADR_START_CODE	(0x00017F40UL)

/* Secure DTC code address */
/**
 * @def			SB_BLCK_SDTC_CODE
 * @value		1534U
 * @resolution	-
 * @brief 		Defines the block number for the Secure DTC (Diagnostic Trouble Code) address.
 */
#define SB_BLCK_SDTC_CODE	(1534U)
/**
 * @def			SB_VADR_SDTC_CODE
 * @value		0x00017F80UL
 * @resolution	-
 * @brief 		Defines the virtual address for the Secure DTC code.
 */
#define SB_VADR_SDTC_CODE	(0x00017F80UL)

/* Customer Code */
/**
 * @def			SB_SIZE_CUSTOMER_CODE_CP
 * @value		32U
 * @resolution	-
 * @brief 		Defines the size in bytes of the customer-specific code or identifier.
 */
#define SB_SIZE_CUSTOMER_CODE_CP	(32U)
/**
 * @def			SB_SIZE_CUSTOMER_CODE
 * @value		SB_SIZE_CUSTOMER_CODE_CP
 * @resolution	-
 * @brief 		Alias for the size of the customer-specific code.
 */
#define SB_SIZE_CUSTOMER_CODE		(SB_SIZE_CUSTOMER_CODE_CP)

/* Activation Code */
/**
 * @def			SB_SIZE_ACTIVATION_CODE_CP
 * @value		512U
 * @resolution	-
 * @brief 		Defines the buffer size for the activation code, accounting for hexadecimal string representation (2 bytes per 1 byte of data).
 */
#define SB_SIZE_ACTIVATION_CODE_CP	(512U)
/**
 * @def			SB_SIZE_ACTIVATION_CODE
 * @value		SB_SIZE_ACTIVATION_CODE_CP
 * @resolution	-
 * @brief 		Alias for the size of the activation code buffer.
 */
#define SB_SIZE_ACTIVATION_CODE		(SB_SIZE_ACTIVATION_CODE_CP)

/* AES Key */
/**
 * @def			SB_SIZE_MASTER_KEY
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the Master Key in bytes (128-bit AES).
 */
#define SB_SIZE_MASTER_KEY	(16U)
/**
 * @def			SB_SIZE_BOOT_KEY
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the Boot Key in bytes (128-bit AES).
 */
#define SB_SIZE_BOOT_KEY	(16U)
/**
 * @def			SB_SIZE_PROGRAM_KEY
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the Program Key in bytes (128-bit AES).
 */
#define SB_SIZE_PROGRAM_KEY	(16U)
/**
 * @def			SB_SIZE_DEVICE_KEY
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the Device Key in bytes (128-bit AES).
 */
#define SB_SIZE_DEVICE_KEY	(16U)

/* memory cluster */
/**
 * @def			SB_SIZE_MEMCLSTR_DATA
 * @value		655312U
 * @resolution	-
 * @brief 		Defines the size of a memory cluster data block in bytes.
 */
#define SB_SIZE_MEMCLSTR_DATA	(655312U)

/* Public Key Related */
/**
 * @def			SB_SIZE_PEM_3072
 * @value		636U
 * @resolution	-
 * @brief 		Defines the typical buffer size required to store a 3072-bit public key in PEM format.
 */
#define SB_SIZE_PEM_3072		(636U)
/**
 * @def			SB_SIZE_PEM_2048
 * @value		460U
 * @resolution	-
 * @brief 		Defines the typical buffer size required to store a 2048-bit public key in PEM format.
 */
#define SB_SIZE_PEM_2048		(460U)
/**
 * @def			SB_SIZE_PK_LEN_3072
 * @value		384U
 * @resolution	-
 * @brief 		Defines the raw length of a 3072-bit public key modulus in bytes.
 */
#define SB_SIZE_PK_LEN_3072		(384U)
/**
 * @def			SB_SIZE_PK_LEN_2048
 * @value		256U
 * @resolution	-
 * @brief 		Defines the raw length of a 2048-bit public key modulus in bytes.
 */
#define SB_SIZE_PK_LEN_2048		(256U)
/**
 * @def			SB_SIZE_PUBEXP
 * @value		3U
 * @resolution	-
 * @brief 		Defines the size in bytes of the public exponent for an RSA key.
 */
#define SB_SIZE_PUBEXP			(3U)
/**
 * @def			SB_SIZE_DBGPRT_KEY
 * @value		SB_SIZE_PEM_3072
 * @resolution	-
 * @brief 		Defines the size of the debug and print key, aliased to the 3072-bit PEM size.
 */
#define SB_SIZE_DBGPRT_KEY		SB_SIZE_PEM_3072
/**
 * @def			SB_SIZE_PK_EXCHG
 * @value		SB_SIZE_PEM_2048
 * @resolution	-
 * @brief 		Defines the size of the public key for key exchange, aliased to the 2048-bit PEM size.
 */
#define SB_SIZE_PK_EXCHG		SB_SIZE_PEM_2048

/* AES-GCM */
/**
 * @def			SB_SIZE_AESGCM_KEY
 * @value		16U
 * @resolution	-
 * @brief 		Defines the key size for AES-GCM operations in bytes (128-bit).
 */
#define SB_SIZE_AESGCM_KEY			(16U)
/**
 * @def			SB_SIZE_AESGCM_AAD
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the Additional Authenticated Data (AAD) for AES-GCM in bytes.
 */
#define SB_SIZE_AESGCM_AAD			(16U)
/**
 * @def			SB_SIZE_AESGCM_IV
 * @value		12U
 * @resolution	-
 * @brief 		Defines the size of the Initialization Vector (IV) for AES-GCM in bytes.
 */
#define SB_SIZE_AESGCM_IV			(12U)
/**
 * @def			SB_SIZE_AESGCM_TAG
 * @value		16U
 * @resolution	-
 * @brief 		Defines the size of the authentication tag for AES-GCM in bytes.
 */
#define SB_SIZE_AESGCM_TAG			(16U)
/**
 * @def			SB_SIZE_AESGCM_ALL_DATA
 * @value		SB_SIZE_AESGCM_KEY + SB_SIZE_AESGCM_AAD + SB_SIZE_AESGCM_IV
 * @resolution	-
 * @brief 		Defines the total size of concatenated AES-GCM input data (Key + AAD + IV).
 */
#define SB_SIZE_AESGCM_ALL_DATA		(SB_SIZE_AESGCM_KEY + SB_SIZE_AESGCM_AAD + SB_SIZE_AESGCM_IV)
/**
 * @def			SB_OFS_AESGCM_KEY
 * @value		0U
 * @resolution	-
 * @brief 		Defines the offset of the AES-GCM key within a concatenated data buffer.
 */
#define SB_OFS_AESGCM_KEY			(0U)
/**
 * @def			SB_OFS_AESGCM_AAD
 * @value		SB_SIZE_AESGCM_KEY
 * @resolution	-
 * @brief 		Defines the offset of the AES-GCM AAD within a concatenated data buffer.
 */
#define SB_OFS_AESGCM_AAD			(SB_SIZE_AESGCM_KEY)
/**
 * @def			SB_OFS_AESGCM_IV
 * @value		SB_SIZE_AESGCM_KEY + SB_SIZE_AESGCM_AAD
 * @resolution	-
 * @brief 		Defines the offset of the AES-GCM IV within a concatenated data buffer.
 */
#define SB_OFS_AESGCM_IV			(SB_SIZE_AESGCM_KEY + SB_SIZE_AESGCM_AAD)
/**
 * @def			SB_AESGCM_KEY_INI
 * @value		0x00U
 * @resolution	-
 * @brief 		Defines the initialization value for AES-GCM key buffers.
 */
#define SB_AESGCM_KEY_INI			(0x00U)

/* AES Key Size (Encrypted) */
/**
 * @def			SB_SIZE_MASTER_KEY_ENC
 * @value		SB_SIZE_MASTER_KEY + SB_SIZE_AESGCM_TAG
 * @resolution	-
 * @brief 		Defines the total size of the encrypted Master Key, including the AES-GCM authentication tag.
 */
#define SB_SIZE_MASTER_KEY_ENC	(SB_SIZE_MASTER_KEY + SB_SIZE_AESGCM_TAG)
/**
 * @def			SB_SIZE_BOOT_KEY_ENC
 * @value		SB_SIZE_BOOT_KEY + SB_SIZE_AESGCM_TAG
 * @resolution	-
 * @brief 		Defines the total size of the encrypted Boot Key, including the AES-GCM authentication tag.
 */
#define SB_SIZE_BOOT_KEY_ENC	(SB_SIZE_BOOT_KEY + SB_SIZE_AESGCM_TAG)
/**
 * @def			SB_SIZE_PROGRAM_KEY_ENC
 * @value		SB_SIZE_PROGRAM_KEY + SB_SIZE_AESGCM_TAG
 * @resolution	-
 * @brief 		Defines the total size of the encrypted Program Key, including the AES-GCM authentication tag.
 */
#define SB_SIZE_PROGRAM_KEY_ENC	(SB_SIZE_PROGRAM_KEY + SB_SIZE_AESGCM_TAG)
/**
 * @def			SB_SIZE_DEVICE_KEY_ENC
 * @value		SB_SIZE_DEVICE_KEY + SB_SIZE_AESGCM_TAG
 * @resolution	-
 * @brief 		Defines the total size of the encrypted Device Key, including the AES-GCM authentication tag.
 */
#define SB_SIZE_DEVICE_KEY_ENC	(SB_SIZE_DEVICE_KEY + SB_SIZE_AESGCM_TAG)
/**
 * @def			SB_SIZE_DBGPRT_KEY_ENC
 * @value		SB_SIZE_DBGPRT_KEY + SB_SIZE_AESGCM_TAG
 * @resolution	-
 * @brief 		Defines the total size of the encrypted Debug/Print Key, including the AES-GCM authentication tag.
 */
#define SB_SIZE_DBGPRT_KEY_ENC	(SB_SIZE_DBGPRT_KEY + SB_SIZE_AESGCM_TAG)

/* SHA256 Hash */
/**
 * @def			SB_SIZE_HASH_SHA256
 * @value		32U
 * @resolution	-
 * @brief 		Defines the size of a SHA-256 hash digest in bytes.
 */
#define SB_SIZE_HASH_SHA256			(32U)
/**
 * @def			SB_HASH_INI
 * @value		0x00U
 * @resolution	-
 * @brief 		Defines the initialization value for hash buffers.
 */
#define SB_HASH_INI					(0x00U)

/* Random Number */
/**
 * @def			SB_NUM_EXT_SEED
 * @value		4U
 * @resolution	-
 * @brief 		Defines the number of external seeds to use for the random number generator.
 */
#define SB_NUM_EXT_SEED				(4U)
/**
 * @def			SB_RND_INI
 * @value		0x00U
 * @resolution	-
 * @brief 		Defines the initialization value for random number buffers.
 */
#define SB_RND_INI					(0x00U)

/**
 * @def			SB_ARG_INI
 * @value		0xFFU
 * @resolution	-
 * @brief 		Defines an initialization value for function arguments or parameters.
 */
#define SB_ARG_INI					(0xFFU)
/**
 * @def			SB_SIZE_0
 * @value		0U
 * @resolution	-
 * @brief 		Represents a size of zero, used for comparisons and initializations.
 */
#define SB_SIZE_0				(0U)
/**
 * @def			SB_IND_0
 * @value		0U
 * @resolution	-
 * @brief 		Represents an index of zero, used for array access and initializations.
 */
#define SB_IND_0				(0U)
/**
 * @def			SB_SIZE_KEY_MAX
 * @value		16U
 * @resolution	-
 * @brief 		Defines the maximum expected key size in bytes for generic key operations.
 */
#define SB_SIZE_KEY_MAX	(16U)

/* Debugging purposes */
// #define SB_ENB_DUMP_SECURE
// #define SB_ENB_DUMP_SYMM_KEY

/* Additional macros */
/**
 * @def			SB_RTN_NG
 * @value		0U
 * @resolution	-
 * @brief 		Defines the standard return value for a failed (Not Good) operation.
 */
#define SB_RTN_NG (0U)
/**
 * @def			SB_RTN_OK
 * @value		1U
 * @resolution	-
 * @brief 		Defines the standard return value for a successful (OK) operation.
 */
#define SB_RTN_OK (1U)
/********************************************************************************************/
/* Enumeration Type Declaration Section                            */
/********************************************************************************************/
/**
* @brief 		Enumeration of Key IDs for symmetric (AES) keys used in the secure boot process.
*/
enum
{
	SB_ID_MASTER_ECU_KEY = 0,	/**< Identifier for the Master ECU Key. */
	SB_ID_BOOT_MAC_KEY = 1,	/**< Identifier for the Boot MAC Key. */
	SB_ID_KEY_1 = 2,			/**< Identifier for generic key 1. */
	SB_ID_KEY_2 = 3,			/**< Identifier for generic key 2. */
	SB_ID_KEY_3 = 4,			/**< Identifier for generic key 3. */
	SB_ID_KEY_4 = 5,			/**< Identifier for generic key 4. */
	SB_ID_KEY_5 = 6,			/**< Identifier for generic key 5. */
	SB_ID_KEY_6 = 7,			/**< Identifier for generic key 6. */
	SB_ID_KEY_7 = 8,			/**< Identifier for generic key 7. */
	SB_ID_KEY_8 = 9,			/**< Identifier for generic key 8. */
	SB_ID_KEY_9 = 10,			/**< Identifier for generic key 9. */
	SB_ID_KEY_10 = 11,			/**< Identifier for generic key 10. */
	SB_ID_KEY_11 = 12			/**< Identifier for generic key 11. */
};

/**
* @brief 		Enumeration of Key IDs for asymmetric (RSA) public keys.
*/
enum
{
	SB_ID_RSA_KEY_0 = 0U		/**< Identifier for RSA public key 0. */
};

/********************************************************************************************/
/*                          User Type Declaration                                           */
/********************************************************************************************/

/********************************************************************************************/
/*                          Structure Type Declaration                                      */
/********************************************************************************************/

/********************************************************************************************/
/*                          Prototype Declaration                                           */
/********************************************************************************************/

/********************************************************************************************/
/*                          Extern Declaration                                              */
/********************************************************************************************/
/** @cond INTERNAL */
extern uint16 wuhTotlRecvSz_MKEY_ENC;
extern uint16 wuhTotlRecvSz_BKEY_ENC;
extern uint16 wuhTotlRecvSz_PKEY_ENC;
extern uint16 wuhTotlRecvSz_DKEY_ENC;
extern uint16 wuhTotlRecvSz_CCODE;
extern uint16 wuhTotlRecvSz_ACODE;
extern uint16 wuhTotlRecvSz_DBGPRT_KEY_ENC;
extern uint16 wuhTotlRecvSz_PK_EXCHG;
extern uint8 wubRecvData_MKEY_ENC_a[SB_SIZE_MASTER_KEY_ENC];
extern uint8 wubRecvData_BKEY_ENC_a[SB_SIZE_BOOT_KEY_ENC];
extern uint8 wubRecvData_PKEY_ENC_a[SB_SIZE_PROGRAM_KEY_ENC];
extern uint8 wubRecvData_DKEY_ENC_a[SB_SIZE_DEVICE_KEY_ENC];
extern uint8 wubRecvData_DBGPRT_KEY_ENC_a[SB_SIZE_DBGPRT_KEY_ENC];

/********************************************************************************************/
/*                          Global Function Prototype Declaration                           */
/********************************************************************************************/
uint8 nubSBSrGetPKfrmPEM(const uint8* aubPem_p, const uint16 auhPemSiz,
	const uint16 auhModSiz, uint8* aubModulus_p, uint8* aubPubExp_p);

uint8 nubSBSrGetRsaPKfrmDER(const uint8* aubDer_p, const uint16 auhDerSiz,
	uint8* aubModulus_p, uint16* auhModSiz_p, uint8* aubPubExp_p);

uint8 nubSBSrGetEcPKfrmPEM(const uint8* aubPem_p, const uint16 auhPemSiz,
	uint8* aubPubKey_p, uint16* auhKeySize);

uint8 nubSBSrGetEcPKfrmDER(const uint8* aubDer_p, const uint16 auhDerSiz,
	uint8* aubPubKey_p, uint16* auhKeySize);
#endif
/** @endcond */