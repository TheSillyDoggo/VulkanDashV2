#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayerColor.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>

using namespace geode::prelude;

bgfx::IndexBufferHandle getIbh2()
{
    static uint16_t indices[] = {
        0, 1, 2,
        3, 4, 5
    };

    static bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(indices)));
    return ibh;
}

class $modify (BGFXLayerColor, CCLayerColor)
{
    void draw()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, 6, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());

        ccV3F_C4B_T2F out[6];

        const CCPoint v[6] = {
            ccp(0, 0), ccp(0, 1), ccp(1, 0), ccp(0, 1), ccp(1, 1), ccp(1, 0),
        };
        
        for (int i = 0; i < 6; i++)
        {
            out[i].vertices.x = v[i].x * m_pSquareVertices[3].x;
            out[i].vertices.y = v[i].y * m_pSquareVertices[3].y;
            out[i].vertices.z = 0;

            if (v[i] == ccp(0, 0))
            {
                out[i].colors.r = m_pSquareColors[0].r * 255;
                out[i].colors.g = m_pSquareColors[0].g * 255;
                out[i].colors.b = m_pSquareColors[0].b * 255;
                out[i].colors.a = m_pSquareColors[0].a * 255;
            }

            if (v[i] == ccp(1, 0))
            {
                out[i].colors.r = m_pSquareColors[1].r * 255;
                out[i].colors.g = m_pSquareColors[1].g * 255;
                out[i].colors.b = m_pSquareColors[1].b * 255;
                out[i].colors.a = m_pSquareColors[1].a * 255;
            }

            if (v[i] == ccp(0, 1))
            {
                out[i].colors.r = m_pSquareColors[2].r * 255;
                out[i].colors.g = m_pSquareColors[2].g * 255;
                out[i].colors.b = m_pSquareColors[2].b * 255;
                out[i].colors.a = m_pSquareColors[2].a * 255;
            }

            if (v[i] == ccp(1, 1))
            {
                out[i].colors.r = m_pSquareColors[3].r * 255;
                out[i].colors.g = m_pSquareColors[3].g * 255;
                out[i].colors.b = m_pSquareColors[3].b * 255;
                out[i].colors.a = m_pSquareColors[3].a * 255;
            }

            out[i].texCoords.u = 0;
            out[i].texCoords.v = 0;
        }
        
        memcpy(tvb.data, &out, tvb.size);

        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(getIbh2());

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_tBlendFunc));

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};