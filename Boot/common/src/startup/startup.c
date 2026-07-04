/****************************************************************************/
/* File name		: startup.c												*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: C startup code before main() (ANSI C context not yet	*/
/*					: established!)											*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

/*****************************************************************************
* Include files
*****************************************************************************/
#include "cy_project.h"
#include "cy_device_headers.h"
#include "startup_customize.h"
#include "BootConfig.h"


#if defined(__cplusplus)
extern "C" {
#endif

/*****************************************************************************
* Local pre-processor symbols/macros ('define')
*****************************************************************************/

#ifdef STARTUP_CUSTOMIZE__ENABLE_ASSERTIONS
	/** If assertions are enabled and an assertion fails, execution will stop in this endless loop */
	#define STARTUP_ASSERT(x)							if ((x) == 0U) { while (1) {} }
#else
	/** Remove assertion code with this empty macro if assertions are disabled */
	#define STARTUP_ASSERT(x)
#endif

/** Returns 'logical true' if the given address is within the given area, otherwise 'logical false' */
#define IS_ADDRESS_IN_AREA(addr,start,end)				((start) != 0U ? ((start) <= (addr)) && ((end) >= (addr)) : ((end) >= (addr)))

/** Returns the dimension of an array */
#define GET_NR_OF_ARRAY_ELEMENTS(array)					(sizeof(array) / sizeof(array[0]))


// Most restrictive native ECC width of all "normal" memories (SRAM, DTCM, ITCM) in any Traveo II derivate is used to keep the code generic
// Note: In M7 based TVII derivates the native ECC width is different across memories, e.g. SRAM/ITCM = 64-bit <-> DTCM = 32-bit.
//       In M4 based TVII derivates the native ECC width of SRAM is 32-bit and there are no TCMs, but 64-bit is used anyway to keep the code generic
/** The ECC initialization is based on this granularity */
#define ECC_INIT_WIDTH_BYTES		8U

#define RESET_COUNTER_VAR_ADDR (0x28007FF0UL)

/** Define an abstract type for the chosen ECC initialization granularity */
typedef uint64_t  ecc_init_width_t;


/** Check whether necessary project defines are set if enabling of caches is requested by the user */
#if (CY_CPU_CORTEX_M7)
	#ifdef STARTUP_CUSTOMIZE__ENABLE_CM7_INSTRUCTION_CACHE
		#if !defined(__ICACHE_PRESENT) || (__ICACHE_PRESENT == 0)
			#error "__ICACHE_PRESENT=1 must be set as preprocessor define for the project, otherwise CMSIS code is not included!"
		#endif
	#endif
	#ifdef STARTUP_CUSTOMIZE__ENABLE_CM7_DATA_CACHE
		#if !defined(__DCACHE_PRESENT) || (__DCACHE_PRESENT == 0)
			#error "__DCACHE_PRESENT=1 must be set as preprocessor define for the project, otherwise CMSIS code is not included!"
		#endif
	#endif
#endif


#define SROM_VECTOR_TABLE_BASE_ADDRESS		0x00000000U
#define VECTOR_TABLE_OFFSET_IRQ0			0x40U
#define VECTOR_TABLE_OFFSET_IRQ1			0x44U
#define BYTES_OF_VECTOR						4U


/*****************************************************************************
* Global variable definitions (declared in header file with 'extern')
*****************************************************************************/
// CAUTION: Static or global initialized and non-const variables will not have their init value yet!


/*****************************************************************************
* Local type definitions ('typedef')
*****************************************************************************/
/** Describes a memory area which is defined by its start and end address */
typedef struct
{
	uint32_t u32StartAddr;		//!< First address within a region
	uint32_t u32EndAddr;		//!< Last address within a region
} stc_region_t;


/*****************************************************************************
* Local variable definitions ('static')
*****************************************************************************/
// CAUTION: Static or global initialized and non-const variables will not have their init value yet!


/*****************************************************************************
* Local constant definitions ('static')
*****************************************************************************/
static const cy_stc_mpu_region_cfg_t mpuConfigList[] =
{
    MPU_CONFIG_LIST

	/* terminator */
	{0}
};


/*****************************************************************************
* Local function prototypes ('static')
*****************************************************************************/
#ifdef STARTUP_CUSTOMIZE__ENABLE_ECC_INITIALIZATION
static void InitRamEcc(void);
static void InitRamEccClearArea(uint32_t u32StartAddr, uint32_t u32EndAddr);
#endif

static void CopyVectorTable(void);
#if (CY_CPU_CORTEX_M0P)
static void PrepareSystemCallInfrastructure(void);
#endif

static void ConfigureECC(void);
static void ConfigureMPU(void);

/*****************************************************************************
* Function implementation - global ('extern') and local ('static')
*****************************************************************************/

/****************************************************************************/
/* Function name	: Startup_Init											*/
/* Description		: Startup initializations written in C, called from		*/
/*					: startup assembly code.								*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: This function is executed in a non-ANSI C context		*/
/*					: (i.e. .bss sections not yet cleared, init values not	*/
/*					: yet copied to .data sections), so static and global	*/
/*					: variables must be used carefully, if at all!			*/
/****************************************************************************/
void Startup_Init(void)
{
  #if !(CY_CPU_CORTEX_M0P)
	// Enable the FPU if used
	// CAUTION: Implementation of this C function must be aware that it is executed in non-ANSI C context!
	Cy_SystemInitFpuEnable();
  #endif

  #if (CY_CPU_CORTEX_M7)
	ConfigureECC();
  #endif

  #ifdef STARTUP_CUSTOMIZE__ENABLE_ECC_INITIALIZATION
	InitRamEcc();
  #endif

  #if (defined (tviibh4m) || defined (tviibh8m) || defined (tviic2d6m) || defined (tviic2d4m) || defined (tviic2d6mddr)  || defined (tviibh16m)) && (CY_CPU_CORTEX_M0P)
	// Enable ECC checking in SRAM controllers again (had been switched off by assembly startup code)
	CPUSS->unRAM0_CTL0.stcField.u1ECC_CHECK_DIS = 0U;
	#ifdef CPUSS_RAMC1_PRESENT
	CPUSS->unRAM1_CTL0.stcField.u1ECC_CHECK_DIS = 0U;
	#endif
	#ifdef CPUSS_RAMC2_PRESENT
	CPUSS->unRAM2_CTL0.stcField.u1ECC_CHECK_DIS = 0U;
	#endif
  #endif

	CopyVectorTable();
  #if (CY_CPU_CORTEX_M0P)
	PrepareSystemCallInfrastructure();
	ConfigureECC();
	ConfigureMPU();
  #endif

  #if (CY_CPU_CORTEX_M7)
	#ifdef STARTUP_CUSTOMIZE__ENABLE_CM7_INSTRUCTION_CACHE
	SCB_EnableICache();
	#endif
	#ifdef STARTUP_CUSTOMIZE__ENABLE_CM7_DATA_CACHE
	SCB_EnableDCache();
	#else
	// Ensure that the undefined valid bits in the cache RAM are set to invalid if cache is disabled, because the application
	// may call further cache maintenance functions (e.g. SCB_CleanInvalidateDCache) independent of the "cache enabled" state.
	SCB_InvalidateDCache();
	#endif
	ConfigureMPU();
  #endif

}


#ifdef STARTUP_CUSTOMIZE__ENABLE_ECC_INITIALIZATION

/****************************************************************************/
/* Function name	: InitRamEcc											*/
/* Description		: Takes care of initializing the ECC in all memory areas*/
/*					: as per the user configuration given in startup_custom-*/
/*					: ize.h.												*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: The startup stack has already been initialized by		*/
/*					: startup_cm*.arm/s, so it will be skipped here (also to*/
/*					: preserve the state of caller functions!)				*/
/****************************************************************************/
static void InitRamEcc(void)
{
	stc_region_t astcClearRegions[] = { RAM_ECC_CLEAR_REGIONS };

  #ifdef STARTUP_CUSTOMIZE__ENABLE_ASSERTIONS
	// Check alignment of region start/end addresses
	for (uint8_t u8Index = 0U; u8Index < GET_NR_OF_ARRAY_ELEMENTS(astcClearRegions); u8Index++) {
		STARTUP_ASSERT(((astcClearRegions[u8Index].u32StartAddr)    % ECC_INIT_WIDTH_BYTES) == 0U);
		STARTUP_ASSERT(((astcClearRegions[u8Index].u32EndAddr + 1U) % ECC_INIT_WIDTH_BYTES) == 0U);
	}
	STARTUP_ASSERT(((Cy_u32StartupStackStartAddress)    % ECC_INIT_WIDTH_BYTES) == 0U);
	STARTUP_ASSERT(((Cy_u32StartupStackEndAddress + 1U) % ECC_INIT_WIDTH_BYTES) == 0U);
  #endif

	for (uint8_t u8Index = 0U; u8Index < GET_NR_OF_ARRAY_ELEMENTS(astcClearRegions); u8Index++) {
		if (IS_ADDRESS_IN_AREA(RESET_COUNTER_VAR_ADDR, astcClearRegions[u8Index].u32StartAddr, astcClearRegions[u8Index].u32EndAddr))
		{
			/* Not cleared since RESET_COUNTER_VAR_ADDR (2 bytes) is used to retain secure boot reset counter */
		}
		else
		{
			// If startup stack is located in current region to be cleared, the clear operation is split up, effectively excluding the startup stack
			if (IS_ADDRESS_IN_AREA(Cy_u32StartupStackStartAddress, astcClearRegions[u8Index].u32StartAddr, astcClearRegions[u8Index].u32EndAddr)) {
				InitRamEccClearArea(astcClearRegions[u8Index].u32StartAddr, Cy_u32StartupStackStartAddress - 1U);
				InitRamEccClearArea(Cy_u32StartupStackEndAddress + 1U,      astcClearRegions[u8Index].u32EndAddr);
			} else {
				InitRamEccClearArea(astcClearRegions[u8Index].u32StartAddr, astcClearRegions[u8Index].u32EndAddr);
			}
		}
	}
}


/****************************************************************************/
/* Function name	: InitRamEccClearArea									*/
/* Description		: Clears an area by writing '0' using a pointer of type	*/
/*					: #ecc_init_width_t.									*/
/* Argument			: u32StartAddr	- Start address of area to be cleared	*/
/*					: u32EndAddr	- Last address within area to be cleared*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: 														*/
/****************************************************************************/
static void InitRamEccClearArea(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
	volatile ecc_init_width_t * pRam = (volatile ecc_init_width_t *) u32StartAddr;
	ecc_init_width_t Zero = 0U;

	for (; (uint32_t)pRam < u32EndAddr; pRam++) {
		// Note: Even if ecc_init_width_t is uint64_t, this will be compiled as two 32-bit accesses 
		//       in case of CM0+, because there is no STRD instruction specified in ARMv6-M Thumb
		*pRam = Zero;
	}
}

#endif // STARTUP_CUSTOMIZE__ENABLE_ECC_INITIALIZATION


/****************************************************************************/
/* Function name	: CopyVectorTable										*/
/* Description		: Copies the vector table from ROM to RAM and updates	*/
/*					: the VTOR (CMx vector table base register) accordingly.*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: 														*/
/****************************************************************************/
static void CopyVectorTable(void)
{
	const uint8_t    u8NrOfVectors = (uint8_t) ((uint32_t) &__Vectors_Size / BYTES_OF_VECTOR);
	uint32_t * const pu32RamTable  = (uint32_t *) __ramVectors;
	uint32_t * const pu32RomTable  = (uint32_t *) (&__Vectors);

	for (uint8_t u8Index = 0U; u8Index < u8NrOfVectors; u8Index++) {
		pu32RamTable[u8Index] = pu32RomTable[u8Index];
	}

	SCB->VTOR = (uint32_t) pu32RamTable;
}


#if (CY_CPU_CORTEX_M0P)

/****************************************************************************/
/* Function name	: CopyVectorTable										*/
/* Description		: Prepares necessary settings to get SROM system calls	*/
/*					: working.												*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: 														*/
/****************************************************************************/
static void PrepareSystemCallInfrastructure(void)
{
	const uint8_t u8Irq0Index = (uint8_t) (VECTOR_TABLE_OFFSET_IRQ0 / BYTES_OF_VECTOR);
	const uint8_t u8Irq1Index = (uint8_t) (VECTOR_TABLE_OFFSET_IRQ1 / BYTES_OF_VECTOR);
	uint32_t * const pu32RamTable   = (uint32_t *) __ramVectors;
	uint32_t * const pu32SromTable  = (uint32_t *) SROM_VECTOR_TABLE_BASE_ADDRESS;

	// Use IRQ0 and IRQ1 handlers from SROM vector table
	pu32RamTable[u8Irq0Index] = pu32SromTable[u8Irq0Index];
	pu32RamTable[u8Irq1Index] = pu32SromTable[u8Irq1Index];

	NVIC_SetPriority(CPUIntIdx0_IRQn, 1U);
	NVIC_SetPriority(CPUIntIdx1_IRQn, 0U);
	NVIC_EnableIRQ(CPUIntIdx0_IRQn);
	NVIC_EnableIRQ(CPUIntIdx1_IRQn);

	// Only item left is clearing of PRIMASK:
	// This should be done by the application at a later point in time (e.g. in main())
}

/****************************************************************************/
/* Function name	: ConfigureECC											*/
/* Description		: Configure FLASH and SRAM ECC, CM0+ CPU cache as needed*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: The following settings are enabled by default, so you	*/
/*					: can implement them when disabled.						*/
/****************************************************************************/
static void ConfigureECC(void)
{
	/* Disable FLASH ECC */
	FLASHC->unFLASH_CTL.stcField.u1MAIN_ECC_EN = FLASHC_MAIN_ECC_EN_VALUE;
	FLASHC->unFLASH_CTL.stcField.u1WORK_ECC_EN = FLASHC_WORK_ECC_EN_VALUE;

	/* Disable SRAM ECC */
	CPUSS->unRAM0_CTL0.stcField.u1ECC_EN = SRAM0_CTL_ECC_EN_VALUE;
	CPUSS->unRAM1_CTL0.stcField.u1ECC_EN = SRAM1_CTL_ECC_EN_VALUE;
	CPUSS->unRAM2_CTL0.stcField.u1ECC_EN = SRAM2_CTL_ECC_EN_VALUE;

	/* Disable ECC of CM0+ CPU Cache */
	FLASHC->unCM0_CA_CTL0.stcField.u1RAM_ECC_EN = FLASHC_CA_RAM_ECC_EN_VALUE;

	/* Disable CM0+ CPU Cache */
	FLASHC->unCM0_CA_CTL0.stcField.u1CA_EN = FLASHC_CA_EN_VALUE;
}

#endif

#if (CY_CPU_CORTEX_M7)

/****************************************************************************/
/* Function name	: ConfigureECC											*/
/* Description		: Configure ECC of ITCM, DTCM, L1 cache as needed.		*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: 														*/
/****************************************************************************/
static void ConfigureECC(void)
{
  #if defined(CY_CORE_CM7_0)

	/* Enable ITCM and DTCM ECC which is disabled by default */
	CPUSS->unCM7_0_CTL.stcField.u1ITCM_ECC_EN = CM7_0_ITCM_ECC_EN_VALUE;
	CPUSS->unCM7_0_CTL.stcField.u1DTCM_ECC_EN = CM7_0_DTCM_ECC_EN_VALUE;

	/* Disable ICache and DCache ECC which is enabled by default */
	SCB->CACR = (SCB->CACR & ~(uint32_t)SCB_CACR_ECCDIS_Msk) |
        (uint32_t)(CM7_0_CACR_ECCDIS_VALUE << SCB_CACR_ECCDIS_Pos);

  #else /* CY_CORE_CM7_1 */

	/* Enable ITCM and DTCM ECC which is disabled by default */
	CPUSS->unCM7_1_CTL.stcField.u1ITCM_ECC_EN = CM7_1_ITCM_ECC_EN_VALUE;
	CPUSS->unCM7_1_CTL.stcField.u1DTCM_ECC_EN = CM7_1_DTCM_ECC_EN_VALUE;

	/* Disable ICache and DCache ECC which is enabled by default */
	SCB->CACR = (SCB->CACR & ~(uint32_t)SCB_CACR_ECCDIS_Msk) |
        (uint32_t)(CM7_1_CACR_ECCDIS_VALUE << SCB_CACR_ECCDIS_Pos);

  #endif
}

#endif

/****************************************************************************/
/* Function name	: ConfigureMPU											*/
/* Description		: Configure Memory Protection Unit.						*/
/* Argument			: None													*/
/* Return value		: None													*/
/* Developer		: Infineon												*/
/* Developed date	: 2023/05/23											*/
/* Remarks			: 														*/
/****************************************************************************/
static void ConfigureMPU(void)
{
	uint32_t numOfConfig = GET_NR_OF_ARRAY_ELEMENTS(mpuConfigList) - 1U;

	if (numOfConfig > 0U) {
		Cy_MPU_Setup(mpuConfigList, numOfConfig,
            (cy_en_mpu_privdefena_t)MPU_PRIV_DEF_ENA,
            (cy_en_mpu_hfnmiena_t)MPU_HF_NMI_ENA);
	}
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
