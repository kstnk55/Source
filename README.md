Purpose:
IPL baseline source code analysis.
Execution chain:
IPL CM0 code in vHSM folder
IPL CM7 code in CM7 folder

DualBank_Manager.asm
-> ARMStartup_CortexM.c
-> BrsMainStartup.c
-> BrsMain.c
-> SystemInit
-> vHsm.c
-> vHsm_Callout_Stubs.c

Current source code is for 4BF. We must porting to 4DN
