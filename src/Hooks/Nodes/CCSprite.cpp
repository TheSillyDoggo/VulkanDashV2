#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"

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
    struct Fields
    {
        bool dirty = false;
    };

    void updateMemory()
    {
        if (m_pobBatchNode)
            return;

        // log::warn("updateMemory: {}", this);
    }

    void updateColor(void)
    {
        CCSprite::updateColor();
        updateMemory();
    }

    virtual void setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize)
    {
        CCSprite::setTextureRect(rect, rotated, untrimmedSize);
        updateMemory();
    }

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