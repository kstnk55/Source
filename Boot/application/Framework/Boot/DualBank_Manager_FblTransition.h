/*******************************************************************************
*<                      Revision History                                      >*
********************************************************************************
*< Revision  Date         By          Description                             >*
********************************************************************************
*< 1.0.0:    08-Jan-2024  KhoaLT4   Initial Version                           >*
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* When build HSM, Use types in Platform_Types, Otherwise use self-definition */
#ifdef FLASH_BOOT_BUILD
#   define STD_OFF 0x00U /** \brief Autosar definition for 'off' */

    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned long uint32;
#else
#   include "Std_Types.h"
#endif

/* Define enable transition to FBL */
#define JUMP_TO_FBL_ENABLE                     STD_OFF
#define FBL_ENTRY_ADDRESS (*(volatile uint32*) 0x103F8000UL)
#define RESET_COUNTER_LIMIT (2UL)
#define RESET_COUNTER (*(volatile uint16*)0x28007FF0)
/*Register CM7_0*/
#define CM7_0_VECTOR_TABLE_BASE (*(volatile uint32*) 0x40200200UL)
#define CM7_0_PWR_CTL           (*(volatile uint32*) 0x40201200UL)
#define CM7_0_CTL               (*(volatile uint32*) 0x4020000CUL)

#define CM7_1_VECTOR_TABLE_BASE (*(volatile uint32*) 0x40200600UL)
#define CM7_1_PWR_CTL           (*(volatile uint32*) 0x40201210UL)
#define CM7_1_CTL               (*(volatile uint32*) 0x4020040CUL)

/* Sound Vp Failure Counter */
#define SOUNDSECBOOT_COUNTER_1 (0xBCBC)
#define SOUNDSECBOOT_COUNTER_2 (0xCDCD)
#define SOUNDSECBOOT_COUNTER_3 (0xDEDE)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void TransitionToFBL(void);
/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FFA */
extern uint16 SoundSecBootFailCounter;
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FFC */
extern uint16 VpSecBootFailCounter;
