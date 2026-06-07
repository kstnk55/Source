/****************************************************************************/
/* File name		: cy_si_keystorage.h									*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Secure key storage header for the secure image.		*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#ifndef CY_SI_KEYSTORAGE_H
#define CY_SI_KEYSTORAGE_H

#include <stdint.h>
#include <stddef.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*               Macros
***************************************/

/** \addtogroup group_secure_image_macro
* \{
*/

/** \defgroup group_secure_image_pubkey_macros Public Key Macros
* Macros used to define the Public key.
* \{
*/    
#define CY_SI_PUBLIC_KEY_STRUCT_OFFSET	(8UL)	/**< Offset to public key struct in number of bytes */
#define CY_SI_PUBLIC_KEY_MODULOLENGTH	(256UL)	/**< Modulus length of the RSA 2K key */
#define CY_SI_PUBLIC_KEY_MODULOLENGTH_3K	(384UL) /**< Modulus length of the RSA 3K key */
/* #define CY_SI_PUBLIC_KEY_MODULOLENGTH	(512UL) */	/**< Modulus length of the RSA 4K key */
#define CY_SI_PUBLIC_KEY_EXPLENGTH		(32UL)	/**< Exponent length of the RSA key */
#define CY_SI_PUBLIC_KEY_SIZEOF_BYTE	(8UL)	/**< Size of Byte in number of bits */
/** \} group_secure_image_pubkey_macros */

/** \} group_secure_image_macro */


/***************************************
*               Structs
***************************************/

/**
* \addtogroup group_secure_image_data_structures
* \{
*/

/** Public key definition structure as expected by the Crypto driver */
typedef struct
{
	uint32_t moduloAddr;			/**< Address of the public key modulus */
	uint32_t moduloSize;			/**< Size (bits) of the modulus part of the public key */
	uint32_t expAddr;				/**< Address of the public key exponent */
	uint32_t expSize;				/**< Size (bits) of the exponent part of the public key */
	uint32_t barrettAddr;			/**< Address of the Barret coefficient */
	uint32_t inverseModuloAddr;		/**< Address of the binary inverse modulo */
	uint32_t rBarAddr;				/**< Address of the (2^moduloLength mod modulo) */
} cy_si_stc_crypto_public_key_t;

/** Public key structure */
typedef struct
{
	uint32_t objSize;											/**< Public key Object size */
	uint32_t signatureScheme;									/**< Signature scheme */
	cy_si_stc_crypto_public_key_t publicKeyStruct;				/**< Public key definition struct */
	uint8_t  moduloData[CY_SI_PUBLIC_KEY_MODULOLENGTH];			/**< Modulo data */
	uint8_t  expData[CY_SI_PUBLIC_KEY_EXPLENGTH];				/**< Exponent data */
	uint8_t  barrettData[CY_SI_PUBLIC_KEY_MODULOLENGTH + 4UL];	/**< Barret coefficient data */
	uint8_t  inverseModuloData[CY_SI_PUBLIC_KEY_MODULOLENGTH];	/**< Binary inverse modulo data */
	uint8_t  rBarData[CY_SI_PUBLIC_KEY_MODULOLENGTH];			/**< 2^moduloLength mod modulo data */
} cy_si_stc_public_key_t;

/** 3K Public key structure */
typedef struct
{
	uint32_t objSize;											/**< Public key Object size */
	uint32_t signatureScheme;									/**< Signature scheme */
	cy_si_stc_crypto_public_key_t publicKeyStruct;				/**< Public key definition struct */
	uint8_t  moduloData[CY_SI_PUBLIC_KEY_MODULOLENGTH_3K];			/**< Modulo data */
	uint8_t  expData[CY_SI_PUBLIC_KEY_EXPLENGTH];				/**< Exponent data */
	uint8_t  barrettData[CY_SI_PUBLIC_KEY_MODULOLENGTH_3K + 4UL];	/**< Barret coefficient data */
	uint8_t  inverseModuloData[CY_SI_PUBLIC_KEY_MODULOLENGTH_3K];	/**< Binary inverse modulo data */
	uint8_t  rBarData[CY_SI_PUBLIC_KEY_MODULOLENGTH_3K];			/**< 2^moduloLength mod modulo data */
} cy_si_stc_public_key_3K_t;
/** \} group_secure_image_data_structures */


/***************************************
*               Globals
***************************************/

/** Public key in SFlash */
extern const cy_si_stc_public_key_t cy_publicKey;
extern const cy_si_stc_public_key_3K_t cy_publicKey_3K;

#if defined(__cplusplus)
}
#endif

#endif /* CY_SI_KEYSTORAGE_H */

/* [] END OF FILE */
