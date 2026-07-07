#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"

using namespace geode::prelude;

kmMat4 getNodeToWorldTransform()
{
    kmMat4 model;
    kmGLGetMatrix(KM_GL_MODELVIEW, &model);

    kmMat4 formatted;
    kmMat4Transpose(&formatted, &model);

    return formatted;
}

class $modify (BGFXSprite, CCSprite)
{
    struct Fields
    {
        bgfx::VertexBufferHandle vbh;
        bgfx::IndexBufferHandle ibh;
    };

    virtual bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
    {
        static cocos2d::ccV3F_C4B_T2F vertices[] = {
            {{0, 1, 0.0f}, ccc4(255, 0, 0, 255), {0, 0}},
            {{1, 1, 0.0f}, ccc4(0, 255, 0, 255), {0, 0}},
            {{0, 0, 0.0f}, ccc4(0, 0, 255, 255), {0, 0}},
            {{1, 0, 0.0f}, ccc4(0, 0, 0, 255), {0, 0}},
        };

        static const uint16_t indices[] = {
            0, 1, 2,
            1, 3, 2
        };

        m_fields->vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        m_fields->ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));

        return CCSprite::initWithTexture(pTexture, rect);
    }

    void draw()
    {
        kmMat4 mat = getNodeToWorldTransform();
        
        bgfx::setTransform(mat.mat);

        bgfx::setVertexBuffer(0, m_fields->vbh);
        bgfx::setIndexBuffer(m_fields->ibh);

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};