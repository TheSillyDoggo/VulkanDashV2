#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLViewProtocol.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>

using namespace geode::prelude;

class $modify (BGFXEGLViewProtocol, CCEGLViewProtocol)
{
    virtual void setFrameSize(float width, float height)
    {
        CCEGLViewProtocol::setFrameSize(width, height);

        if (bgfx::getRendererType() != bgfx::RendererType::Noop)
            bgfx::reset((int)width, (int)height);
    }
};