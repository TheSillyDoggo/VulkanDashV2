#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"
#include "CCSpriteBatchNode.hpp"

using namespace geode::prelude;

bgfx::IndexBufferHandle getIbh()
{
    static uint16_t indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    static bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(indices)));
    return ibh;
}

class $modify (BGFXSprite, CCSprite)
{
    /*virtual void updateTransform(void)
    {
        if (m_pobBatchNode && isDirty())
        {
            static_cast<BGFXSpriteBatchNode*>(m_pobBatchNode)->updateInstance(this);
            setDirty(false);
        }

        CCSprite::updateTransform();
    }
*/
    void draw()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, 4, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        memcpy(tvb.data, &m_sQuad, tvb.size);

        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(getIbh());
        static_cast<BGFXTexture2D*>(m_pobTexture)->bind();

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_sBlendFunc));

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};