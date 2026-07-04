/****************************************************************************/
/* File name		: BootConfig.h											*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes user-configurable definitions.				*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#ifndef BOOT_CONFIG_H
#define BOOT_CONFIG_H

/*----------------------------------------------------------------------------
 * Configurations of DualBank_Manager.asm/DualBank_ManagerCallback.c
 *----------------------------------------------------------------------------
 */
#if defined(DUAL_BANK_MANAGER_ASM) || defined(DUAL_BANK_MANAGER_CALLBACK_C)

/* Set a sufficient startup stack size for correct operation of C callback code */
#define STARTUP_STACK_SIZE_DOUBLE_WORDS			(128U)

/* Macro that compare with the magic word value */
#define MAGIC_WORD_B								(0xBBBBBBBBUL)
#define MAGIC_WORD_A								(0xAAAAAAAAUL)
#define RESET_COUNTER_ADDR							(0x28007FF0UL)
#define BANKA_DTC_FLAG_VAR_ADDR					(0x28013FE4UL)
/* Macro that indicates the address where the magic word is stored */
#if defined(tviibh4m)
#define ADDR_MAKER_ON_WORK						(0x14030000UL)
#elif defined(tviibh8m)
#define ADDR_MAKER_ON_WORK						(0x1403FE80UL)
#define ADDR_BACKUP_MAKER_ON_WORK				(0x1403FF00UL)
#elif defined(tviic2d4m)
#define ADDR_MAKER_ON_WORK						(0x14018000UL)
#elif defined(tviic2d6m)
#define ADDR_MAKER_ON_WORK						(0x14018000UL)
#endif

/* Macro to enable application authentication by Dual Bank Manager */
#define AUTHENTICATION_ENABLE					(0x00000001UL)

/* Macro to disable application authentication by Dual Bank Manager */
#define AUTHENTICATION_DISABLE					(0x55555555UL)

/* Set AUTHENTICATION_CHECK to AUTHENTICATION_ENABLE or AUTHENTICATION_DISABLE */
#define AUTHENTICATION_CHECK					(AUTHENTICATION_DISABLE)

/* Macro for offset value from beginning of code flash to CM0+ app */
#define APP_OFFSET_VALUE						(0x00000000UL)

/*----------------------------------------------------------------------------
 * Configurations of startup_cm0plus.arm
 *----------------------------------------------------------------------------
 */
#elif defined(STARTUP_CM0PLUS_ARM)

/* Set a sufficient startup stack size for correct operation of C startup code */
#define STARTUP_STACK_SIZE_DOUBLE_WORDS			(256U)


/*----------------------------------------------------------------------------
 * Configurations of startup_cm7.arm
 *----------------------------------------------------------------------------
 */
#elif defined(STARTUP_CM7_ARM)

/* Set a sufficient startup stack size for correct operation of C startup code */
#define STARTUP_STACK_SIZE_DOUBLE_WORDS			(32U)

/* Register setting value that determines whether or not to use ITCM */
#define ITCMCR_SET_VALUE						(7U)

/* Register setting value that determines whether or not to use DTCM */
#define DTCMCR_SET_VALUE						(7U)


/*----------------------------------------------------------------------------
 * Configurations of other C files
 *----------------------------------------------------------------------------
 */
#else /* C files configuration */

/* Set the Code FLASH size to allocate to each application */
#define CM0PLUS_CODE_FLASH_RESERVED				(0x0008FD80UL)				/* CM0+  can be used up to 1024K. */
#define CM7_0_CODE_FLASH_RESERVED				(0x00280000UL)				/* CM7_0 can be used up to 2560K. */
#define CM7_1_CODE_FLASH_RESERVED				(0x00078000UL)				/* CM7_1 can be used up to  480K. */

/* Macro that indicates the top address of CM0+ application, etc. */
#define CM0PLUS_APP_HEADER_ADDRESS				(CY_FLASH_LG_DBM0_BASE)
#define CM0PLUS_VECTOR_TABLE_ADDRESS			(CM0PLUS_APP_HEADER_ADDRESS + 256U)
#define CM0PLUS_DIGITAL_SIGNATURE_ADDRESS		(CM0PLUS_APP_HEADER_ADDRESS + CM0PLUS_CODE_FLASH_RESERVED - CY_SI_SECURE_DIGSIG_SIZE)

/* Macro that indicates the top address of CM7_0 application, etc. */
#define CM7_0_VECTOR_TABLE_ADDRESS				(CY_FLASH_LG_DBM0_BASE + CM0PLUS_CODE_FLASH_RESERVED)
#define CM7_0_DIGITAL_SIGNATURE_ADDRESS			(CM7_0_VECTOR_TABLE_ADDRESS + CM7_0_CODE_FLASH_RESERVED - CY_SI_SECURE_DIGSIG_SIZE)

/* Macro that indicates the top address of CM7_1 application, etc. */
#define CM7_1_VECTOR_TABLE_ADDRESS				(CY_FLASH_LG_DBM0_BASE + CM0PLUS_CODE_FLASH_RESERVED + CM7_0_CODE_FLASH_RESERVED)
#define CM7_1_DIGITAL_SIGNATURE_ADDRESS			(CM7_1_VECTOR_TABLE_ADDRESS + CM7_1_CODE_FLASH_RESERVED - CY_SI_SECURE_DIGSIG_SIZE)

/* Enables/Disables assertions within the startup code (default implementation for failed assertions: endless loop) */
#define STARTUP_CUSTOMIZE__ENABLE_ASSERTIONS

/* Enables/Disables the ECC initialization of the memories (SRAM, and DTCM/ITCM if available) */
#define STARTUP_CUSTOMIZE__ENABLE_ECC_INITIALIZATION

/* Enables/Disables the Cortex-M7 instruction cache (setting is ignored in case of Cortex-M0+ or Cortex-M4F) */
#define STARTUP_CUSTOMIZE__ENABLE_CM7_INSTRUCTION_CACHE

/* Enables/Disables the Cortex-M7 data cache (setting is ignored in case of Cortex-M0+ or Cortex-M4F) */
#define STARTUP_CUSTOMIZE__ENABLE_CM7_DATA_CACHE

#if (CY_CPU_CORTEX_M0P)

/* Set RAM area to be cleared for ECC */
#define RAM_ECC_CLEAR_REGIONS \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_END_ADDRESS, \
	}

/* Set Cortex-M MPU settings */
#define MPU_CONFIG_LIST

/* Specifies enable/disable privileged software access to the default memory map */
#define MPU_PRIV_DEF_ENA						(4U)	/* =CY_MPU_USE_DEFAULT_MAP_AS_BG */

/* Specifies enable/disable the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define MPU_HF_NMI_ENA							(0U)	/* =CY_MPU_DISABLED_DURING_FAULT_NMI */

#elif defined(CY_CORE_CM7_0)

/* Set RAM area to be cleared for ECC (Cortex-M7) */
#define RAM_ECC_CLEAR_REGIONS \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_END_ADDRESS, \
	}, \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_DTCM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_DTCM_END_ADDRESS, \
	}, \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_ITCM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_ITCM_END_ADDRESS, \
	}

/* Set Cortex-M MPU settings */
#define MPU_CONFIG_LIST

/* Specifies enable/disable privileged software access to the default memory map */
#define MPU_PRIV_DEF_ENA						(4U)	/* =CY_MPU_USE_DEFAULT_MAP_AS_BG */

/* Specifies enable/disable the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define MPU_HF_NMI_ENA							(0U)	/* =CY_MPU_DISABLED_DURING_FAULT_NMI */

#else /* CY_CORE_CM7_1 */

/* Set RAM area to be cleared for ECC (Cortex-M7) */
#define RAM_ECC_CLEAR_REGIONS \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_SRAM_END_ADDRESS, \
	}, \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_DTCM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_DTCM_END_ADDRESS, \
	}, \
	{ \
		.u32StartAddr	= STARTUP_CUSTOMIZE__ECC_INIT_ITCM_START_ADDRESS, \
		.u32EndAddr		= STARTUP_CUSTOMIZE__ECC_INIT_ITCM_END_ADDRESS, \
	}

/* Set Cortex-M MPU settings */
#define MPU_CONFIG_LIST

/* Specifies enable/disable privileged software access to the default memory map */
#define MPU_PRIV_DEF_ENA						(4U)	/* =CY_MPU_USE_DEFAULT_MAP_AS_BG */

/* Specifies enable/disable the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define MPU_HF_NMI_ENA							(0U)	/* =CY_MPU_DISABLED_DURING_FAULT_NMI */

#endif /* CY_CORE_CM7_1 */

/* Register setting macros related to Cortex-M0+ ECC */
#define FLASHC_MAIN_ECC_EN_VALUE				(1U)		/* FLASHC_FLASH_CTL.MAIN_ECC_EN		*/
#define FLASHC_WORK_ECC_EN_VALUE				(0U)		/* FLASHC_FLASH_CTL.WORK_ECC_EN		*/
#define SRAM0_CTL_ECC_EN_VALUE					(1U)		/* CPUSS_RAM0_CTL0.ECC_EN			*/
#define SRAM1_CTL_ECC_EN_VALUE					(1U)		/* CPUSS_RAM1_CTL0.ECC_EN			*/
#define SRAM2_CTL_ECC_EN_VALUE					(1U)		/* CPUSS_RAM2_CTL0.ECC_EN			*/
#define FLASHC_CA_RAM_ECC_EN_VALUE				(1U)		/* FLASHC_CM0_CA_CTL0.RAM_ECC_EN	*/
#define FLASHC_CA_EN_VALUE						(1U)		/* FLASHC_CM0_CA_CTL0.CA_EN			*/

/* Register setting macros related to Cortex-M7 ECC */
#define CM7_0_ITCM_ECC_EN_VALUE					(0U)		/* CPUSS_CM7_0_CTL.ITCM_ECC_EN		*/
#define CM7_0_DTCM_ECC_EN_VALUE					(0U)		/* CPUSS_CM7_0_CTL.DTCM_ECC_EN		*/
#define CM7_0_CACR_ECCDIS_VALUE					(0U)		/* CM7_SCS_CM7_CACR.ECCDIS			*/
#define CM7_1_ITCM_ECC_EN_VALUE					(0U)		/* CPUSS_CM7_1_CTL.ITCM_ECC_EN		*/
#define CM7_1_DTCM_ECC_EN_VALUE					(0U)		/* CPUSS_CM7_1_CTL.DTCM_ECC_EN		*/
#define CM7_1_CACR_ECCDIS_VALUE					(0U)		/* CM7_SCS_CM7_CACR.ECCDIS			*/


#endif /* C files configuration */

#endif /* BOOT_CONFIG_H */
