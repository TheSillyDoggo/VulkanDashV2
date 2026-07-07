#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCTexture2D.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>

class $modify (BGFXTexture2D, cocos2d::CCTexture2D)
{
    struct BGFXData
    {
        bgfx::TextureHandle handle;
    };

    bool initWithData(const void* data, cocos2d::CCTexture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const cocos2d::CCSize& contentSize);

    bgfx::TextureHandle getHandle();

    static bgfx::TextureFormat::Enum ccFormatToBGFX(cocos2d::CCTexture2DPixelFormat pf);
};