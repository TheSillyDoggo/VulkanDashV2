#include <BGFX.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <ShaderCache.hpp>
#include <Geode/Geode.hpp>

void BGFXUtils::initBGFX(void* nativeHandle, int width, int height)
{
    bgfx::Init init;
    init.type = bgfx::RendererType::Enum::Metal;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.platformData.nwh  = nativeHandle;
    init.platformData.ndt  = nullptr;
    init.platformData.type = bgfx::NativeWindowHandleType::Default;
    init.resolution.width  = width;
    init.resolution.height = height;
    init.resolution.reset  = BGFX_RESET_NONE;
    init.resolution.debugTextScale = 3;
    
    bgfx::init(init);
    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::setViewClear(0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x000000ff,
        1.0f,
        0
    );
}

kmMat4 BGFXUtils::getMatrix()
{
    kmMat4 model;
    kmGLGetMatrix(KM_GL_MODELVIEW, &model);

    return model;
}

uint64_t BGFXUtils::getBlendFunc()
{
    GLint blendSrcRGB, blendDstRGB, blendSrcAlpha, blendDstAlpha;

    glGetIntegerv(GL_BLEND_SRC_RGB, &blendSrcRGB);
    glGetIntegerv(GL_BLEND_DST_RGB, &blendDstRGB);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrcAlpha);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDstAlpha);

    return BGFX_STATE_BLEND_FUNC_SEPARATE(glToBGFXBlend(blendSrcRGB), glToBGFXBlend(blendDstRGB), glToBGFXBlend(blendSrcAlpha), glToBGFXBlend(blendDstAlpha));
}

uint64_t BGFXUtils::getBlendFunc(cocos2d::ccBlendFunc blend)
{
    return BGFX_STATE_BLEND_FUNC(glToBGFXBlend(blend.src), glToBGFXBlend(blend.dst));
}

uint64_t BGFXUtils::glToBGFXBlend(int gl)
{
    switch (gl)
    {
        case GL_ONE:
            return BGFX_STATE_BLEND_ONE;
        case GL_SRC_COLOR:
            return BGFX_STATE_BLEND_SRC_COLOR;
        case GL_ONE_MINUS_SRC_COLOR:
            return BGFX_STATE_BLEND_INV_SRC_COLOR;
        case GL_SRC_ALPHA:
            return BGFX_STATE_BLEND_SRC_ALPHA;
        case GL_ONE_MINUS_SRC_ALPHA:
            return BGFX_STATE_BLEND_INV_SRC_ALPHA;
        case GL_DST_ALPHA:
            return BGFX_STATE_BLEND_DST_ALPHA;
        case GL_ONE_MINUS_DST_ALPHA:
            return BGFX_STATE_BLEND_INV_DST_ALPHA;
        case GL_DST_COLOR:
            return BGFX_STATE_BLEND_DST_COLOR;
        case GL_ONE_MINUS_DST_COLOR:
            return BGFX_STATE_BLEND_INV_DST_COLOR;
        case GL_SRC_ALPHA_SATURATE:
            return BGFX_STATE_BLEND_SRC_ALPHA_SAT;
        default:
            return 0;
    }
}

cocos2d::CCTexture2D* BGFXUtils::getBlankTex()
{
    return cocos2d::CCTextureCache::get()->addImage("cc_2x2_white_image", true);
}