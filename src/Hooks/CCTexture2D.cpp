#include "CCTexture2D.hpp"
#include <ShaderCache.hpp>

using namespace geode::prelude;

std::unordered_map<CCTexture2D*, BGFXTexture2D::BGFXData> extraData = {};

void BGFXTexture2D::onModify(auto& self)
{
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::initWithData", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::setTexParameters", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::setAntiAliasTexParameters", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::setAliasTexParameters", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::generateMipmap", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::drawAtPoint", Priority::Replace);
    (void)self.setHookPriorityPost("cocos2d::CCTexture2D::drawInRect", Priority::Replace);
}

bool BGFXTexture2D::initWithData(const void* data, CCTexture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const CCSize& contentSize)
{
    BGFXData bgData{};

    bgData.handle = bgfx::createTexture2D(pixelsWide, pixelsHigh,
        false,
        1,
        ccFormatToBGFX(pixelFormat),
        0, 
        bgfx::copy(data, pixelsWide * pixelsHigh * bitsPerPixelForFormat(pixelFormat) / 8)
    );

    extraData[this] = bgData;

    // reimplementation of original ::initWithData but without the opengl stuff
    m_tContentSize = contentSize;
    m_uPixelsWide = pixelsWide;
    m_uPixelsHigh = pixelsHigh;
    m_ePixelFormat = pixelFormat;
    m_fMaxS = contentSize.width / (float)(pixelsWide);
    m_fMaxT = contentSize.height / (float)(pixelsHigh);

    m_bHasPremultipliedAlpha = false;
    m_bHasMipmaps = false;

    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
    return true;
}

void BGFXTexture2D::setTexParameters(ccTexParams* texParams)
{
    uint32_t flags = 0;

    switch (texParams->wrapS)
    {
        case GL_CLAMP_TO_EDGE:
            flags |= BGFX_SAMPLER_U_CLAMP;
            break;
        case GL_MIRRORED_REPEAT:
            flags |= BGFX_SAMPLER_U_MIRROR;
            break;
    }

    switch (texParams->wrapT)
    {
        case GL_CLAMP_TO_EDGE:
            flags |= BGFX_SAMPLER_V_CLAMP;
            break;
        case GL_MIRRORED_REPEAT:
            flags |= BGFX_SAMPLER_V_MIRROR;
            break;
    }

    if (texParams->magFilter == GL_NEAREST)
        flags |= BGFX_SAMPLER_MAG_POINT;

    switch (texParams->minFilter)
    {
        case GL_NEAREST_MIPMAP_LINEAR:
        case GL_NEAREST:
            flags |= BGFX_SAMPLER_MIN_POINT;
            break;
        case GL_NEAREST_MIPMAP_NEAREST:
            flags |= BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MIP_POINT;

        case GL_LINEAR_MIPMAP_NEAREST:
            flags |= BGFX_SAMPLER_MIP_POINT;
    }

    extraData[this].flags = flags;
}

void BGFXTexture2D::setAntiAliasTexParameters()
{
    log::error("CCTexture2D::setAntiAliasTexParameters: Unimplemented :3");
}

void BGFXTexture2D::setAliasTexParameters()
{
    log::error("CCTexture2D::setAliasTexParameters: Unimplemented :3");
}

#ifndef GEODE_IS_IOS

void BGFXTexture2D::generateMipmap()
{
    log::error("CCTexture2D::generateMipmap: Unimplemented :3");
}

void BGFXTexture2D::drawAtPoint(const CCPoint& point)
{
    log::error("CCTexture2D::drawAtPoint: Unimplemented :3");
}

void BGFXTexture2D::drawInRect(const CCRect& rect)
{
    log::error("CCTexture2D::drawInRect: Unimplemented :3");
}

#endif

void BGFXTexture2D::bind()
{
    bgfx::setTexture(0, ShaderCache::getSpriteUniform(), getHandle(), extraData[this].flags);
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