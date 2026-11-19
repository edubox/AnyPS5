#include "prx/libSceDipsw/include/Api.hpp"
#include <cstdlib>

int main() {
    constexpr int InvalidValue = static_cast<int>(0x80020016u);
    constexpr int NoDipsw = 0;
    if (sceKernelIsDevelopmentMode() != NoDipsw) std::abort();
    if (sceKernelIsAssistMode() != NoDipsw) std::abort();
    if (sceKernelIsDisableRazor() != NoDipsw) std::abort();
    if (sceKernelGetDiableBinaryVersionCheckValue() != NoDipsw) std::abort();
    if (sceKernelCheckDipsw(0u) != NoDipsw) std::abort();
    if (sceKernelCheckDipsw(0xffu) != NoDipsw) std::abort();
    if (sceKernelCheckDipsw(0x100u) != InvalidValue) std::abort();
    if (sceKernelCheckDipsw(0xffffffffu) != InvalidValue) std::abort();
    return 0;
}
