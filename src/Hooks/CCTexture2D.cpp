#include "CCTexture2D.hpp"

using namespace geode::prelude;

std::unordered_map<CCTexture2D*, BGFXTexture2D::BGFXData> extraData = {};

bool BGFXTexture2D::initWithData(const void* data, CCTexture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const CCSize& contentSize)
{
    BGFXData bgData{};

    log::info("initWithData: {}x{}", pixelsWide, pixelsHigh);

    bgData.handle = bgfx::createTexture2D(pixelsWide, pixelsHigh,
        false,
        1,
        ccFormatToBGFX(pixelFormat),
        0, 
        bgfx::makeRef(data, pixelsWide * pixelsHigh * bitsPerPixelForFormat(pixelFormat) / 8)
    );

    extraData[this] = bgData;
    return CCTexture2D::initWithData(data, pixelFormat, pixelsWide, pixelsHigh, contentSize);
}

bgfx::TextureHandle BGFXTexture2D::getHandle()
{
    return extraData[this].handle;
}

bgfx::TextureFormat::Enum BGFXTexture2D::ccFormatToBGFX(cocos2d::CCTexture2DPixelFormat pf)
{
    switch (pf)
    {
        case kCCTexture2DPixelFormat_RGBA8888:
            return bgfx::TextureFormat::Enum::RGBA8;
        case kCCTexture2DPixelFormat_RGB888:
            return bgfx::TextureFormat::Enum::RGB8;
        case kCCTexture2DPixelFormat_RGB565:
            return bgfx::TextureFormat::Enum::R5G6B5;
        case kCCTexture2DPixelFormat_A8:
            return bgfx::TextureFormat::Enum::A8;
        case kCCTexture2DPixelFormat_I8:
            return bgfx::TextureFormat::Enum::R8;
        case kCCTexture2DPixelFormat_AI88:
            return bgfx::TextureFormat::Enum::RG8;
        case kCCTexture2DPixelFormat_RGBA4444:
            return bgfx::TextureFormat::RGBA4;
        case kCCTexture2DPixelFormat_RGB5A1:
            return bgfx::TextureFormat::RGB5A1;
        case kCCTexture2DPixelFormat_PVRTC4:
            return bgfx::TextureFormat::PTC14A;
        case kCCTexture2DPixelFormat_PVRTC2:
            return bgfx::TextureFormat::PTC12A;
        default:
            return bgfx::TextureFormat::Enum::Unknown;
    };
}