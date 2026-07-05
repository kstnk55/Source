/**
 * @file cy_si_config.h
 * @brief Secure Image configuration header ( This module provided by Nippon Seiki should be left unchanged by FPT.)
 * @details Definitions and function prototypes for Secure Image on TRAVEO T2G platform. This module provided by Nippon Seiki should be left unchanged by FPT.
 */

/****************************************************************************/
/* File name		: cy_si_config.h										*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Definitions and function prototypes for Secure Image.	*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#ifndef CY_SI_CONFIG_H
#define CY_SI_CONFIG_H

/* User configuration for Code FLASH memory allocation */
//0x1000 0000 -> 0x1008 FBFF
#define CY_FLASH_LG_DBM0_BASE           		(0x10000000UL)
#define CM0PLUS_APP_HEADER_ADDRESS				(CY_FLASH_LG_DBM0_BASE)
#define CM0PLUS_VECTOR_ADDRESS				    (CM0PLUS_APP_HEADER_ADDRESS + 0x10)
#define CM0PLUS_VECTOR_TABLE_ADDRESS			(CM0PLUS_APP_HEADER_ADDRESS + 256U)
#define CM0PLUS_DIGITAL_SIGNATURE_ADDRESS		(0x1008FC00UL)



/** \defgroup group_Secure_Image_virsion_macros Secure Image version configuration
* Secure Image version configuration.
* \{
*/
#define CY_SI_VERSION_MAJOR				(0UL)	/**< Major version Configure depends on System.*/
#define CY_SI_VERSION_MINOR				(1UL)	/**< Minor version Configure depends on System.*/
/** \} group_Secure_Image_virsion_macros */

/* Application Header */
#define CY_SI_APP_ID_SECUREIMG			(0x0UL)		/**< Secure image ID Type */
#define CY_SI_SECURE_DIGSIG_SIZE			(384UL)			/**< Size (in Bytes) of the digital signature for RSA-3K*/

#define CY_SI_APP_VERSION	((CY_SI_VERSION_MAJOR << 24u) | (CY_SI_VERSION_MINOR << 16u)) /**< App Version */
#define CY_M0PLUS_SI_SIZE	(CM0PLUS_DIGITAL_SIGNATURE_ADDRESS - CM0PLUS_APP_HEADER_ADDRESS)
#define CY_SI_CPUID			(0xC6000000UL)									/* CM0+ ARM CPUID[15:4] Reg shifted to [31:20] */
#define CY_SI_CORE_IDX		(0UL)											/* Index ID of the CM0+ core */


/**
  * \brief Application header Structure
  */
typedef struct {
	volatile uint32 objSize;					/**< Object size (Bytes) */
	volatile uint32 appId;					/**< Application ID/version */
	volatile uint32 appAttributes;			/**< Attributes (reserved for future use) */
	volatile uint32 numCores;					/**< Number of cores */
	volatile uint32 core0Vt;					/**< (CM0+)VT offset - offset to the vector table from that entry */
	volatile uint32 core0Id;					/**< CM0+ core ID */
} cy_stc_si_appheader_t;

#endif /* CY_SI_CONFIG_H */

/* [] END OF FILE */
