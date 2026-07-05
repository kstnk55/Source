/**
 * @file CoreIso_MemMap.h
 * @brief Public header for Memory Mapping Configuration
 * @details Overview: Memory mapping configuration for Core Isolation module to control placement of code and constant sections
 */
 
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *  
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CoreIso_MemMap.h
 *        \brief  
 *      \details  
 *********************************************************************************************************************/
#if !defined (COREISO_MEMMAP_H)
# define COREISO_MEMMAP_H
 
/**
 * @def COREISO_MEMMAP_ERROR
 * @value [defined]
 * @resolution -
 * @brief Error detection flag for memory mapping sections
 */
#ifndef COREISO_MEMMAP_ERROR
  #define COREISO_MEMMAP_ERROR
#endif
 
/**********************************************************************************************************************
 *  CODE sections
 *********************************************************************************************************************/
/**
 * @def COREISO_START_SEC_CODE
 * @value [section-start]
 * @resolution -
 * @brief Start marker for CoreIso code section
 * @details Begins a section for Core Isolation module executable code.
 *          GHS compiler-specific pragma places the code in the ".COREISO_CODE" section.
 */
#ifdef COREISO_START_SEC_CODE
  #pragma ghs section text = ".COREISO_CODE"
  #undef COREISO_START_SEC_CODE
  #undef COREISO_MEMMAP_ERROR
#endif
 
/**
 * @def COREISO_STOP_SEC_CODE
 * @value [section-end]
 * @resolution -
 * @brief End marker for CoreIso code section
 * @details Ends the Core Isolation module code section and returns to the default text section.
 */
#ifdef COREISO_STOP_SEC_CODE
  #pragma ghs section text = default
  #undef COREISO_STOP_SEC_CODE
  #undef COREISO_MEMMAP_ERROR
#endif
 
/**********************************************************************************************************************
 *  CONST sections
 *********************************************************************************************************************/
/**
 * @def COREISO_START_SEC_CONST
 * @value [section-start]
 * @resolution -
 * @brief Start marker for CoreIso constant section
 */
#ifdef COREISO_START_SEC_CONST
  #pragma ghs section rodata = ".COREISO_CONST"
  #undef COREISO_START_SEC_CONST
  #undef COREISO_MEMMAP_ERROR
#endif
 
/**
 * @def COREISO_STOP_SEC_CONST
 * @value [section-end]
 * @resolution -
 * @brief End marker for CoreIso constant section
 */
#ifdef COREISO_STOP_SEC_CONST
 
  #pragma ghs section rodata = default
  #undef COREISO_STOP_SEC_CONST
  #undef COREISO_MEMMAP_ERROR
#endif
 
#if defined (COREISO_MEMMAP_ERROR)
  #error "Error in CoreIso_MemMap.h: MemMap section is not included!"
#endif
 
#endif /* COREISO_MEMMAP_H */
/**********************************************************************************************************************
 *  END OF FILE: CoreIso_MemMap.h
 *********************************************************************************************************************/
 
 