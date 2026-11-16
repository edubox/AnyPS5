# libSceHmd2

## add Functional

- [Reprojection frame start, mirroring disable and VR mode disable](../../../core/libs/prx/libSceHmd2/Export.cpp) (libSceHmd2) - the four exported wrappers check the reprojection session themselves, and `sceHmd2ReprojectionSetMirroringOption` also its 32-byte option (a mode of 0 or 1 and seven zero reserved words), answering `REPROJECTION_NOT_INITIALIZED` (0x8A72000B) without a session, `PARAMETER_NULL` (0x8A720008) for a null or unreadable option and `PARAMETER_INVALID` (0x8A720009) for the rest, as the 13.40 module does. The reprojection pipeline behind them has no host model, so the four still throw once the call needs it. Console execution not measured.
