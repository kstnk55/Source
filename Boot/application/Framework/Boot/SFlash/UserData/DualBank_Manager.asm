;************************************************************************

        .file "DualBank_Manager.asm"

;************************************************************************
;* Constants
;************************************************************************

#define DUAL_BANK_MANAGER_ASM
#include "BootConfig.h"

VTOR                                .equ 0xe000ed08
CPUSS_RAM0_CTL0                     .equ 0x40201300
CPUSS_RAM1_CTL0                     .equ 0x40201380
CPUSS_RAM2_CTL0                     .equ 0x402013a0
FLASHC_FLASH_CTL                    .equ 0x40240000

; Macros used for application authentication

CY_FB_VERIFYAPP_ADDR                .equ 0x17002040
CY_PUBLIC_KEY_ADDR                  .equ 0x17006908

CY_APP_START_ADDR_LB                .equ 0x10000000 + APP_OFFSET_VALUE ; CY_FLASH_LG_DBM0_BASE

CY_APP_CM7_START_ADDR_LB            .equ 0x10090400
CY_APP_CM7_LEN_LB                   .equ 0x00367C00
CY_APP_CM7_SIG_ADDR_LB              .equ 0x10090000

CY_APP_CM7_START_ADDR_UB            .equ 0x10488400
CY_APP_CM7_LEN_UB                   .equ 0x00367C00
CY_APP_CM7_SIG_ADDR_UB              .equ 0x10488000
; Mid-Point of the Large sectors in single bank mode for Traveo II 2M device. This value shall be modified based on the Target Device.
; Application intended to be executed out of Map B shall be placed at this starting address.

#if defined(tviibh4m)
CY_APP_START_ADDR_UB                .equ 0x101F8000 + APP_OFFSET_VALUE ; (CY_FLASH_LG_DBM0_BASE + CY_FLASH_LG_DBM0_SIZE)
#elif defined(tviibh8m)
CY_APP_START_ADDR_UB                .equ 0x103F8000 + APP_OFFSET_VALUE ; (CY_FLASH_LG_DBM0_BASE + CY_FLASH_LG_DBM0_SIZE)
#elif defined(tviic2d4m)
CY_APP_START_ADDR_UB                .equ 0x101F8000 + APP_OFFSET_VALUE ; (CY_FLASH_LG_DBM0_BASE + CY_FLASH_LG_DBM0_SIZE)
#elif defined(tviic2d6m)
CY_APP_START_ADDR_UB                .equ 0x102F8000 + APP_OFFSET_VALUE ; (CY_FLASH_LG_DBM0_BASE + CY_FLASH_LG_DBM0_SIZE)
#endif

; Macro used for the flash boundary check. This macro has the value ( Map A/B Large sector end address in single bank mode - size of the digital signature (256 bytes))for Traveo II 2M device.
; These values shall be modified based on the Target Device

#if defined(tviibh4m)
CY_APP_END_ADDR_LB                  .equ 0x1008FC00 ; 0x101F8000(CY_APP_START_ADDR_LB + CY_FLASH_LG_DBM0_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
CY_APP_END_ADDR_UB                  .equ 0x103EFF00 ; 0x103F0000(CY_APP_START_ADDR_UB + CY_FLASH_LG_DBM1_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
#elif defined(tviibh8m)
CY_APP_END_ADDR_LB                  .equ 0x1008FC00 ; 0x10000000(CY_APP_START_ADDR_LB) + 0x8FC00(VEHSM_SIZE)
CY_APP_CM7_END_ADDR_LB              .equ 0x103F8000 ; 0x10090400(CY_APP_CM7_START_ADDR_LB) + 0x367C00(CM7_APP_SIZE)
CY_APP_END_ADDR_UB                  .equ 0x10487C00 ; 0x103F8000(CY_APP_START_ADDR_UB) + 0x8FC00(VEHSM_SIZE)
CY_APP_CM7_END_ADDR_UB              .equ 0x107F0000 ; 0x10488400(CY_APP_CM7_START_ADDR_UB) + 0x367C00(CM7_APP_SIZE)
#elif defined(tviic2d4m)
CY_APP_END_ADDR_LB                  .equ 0x101F7F00 ; 0x101F8000(CY_APP_START_ADDR_LB + CY_FLASH_LG_DBM0_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
CY_APP_END_ADDR_UB                  .equ 0x103EFF00 ; 0x103F0000(CY_APP_START_ADDR_UB + CY_FLASH_LG_DBM1_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
#elif defined(tviic2d6m)
CY_APP_END_ADDR_LB                  .equ 0x102F7F00 ; 0x102F8000(CY_APP_START_ADDR_LB + CY_FLASH_LG_DBM0_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
CY_APP_END_ADDR_UB                  .equ 0x105EFF00 ; 0x105F0000(CY_APP_START_ADDR_UB + CY_FLASH_LG_DBM1_SIZE) - 0x100(CY_SI_SECURE_DIGSIG_SIZE)
#endif

;************************************************************************
;* Import symbols
;************************************************************************
        .import __ghsend_stack
        .import _startcontd
        .import DualBankMngr_CheckMagicWord
        .import DualBankMngr_HdlInvImg
        .import DualBankMngr_HdlInvAppImg
        .import Exception_Handler_Custom

;************************************************************************
;* Export symbols
;************************************************************************
        .export _start

;************************************************************************
;* Dual Bank Manager Vector Table
;************************************************************************
; This is the vector table required for CySAF of the Dual Bank Manager. Only the first 4 entries are used, others are filled with zero.
        .section ".sflashintvec", "a"
        ; align to 256 bytes, because CM0_VECTOR_TABLE_BASE register only supports address bits [31:8]
        .align 256

__sflashvector_table:

        DCD     __ghsend_stack
        DCD     _start
        DCD     Exception_handler
        DCD     Exception_handler
        DCD     0
        DCD     0
        DCD     0
__sflashvector_table_0x1c:
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0

        ; External interrupts              PowerMode    Description

        DCD     0                        ; DeepSleep    CPU User Interrupt #0
        DCD     0                        ; DeepSleep    CPU User Interrupt #1
        DCD     0                        ; DeepSleep    CPU User Interrupt #2
        DCD     0                        ; DeepSleep    CPU User Interrupt #3
        DCD     0                        ; DeepSleep    CPU User Interrupt #4
        DCD     0                        ; DeepSleep    CPU User Interrupt #5
        DCD     0                        ; DeepSleep    CPU User Interrupt #6
        DCD     0                        ; DeepSleep    CPU User Interrupt #7

        ; These IRQs can only be triggered by SW via NVIC regs
        DCD     0                        ; Active       CPU User Interrupt #8
        DCD     0                        ; Active       CPU User Interrupt #9
        DCD     0                        ; Active       CPU User Interrupt #10
        DCD     0                        ; Active       CPU User Interrupt #11
        DCD     0                        ; Active       CPU User Interrupt #12
        DCD     0                        ; Active       CPU User Interrupt #13
        DCD     0                        ; Active       CPU User Interrupt #14
        DCD     0                        ; Active       CPU User Interrupt #15

        .endo __sflashvector_table

;************************************************************************
;* SRAM Function Space Reservation
;************************************************************************
; SRAM section to reserve space for SRAM function needed for flash bank configurations
        .section ".ramprog", "awx"
        .align 8

; number of bytes for to allocated in ramprog for _flashbankswitchramcopy
_flashbankswitchsize           .equ (_flashbankswitchend - _flashbankswitch)

_flashbankswitchramcopy:
        .space        _flashbankswitchsize

;************************************************************************
;* Dual Bank Manager
;************************************************************************
        .weak Reset_Handler
        .section ".mapboot", "ax"
        .thumb

; For CYT2B78CAE device, the SFlash application will be placed in the SFlash user data region and program in NORMAL_PROVISIONED mode.
; The FlashBoot will launch this application, the reset handler of this application checks if authentication of CM0+ CodeFlash application
; is valid , copies _flashbankswitch function to SRAM and and jumps to SRAM function which does the flash bank operation and jumps to
; reset handler of the CM0+ CodeFlash application where additional startup is continued

.align 4
Reset_Handler:
_start:

;************************************************************************
;* Disabling Interrupts
;************************************************************************
;Disable global interrupts
        CPSID I

;************************************************************************
;* Updating VTOR
;************************************************************************
; Update Vector Table Offset Register with address of SFlash vector table

        LDR  r0, =__sflashvector_table
        LDR  r1, =VTOR
        STR  r0, [r1]
        DSB

;************************************************************************
;* Disabling SRAM ECC Check
;************************************************************************
; CM0+ bus width is 32-bit, but SRAM is built with 64-bit based ECC on Traveo II parts with CM7 core
; Set CPUSS->RAMx_CTL0.ECC_CHECK_DIS bits to avoid causing unintentional ECC faults during startup while SRAM ECC has not been initialized yet
; Done for all SRAM macros as the stack/function could be placed any where based on linker script, this could also be modified only to specific SRAM macros

#if (defined (tviibh4m) || defined (tviibh8m) || defined (tviic2d6m) || defined (tviic2d4m))
        MOVS r4, #1
        LSLS r4, r4, #19
        LDR  r1, =CPUSS_RAM0_CTL0
        LDR  r2, [r1]
        ORRS r2, r4
        STR  r2, [r1]
        LDR  r1, =CPUSS_RAM1_CTL0
        LDR  r2, [r1]
        ORRS r2, r4
        STR  r2, [r1]
        LDR  r1, =CPUSS_RAM2_CTL0
        LDR  r2, [r1]
        ORRS r2, r4
        STR  r2, [r1]
#endif

;************************************************************************
;* Initializing Stack
;************************************************************************
; Initialize ECC of startup stack
        MOVS r0, #0 ; clear value
        MOVS r1, #0 ; clear value
        LDR  r2, flashmarkers+28

startup_stack_ecc_init_loop:
        STM  r2!, {r0, r1}
        CMP  r2, sp
        BNE  startup_stack_ecc_init_loop

; For Traveo II devices with 64-bit based ECC SRAM, initialize ECC of the region where SRAM function shall be copied later from SFlash
#if (defined (tviibh4m) || defined (tviibh8m) || defined (tviic2d6m) || defined (tviic2d4m))

        LDR  r2, flashmarkers
; Subtract 1 from R2 due to Thumb alignment
        SUBS r2, 1
        LDR  r3, flashmarkers+4

; loop to clear the SRAM
SRAM_function_ecc_init_loop:
        STR  r1, [r2,r0]
        ADDS r0, #8
        CMP  r0, r3
        BCC  SRAM_function_ecc_init_loop

; Clear CPUSS->RAMx_CTL0.ECC_CHECK_DIS bits to enable ECC check/correction; r4 already has the bit position.

        LDR  r1, =CPUSS_RAM0_CTL0
        LDR  r2, [r1]
        BICS r2, r4
        STR  r2, [r1]
        LDR  r1, =CPUSS_RAM1_CTL0
        LDR  r2, [r1]
        BICS r2, r4
        STR  r2, [r1]
        LDR  r1, =CPUSS_RAM2_CTL0
        LDR  r2, [r1]
        BICS r2, r4
        STR  r2, [r1]
#endif

;************************************************************************
;* Disabling Work Flash Bus Error
;************************************************************************
; Load the address for FLASHC_FLASH_CTL
        LDR  r4, flashmarkers+8

; ### Read the value of FLASHC_FLASH_CTL and back up to undo ###
        LDR  r0, [r4]
        MOV  r8, r0

; Set FLASHC_FLASH_CTL.WORK_ERR_SILENT
; Reading the Work Flash in erased state can cause bus fault when FLASHC_FLASH_CTL.WORK_ERR_SILENT is 0
        MOVS r1, #1
        LSLS r1, r1, #22
        ORRS r0, r1
        STR  r0, [r4]
        LDR  r0, [r4]

;************************************************************************
;* Magic Word Check
;************************************************************************
; Initialize maigc word backup and wordflash market main invalid flag
        MOV r1,#0                       ; Select register r1 as a flag for check magic main with 0: valid, 1:invalid     

MagicWordCheck:
; Check if the magic word is present in Work Flash address

        LDR  r2, flashmarkers+12        ; Load the address of WorkFlash marker main
        B Common_check
        
MagicwordbackupCheck:
        LDR  r2, flashmarkers+44        ; Load the address of WorkFlash marker backup
        MOV  r1, #1                     ; set flag when magic word main invalid


Common_check:
        LDR  r0, [r2]                   ; Load the marker value to r0
        LDR  r4, flashmarkers+20        ; Load the flag for authentication check
        LDR  r5, flashmarkers+24        ; Load the AUTHENTICATION_DISABLE for comparison

        CMP  r1, #1                     ; Check magic word main is valid or not
        BEQ  Invalid_check

        LDR  r7, flashmarkers+32        ; Load the address of DualBankMngr_CheckMagicWord
        BLX  r7

        CMP  r0, #0
        BEQ  MagicwordbackupCheck
        BNE  Mapping_Check

Invalid_check:
        LDR  r7, flashmarkers+32        ; Load the address of DualBankMngr_CheckMagicWord
        BLX  r7
        CMP  r0, #0
        BEQ  Check_MapA_LB               

Mapping_Check:
        CMP  r0, #1
        BNE  Check_MapA_LB

;************************************************************************
;* Authentication Check
;************************************************************************
Check_MapB_UB:
; Check if the authentication check is disabled. If disabled directly jump to Auth_Skip_MapB. If enabled, perform the authentication.
        CMP  r4, r5
        BEQ  Auth_Skip_MapB

; Check if the result of authentication of upper bank image is successful, if not jump to Check_MapB_LB and check lower bank
        BL   _checkUB
        CMP  r0, #1
        BNE  ImageInvalid
        BL   _checkUB_CM7
        CMP  r0, #1
        BNE  AppImageInvalid
; Clear failure counter after successful verification
        LDR  r4, flashmarkers+48
        MOVS r5, #0
        STR  r5, [r4]
; Clear failure dtc bankB after successful verification
        LDR  r4, flashmarkers+52        ; address of the code flash A failure dtc
        LDR  r5, [r4]
        MOVS r6, #0xFF                  
        AND  r5, r6
        STR  r5, [r4]
Auth_Skip_MapB:
; Jump to the FlashtoRAM_copy function with register r6 set
        MOVS r6, #1
        B    FlashtoRAM_copy

Check_MapB_LB:
; Check if the result of authentication of lower bank image is successful, if not jump to ImageInvalid, and no application is launched.
        BL   _checkLB
        CMP  r0, #1
        BNE  ImageInvalid

; Jump to the FlashtoRAM_copy copy function with register r6 cleared
        MOVS r6, #0
        B    FlashtoRAM_copy

Check_MapA_LB:

; Check if the authentication check is disabled. If disabled directly jump to Auth_Skip_MapA. If enabled, perform the authentication.
        CMP  r4, r5
        BEQ  Auth_Skip_MapA

; Check if the result of authentication of lower bank image is successful, if not jump to Check_MapA_UB and check upper bank
        BL   _checkLB
        CMP  r0, #1
        BNE  ImageInvalid
        BL   _checkLB_CM7
        CMP  r0, #1
        BNE  AppImageInvalid
; Clear failure counter after successful verification
        LDR  r4, flashmarkers+48
        MOVS r5, #0
        STR  r5, [r4]
; Clear failure dtc bankA after successful verification
        LDR  r4, flashmarkers+52        ; address of the code flash A failure dtc
        LDR  r5, [r4]
        MOVS r6, #0xFF
        LSLS r6, r6, #8                 ; shift to ignore code flash B failure dtc
        AND  r5, r6
        STR  r5, [r4]

Auth_Skip_MapA:
; Jump to the FlashtoRAM_copy function with register r6 cleared
        MOVS r6, #0
        B    FlashtoRAM_copy

Check_MapA_UB:
; Check if the result of authentication of upper bank image is successful, if not jump to ImageInvalid, no application is launched.
        BL   _checkUB
        CMP  r0, #1
        BNE  ImageInvalid

; Jump to the FlashtoRAM_copy function with register r6 set
        MOVS r6, #1
        B    FlashtoRAM_copy

;************************************************************************
;* Authentication Failure
;************************************************************************
; Enters this handler when both banks have invalid images

ImageInvalid:
        LDR  r7, flashmarkers+36        ; Load the address of DualBankMngr_HdlInvImg
        BLX  r7
        B    InfLoop
AppImageInvalid:
        LDR  r7, flashmarkers+40        ; Load the address of DualBankMngr_HdlInvAppImg
        BLX  r7
        B    InfLoop
InfLoop:
        B    InfLoop

;************************************************************************
;* Exception_handler
;************************************************************************
; Enters this handler when HardFault happens during the Dual Bank Manager execution
Exception_handler:
        LDR  r7, flashmarkers+56        ; Load the address of Exception_Handler_Custom:
        BLX  r7
        B    InfLoop

;************************************************************************
;* SFlash to SRAM Copy
;************************************************************************
FlashtoRAM_copy:

; ### Undo the FLASHC_FLASH_CTL.WORK_ERR_SILENT to initial value ###
        MOV  r0, r8
        LDR  r1, flashmarkers+8
        STR  r0, [r1]
        LDR  r0, [r1]

; Copy the _flashbankswitch function to SRAM and Dual Bank Manager jumps to SRAM where the dual bank configuration is done

; Load the register with the source address, destination address and size
        ADR  r3, _flashbankswitch
        LDR  r2, flashmarkers
        LDR  r1, flashmarkers+4

; Subtract 1 from R2 due to Thumb alignment
        SUBS r2, #1

; R0 is used for compare operation
        MOVS r0, #0
        B    compare

; loop to copy the complete SFlash function to SRAM
copyloop:
        LDR  r4, [r3,r0]
        STR  r4, [r2,r0]
        ADDS r0, #4

compare:
        CMP  r0, r1
        BCC  copyloop

; Jump to the _flashbankswitch copy function in SRAM with valid r6
        LDR  r7, flashmarkers
        BX   r7
        .endf _start

;************************************************************************
;* Flashmarkers Macros
;************************************************************************
; Markers for flash copy operation
.align 4
flashmarkers:
        DCD    _flashbankswitchramcopy                                    ; flashmarkers
        DCD    _flashbankswitchsize                                       ; flashmarkers+4
        DCD    FLASHC_FLASH_CTL                                           ; flashmarkers+8
        DCD    ADDR_MAKER_ON_WORK                                         ; flashmarkers+12
        DCD    MAGIC_WORD_B                                               ; flashmarkers+16
        DCD    AUTHENTICATION_CHECK                                       ; flashmarkers+20
        DCD    AUTHENTICATION_DISABLE                                     ; flashmarkers+24
        DCD    (__ghsend_stack - (#STARTUP_STACK_SIZE_DOUBLE_WORDS * 8))  ; flashmarkers+28
        DCD    DualBankMngr_CheckMagicWord                                ; flashmarkers+32
        DCD    DualBankMngr_HdlInvImg                                     ; flashmarkers+36
        DCD    DualBankMngr_HdlInvAppImg                                  ; flashmarkers+40
        DCD    ADDR_BACKUP_MAKER_ON_WORK                                  ; flashmarkers+44
        DCD    RESET_COUNTER_ADDR                                         ; flashmarkers+48
        DCD    BANKA_DTC_FLAG_VAR_ADDR                                    ; flashmarkers+52
        DCD    Exception_Handler_Custom                                   ; flashmarkers+56
.endo flashmarkers

;************************************************************************
;* Digital Signature Verification Function
;************************************************************************
; Performs authentication of the lower Bank
LowerBankCheck:
.align 4

_checkLB:

        PUSH {LR}

; Check if the Application is valid with Cy_FB_VerifyApplication()

; Load the registers with the lower bank parameters for Cy_FB_VerifyApplication() function
        LDR  r0, addrmarker+4        ; address of the lower bank image
        LDR  r1, [r0]                ; length of the lower bank image
        ADDS r2, r0, r1              ; address of the digital signature
        BCS  skip_LB_check           ; carry bit detected, boundary violation
        LDR  r4, addrmarker+16       ; end address for the lower bank
        CMP  r2, r4                  ; boundary condition check
        BHI  skip_LB_check           ; skip Cy_FB_VerifyApplication
        LDR  r3, addrmarker+8        ; address of the public key

; Get the address of Cy_FB_VerifyApplication() from SFlash marker
        LDR  r4, addrmarker
        LDR  r7, [r4]

; Call Cy_FB_VerifyApplication() function
        BLX  r7

skip_LB_check:
        POP  {PC}

        .endf _checkLB

_checkLB_CM7:

        PUSH {LR}

; Check if the Application is valid with Cy_FB_VerifyApplication()

; Load the registers with the lower bank parameters for Cy_FB_VerifyApplication() function
        LDR  r0, addrmarker+32       ; address of the lower bank image
        LDR  r1, addrmarker+24       ; length of the lower bank image
        LDR  r2, addrmarker+28       ; address of the digital signature
        LDR  r4, addrmarker+36       ; end address for the lower bank
        LDR  r3, addrmarker+8        ; address of the public key

; Get the address of Cy_FB_VerifyApplication() from SFlash marker
        LDR  r4, addrmarker
        LDR  r7, [r4]

; Call Cy_FB_VerifyApplication() function
        BLX  r7

skip_LB_check_CM7:
        POP  {PC}

        .endf _checkLB_CM7

; Performs authentication of the upper Bank
UpperBankCheck:
.align 4

_checkUB:

        PUSH {LR}

; Check if the Application is valid with Cy_FB_VerifyApplication()

; Load the registers with the upper bank parameters for Cy_FB_VerifyApplication() function
        LDR  r0, addrmarker+12       ; address of the upper bank image
        LDR  r1, [r0]                ; length of the upper bank image
        ADDS r2, r0, r1              ; address of the digital signature
        BCS  skip_UB_check           ; carry bit detected, boundary violation
        LDR  r4, addrmarker+20       ; end address for the upper bank
        CMP  r2, r4                  ; boundary condition check
        BHI  skip_UB_check           ; skip Cy_FB_VerifyApplication
        LDR  r3, addrmarker+8        ; address of the public key

; Get the address of Cy_FB_VerifyApplication() from SFlash marker
        LDR  r4, addrmarker
        LDR  r7, [r4]

; Call Cy_FB_VerifyApplication() function
        BLX  r7

skip_UB_check:
        POP  {PC}

        .endf _checkUB

_checkUB_CM7:

        PUSH {LR}

; Check if the Application is valid with Cy_FB_VerifyApplication()

; Load the registers with the upper bank parameters for Cy_FB_VerifyApplication() function
        LDR  r0, addrmarker+48       ; address of the upper bank image
        LDR  r1, addrmarker+40       ; length of the upper bank image
        LDR  r2, addrmarker+44       ; address of the digital signature
        LDR  r4, addrmarker+52       ; end address for the upper bank
        LDR  r3, addrmarker+8        ; address of the public key

; Get the address of Cy_FB_VerifyApplication() from SFlash marker
        LDR  r4, addrmarker
        LDR  r7, [r4]

; Call Cy_FB_VerifyApplication() function
        BLX  r7

skip_UB_check_CM7:
        POP  {PC}

        .endf _checkUB_CM7

;************************************************************************
;* SRAM Function for Flash Bank Management
;************************************************************************
;************************************************************************
;* Addrmarker Macros
;************************************************************************
; Markers used by the LowerBankCheck and UpperBankCheck functions
.align 4
addrmarker:
        DCD    CY_FB_VERIFYAPP_ADDR      ; addrmarker
        DCD    CY_APP_START_ADDR_LB      ; addrmarker+4
        DCD    CY_PUBLIC_KEY_ADDR        ; addrmarker+8
        DCD    CY_APP_START_ADDR_UB      ; addrmarker+12
        DCD    CY_APP_END_ADDR_LB        ; addrmarker+16
        DCD    CY_APP_END_ADDR_UB        ; addrmarker+20
        DCD    CY_APP_CM7_LEN_LB         ; addrmarker+24
        DCD    CY_APP_CM7_SIG_ADDR_LB    ; addrmarker+28
        DCD    CY_APP_CM7_START_ADDR_LB  ; addrmarker+32
        DCD    CY_APP_CM7_END_ADDR_LB    ; addrmarker+36
        DCD    CY_APP_CM7_LEN_UB         ; addrmarker+40
        DCD    CY_APP_CM7_SIG_ADDR_UB    ; addrmarker+44
        DCD    CY_APP_CM7_START_ADDR_UB  ; addrmarker+48
        DCD    CY_APP_CM7_END_ADDR_UB    ; addrmarker+52
.endo addrmarker

;************************************************************************
;* Configure Flash as Dual Bank
;************************************************************************
.align 4
; Flash copy for the dual bank configuration function
; This function does the dual bank configuration based on r6 register, invalidates the cache and jumps to the reset handler of the CM0+ application.
_flashbankswitch:

; Load the address for FLASHC_FLASH_CTL
        LDR  r4, ramdatamarker

; Set FLASHC_FLASH_CTL.MAIN_BANK_MODE for dual bank mode
        LDR  r0, [r4]
        MOVS r1, #1
        LSLS r1, r1, #12
        ORRS r0, r1
        STR  r0, [r4]
        LDR  r0, [r4]

;************************************************************************
;* Configure Flash Map
;************************************************************************
; Set '1' for bit corresponding to FLASHC_FLASH_CTL.MAIN_MAP in register R1
        MOVS r1, #1
        ADDS r1, #255

; Check if register R6 is set
        CMP  r6, #1
        BNE  MapA

; Map B is valid, set the bit corresponding to FLASHC_FLASH_CTL.MAIN_MAP
MapB:
        ORRS r0, r1
        B    common

; Map A is valid, clear the bit corresponding to FLASHC_FLASH_CTL.MAIN_MAP
MapA:
        BICS r0, r1

common:

; configure FLASHC_FLASH_CTL.MAIN_MAP
        STR  r0, [r4]

; read back FLASHC_FLASH_CTL
        LDR  r0, [r4]

;************************************************************************
;* Memory Barrier Operations and Cache Invalidation
;************************************************************************
; instruction barrier operation
        ISB  SY

; invalidate cache and buffers
        LDR  r0, [r4,8]
        MOVS r1, #1
        ORRS r0, r1
        STR  r0, [r4,8]

; wait till cache and buffers are invalidated
cache_clearloop:
        LDR  r0, [r4,8]
        LSLS r0, r0, #31
        BMI  cache_clearloop

;************************************************************************
;* Branch to CM0+ Application
;************************************************************************
; jump to the _startcontd function which is the reset handler of the CM0+ application placed at 0x10000000 based on CySAF
        LDR  r5, ramdatamarker+4         ; Load the starting address of CySAF
        LDR  r1, [r5,16]
        ADDS r1, #16
        ADDS r5, r1
        LDR  r7, [r5,4]
        LDR  r6, [r5]                    ; Load the starting address of CM0P application's stack
        MSR  msp, r6                     ; Set the msp address
        BX   r7
        
        .endf _flashbankswitch

;************************************************************************
;* Ramdatamarker Macros
;************************************************************************
; Markers used by the RAM function
.align 4
ramdatamarker:
        DCD    FLASHC_FLASH_CTL          ; ramdatamarker
        DCD    CY_APP_START_ADDR_LB      ; ramdatamarker+4
.endo ramdatamarker

_flashbankswitchend

;************************************************************************
;* File end
;************************************************************************

        END

