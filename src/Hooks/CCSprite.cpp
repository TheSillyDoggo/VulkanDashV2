/*#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"

using namespace geode::prelude;

kmMat4 getNodeToWorldTransform(cocos2d::CCNode* node)
{
    kmMat4 model;
    kmGLGetMatrix(KM_GL_MODELVIEW, &model);

    kmMat4 projection;
    kmGLGetMatrix(KM_GL_PROJECTION, &projection);

    kmMat4 mvp;
    kmMat4Multiply(&mvp, &projection, &model);

    return mvp;
}

class $modify (BGFXSprite, CCSprite)
{
    struct Fields
    {
        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer tib;
        bgfx::DynamicVertexBufferHandle vbh;
        bgfx::DynamicIndexBufferHandle ibh;
    };

    virtual bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
    {
        static const uint16_t indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        bgfx::allocTransientVertexBuffer(&m_fields->tvb, 4, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        bgfx::allocTransientIndexBuffer(&m_fields->tib, 6);
        memcpy(m_fields->tib.data, indices, sizeof(indices));

        const auto& q = m_sQuad;
        cocos2d::ccV3F_C4B_T2F verts[4] = {
            q.bl, q.br, q.tr, q.tl
        };

        memcpy(m_fields->tvb.data, verts, sizeof(verts));

        m_fields->vbh = bgfx::createDynamicVertexBuffer(bgfx::copy(verts, sizeof(verts)), VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        m_fields->ibh = bgfx::createDynamicIndexBuffer(bgfx::copy(indices, sizeof(indices)));

        return CCSprite::initWithTexture(pTexture, rect);
    }

    void updateMemory()
    {
        const auto& q = m_sQuad;
        cocos2d::ccV3F_C4B_T2F verts[4] = {
            q.bl, q.br, q.tr, q.tl
        };
        
        memcpy(m_fields->tvb.data, verts, sizeof(verts));

        bgfx::update(m_fields->vbh, 0, bgfx::copy(verts, sizeof(verts)));
    }

    virtual void updateTransform(void)
    {
        CCSprite::updateTransform();

        updateMemory();
    }

    void draw()
    {
        static bgfx::ProgramHandle program = ShaderCache::get("sprite.fs.sc", "sprite.vs.sc");

        // Layout must match your vertex type
        static auto layout = VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>();

        // Transform
        kmMat4 mat = getNodeToWorldTransform(this);
        bgfx::setTransform(mat.mat);

        // Bind buffers
        // bgfx::setVertexBuffer(0, &m_fields->vbh);
        // bgfx::setIndexBuffer(&m_fields->ibh);
        bgfx::setVertexBuffer(0, m_fields->vbh);
        bgfx::setIndexBuffer(m_fields->ibh);

        // Texture (if you use it)
        // bgfx::setTexture(0, s_texColor, textureHandle);

        bgfx::setState(
            BGFX_STATE_WRITE_RGB |
            BGFX_STATE_WRITE_A |
            BGFX_STATE_BLEND_ALPHA
        );

        bgfx::submit(0, program);
    }
};*/