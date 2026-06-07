import time

targetAddress = 0x28013000
workflashAddress1 = 0x14030300
workflashSize1 = 0x3D00
workflashAddress2 = 0x14034000
workflashSize2 = 0x2000
workflashAddress3 = 0x14036000
workflashSize3 = 0x1F00

range_check = [(workflashAddress1, workflashSize1), (workflashAddress2, workflashSize2), (workflashAddress3, workflashSize3)]
Status1 = 0
Status2 = 0
Status3 = 0

IPC3AcquireReg = 0x40220060
IPC3Data0Reg = 0x4022006c
IPC3NotifyReg = 0x40220068
Initialdata = 0x80000f03
NotifytoIPC0 = 0x00000001
BlankCheck_param = 0x2A000000

for (addr_, len_) in range_check:
    print("Check blank range {} - {}".format(hex(addr_), hex(addr_+len_-1)))
    WriteViaSysAp(IPC3AcquireReg, Initialdata)

    WriteViaSysAp(IPC3Data0Reg, targetAddress)

    WriteViaSysAp(targetAddress, BlankCheck_param)
    targetAddress += 4
    WriteViaSysAp(targetAddress, workflashAddress1)
    targetAddress += 4
    WriteViaSysAp(targetAddress, workflashSize1)

    WriteViaSysAp(IPC3NotifyReg, NotifytoIPC0)

    time.sleep(1) # Sleep for 1 seconds

    #CheckOutput
    targetAddress -= 8
    Status = ReadViaSysAp(targetAddress)
    while Status == 0xA0000009:
        Status = ReadViaSysAp(targetAddress)
        
    if Status & 0xF0000000 == 0xA0000000:
        print("Workflash is BLANK! Status: ", hex(Status))
    else:
        print("Workflash is NOT BLANK! Status: ", hex(Status))
    print("")