/****************************************************************************/
/* File name		: startup_customize.h									*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes definitions for C startup code.				*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#if !defined(STARTUP_CUSTOMIZE_H)
#define STARTUP_CUSTOMIZE_H

#include <stddef.h>
#include <stdbool.h>
#include "cy_device_headers.h"


#if defined(__cplusplus)
extern "C" {
#endif


/** Declarations for symbols created in the linker file */
extern void * __ecc_init_sram_start_address;
extern void * __ecc_init_sram_end_address;
extern void * __ecc_init_dtcm_start_address;
extern void * __ecc_init_dtcm_end_address;
extern void * __ecc_init_itcm_start_address;
extern void * __ecc_init_itcm_end_address;

/** SRAM start and end address for ECC initialisation */
#define STARTUP_CUSTOMIZE__ECC_INIT_SRAM_START_ADDRESS		((uint32_t) &__ecc_init_sram_start_address)
#define STARTUP_CUSTOMIZE__ECC_INIT_SRAM_END_ADDRESS		((uint32_t) &__ecc_init_sram_end_address)

/** DTCM start and end address for ECC initialisation (setting is ignored in case of Cortex-M0+ or Cortex-M4F) */
#define STARTUP_CUSTOMIZE__ECC_INIT_DTCM_START_ADDRESS		((uint32_t) &__ecc_init_dtcm_start_address)
#define STARTUP_CUSTOMIZE__ECC_INIT_DTCM_END_ADDRESS		((uint32_t) &__ecc_init_dtcm_end_address)

/** ITCM start and end address for ECC initialisation (setting is ignored in case of Cortex-M0+ or Cortex-M4F) */
#define STARTUP_CUSTOMIZE__ECC_INIT_ITCM_START_ADDRESS		((uint32_t) &__ecc_init_itcm_start_address)
#define STARTUP_CUSTOMIZE__ECC_INIT_ITCM_END_ADDRESS		((uint32_t) &__ecc_init_itcm_end_address)


/** Declarations for symbols created in startup_cm*.arm/s assembly file */
extern uint32_t Cy_u32StartupStackStartAddress;
extern uint32_t Cy_u32StartupStackEndAddress;
extern void * __Vectors_Size;
extern const cy_israddress __Vectors[];


#if defined(__cplusplus)
}
#endif

#endif /* STARTUP_CUSTOMIZE_H */


/* [] END OF FILE */
