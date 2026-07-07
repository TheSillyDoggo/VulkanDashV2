#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <ShaderCache.hpp>

using namespace geode::prelude;

void* getWindowHandle()
{
    #ifdef GEODE_IS_WINDOWS
    return WindowFromDC(wglGetCurrentDC());
    #elifdef GEODE_IS_MACOS
    return nullptr;
    #else
    return nullptr;
    #endif
}

class $modify (BGFXEGLView, CCEGLView)
{
    bool initGlew()
    {
        CCEGLView::initGlew();

        bgfx::Init init;
        init.type = bgfx::RendererType::Enum::OpenGL;
        init.vendorId = BGFX_PCI_ID_NONE;
        init.platformData.nwh  = getWindowHandle();
        init.platformData.ndt  = nullptr;
        init.platformData.type = bgfx::NativeWindowHandleType::Default;
        init.resolution.width  = (int)m_obScreenSize.width;
        init.resolution.height = (int)m_obScreenSize.height;
        init.resolution.reset  = BGFX_RESET_NONE;
        bgfx::renderFrame();
        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        bgfx::setViewClear(0,
            BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            0x000000ff,
            1.0f,
            0
        );

        return true;
    }

    void swapBuffers()
    {
        bgfx::frame();
        bgfx::renderFrame();
    }
};

$on_mod(Loaded)
{
    (void)Mod::get()->patch(reinterpret_cast<void*>(geode::base::getCocos() + 0xbe40e), { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
};