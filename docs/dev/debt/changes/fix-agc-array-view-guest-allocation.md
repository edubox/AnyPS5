# libSceAgcDriver

## add Functional

- [Array views past their guest allocation](../../../core/libs/prx/libSceAgcDriver/Graphics/src/TextureTiling.cpp) (libSceAgcDriver) - a sampled or storage view of a 1D or 2D array larger than the guest allocation that holds it is cut to the slices that fit. The cut keeps the first viewed slice (`baseArray`) and the DCC metadata and only lowers the last slice, so a shader that samples or stores a layer past the cut reaches outside its image, where those layers already had no backing. Depth-surface storage images (`DepthSurface.cpp`) are not cut, cubes are left whole, and a view whose first viewed slice lies outside its allocation keeps its descriptor whole. Closes when: depth storage is cut the same way and a view with no slice inside its allocation is refused instead of materialized. PPSA15508's 2560x1440 format-69 array of 1701 slices, 46 inside a 2200 MiB allocation, asked for one 49.8 GiB host allocation before this; no title has run since.
