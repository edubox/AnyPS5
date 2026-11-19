#include "prx/libSceDipsw/include/Api.hpp"
#include <cstdint>
#include <cstddef>
#include "SceTypes.hpp"
#include "prx/libc/include/General.hpp"
#include "prx/libkernel/include/Api.hpp"
#include <cerrno>

extern "C" {

int APS5_VABI sceKernelCheckDipsw(std::uint32_t id) {
    if (id >= 0x100u) return sceKernelError(EINVAL);
    return 0;
}

int APS5_VABI sceKernelInitializeDipsw() {
    NotImplemented_nid_no_patch(__func__);
    return 0;
}

int APS5_VABI sceKernelIsAssistMode() {
    return sceKernelCheckDipsw(2u);
}

int APS5_VABI sceKernelIsDevelopmentMode() {
    return sceKernelCheckDipsw(0u);
}

int APS5_VABI sceKernelIsDisableRazor() {
    return sceKernelCheckDipsw(0x18u);
}

int APS5_VABI sceKernelGetDiableBinaryVersionCheckValue() {
    return sceKernelCheckDipsw(0x1eu);
}

int APS5_VABI sceKernelReadDipswData() {
    NotImplemented_nid_no_patch(__func__);
    return 0;
}

int APS5_VABI sceKernelSetDipsw() {
    NotImplemented_nid_no_patch(__func__);
    return 0;
}

int APS5_VABI sceKernelUnsetDipsw() {
    NotImplemented_nid_no_patch(__func__);
    return 0;
}

int APS5_VABI sceKernelWriteDipswData() {
    NotImplemented_nid_no_patch(__func__);
    return 0;
}

}
