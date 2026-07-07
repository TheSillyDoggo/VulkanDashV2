#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <VertexLayoutManager.hpp>
#include <ShaderCache.hpp>

using namespace geode::prelude;

class $modify (BGFXDirector, CCDirector)
{
    void drawScene(void)
    {
        float proj[16];
        bx::mtxOrtho(
            proj,
            0.0f,
            CCDirector::get()->getWinSize().width, 
            0,
            CCDirector::get()->getWinSize().height,
            -10.0f,
            1000.0f,
            0.0f,
            bgfx::getCaps()->homogeneousDepth
        );

        float view[16];
        bx::mtxIdentity(view);

        bgfx::setViewTransform(0, view, proj);
        bgfx::setViewRect(0, 0, 0, uint16_t(CCEGLView::get()->m_obScreenSize.width), uint16_t(CCEGLView::get()->m_obScreenSize.height));
        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);


        CCDirector::drawScene();
    }
};