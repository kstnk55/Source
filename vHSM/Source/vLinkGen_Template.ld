/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * CAUTION - DO NOT EDIT
 * -------------------------------------------------------------------------------------------------------------------
 * Never manually edit the following memory definitions in this file. Only change them in the vLinkGen configuration
 * (/MICROSAR/vLinkGen/vLinkGenMemLayout/vLinkGenMemoryRegion/vLinkGenMemoryRegionBlock) and regenerate the files.
 *********************************************************************************************************************/
MEMORY
{
  cy_app_header : ORIGIN = 0x10000000 , LENGTH = 0x00000100 /* 256 Byte */
  CoreExceptions_FirstExecInst : ORIGIN = 0x10000100 , LENGTH = 0x00000100 /* 256 Byte */
  StartupCode_FirstExecInst : ORIGIN = 0x10000200 , LENGTH = 0x00000400 /* 1024 Byte */
  FLASH : ORIGIN = 0x10000600 , LENGTH = 0x0008F600 /* 574 KiB */
  veHSM_Signature : ORIGIN = 0x1008FC00 , LENGTH = 0x000003E0 /* 992 Byte */
  M0_Soft_Version : ORIGIN = 0x1008FFE0 , LENGTH = 0x00000020 /* 32 Byte */
  RAM : ORIGIN = 0x28000800 , LENGTH = 0x000076A8 /* 30 KiB */
  LifeCycleStage : ORIGIN = 0x28007EA8 , LENGTH = 0x00000138 /* 312 Byte */
  Variables_Shared : ORIGIN = 0x28007FE0 , LENGTH = 0x00000010 /* 16 Byte */
  SRAM0_Retention : ORIGIN = 0x28007FF0 , LENGTH = 0x00000010 /* 16 Byte */
  SECURE_DTC : ORIGIN = 0x28013FE4 , LENGTH = 0x00000004 /* 4 Byte */
  Mem_Local : ORIGIN = 0x28014000 , LENGTH = 0x00000800 /* 2 KiB */
  StartupStack_Shared : ORIGIN = 0x28014800 , LENGTH = 0x00001000 /* 4 KiB */
  Data_Extension : ORIGIN = 0x28015800 , LENGTH = 0x00002800 /* 10 KiB */
}

SECTIONS
{
  .OS_STACKS_CORE0_VAR_NOINIT :
  {
    *(.OS_STACK_OSCORE0_ERROR_VAR_NOINIT)
    *(.OS_STACK_OSCORE0_INIT_VAR_NOINIT)
    *(.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT)
    *(.OS_STACK_OSCORE0_SHUTDOWN_VAR_NOINIT)
    *(.OS_STACK_OSCORE0_STARTUP_VAR_NOINIT)
  } > RAM
  _OS_STACKS_CORE0_VAR_NOINIT_START = ADDR(.OS_STACKS_CORE0_VAR_NOINIT);
  _OS_STACKS_CORE0_VAR_NOINIT_END = ENDADDR(.OS_STACKS_CORE0_VAR_NOINIT) - 1;
  _OS_STACKS_CORE0_VAR_NOINIT_LIMIT = ENDADDR(.OS_STACKS_CORE0_VAR_NOINIT);

  _OS_STACKS_CORE0_VAR_ALL_START = _OS_STACKS_CORE0_VAR_NOINIT_START;
  _OS_STACKS_CORE0_VAR_ALL_END = _OS_STACKS_CORE0_VAR_NOINIT_END;
  _OS_STACKS_CORE0_VAR_ALL_LIMIT = _OS_STACKS_CORE0_VAR_NOINIT_LIMIT;

  .intvec ALIGN(256) :
  {
    *(.brsExcVect)
    *(.brsExcVectConst)
  } > CoreExceptions_FirstExecInst
  _intvec_START = ADDR(.intvec);
  _intvec_END = ENDADDR(.intvec) - 1;
  _intvec_LIMIT = ENDADDR(.intvec);

  _Brs_ExcVect_ALL_START = _intvec_START;
  _Brs_ExcVect_ALL_END = _intvec_END;
  _Brs_ExcVect_ALL_LIMIT = _intvec_LIMIT;

  .Brs_Startup_Code :
  {
    *(.brsStartup)
  } > StartupCode_FirstExecInst
  _Brs_Startup_Code_START = ADDR(.Brs_Startup_Code);
  _Brs_Startup_Code_END = ENDADDR(.Brs_Startup_Code) - 1;
  _Brs_Startup_Code_LIMIT = ENDADDR(.Brs_Startup_Code);

  .BrsMain_Startup_Code :
  {
    *(.brsMainStartup)
  } > StartupCode_FirstExecInst
  _BrsMain_Startup_Code_START = ADDR(.BrsMain_Startup_Code);
  _BrsMain_Startup_Code_END = ENDADDR(.BrsMain_Startup_Code) - 1;
  _BrsMain_Startup_Code_LIMIT = ENDADDR(.BrsMain_Startup_Code);

  _Brs_Startup_Code_ALL_START = _Brs_Startup_Code_START;
  _Brs_Startup_Code_ALL_END = _BrsMain_Startup_Code_END;
  _Brs_Startup_Code_ALL_LIMIT = _BrsMain_Startup_Code_LIMIT;

  .Brs_Shared_Const :
  {
    *(.brsSharedConst)
  } > FLASH
  _Brs_Shared_Const_START = ADDR(.Brs_Shared_Const);
  _Brs_Shared_Const_END = ENDADDR(.Brs_Shared_Const) - 1;
  _Brs_Shared_Const_LIMIT = ENDADDR(.Brs_Shared_Const);

  _Brs_Shared_Const_ALL_START = _Brs_Shared_Const_START;
  _Brs_Shared_Const_ALL_END = _Brs_Shared_Const_END;
  _Brs_Shared_Const_ALL_LIMIT = _Brs_Shared_Const_LIMIT;

  .Brs_Shared_Var :
  {
    *(.brsSharedVar)
  } > Variables_Shared
  _Brs_Shared_Var_START = ADDR(.Brs_Shared_Var);
  _Brs_Shared_Var_END = ENDADDR(.Brs_Shared_Var) - 1;
  _Brs_Shared_Var_LIMIT = ENDADDR(.Brs_Shared_Var);

  _Brs_Shared_Var_ALL_START = _Brs_Shared_Var_START;
  _Brs_Shared_Var_ALL_END = _Brs_Shared_Var_END;
  _Brs_Shared_Var_ALL_LIMIT = _Brs_Shared_Var_LIMIT;

  .cy_app_header :
  {
    *(.cy_app_header)
  } > cy_app_header
  _cy_app_header_START = ADDR(.cy_app_header);
  _cy_app_header_END = ENDADDR(.cy_app_header) - 1;
  _cy_app_header_LIMIT = ENDADDR(.cy_app_header);

  _cy_app_header_ALL_START = _cy_app_header_START;
  _cy_app_header_ALL_END = _cy_app_header_END;
  _cy_app_header_ALL_LIMIT = _cy_app_header_LIMIT;

  .cy_app_signature :
  {
    *(.cy_app_signature)
  } > veHSM_Signature
  _cy_app_signature_START = ADDR(.cy_app_signature);
  _cy_app_signature_END = ENDADDR(.cy_app_signature) - 1;
  _cy_app_signature_LIMIT = ENDADDR(.cy_app_signature);

  _cy_app_signature_ALL_START = _cy_app_signature_START;
  _cy_app_signature_ALL_END = _cy_app_signature_END;
  _cy_app_signature_ALL_LIMIT = _cy_app_signature_LIMIT;

  _Ipc0Isr = 0x49;
  _Ipc1Isr = 0x2A5;

  .interfunc :
  {
  } > FLASH
  _interfunc_START = ADDR(.interfunc);
  _interfunc_END = ENDADDR(.interfunc) - 1;
  _interfunc_LIMIT = ENDADDR(.interfunc);

  _interfunc_ALL_START = _interfunc_START;
  _interfunc_ALL_END = _interfunc_END;
  _interfunc_ALL_LIMIT = _interfunc_LIMIT;

  .intvec_ram ALIGN(256) :
  {
  } > Mem_Local
  _intvec_ram_START = ADDR(.intvec_ram);
  _intvec_ram_END = ENDADDR(.intvec_ram) - 1;
  _intvec_ram_LIMIT = ENDADDR(.intvec_ram);

  _intvec_ram_ALL_START = _intvec_ram_START;
  _intvec_ram_ALL_END = _intvec_ram_END;
  _intvec_ram_ALL_LIMIT = _intvec_ram_LIMIT;

  .LifeCycleStage :
  {
    *(.LifeCycleStage)
  } > LifeCycleStage
  _LifeCycleStage_START = ADDR(.LifeCycleStage);
  _LifeCycleStage_END = ENDADDR(.LifeCycleStage) - 1;
  _LifeCycleStage_LIMIT = ENDADDR(.LifeCycleStage);

  _LifeCycleStage_ALL_START = _LifeCycleStage_START;
  _LifeCycleStage_ALL_END = _LifeCycleStage_END;
  _LifeCycleStage_ALL_LIMIT = _LifeCycleStage_LIMIT;

  .m0_soft_version :
  {
    *(.m0_soft_version)
  } > M0_Soft_Version
  _m0_soft_version_START = ADDR(.m0_soft_version);
  _m0_soft_version_END = ENDADDR(.m0_soft_version) - 1;
  _m0_soft_version_LIMIT = ENDADDR(.m0_soft_version);

  _m0_soft_version_ALL_START = _m0_soft_version_START;
  _m0_soft_version_ALL_END = _m0_soft_version_END;
  _m0_soft_version_ALL_LIMIT = _m0_soft_version_LIMIT;

  .MSR_CODE :
  {
    *(.COREISO_CODE)
    *(.MSR_CODE)
  } > FLASH
  _MSR_CODE_START = ADDR(.MSR_CODE);
  _MSR_CODE_END = ENDADDR(.MSR_CODE) - 1;
  _MSR_CODE_LIMIT = ENDADDR(.MSR_CODE);

  _MSR_CODE_ALL_START = _MSR_CODE_START;
  _MSR_CODE_ALL_END = _MSR_CODE_END;
  _MSR_CODE_ALL_LIMIT = _MSR_CODE_LIMIT;

  .MSR_CONST :
  {
    *(.COREISO_CONST)
    *(.MSR_CONST)
    *(.MSR_CONST_FAST)
  } > FLASH
  _MSR_CONST_START = ADDR(.MSR_CONST);
  _MSR_CONST_END = ENDADDR(.MSR_CONST) - 1;
  _MSR_CONST_LIMIT = ENDADDR(.MSR_CONST);

  _MSR_CONST_ALL_START = _MSR_CONST_START;
  _MSR_CONST_ALL_END = _MSR_CONST_END;
  _MSR_CONST_ALL_LIMIT = _MSR_CONST_LIMIT;

  .MSR_PBCFG_CONST :
  {
    *(.MSR_PBCFG_CONST)
    *(.MSR_PBCFG_CONST_FAST)
  } > FLASH
  _MSR_PBCFG_CONST_START = ADDR(.MSR_PBCFG_CONST);
  _MSR_PBCFG_CONST_END = ENDADDR(.MSR_PBCFG_CONST) - 1;
  _MSR_PBCFG_CONST_LIMIT = ENDADDR(.MSR_PBCFG_CONST);

  _MSR_PBCFG_CONST_ALL_START = _MSR_PBCFG_CONST_START;
  _MSR_PBCFG_CONST_ALL_END = _MSR_PBCFG_CONST_END;
  _MSR_PBCFG_CONST_ALL_LIMIT = _MSR_PBCFG_CONST_LIMIT;

  .MSR_PBCFG_VAR_CLEARED ALIGN(4) :
  {
    *(.MSR_PBCFG_VAR_CLEARED)
    *(.MSR_PBCFG_VAR_FAST_CLEARED)
    . = ALIGN(4);
  } > Mem_Local
  _MSR_PBCFG_VAR_CLEARED_START = ADDR(.MSR_PBCFG_VAR_CLEARED);
  _MSR_PBCFG_VAR_CLEARED_END = ENDADDR(.MSR_PBCFG_VAR_CLEARED) - 1;
  _MSR_PBCFG_VAR_CLEARED_LIMIT = ENDADDR(.MSR_PBCFG_VAR_CLEARED);

  .MSR_PBCFG_VAR_INIT_ROM ROM_NOCOPY(.MSR_PBCFG_VAR_INIT) :> FLASH
  _MSR_PBCFG_VAR_INIT_ROM_START = ADDR(.MSR_PBCFG_VAR_INIT_ROM);
  _MSR_PBCFG_VAR_INIT_ROM_LIMIT = ENDADDR(.MSR_PBCFG_VAR_INIT_ROM);

  .MSR_PBCFG_VAR_INIT ALIGN(4) :
  {
    *(.MSR_PBCFG_VAR)
    *(.MSR_PBCFG_VAR_FAST)
    . = ALIGN(4);
  } > Mem_Local
  _MSR_PBCFG_VAR_INIT_START = ADDR(.MSR_PBCFG_VAR_INIT);
  _MSR_PBCFG_VAR_INIT_END = ENDADDR(.MSR_PBCFG_VAR_INIT) - 1;
  _MSR_PBCFG_VAR_INIT_LIMIT = ENDADDR(.MSR_PBCFG_VAR_INIT);

  .MSR_PBCFG_VAR_NO_INIT :
  {
    *(.MSR_PBCFG_VAR_FAST_NO_INIT)
    *(.MSR_PBCFG_VAR_NO_INIT)
  } > Mem_Local
  _MSR_PBCFG_VAR_NO_INIT_START = ADDR(.MSR_PBCFG_VAR_NO_INIT);
  _MSR_PBCFG_VAR_NO_INIT_END = ENDADDR(.MSR_PBCFG_VAR_NO_INIT) - 1;
  _MSR_PBCFG_VAR_NO_INIT_LIMIT = ENDADDR(.MSR_PBCFG_VAR_NO_INIT);

  _MSR_PBCFG_VAR_ALL_START = _MSR_PBCFG_VAR_CLEARED_START;
  _MSR_PBCFG_VAR_ALL_END = _MSR_PBCFG_VAR_NO_INIT_END;
  _MSR_PBCFG_VAR_ALL_LIMIT = _MSR_PBCFG_VAR_NO_INIT_LIMIT;

  .MSR_VAR_CLEARED ALIGN(4) :
  {
    *(.MSR_VAR_CLEARED)
    *(.MSR_VAR_FAST_CLEARED)
    . = ALIGN(4);
  } > Mem_Local
  _MSR_VAR_CLEARED_START = ADDR(.MSR_VAR_CLEARED);
  _MSR_VAR_CLEARED_END = ENDADDR(.MSR_VAR_CLEARED) - 1;
  _MSR_VAR_CLEARED_LIMIT = ENDADDR(.MSR_VAR_CLEARED);

  .MSR_VAR_INIT_ROM ROM_NOCOPY(.MSR_VAR_INIT) :> FLASH
  _MSR_VAR_INIT_ROM_START = ADDR(.MSR_VAR_INIT_ROM);
  _MSR_VAR_INIT_ROM_LIMIT = ENDADDR(.MSR_VAR_INIT_ROM);

  .MSR_VAR_INIT ALIGN(4) :
  {
    *(.MSR_VAR_FAST_INIT)
    *(.MSR_VAR_INIT)
    . = ALIGN(4);
  } > Mem_Local
  _MSR_VAR_INIT_START = ADDR(.MSR_VAR_INIT);
  _MSR_VAR_INIT_END = ENDADDR(.MSR_VAR_INIT) - 1;
  _MSR_VAR_INIT_LIMIT = ENDADDR(.MSR_VAR_INIT);

  .MSR_VAR_NO_INIT :
  {
    *(.MSR_VAR_FAST_NO_INIT)
    *(.MSR_VAR_NO_INIT)
  } > Mem_Local
  _MSR_VAR_NO_INIT_START = ADDR(.MSR_VAR_NO_INIT);
  _MSR_VAR_NO_INIT_END = ENDADDR(.MSR_VAR_NO_INIT) - 1;
  _MSR_VAR_NO_INIT_LIMIT = ENDADDR(.MSR_VAR_NO_INIT);

  _MSR_VAR_ALL_START = _MSR_VAR_CLEARED_START;
  _MSR_VAR_ALL_END = _MSR_VAR_NO_INIT_END;
  _MSR_VAR_ALL_LIMIT = _MSR_VAR_NO_INIT_LIMIT;

  .MSR_VAR_SAVED_ZONE_INIT_ROM ROM_NOCOPY(.MSR_VAR_SAVED_ZONE_INIT) :> FLASH
  _MSR_VAR_SAVED_ZONE_INIT_ROM_START = ADDR(.MSR_VAR_SAVED_ZONE_INIT_ROM);
  _MSR_VAR_SAVED_ZONE_INIT_ROM_LIMIT = ENDADDR(.MSR_VAR_SAVED_ZONE_INIT_ROM);

  .MSR_VAR_SAVED_ZONE_INIT ALIGN(4) :
  {
    *(.MSR_VAR_SAVED_ZONE_FAST_INIT)
    *(.MSR_VAR_SAVED_ZONE_INIT)
    . = ALIGN(4);
  } > Mem_Local
  _MSR_VAR_SAVED_ZONE_INIT_START = ADDR(.MSR_VAR_SAVED_ZONE_INIT);
  _MSR_VAR_SAVED_ZONE_INIT_END = ENDADDR(.MSR_VAR_SAVED_ZONE_INIT) - 1;
  _MSR_VAR_SAVED_ZONE_INIT_LIMIT = ENDADDR(.MSR_VAR_SAVED_ZONE_INIT);

  .MSR_VAR_SAVED_ZONE_NO_INIT :
  {
    *(.MSR_VAR_SAVED_ZONE_FAST_NO_INIT)
    *(.MSR_VAR_SAVED_ZONE_NO_INIT)
  } > Mem_Local
  _MSR_VAR_SAVED_ZONE_NO_INIT_START = ADDR(.MSR_VAR_SAVED_ZONE_NO_INIT);
  _MSR_VAR_SAVED_ZONE_NO_INIT_END = ENDADDR(.MSR_VAR_SAVED_ZONE_NO_INIT) - 1;
  _MSR_VAR_SAVED_ZONE_NO_INIT_LIMIT = ENDADDR(.MSR_VAR_SAVED_ZONE_NO_INIT);

  _MSR_VAR_SAVED_ZONE_ALL_START = _MSR_VAR_SAVED_ZONE_INIT_START;
  _MSR_VAR_SAVED_ZONE_ALL_END = _MSR_VAR_SAVED_ZONE_NO_INIT_END;
  _MSR_VAR_SAVED_ZONE_ALL_LIMIT = _MSR_VAR_SAVED_ZONE_NO_INIT_LIMIT;

  .OS_CODE :
  {
    *(.OS_CODE)
    *(.OS_OS_COREINITHOOK_CODE)
  } > FLASH
  _OS_CODE_START = ADDR(.OS_CODE);
  _OS_CODE_END = ENDADDR(.OS_CODE) - 1;
  _OS_CODE_LIMIT = ENDADDR(.OS_CODE);

  _OS_CODE_ALL_START = _OS_CODE_START;
  _OS_CODE_ALL_END = _OS_CODE_END;
  _OS_CODE_ALL_LIMIT = _OS_CODE_LIMIT;

  .OS_CONST :
  {
    *(.OS_CONST)
    *(.OS_CORE0_CONST)
    *(.OS_SystemApplication_OsCore0_CONST)
  } > FLASH
  _OS_CONST_START = ADDR(.OS_CONST);
  _OS_CONST_END = ENDADDR(.OS_CONST) - 1;
  _OS_CONST_LIMIT = ENDADDR(.OS_CONST);

  _OS_CONST_ALL_START = _OS_CONST_START;
  _OS_CONST_ALL_END = _OS_CONST_END;
  _OS_CONST_ALL_LIMIT = _OS_CONST_LIMIT;

  .OS_DATA_CORE0_VAR_INIT_ROM ROM_NOCOPY(.OS_DATA_CORE0_VAR_INIT) :> FLASH
  _OS_DATA_CORE0_VAR_INIT_ROM_START = ADDR(.OS_DATA_CORE0_VAR_INIT_ROM);
  _OS_DATA_CORE0_VAR_INIT_ROM_LIMIT = ENDADDR(.OS_DATA_CORE0_VAR_INIT_ROM);

  .OS_DATA_CORE0_VAR_INIT ALIGN(4) :
  {
    *(.OS_CORE0_VAR)
    *(.OS_CORE0_VAR_NOCACHE)
    *(.OS_SystemApplication_OsCore0_VAR)
    *(.OS_SystemApplication_OsCore0_VAR_NOCACHE)
    *(.OS_SystemApplication_OsCore0_VAR_SAVED_ZONE)
    . = ALIGN(4);
  } > Mem_Local
  _OS_DATA_CORE0_VAR_INIT_START = ADDR(.OS_DATA_CORE0_VAR_INIT);
  _OS_DATA_CORE0_VAR_INIT_END = ENDADDR(.OS_DATA_CORE0_VAR_INIT) - 1;
  _OS_DATA_CORE0_VAR_INIT_LIMIT = ENDADDR(.OS_DATA_CORE0_VAR_INIT);

  .OS_DATA_CORE0_VAR_NOINIT :
  {
    *(.OS_CORE0_VAR_NOCACHE_NOINIT)
    *(.OS_CORE0_VAR_NOINIT)
    *(.OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT)
    *(.OS_SystemApplication_OsCore0_VAR_NOINIT)
    *(.OS_SystemApplication_OsCore0_VAR_SAVED_ZONE_NOINIT)
  } > Mem_Local
  _OS_DATA_CORE0_VAR_NOINIT_START = ADDR(.OS_DATA_CORE0_VAR_NOINIT);
  _OS_DATA_CORE0_VAR_NOINIT_END = ENDADDR(.OS_DATA_CORE0_VAR_NOINIT) - 1;
  _OS_DATA_CORE0_VAR_NOINIT_LIMIT = ENDADDR(.OS_DATA_CORE0_VAR_NOINIT);

  .OS_DATA_CORE0_VAR_ZERO_INIT ALIGN(4) :
  {
    *(.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT)
    *(.OS_SystemApplication_OsCore0_VAR_ZERO_INIT)
    . = ALIGN(4);
  } > Mem_Local
  _OS_DATA_CORE0_VAR_ZERO_INIT_START = ADDR(.OS_DATA_CORE0_VAR_ZERO_INIT);
  _OS_DATA_CORE0_VAR_ZERO_INIT_END = ENDADDR(.OS_DATA_CORE0_VAR_ZERO_INIT) - 1;
  _OS_DATA_CORE0_VAR_ZERO_INIT_LIMIT = ENDADDR(.OS_DATA_CORE0_VAR_ZERO_INIT);

  .OS_DATA_CORE0_VAR_ZERO_INIT_bss ALIGN(4) :
  {
    *(.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss)
    *(.OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss)
    . = ALIGN(4);
  } > Mem_Local
  _OS_DATA_CORE0_VAR_ZERO_INIT_bss_START = ADDR(.OS_DATA_CORE0_VAR_ZERO_INIT_bss);
  _OS_DATA_CORE0_VAR_ZERO_INIT_bss_END = ENDADDR(.OS_DATA_CORE0_VAR_ZERO_INIT_bss) - 1;
  _OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT = ENDADDR(.OS_DATA_CORE0_VAR_ZERO_INIT_bss);

  _OS_DATA_CORE0_VAR_ALL_START = _OS_DATA_CORE0_VAR_INIT_START;
  _OS_DATA_CORE0_VAR_ALL_END = _OS_DATA_CORE0_VAR_ZERO_INIT_bss_END;
  _OS_DATA_CORE0_VAR_ALL_LIMIT = _OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT;

  .OS_DATA_SHARED_VAR_INIT_ROM ROM_NOCOPY(.OS_DATA_SHARED_VAR_INIT) :> FLASH
  _OS_DATA_SHARED_VAR_INIT_ROM_START = ADDR(.OS_DATA_SHARED_VAR_INIT_ROM);
  _OS_DATA_SHARED_VAR_INIT_ROM_LIMIT = ENDADDR(.OS_DATA_SHARED_VAR_INIT_ROM);

  .OS_DATA_SHARED_VAR_INIT ALIGN(4) :
  {
    *(.OS_VAR_NOCACHE)
    . = ALIGN(4);
  } > Mem_Local
  _OS_DATA_SHARED_VAR_INIT_START = ADDR(.OS_DATA_SHARED_VAR_INIT);
  _OS_DATA_SHARED_VAR_INIT_END = ENDADDR(.OS_DATA_SHARED_VAR_INIT) - 1;
  _OS_DATA_SHARED_VAR_INIT_LIMIT = ENDADDR(.OS_DATA_SHARED_VAR_INIT);

  .OS_DATA_SHARED_VAR_NOINIT :
  {
    *(.OS_BARRIER_CORE0_VAR_NOCACHE_NOINIT)
    *(.OS_CORESTATUS_CORE0_VAR_NOCACHE_NOINIT)
    *(.OS_PUBLIC_CORE0_VAR_NOINIT)
    *(.OS_VAR_NOCACHE_NOINIT)
  } > Mem_Local
  _OS_DATA_SHARED_VAR_NOINIT_START = ADDR(.OS_DATA_SHARED_VAR_NOINIT);
  _OS_DATA_SHARED_VAR_NOINIT_END = ENDADDR(.OS_DATA_SHARED_VAR_NOINIT) - 1;
  _OS_DATA_SHARED_VAR_NOINIT_LIMIT = ENDADDR(.OS_DATA_SHARED_VAR_NOINIT);

  _OS_DATA_SHARED_VAR_ALL_START = _OS_DATA_SHARED_VAR_INIT_START;
  _OS_DATA_SHARED_VAR_ALL_END = _OS_DATA_SHARED_VAR_NOINIT_END;
  _OS_DATA_SHARED_VAR_ALL_LIMIT = _OS_DATA_SHARED_VAR_NOINIT_LIMIT;

  .OS_EXCVEC_CORE0_CODE :
  {
    *(.OS_EXCVEC_CORE0_CODE)
  } > FLASH
  _OS_EXCVEC_CORE0_CODE_START = ADDR(.OS_EXCVEC_CORE0_CODE);
  _OS_EXCVEC_CORE0_CODE_END = ENDADDR(.OS_EXCVEC_CORE0_CODE) - 1;
  _OS_EXCVEC_CORE0_CODE_LIMIT = ENDADDR(.OS_EXCVEC_CORE0_CODE);

  _OS_EXCVEC_CORE0_CODE_ALL_START = _OS_EXCVEC_CORE0_CODE_START;
  _OS_EXCVEC_CORE0_CODE_ALL_END = _OS_EXCVEC_CORE0_CODE_END;
  _OS_EXCVEC_CORE0_CODE_ALL_LIMIT = _OS_EXCVEC_CORE0_CODE_LIMIT;

  .OS_EXCVEC_CORE0_CONST :
  {
    *(.OS_EXCVEC_CORE0_CONST)
  } > FLASH
  _OS_EXCVEC_CORE0_CONST_START = ADDR(.OS_EXCVEC_CORE0_CONST);
  _OS_EXCVEC_CORE0_CONST_END = ENDADDR(.OS_EXCVEC_CORE0_CONST) - 1;
  _OS_EXCVEC_CORE0_CONST_LIMIT = ENDADDR(.OS_EXCVEC_CORE0_CONST);

  _OS_EXCVEC_CORE0_CONST_ALL_START = _OS_EXCVEC_CORE0_CONST_START;
  _OS_EXCVEC_CORE0_CONST_ALL_END = _OS_EXCVEC_CORE0_CONST_END;
  _OS_EXCVEC_CORE0_CONST_ALL_LIMIT = _OS_EXCVEC_CORE0_CONST_LIMIT;

  .OS_GLOBALSHARED_CONST :
  {
    *(.OS_GLOBALSHARED_CONST)
  } > FLASH
  _OS_GLOBALSHARED_CONST_START = ADDR(.OS_GLOBALSHARED_CONST);
  _OS_GLOBALSHARED_CONST_END = ENDADDR(.OS_GLOBALSHARED_CONST) - 1;
  _OS_GLOBALSHARED_CONST_LIMIT = ENDADDR(.OS_GLOBALSHARED_CONST);

  _OS_GLOBALSHARED_CONST_ALL_START = _OS_GLOBALSHARED_CONST_START;
  _OS_GLOBALSHARED_CONST_ALL_END = _OS_GLOBALSHARED_CONST_END;
  _OS_GLOBALSHARED_CONST_ALL_LIMIT = _OS_GLOBALSHARED_CONST_LIMIT;

  .OS_GLOBALSHARED_VAR_INIT_ROM ROM_NOCOPY(.OS_GLOBALSHARED_VAR_INIT) :> FLASH
  _OS_GLOBALSHARED_VAR_INIT_ROM_START = ADDR(.OS_GLOBALSHARED_VAR_INIT_ROM);
  _OS_GLOBALSHARED_VAR_INIT_ROM_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_INIT_ROM);

  .OS_GLOBALSHARED_VAR_INIT ALIGN(4) :
  {
    *(.OS_GLOBALSHARED_VAR)
    *(.OS_GLOBALSHARED_VAR_NOCACHE)
    . = ALIGN(4);
  } > Mem_Local
  _OS_GLOBALSHARED_VAR_INIT_START = ADDR(.OS_GLOBALSHARED_VAR_INIT);
  _OS_GLOBALSHARED_VAR_INIT_END = ENDADDR(.OS_GLOBALSHARED_VAR_INIT) - 1;
  _OS_GLOBALSHARED_VAR_INIT_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_INIT);

  .OS_GLOBALSHARED_VAR_NOINIT :
  {
    *(.OS_GLOBALSHARED_VAR_NOCACHE_NOINIT)
    *(.OS_GLOBALSHARED_VAR_NOINIT)
  } > Mem_Local
  _OS_GLOBALSHARED_VAR_NOINIT_START = ADDR(.OS_GLOBALSHARED_VAR_NOINIT);
  _OS_GLOBALSHARED_VAR_NOINIT_END = ENDADDR(.OS_GLOBALSHARED_VAR_NOINIT) - 1;
  _OS_GLOBALSHARED_VAR_NOINIT_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_NOINIT);

  .OS_GLOBALSHARED_VAR_ZERO_INIT ALIGN(4) :
  {
    *(.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT)
    *(.OS_GLOBALSHARED_VAR_ZERO_INIT)
    . = ALIGN(4);
  } > Mem_Local
  _OS_GLOBALSHARED_VAR_ZERO_INIT_START = ADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT);
  _OS_GLOBALSHARED_VAR_ZERO_INIT_END = ENDADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT) - 1;
  _OS_GLOBALSHARED_VAR_ZERO_INIT_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT);

  .OS_GLOBALSHARED_VAR_ZERO_INIT_bss ALIGN(4) :
  {
    *(.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss)
    *(.OS_GLOBALSHARED_VAR_ZERO_INIT_bss)
    . = ALIGN(4);
  } > Mem_Local
  _OS_GLOBALSHARED_VAR_ZERO_INIT_bss_START = ADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT_bss);
  _OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END = ENDADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT_bss) - 1;
  _OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_ZERO_INIT_bss);

  _OS_GLOBALSHARED_VAR_ALL_START = _OS_GLOBALSHARED_VAR_INIT_START;
  _OS_GLOBALSHARED_VAR_ALL_END = _OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END;
  _OS_GLOBALSHARED_VAR_ALL_LIMIT = _OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT;

  .OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM ROM_NOCOPY(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT) :> FLASH
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_START = ADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM);
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM);

  .OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT ALIGN(4) :
  {
    *(.OS_GLOBALSHARED_VAR_SAVED_ZONE)
    . = ALIGN(4);
  } > RAM
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_START = ADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT);
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_END = ENDADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT) - 1;
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT);

  .OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT :
  {
    *(.OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT)
  } > RAM
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_START = ADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT);
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_END = ENDADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT) - 1;
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_LIMIT = ENDADDR(.OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT);

  _OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_START = _OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_START;
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_END = _OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_END;
  _OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_LIMIT = _OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_LIMIT;

  .OS_INTVEC_CODE ALIGN(256) :
  {
    . = ALIGN(256);
    *(.OS_INTVEC_CODE)
  } > FLASH
  _OS_INTVEC_CODE_START = ADDR(.OS_INTVEC_CODE);
  _OS_INTVEC_CODE_END = ENDADDR(.OS_INTVEC_CODE) - 1;
  _OS_INTVEC_CODE_LIMIT = ENDADDR(.OS_INTVEC_CODE);

  _OS_INTVEC_CODE_ALL_START = _OS_INTVEC_CODE_START;
  _OS_INTVEC_CODE_ALL_END = _OS_INTVEC_CODE_END;
  _OS_INTVEC_CODE_ALL_LIMIT = _OS_INTVEC_CODE_LIMIT;

  .OS_INTVEC_CONST ALIGN(256) :
  {
    *(.OS_INTVEC_CONST)
  } > FLASH
  _OS_INTVEC_CONST_START = ADDR(.OS_INTVEC_CONST);
  _OS_INTVEC_CONST_END = ENDADDR(.OS_INTVEC_CONST) - 1;
  _OS_INTVEC_CONST_LIMIT = ENDADDR(.OS_INTVEC_CONST);

  _OS_INTVEC_CONST_ALL_START = _OS_INTVEC_CONST_START;
  _OS_INTVEC_CONST_ALL_END = _OS_INTVEC_CONST_END;
  _OS_INTVEC_CONST_ALL_LIMIT = _OS_INTVEC_CONST_LIMIT;

  .OS_INTVEC_CORE0_CODE ALIGN(256) :
  {
    . = ALIGN(256);
    *(.OS_INTVEC_CORE0_CODE)
  } > FLASH
  _OS_INTVEC_CORE0_CODE_START = ADDR(.OS_INTVEC_CORE0_CODE);
  _OS_INTVEC_CORE0_CODE_END = ENDADDR(.OS_INTVEC_CORE0_CODE) - 1;
  _OS_INTVEC_CORE0_CODE_LIMIT = ENDADDR(.OS_INTVEC_CORE0_CODE);

  _OS_INTVEC_CORE0_CODE_ALL_START = _OS_INTVEC_CORE0_CODE_START;
  _OS_INTVEC_CORE0_CODE_ALL_END = _OS_INTVEC_CORE0_CODE_END;
  _OS_INTVEC_CORE0_CODE_ALL_LIMIT = _OS_INTVEC_CORE0_CODE_LIMIT;

  .OS_INTVEC_CORE0_CONST ALIGN(256) :
  {
    . = ALIGN(256);
    *(.OS_INTVEC_CORE0_CONST)
  } > FLASH
  _OS_INTVEC_CORE0_CONST_START = ADDR(.OS_INTVEC_CORE0_CONST);
  _OS_INTVEC_CORE0_CONST_END = ENDADDR(.OS_INTVEC_CORE0_CONST) - 1;
  _OS_INTVEC_CORE0_CONST_LIMIT = ENDADDR(.OS_INTVEC_CORE0_CONST);

  _OS_INTVEC_CORE0_CONST_ALL_START = _OS_INTVEC_CORE0_CONST_START;
  _OS_INTVEC_CORE0_CONST_ALL_END = _OS_INTVEC_CORE0_CONST_END;
  _OS_INTVEC_CORE0_CONST_ALL_LIMIT = _OS_INTVEC_CORE0_CONST_LIMIT;

  .OS_USER_CODE :
  {
    *(.OS_ERRORHOOK_CODE)
    *(.OS_PANICHOOK_CODE)
    *(.OS_SHUTDOWNHOOK_CODE)
    *(.OS_STARTUPHOOK_CODE)
  } > FLASH
  _OS_USER_CODE_START = ADDR(.OS_USER_CODE);
  _OS_USER_CODE_END = ENDADDR(.OS_USER_CODE) - 1;
  _OS_USER_CODE_LIMIT = ENDADDR(.OS_USER_CODE);

  _OS_USER_CODE_ALL_START = _OS_USER_CODE_START;
  _OS_USER_CODE_ALL_END = _OS_USER_CODE_END;
  _OS_USER_CODE_ALL_LIMIT = _OS_USER_CODE_LIMIT;

  .SECURE_DTC :
  {
    *(.SECURE_DTC)
  } > SECURE_DTC
  _SECURE_DTC_START = ADDR(.SECURE_DTC);
  _SECURE_DTC_END = ENDADDR(.SECURE_DTC) - 1;
  _SECURE_DTC_LIMIT = ENDADDR(.SECURE_DTC);

  _SECURE_DTC_ALL_START = _SECURE_DTC_START;
  _SECURE_DTC_ALL_END = _SECURE_DTC_END;
  _SECURE_DTC_ALL_LIMIT = _SECURE_DTC_LIMIT;

  .vLinkGenVarSectionGroup :
  {
    *(.SRAM0_Retention)
  } > SRAM0_Retention
  _vLinkGenVarSectionGroup_START = ADDR(.vLinkGenVarSectionGroup);
  _vLinkGenVarSectionGroup_END = ENDADDR(.vLinkGenVarSectionGroup) - 1;
  _vLinkGenVarSectionGroup_LIMIT = ENDADDR(.vLinkGenVarSectionGroup);

  _SRAM0_Retention_ALL_START = _vLinkGenVarSectionGroup_START;
  _SRAM0_Retention_ALL_END = _vLinkGenVarSectionGroup_END;
  _SRAM0_Retention_ALL_LIMIT = _vLinkGenVarSectionGroup_LIMIT;

  .STACK_C0 ALIGN(4) :
  {
    . += 4096;
    . = ALIGN(4);
  } > StartupStack_Shared
  _STACK_C0_START = ADDR(.STACK_C0);
  _STACK_C0_END = ENDADDR(.STACK_C0) - 1;
  _STACK_C0_LIMIT = ENDADDR(.STACK_C0);

  _STACK_C0_ALL_START = _STACK_C0_START;
  _STACK_C0_ALL_END = _STACK_C0_END;
  _STACK_C0_ALL_LIMIT = _STACK_C0_LIMIT;

  _start = Brs_ApplicationEntry +1;

  .vHsmRamCode_Code_ROM ROM_NOCOPY(.vHsmRamCode_Code) :> FLASH
  _vHsmRamCode_Code_ROM_START = ADDR(.vHsmRamCode_Code_ROM);
  _vHsmRamCode_Code_ROM_LIMIT = ENDADDR(.vHsmRamCode_Code_ROM);

  .vHsmRamCode_Code ALIGN(4) :
  {
    *(.vHsmRamCode)
    . = ALIGN(4);
  } > RAM
  _vHsmRamCode_Code_START = ADDR(.vHsmRamCode_Code);
  _vHsmRamCode_Code_END = ENDADDR(.vHsmRamCode_Code) - 1;
  _vHsmRamCode_Code_LIMIT = ENDADDR(.vHsmRamCode_Code);

  _vHsmRamCode_Code_ALL_START = _vHsmRamCode_Code_START;
  _vHsmRamCode_Code_ALL_END = _vHsmRamCode_Code_END;
  _vHsmRamCode_Code_ALL_LIMIT = _vHsmRamCode_Code_LIMIT;

  .vHsmRamCode_Const_ROM ROM_NOCOPY(.vHsmRamCode_Const) :> FLASH
  _vHsmRamCode_Const_ROM_START = ADDR(.vHsmRamCode_Const_ROM);
  _vHsmRamCode_Const_ROM_LIMIT = ENDADDR(.vHsmRamCode_Const_ROM);

  .vHsmRamCode_Const ALIGN(4) :
  {
    *(.vHsmRamCode)
    . = ALIGN(4);
  } > RAM
  _vHsmRamCode_Const_START = ADDR(.vHsmRamCode_Const);
  _vHsmRamCode_Const_END = ENDADDR(.vHsmRamCode_Const) - 1;
  _vHsmRamCode_Const_LIMIT = ENDADDR(.vHsmRamCode_Const);

  _vHsmRamCode_Const_ALL_START = _vHsmRamCode_Const_START;
  _vHsmRamCode_Const_ALL_END = _vHsmRamCode_Const_END;
  _vHsmRamCode_Const_ALL_LIMIT = _vHsmRamCode_Const_LIMIT;

  .vHsmResetInfo ALIGN(4) :
  {
    . = ALIGN(4);
    *(.vHsmResetInfo)
    . = ALIGN(4);
  } > RAM
  _vHsmResetInfo_START = ADDR(.vHsmResetInfo);
  _vHsmResetInfo_END = ENDADDR(.vHsmResetInfo) - 1;
  _vHsmResetInfo_LIMIT = ENDADDR(.vHsmResetInfo);

  _vHsmResetInfo_ALL_START = _vHsmResetInfo_START;
  _vHsmResetInfo_ALL_END = _vHsmResetInfo_END;
  _vHsmResetInfo_ALL_LIMIT = _vHsmResetInfo_LIMIT;

  VHSM_FIRMWARE_UPDATER = Brs_ApplicationEntry;

  .rodata :
  {
    *(.rodata)
  } > FLASH
  _rodata_START = ADDR(.rodata);
  _rodata_END = ENDADDR(.rodata) - 1;
  _rodata_LIMIT = ENDADDR(.rodata);

  .rosdata :
  {
    *(.ldata)
    *(.rosdata)
  } > FLASH
  _rosdata_START = ADDR(.rosdata);
  _rosdata_END = ENDADDR(.rosdata) - 1;
  _rosdata_LIMIT = ENDADDR(.rosdata);

  .rozdata :
  {
    *(.rozdata)
    *(.zrodata)
  } > FLASH
  _rozdata_START = ADDR(.rozdata);
  _rozdata_END = ENDADDR(.rozdata) - 1;
  _rozdata_LIMIT = ENDADDR(.rozdata);

  .sdata2 :
  {
    *(.sdata2)
  } > FLASH
  _sdata2_START = ADDR(.sdata2);
  _sdata2_END = ENDADDR(.sdata2) - 1;
  _sdata2_LIMIT = ENDADDR(.sdata2);

  .secinfo :
  {
    *(.secinfo)
  } > FLASH
  _secinfo_START = ADDR(.secinfo);
  _secinfo_END = ENDADDR(.secinfo) - 1;
  _secinfo_LIMIT = ENDADDR(.secinfo);

  .tdata :
  {
    *(.tdata)
  } > FLASH
  _tdata_START = ADDR(.tdata);
  _tdata_END = ENDADDR(.tdata) - 1;
  _tdata_LIMIT = ENDADDR(.tdata);

  .text :
  {
    *(.fixaddr)
    *(.fixtype)
    *(.picbase)
    *(.pidbase)
    *(.syscall)
    *(.text)
    *(.vletext)
  } > FLASH
  _text_START = ADDR(.text);
  _text_END = ENDADDR(.text) - 1;
  _text_LIMIT = ENDADDR(.text);

  _Const_Default_ALL_START = _rodata_START;
  _Const_Default_ALL_END = _text_END;
  _Const_Default_ALL_LIMIT = _text_LIMIT;

  .bss ALIGN(4) CLEAR :
  {
    *(.bss)
    *(COMMON)
    . = ALIGN(4);
  } > RAM
  _bss_START = ADDR(.bss);
  _bss_END = ENDADDR(.bss) - 1;
  _bss_LIMIT = ENDADDR(.bss);

  .sbss ALIGN(4) CLEAR :
  {
    *(.sbss)
    *(SMALLCOMMON)
    . = ALIGN(4);
  } > RAM
  _sbss_START = ADDR(.sbss);
  _sbss_END = ENDADDR(.sbss) - 1;
  _sbss_LIMIT = ENDADDR(.sbss);

  .sdabase :
  {
    *(.sdabase)
  } > RAM
  _sdabase_START = ADDR(.sdabase);
  _sdabase_END = ENDADDR(.sdabase) - 1;
  _sdabase_LIMIT = ENDADDR(.sdabase);

  .sdata_ROM ROM_NOCOPY(.sdata) :> FLASH
  _sdata_ROM_START = ADDR(.sdata_ROM);
  _sdata_ROM_LIMIT = ENDADDR(.sdata_ROM);

  .sdata ALIGN(4) :
  {
    *(.sdata)
    . = ALIGN(4);
  } > RAM
  _sdata_START = ADDR(.sdata);
  _sdata_END = ENDADDR(.sdata) - 1;
  _sdata_LIMIT = ENDADDR(.sdata);

  .zbss ALIGN(4) CLEAR :
  {
    *(.PPC.EMB.sbss0)
    *(.zbss)
    *(ZEROCOMMON)
    . = ALIGN(4);
  } > RAM
  _zbss_START = ADDR(.zbss);
  _zbss_END = ENDADDR(.zbss) - 1;
  _zbss_LIMIT = ENDADDR(.zbss);

  .zdata_ROM ROM_NOCOPY(.zdata) :> FLASH
  _zdata_ROM_START = ADDR(.zdata_ROM);
  _zdata_ROM_LIMIT = ENDADDR(.zdata_ROM);

  .zdata ALIGN(4) :
  {
    *(.PPC.EMB.sdata0)
    *(.zdata)
    . = ALIGN(4);
  } > RAM
  _zdata_START = ADDR(.zdata);
  _zdata_END = ENDADDR(.zdata) - 1;
  _zdata_LIMIT = ENDADDR(.zdata);

  _Data_Default_ALL_START = _bss_START;
  _Data_Default_ALL_END = _zdata_END;
  _Data_Default_ALL_LIMIT = _zdata_LIMIT;

  .data_ROM ROM_NOCOPY(.data) :> FLASH
  _data_ROM_START = ADDR(.data_ROM);
  _data_ROM_LIMIT = ENDADDR(.data_ROM);

  .data ALIGN(4) :
  {
    *(.data)
    . = ALIGN(4);
  } > Data_Extension
  _data_START = ADDR(.data);
  _data_END = ENDADDR(.data) - 1;
  _data_LIMIT = ENDADDR(.data);

  .LargeHsmVar ALIGN(4) :
  {
    *(.LargeHsmVar)
    . = ALIGN(4);
  } > Data_Extension
  _LargeHsmVar_START = ADDR(.LargeHsmVar);
  _LargeHsmVar_END = ENDADDR(.LargeHsmVar) - 1;
  _LargeHsmVar_LIMIT = ENDADDR(.LargeHsmVar);

  _Data_Extension_ALL_START = _data_START;
  _Data_Extension_ALL_END = _LargeHsmVar_END;
  _Data_Extension_ALL_LIMIT = _LargeHsmVar_LIMIT;

  __cy_app_verify_start = _cy_app_header_START;
  __ecc_init_sram_end_address = 0x2801ffff;
  __ecc_init_sram_start_address = 0x28000800;
  __ghs_rambootcodeend = 0;
  __ghs_rambootcodestart = 0;
  __ghs_rombootcodeend = _cy_app_signature_START;
  __ghs_rombootcodestart = 0x10000000;
  __ghsbegin_picbase = _text_START;
  __ghsbegin_pidbase = _data_START;
  __ghsbegin_robase = _rodata_START;
  __ghsend_stack = _STACK_C0_LIMIT;
  __cy_app_verify_length = _cy_app_signature_START-_cy_app_header_START;

}


