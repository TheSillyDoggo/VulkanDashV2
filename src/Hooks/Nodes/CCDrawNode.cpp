#include <Geode/Geode.hpp>
#include <Geode/modify/CCDrawNode.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"
#include "CCSpriteBatchNode.hpp"

using namespace geode::prelude;

class $modify (BGFXDrawNode, CCDrawNode)
{
    virtual void draw()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, m_nBufferCount, VertexLayoutManager::get<cocos2d::ccV2F_C4B_T2F>());
        memcpy(tvb.data, m_pBuffer, tvb.size);

        bgfx::setVertexBuffer(0, &tvb);
        static_cast<BGFXTexture2D*>(BGFXUtils::getBlankTex())->bind();

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_sBlendFunc));

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};