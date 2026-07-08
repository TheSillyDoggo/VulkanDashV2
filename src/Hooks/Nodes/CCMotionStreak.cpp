#include <Geode/Geode.hpp>
#include <Geode/modify/CCMotionStreak.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"

using namespace geode::prelude;

class $modify (BGFXMotionStreak, CCMotionStreak)
{
    virtual void draw()
    {
        if (m_uNuPoints <= 1)
            return;

        size_t totalVertices = m_uNuPoints * 2;
        
        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, totalVertices, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        
        ccV3F_C4B_T2F* dst = reinterpret_cast<ccV3F_C4B_T2F*>(tvb.data);
        ccColor4B* srcColors = reinterpret_cast<ccColor4B*>(m_pColorPointer);

        for (size_t i = 0; i < totalVertices; ++i)
        {
            dst[i].vertices = { m_pVertices[i].x, m_pVertices[i].y, 0.0f };
            dst[i].colors   = srcColors[i];
            dst[i].texCoords = m_pTexCoords[i];
        }

        kmMat4 mat = BGFXUtils::getMatrix();
        bgfx::setTransform(mat.mat);

        bgfx::setVertexBuffer(0, &tvb, 0, totalVertices);
        
        static_cast<BGFXTexture2D*>(m_pTexture)->bind();
        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_tBlendFunc) | BGFX_STATE_PT_TRISTRIP);

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};