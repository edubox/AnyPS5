# libSceGnmDriverForNeoMode

## change [libSceGnmDriverForNeoMode pending exports]

- [libSceGnmDriverForNeoMode pending exports](../../../core/libs/prx/libSceGnmDriverForNeoMode/Export.cpp) - 17 named callable exports are listed in the [PS5 3.20 export table](https://github.com/DNNDHH/PS5-3.20_Libs/blob/b2a77c09cd71c01f34c790cfbe98c751a13262ad/libSceGnmDriverForNeoMode.c) and were cross-checked against the same module in PS5 firmware 13.60. Their signatures and behaviour are unverified; the declarations use the no-parameter unknown-signature convention and throw through `NotImplemented_nid_no_patch`.

## add Functional

- [status queries](../../../core/libs/prx/libSceGnmDriverForNeoMode/Export.cpp) (libSceGnmDriverForNeoMode) - `sceGnmGetGpuBlockStatus`, `sceGnmGetGpuInfoStatus`, `sceGnmGetLastWaitedAddress`, `sceGnmGetProtectionFaultTimeStamp`, `sceGnmGetShaderProgramBaseAddress`, `sceGnmGetShaderStatus` and `sceGnmInsertThreadTraceMarker` return 0, and `sceGnmGetNumTcaUnits` returns 2, because that is the whole body of each export in the decrypted firmware module: `xor eax, eax; ret` at 0x450 to 0x4a0 and 0x4000, and `mov eax, 2; ret` for the last. The 11.00 module answers the same for the seven but its `sceGnmGetNumTcaUnits` (0x760, 95 bytes) returns 2 minus the low bit of a value it reads after an internal call, so 1 is possible there; that call and the condition are not identified, and no title in the dumps imports this library. The three exports whose body is a bare `ret` (`sceGnmGpuPaDebugEnter`, `sceGnmGpuPaDebugLeave`, `sceGnmRegisterGnmLiveCallbackConfig`) still throw, since the module leaves no return value to reproduce and their declarations return `int`.
