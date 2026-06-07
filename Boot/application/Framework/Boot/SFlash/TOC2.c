/****************************************************************************/
/* File name		: TOC.c													*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes TOC2 settings.								*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#include "cy_project.h"
#include "cy_si_config.h"

/* Flashboot parameters */
#define CY_SI_FLASHBOOT_FLAGS ((CY_SI_FLASHBOOT_CLK_100MHZ << CY_SI_TOC_FLAGS_CLOCKS_POS) \
				| (CY_SI_FLASHBOOT_WAIT_20MS << CY_SI_TOC_FLAGS_DELAY_POS) \
				| (CY_SI_FLASHBOOT_SWJ_ENABLE << CY_SI_TOC_FLAGS_SWJEN_POS) \
				| (CY_SI_FLASHBOOT_VALIDATE_DISABLE << CY_SI_TOC_FLAGS_APP_VERIFY_POS) \
				| (CY_SI_FLASHBOOT_FBLOADER_DISABLE << CY_SI_TOC_FLAGS_FBLOADER_ENABLE_POS))

/* TOC2 in SFlash */
CY_SECTION(".cy_toc_part2") __USED static const cy_stc_si_toc_t cy_toc2 =
{
	.objSize		= CY_SI_TOC2_OBJECTSIZE,			/* Offset+0x00: Object Size (Bytes) excluding CRC */
	.magicNum		= CY_SI_TOC2_MAGICNUMBER,			/* Offset+0x04: TOC2 ID (magic number) */
	.smifCfgAddr	= 0UL,								/* Offset+0x08: SMIF config list pointer */
	.cm0pappAddr1	= CY_SI_SECURE_SFLASH_BEGIN,		/* Offset+0x0C: App1 (CM0+ First User App Object) addr */
	.cm0pappFormat1	= CY_SI_APP_FORMAT_CYPRESS,			/* Offset+0x10: App1 Format */
	.cm0pappAddr2	= CY_SI_USERAPP_FLASH_BEGIN,		/* Offset+0x14: App2 (CM0+ Second User App Object) addr */
	.cm0pappFormat2	= CY_SI_APP_FORMAT_BASIC,			/* Offset+0x18: App2 Format */
	.cm4_71appAddr1	= CY_SI_CM471_1stAPP_FLASH_BEGIN,	/* Offset+0x1C: App3 (CM4/CM7_1 1st User App Object) addr */
	.cm4_71appAddr2	= CY_SI_CM471_2ndAPP_FLASH_BEGIN,	/* Offset+0x20: App4 (CM4/CM7_1 2nd User App Object) addr */
	.cm72appAddr1	= CY_SI_CM72_1stAPP_FLASH_BEGIN,	/* Offset+0x24: App5 (CM7_2 1st User App Object) addr */
	.cm72appAddr2	= CY_SI_CM72_2ndAPP_FLASH_BEGIN,	/* Offset+0x28: App6 (CM7_2 1st User App Object) addr */
	.reserved1		= 0UL,								/* Offset+0x2C-0xFB: Reserved area 212Bytes */
	.securityMarker	= CY_SECURITY_NOT_ENHANCED,			/* Offset+0xFC Security Enhance Marker */
	.shashObj		= 4UL,								/* Offset+0x100: Number of verified additional objects (S-HASH)*/
	.sigKeyAddr		= CY_SI_PUBLIC_KEY,					/* Offset+0x104: Addr of signature verification key */
	.swpuAddr		= CY_SI_SWPU_BEGIN,					/* Offset+0x108: Addr of SWPU Objects */
	.toc2Addr		= 0UL,								/* Offset+0x10C: TOC2_OBJECT_ADDR_UNUSED */
	.addObj			= 0UL,								/* Offset+0x110-0x1F4: Reserved area 232Bytes */
	.addObj[0]		= CY_SI_SECURE_SFLASH_BEGIN,		/* Offset+0x110: SFlash App is added as additional obj for SECURE HASH calculation */
	.tocFlags		= CY_SI_FLASHBOOT_FLAGS,			/* Flashboot flags stored in TOC2 */
	.crc			= 0UL,								/* Offset+0x1FC: Reserved area 1Byte */
};

