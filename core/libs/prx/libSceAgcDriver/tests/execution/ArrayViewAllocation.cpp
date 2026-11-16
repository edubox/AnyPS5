#include "prx/libSceAgcDriver/Execution/include/VulkanDevice.hpp"
#include "prx/libSceAgcDriver/Graphics/include/Recorder.hpp"
#include "prx/libSceAgcDriver/Graphics/include/ShaderResources.hpp"
#include "prx/libSceAgcDriver/Graphics/include/TextureTiling.hpp"
#include "prx/libc/include/GuestAllocations.hpp"
#include "VulkanTestDevice.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

namespace {

using AgcDriver::Graphics::DescribeSurface;
using AgcDriver::Graphics::GuestTextureResource;
using AgcDriver::Graphics::Recorder;
using AgcDriver::Graphics::Require;
using AgcDriver::Graphics::StorageTexture;
using AgcDriver::Graphics::TextureDimension;
using AgcDriver::Graphics::TextureTileMode;

constexpr std::uint32_t Side = 64;
constexpr std::uint32_t Format32UInt = 20;
constexpr std::uint32_t Slices = 1701;
constexpr std::uint32_t Fitting = 46;
constexpr std::uint32_t Base = 3;

int BoundArrayView() {
    const auto device = OpenVulkanTestDevice();
    if (!device) return VulkanTestSkipped;
    const auto context = device->graphicsContext();

    GuestTextureResource resource{};
    resource.width = Side;
    resource.height = Side;
    resource.format = Format32UInt;
    resource.mipCount = 1;
    resource.dimension = TextureDimension::k2DArray;
    resource.tileMode = TextureTileMode::kR64KBX;
    resource.baseArray = Base;
    resource.depthOrLastArray = Slices - 1u;
    const auto geometry = DescribeSurface(resource);
    const auto held = geometry.layerBytes * Fitting;

    auto* memory = static_cast<std::uint8_t*>(std::aligned_alloc(65536, static_cast<std::size_t>(geometry.guestBytes)));
    Require(memory != nullptr, "cannot allocate the guest block");
    std::memset(memory, 0x5a, static_cast<std::size_t>(geometry.guestBytes));
    auto* texels = reinterpret_cast<void*>(memory);
    resource.baseAddress = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(memory));

    {
        GuestAllocations::Mutation mutation;
        mutation.Add(texels, static_cast<std::size_t>(held), true, true, true);
    }
    try {
        std::shared_ptr<StorageTexture> image;
        {
            Recorder recorder(context);
            recorder.Activate();
            recorder.Commands();
            image = AgcDriver::Graphics::CachedStorageSurface(context, resource);
            recorder.Sync();
        }
        Require(image != nullptr, "an array storage view of " + std::to_string(Slices) + " slices inside an allocation of " + std::to_string(Fitting) + " made no image");
        Require(image->GuestBytes() == held, "an array storage view inside a guest allocation of " + std::to_string(held) + " bytes made an image of " + std::to_string(image->GuestBytes()) + " guest bytes");
        Require(StorageTexture::FindLive(resource.baseAddress, held) != nullptr, "the image does not serve the slices its guest allocation holds");
        Require(StorageTexture::FindLive(resource.baseAddress, geometry.guestBytes) == nullptr, "the image still covers the whole array");
        device->WaitIdle();
        AgcDriver::Graphics::ReleaseTextureCaches(~std::uint64_t{0});
        Require(StorageTexture::FindLive(resource.baseAddress, held) == nullptr, "the image survived a release of the caches");
    } catch (...) {
        GuestAllocations::Mutation().Remove(texels);
        std::free(memory);
        throw;
    }
    GuestAllocations::Mutation().Remove(texels);
    std::free(memory);
    std::puts("array view guest allocation tests passed");
    return 0;
}

}

int main() {
    try {
        return BoundArrayView();
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
