/****************************************************************************/
/* File name		: NAR.c													*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes access restriction settings.				*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#include "cy_project.h"
#include "cy_si_config.h"

/* Access Restriction */
/* CY_SI_DIRECT_EXE_DISABLE in CY_SI_NAR_NORMALACCESSRESTRICTION is fixed value */
#define CY_SI_NAR_NORMALACCESSRESTRICTION ((CY_SI_CM0_ENABLE << CY_SI_CM0_AP_POS) \
				| (CY_SI_CM4_ENABLE << CY_SI_CM4_AP_POS) \
				| (CY_SI_SYS_ENABLE << CY_SI_SYS_AP_POS) \
				| (CY_SI_MPU_DISABLE << CY_SI_AP_MPU_POS)\
				| (CY_SI_DIRECT_EXE_DISABLE << CY_SI_DIRECT_EXECUTE_POS) \
				| (CY_SI_FLASH_ENABLE << CY_SI_FLASH_POS) \
				| (CY_SI_RAM0_ENABLE  << CY_SI_RAM0_POS) \
				| (CY_SI_WORK_FLASH_ENABLE << CY_SI_WORK_FLASH_POS) \
				| (CY_SI_SFLASH_ENABLE << CY_SI_SFLASH_POS) \
				| (CY_SI_MMIO_ENABLE << CY_SI_MMIO_POS))

#define CY_SI_NAR_NORMALDEADACCESSRESTRICTION ((CY_SI_CM0_ENABLE << CY_SI_CM0_AP_POS) \
				| (CY_SI_CM4_ENABLE << CY_SI_CM4_AP_POS) \
				| (CY_SI_SYS_ENABLE << CY_SI_SYS_AP_POS) \
				| (CY_SI_MPU_DISABLE  << CY_SI_AP_MPU_POS) \
				| (CY_SI_DIRECT_EXE_ENABLE << CY_SI_DIRECT_EXECUTE_POS) \
				| (CY_SI_FLASH_ENABLE << CY_SI_FLASH_POS) \
				| (CY_SI_RAM0_ENABLE  << CY_SI_RAM0_POS) \
				| (CY_SI_WORK_FLASH_ENABLE << CY_SI_WORK_FLASH_POS) \
				| (CY_SI_SFLASH_ENABLE << CY_SI_SFLASH_POS) \
				| (CY_SI_MMIO_ENABLE << CY_SI_MMIO_POS))

CY_SECTION(".cy_sflash_nar") __USED static const cy_stc_si_nar_t cy_nar =
{
	.nar		= CY_SI_NAR_NORMALACCESSRESTRICTION,		/* Normal Access Restrictions */
	.ndar		= CY_SI_NAR_NORMALDEADACCESSRESTRICTION,	/* Normal Dead Access Restrictions */
};

