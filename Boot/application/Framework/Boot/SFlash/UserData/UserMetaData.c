/****************************************************************************/
/* File name		: UserMetaData.c										*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes meta data about the dual bank manager.		*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#include "cy_project.h"
#include "cy_si_config.h"

#define CY_SFLASH_SI_VECTOR_OFFSET	((uint32_t) 0x00000100UL)
#define CY_SFLASH_SI_SIZE			((uint32_t) 0x00000800UL)
#define CY_SF_SI_VT_OFFSET	(CY_SFLASH_SI_VECTOR_OFFSET) \
							 - offsetof(cy_stc_si_appheader_t, core0Vt)	/* CM0+ VT Offset */
#define CY_SI_CPUID 		(0xC6000000UL)								/* CM0+ ARM CPUID[15:4] Reg shifted to [31:20] */
#define CY_SI_CORE_IDX		(0UL)										/* Index ID of the CM0+ core */

/* Secure Application header */
CY_SECTION(".cy_sf_app_header") __USED static const cy_stc_si_appheader_t cy_si_sflash_appHeader =
{
	.objSize		= CY_SFLASH_SI_SIZE,
	.appId			= (CY_SI_APP_VERSION | CY_SI_APP_ID_SECUREIMG),
	.appAttributes	= 0UL,							/* Reserved */
	.numCores		= 1UL,							/* Only CM0+ */
	.core0Vt		= CY_SF_SI_VT_OFFSET,			/* CM0+ VT offset */
	.core0Id		= CY_SI_CPUID | CY_SI_CORE_IDX	/* CM0+ core ID */
};

