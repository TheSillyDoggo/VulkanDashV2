#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextureAtlas.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"
#include "CCSpriteBatchNode.hpp"

using namespace geode::prelude;

class $modify (BGFXTextureAtlas, CCTextureAtlas)
{
    void drawQuads()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, m_uTotalQuads * 4, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        memcpy(tvb.data, m_pQuads, tvb.size);

        bgfx::TransientIndexBuffer tib;
        bgfx::allocTransientIndexBuffer(&tib, m_uTotalQuads * 6, true);
        auto data = reinterpret_cast<uint32_t*>(tib.data);

        for (size_t i = 0; i < m_uTotalQuads; i++)
        {
            size_t baseVert = i * 4;
            size_t baseInd = i * 6;

            data[baseInd] = baseVert;
            data[baseInd + 1] = baseVert + 1;
            data[baseInd + 2] = baseVert + 2;

            data[baseInd + 3] = baseVert + 1;
            data[baseInd + 4] = baseVert + 3;
            data[baseInd + 5] = baseVert + 2;
        }

        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(&tib);
        static_cast<BGFXTexture2D*>(m_pTexture)->bind();

        /*
        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc());
        */
        auto bn = BGFXSpriteBatchNode::getLastBatchNode();
        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | (bn ? BGFXUtils::getBlendFunc(bn->m_blendFunc) : BGFXUtils::getBlendFunc()));

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};