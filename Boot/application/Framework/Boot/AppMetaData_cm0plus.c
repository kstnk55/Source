/****************************************************************************/
/* File name		: AppMetaData_cm0plus.c									*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes meta data about the CM0+ application.		*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#include "cy_project.h"
#include "cy_si_config.h"
#include "BootConfig.h"

#define CY_M0PLUS_SI_SIZE	(CM0PLUS_DIGITAL_SIGNATURE_ADDRESS - CM0PLUS_APP_HEADER_ADDRESS)
#define CY_SI_VT_OFFSET		(CM0PLUS_VECTOR_TABLE_ADDRESS - CM0PLUS_APP_HEADER_ADDRESS) \
								- offsetof(cy_stc_si_appheader_t, core0Vt)	/* CM0+ VT Offset */
#define CY_SI_CPUID			(0xC6000000UL)									/* CM0+ ARM CPUID[15:4] Reg shifted to [31:20] */
#define CY_SI_CORE_IDX		(0UL)											/* Index ID of the CM0+ core */

/* Secure Application header */
CY_SECTION(".cy_app_header") __USED static const cy_stc_si_appheader_t cy_si_appHeader = 
{
	.objSize		= CY_M0PLUS_SI_SIZE,
	.appId			= (CY_SI_APP_VERSION | CY_SI_APP_ID_SECUREIMG),
	.appAttributes	= 0UL,							/* Reserved */
	.numCores		= 1UL,							/* Only CM0+ */
	.core0Vt		= CY_SI_VT_OFFSET,				/* CM0+ VT offset */
	.core0Id		= CY_SI_CPUID | CY_SI_CORE_IDX,	/* CM0+ core ID */
};

/* Secure Image Digital signature (Populated by cymcuelftool) */
CY_SECTION(".cy_app_signature") __USED CY_ALIGN(4) 
static const uint8_t cy_si_appSignature[CY_SI_SECURE_DIGSIG_SIZE] = {0u};
