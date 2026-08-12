/****************************************************************************/
/* File name        : DualBank_ManagerCallback.c                            */
/*--------------------------------------------------------------------------*/
/* Customer         : Platform module                                       */
/*--------------------------------------------------------------------------*/
/* CPU              : TRAVEO T2G Body/cluster model                         */
/*                  : (CYT3BB/CYT4BF/CYT3DL/CYT4DN)                         */
/*--------------------------------------------------------------------------*/
/* Programmed by    : Infineon                                              */
/* Date             : 2023/08/21                                            */
/* Copyrights       : Nippon Seiki Co.,Ltd                                  */
/* Description      : Define callback functions to be called from           */
/*                  : DualBank_Manager                                      */
/*--------------------------------------------------------------------------*/
/* Updated by       :                                                       */
/* Date             :                                                       */
/* Revision         :                                                       */
/****************************************************************************/
 
/*****************************************************************************
* Include files
*****************************************************************************/
#include "cy_project.h"
#define DUAL_BANK_MANAGER_CALLBACK_C
#include "BootConfig.h"
#include "DualBank_Manager_FblTransition.h"
 
/*****************************************************************************
* Local pre-processor symbols/macros ('define')
*****************************************************************************/
#define NOP10() do { \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  } while(0)
 
#define CPUSS_RAM0_PWR_MACRO_CTL0 (*(volatile uint32_t*) 0x40201340UL)
#define CM0P_SCS_AIRCR (*(volatile uint32_t*) 0xE000ED0CUL)
#define RESET_COUNTER_LIMIT (2UL)
#define HARDFAULT_COUNTER_LIMIT (2UL)
#define SRAM_RETAIN_VALUE (0x05FA0002UL)
#define SOFTWARE_RESET_VALUE (0x05FA0004UL)
#define RESET_COUNTER_VAR (*(volatile uint16_t*)RESET_COUNTER_ADDR) /* 0x28007FF0 */
#define SWITCHBANK_STATUS_VAR (*(volatile uint16_t*)0x28007FF2)
#define APP_STATUS_VAR (*(volatile uint16_t*)0x28007FF4)
#define HARDFAULT_COUNTER_VAR (*(volatile uint16_t*)0x28007FF6)
#define APP_A_FAIL (0x0A0AU)
#define APP_A_OK (0xAAAAU)
#define APP_B_FAIL (0x0B0BU)
#define APP_B_OK (0xBBBBU)
#define SWITCHBANK_SWITCHED (0xABCDUL)
#define SWITCHBANK_ALLOWED (1UL)
#define SWITCHBANK_NOT_ALLOWED (0UL)
#define SECUREBOOT_DTC_CM0 (0xCCU)
#define SECUREBOOT_DTC_CM7 (0xDDU)
 
/*****************************************************************************
* Global variable definitions (declared in header file with 'extern')
*****************************************************************************/
// CAUTION: Static or global initialized and non-const variables will not have their init value yet!
 
 
/*****************************************************************************
* Local type definitions ('typedef')
*****************************************************************************/
typedef union sDualBank_DTCFlagType
{
    uint32 SecuBootDTCFlag;
    struct{
        uint8 DTC_FLAG_BANKA : 8;
        uint8 DTC_FLAG_BANKB : 8;
        uint8 Resvered1 : 8; // Reserved for the further use such as support DTC flag checking of CoreIsolation feature
        uint8 Resvered2 : 8;
    } DTC_Flag_Block;
} DualBank_DTCFlagType;
 
/*****************************************************************************
* Local variable definitions ('static')
*****************************************************************************/
// CAUTION: Static or global initialized and non-const variables will not have their init value yet!
 
 
/*****************************************************************************
* Local constant definitions ('static')
*****************************************************************************/
 
 
/*****************************************************************************
* Local function prototypes ('static')
*****************************************************************************/
 
 
/*****************************************************************************
* Function implementation - global ('extern') and local ('static')
*****************************************************************************/
 
/****************************************************************************/
/* Function name    : DualBankMngr_CheckMagicWord                           */
/* Description      : Determine the latest bank based on the magic word.    */
/* Argument         : magicWord     - Current value of magic word           */
/* Return value     : 2             - Apply lower bank                      */
/*                  : 1             - Apply upper bank                      */
/*                  : 0             - Invalid bank                          */
/* Developer        : Infineon                                              */
/* Developed date   : 2023/08/21                                            */
/* Remarks          :                                                       */
/****************************************************************************/
CY_SECTION(".mapboot") uint32 DualBankMngr_CheckMagicWord(uint32 magicWord)
{
    uint32 result = 0UL;
 
    /* 注1 コードフラッシュにはアクセス不可。リンカの配置にも注意すること */
    /* 注2 スタック消費量はスタック初期化分を超えないこと */
 
    DualBank_DTCFlagType* SecureBootDtc_Ptr = (DualBank_DTCFlagType*)(volatile uint32*)BANKA_DTC_FLAG_VAR_ADDR;
   
    if (AUTHENTICATION_CHECK == AUTHENTICATION_DISABLE)
    {
        if (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA != 0U)
        {
            SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA = 0U;
        }
       
        if (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB != 0U)
        {
            SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB = 0U;
        }
       
        if (SWITCHBANK_STATUS_VAR != 0UL)
        {
            SWITCHBANK_STATUS_VAR = 0UL;
        }
    }
   
    /* Reset application verification status, might be updated as APP_FAIL later */
    APP_STATUS_VAR = APP_A_OK;
 
    if (magicWord == MAGIC_WORD_B)
    {
        result = 1UL;
        APP_STATUS_VAR = APP_B_OK;
    }
    else if (magicWord == MAGIC_WORD_A)
    {
        result = 2UL;
        APP_STATUS_VAR = APP_A_OK;
    }
 
    if(SWITCHBANK_STATUS_VAR == SWITCHBANK_SWITCHED) /* Try another bank after first secure boot failure*/
    {
        if((0UL == result) || (2UL == result)) /* Invalid or A magic word -> switch it to B*/
        {
            result = 1UL;
            APP_STATUS_VAR = APP_B_OK;
        }
        else if(1UL == result) /* B magic word -> switch it to A*/
        {
            result = 2UL;
            APP_STATUS_VAR = APP_A_OK;
        }
    }
    else
    {
        if((SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA != 0U) && (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA != SECUREBOOT_DTC_CM0) && (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA != SECUREBOOT_DTC_CM7))
        {
            SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA = 0U;
        }
        if((SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB != 0U) && (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB != SECUREBOOT_DTC_CM0) && (SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB != SECUREBOOT_DTC_CM7))
        {
            SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB = 0U;
        }
    }
 
    return result;
}
 
/****************************************************************************/
/* Function name    : DualBankMngr_HdlInvImg                                */
/* Description      : Determine secure boot failure behavior                */
/* Developed date   : 2025/12/05                                            */
/* Remarks          :                                                       */
/****************************************************************************/
CY_SECTION(".mapboot") void DualBankMngr_HdlInvImg(void)
{
    DualBank_DTCFlagType* SecureBootDtc_Ptr = (DualBank_DTCFlagType*)(volatile uint32_t*)BANKA_DTC_FLAG_VAR_ADDR;
   
    if (RESET_COUNTER_VAR < RESET_COUNTER_LIMIT)
    {
        RESET_COUNTER_VAR = RESET_COUNTER_VAR + 1UL;
 
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
    else if (RESET_COUNTER_VAR == RESET_COUNTER_LIMIT)
    {
        RESET_COUNTER_VAR = RESET_COUNTER_VAR + 1UL;
        #if (JUMP_TO_FBL_ENABLE == STD_OFF)
            uint8_t switchBank = SWITCHBANK_ALLOWED;
            if (SWITCHBANK_STATUS_VAR != SWITCHBANK_SWITCHED)
            {
                SWITCHBANK_STATUS_VAR = SWITCHBANK_SWITCHED;
            }
            else
            {
                switchBank = SWITCHBANK_NOT_ALLOWED;
            }
 
            /* Log ram dtc */
            if (APP_A_OK == APP_STATUS_VAR)
            {
                SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA = SECUREBOOT_DTC_CM0;
            }
            else
            {
                SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB = SECUREBOOT_DTC_CM0;
            }
            if(SWITCHBANK_NOT_ALLOWED == switchBank)
            {
                SWITCHBANK_STATUS_VAR = 0UL;
                CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
                NOP10();/* Wait for write buffer empty */
 
                __WFI(); /* Trasition to DeepSleep */
                NOP10(); /* Wait for Trasition DeepSleep complete */
            }
            else /* Reset and switch to new bank */
            {
                RESET_COUNTER_VAR = 0UL;
                CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
                NOP10();/* Wait for write buffer empty */
                CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
            }
        #else
            (void)TransitionToFBL();
        #endif
    }
    else /* garbage value that is other than 0, 1, 2*/
    {
        RESET_COUNTER_VAR = 1UL;/* Secure boot failed 1 at this time */
       
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
}
 
/****************************************************************************/
/* Function name    : DualBankMngr_HdlInvAppImg                             */
/* Description      : Determine secure boot failure behavior of application */
/* Developed date   : 2025/12/05                                            */
/* Remarks          :                                                       */
/****************************************************************************/
CY_SECTION(".mapboot") void DualBankMngr_HdlInvAppImg(void)
{
    DualBank_DTCFlagType* SecureBootDtc_Ptr = (DualBank_DTCFlagType*)(volatile uint32_t*) BANKA_DTC_FLAG_VAR_ADDR;
 
    if(APP_STATUS_VAR == APP_A_OK)
    {
        APP_STATUS_VAR = APP_A_FAIL;
    }
    else
    {
        APP_STATUS_VAR = APP_B_FAIL;
    }
    if (RESET_COUNTER_VAR < RESET_COUNTER_LIMIT)
    {
        RESET_COUNTER_VAR = RESET_COUNTER_VAR + 1UL;
 
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
    else if (RESET_COUNTER_VAR == RESET_COUNTER_LIMIT)
    {
        RESET_COUNTER_VAR = RESET_COUNTER_VAR + 1UL;
        #if (JUMP_TO_FBL_ENABLE == STD_OFF)
            uint8_t switchBank = SWITCHBANK_ALLOWED;
            if (SWITCHBANK_STATUS_VAR != SWITCHBANK_SWITCHED)
            {
                SWITCHBANK_STATUS_VAR = SWITCHBANK_SWITCHED;
            }
            else
            {
                switchBank = SWITCHBANK_NOT_ALLOWED;
            }
 
             /* Log ram dtc */
            if (APP_A_FAIL == APP_STATUS_VAR)
            {
                SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKA = SECUREBOOT_DTC_CM7;
            }
            else
            {
                SecureBootDtc_Ptr->DTC_Flag_Block.DTC_FLAG_BANKB = SECUREBOOT_DTC_CM7;
            }
 
            if(SWITCHBANK_NOT_ALLOWED == switchBank)
            {
                SWITCHBANK_STATUS_VAR = 0UL;
                CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
                NOP10();/* Wait for write buffer empty */
 
                __WFI(); /* Trasition to DeepSleep */
                NOP10(); /* Wait for Trasition DeepSleep complete */
            }
            else /* Reset and switch to new bank */
            {
                RESET_COUNTER_VAR = 0UL;
                CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
                NOP10();/* Wait for write buffer empty */
                CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
            }
        #else
            (void)TransitionToFBL();
        #endif
    }
    else /* garbage value that is other than 0, 1, 2*/
    {
        RESET_COUNTER_VAR = 1UL;/* Secure boot failed 1 at this time */
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
}
 
/****************************************************************************/
/* Function name    : Exception_Handler_Custom                              */
/* Description      : Custom Exception_handler logic                        */
/* Developed date   : 2025/12/05                                            */
/* Remarks          :                                                       */
/****************************************************************************/
CY_SECTION(".mapboot") void Exception_Handler_Custom (void)
{
    if(HARDFAULT_COUNTER_VAR < HARDFAULT_COUNTER_LIMIT)
    {
        HARDFAULT_COUNTER_VAR = HARDFAULT_COUNTER_VAR + 1UL;
 
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
    else if (HARDFAULT_COUNTER_VAR == HARDFAULT_COUNTER_LIMIT)
    {
        HARDFAULT_COUNTER_VAR = HARDFAULT_COUNTER_VAR + 1UL;
 
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
 
        __WFI(); /* Trasition to DeepSleep */
        NOP10(); /* Wait for Trasition DeepSleep complete */
    }
    else /* garbage value that is other than 0, 1, 2*/
    {
        HARDFAULT_COUNTER_VAR = 1UL; /* Hardfault 1 at this time */
 
        CPUSS_RAM0_PWR_MACRO_CTL0 = SRAM_RETAIN_VALUE; /* Keep SRAM in Retained mode */
        NOP10();/* Wait for write buffer empty */
        CM0P_SCS_AIRCR = SOFTWARE_RESET_VALUE; /* Software Reset */
    }
}
 
 