#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <ShaderCache.hpp>
#include <macOS.hpp>
#include <BGFX.hpp>

using namespace geode::prelude;

class $modify (BGFXEGLView, CCEGLView)
{
    void swapBuffers()
    {
        bgfx::touch(0);
        bgfx::setViewRect(0, 0, 0, uint16_t(CCEGLView::get()->m_obScreenSize.width), uint16_t(CCEGLView::get()->m_obScreenSize.height));

        bgfx::dbgTextClear();

        const bgfx::Stats* stats = bgfx::getStats();

        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dx%d"
            , stats->width
            , stats->height
            );

        const GLubyte* gpu = glGetString(GL_RENDERER);

        bgfx::dbgTextPrintf(0, 4, 0x0f, "Renderer: %s", bgfx::getRendererName(bgfx::getRendererType()));
        bgfx::dbgTextPrintf(0, 5, 0x0f, "GPU: %s", reinterpret_cast<const char*>(gpu));
        if (CCDirector::get()->m_pFPSNode)
            bgfx::dbgTextPrintf(0, 6, 0x0f, "%s", CCDirector::get()->m_pFPSNode->getString());
        
        bgfx::frame();
    }
};