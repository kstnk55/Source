Purpose:
IPL baseline source code analysis.
Execution chain:
CM0 code in vHSM
DualBank_Manager.asm
-> ARMStartup_CortexM.c
-> BrsMainStartup.c
-> BrsMain.c
-> SystemInit
-> vHsm.c
-> vHsm_Callout_Stubs.c
Analysis goals:
- Requirement mapping
- Impact analysis
- Porting code from Traveo 4BF to Traveo 4DN

