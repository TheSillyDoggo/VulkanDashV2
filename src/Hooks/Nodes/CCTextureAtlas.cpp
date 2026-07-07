#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextureAtlas.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>

using namespace geode::prelude;

class $modify (BGFXTextureAtlas, CCTextureAtlas)
{
    /*struct Fields
    {
        bgfx::DynamicVertexBufferHandle vbh;
    };

    bool initWithTexture(CCTexture2D *texture, unsigned int capacity)
    {
        if (!CCTextureAtlas::initWithTexture(texture, capacity))
            return false;

        m_fields->vbh = bgfx::createDynamicVertexBuffer()

        return true;
    }

    void updateQuad(ccV3F_C4B_T2F_Quad* quad, unsigned int index)
    {
        
    }*/

    void drawQuads()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, m_uTotalQuads * 4, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        memcpy(tvb.data, getQuads(), tvb.size);

        bgfx::TransientIndexBuffer tib;
        bgfx::allocTransientIndexBuffer(&tib, m_uTotalQuads * 5, true);
        auto data = reinterpret_cast<uint32_t*>(tib.data);

        for (size_t i = 0; i < m_uTotalQuads; i++)
        {
            data[i * 5] = i;
            data[i * 5 + 1] = i + 1;
            data[i * 5 + 2] = i + 2;
            data[i * 5 + 3] = i + 3;
            data[i * 5 + 4] = 0xFFFFFFFF;
        }

        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(&tib);

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA | BGFX_STATE_PT_TRISTRIP);

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};