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