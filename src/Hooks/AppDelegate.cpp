#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <ShaderCache.hpp>
#include <macOS.hpp>
#include <BGFX.hpp>

using namespace geode::prelude;

void* getWindowHandle()
{
    #ifdef GEODE_IS_WINDOWS
    return WindowFromDC(wglGetCurrentDC());
    #elifdef GEODE_IS_MACOS
    return getNSWindowHandle();
    #else
    return nullptr;
    #endif
}

class $modify (AppDelegate)
{
    virtual bool applicationDidFinishLaunching()
    {
        auto size = CCEGLView::sharedOpenGLView()->getFrameSize();

        BGFXUtils::initBGFX(getWindowHandle(), size.width, size.height);
        return AppDelegate::applicationDidFinishLaunching();
    }
};