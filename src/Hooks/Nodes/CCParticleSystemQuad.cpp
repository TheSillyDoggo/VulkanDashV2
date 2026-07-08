#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"

using namespace geode::prelude;

class $modify (BGFXParticleSystemQuad, CCParticleSystemQuad)
{
    struct Fields
    {
        bgfx::IndexBufferHandle ibh = {bgfx::kInvalidHandle};

        ~Fields()
        {
            if (bgfx::isValid(ibh))
                bgfx::destroy(ibh);
        }
    };

    void setupIndices()
    {
        auto fields = m_fields.self();

        if (bgfx::isValid(fields->ibh))
            bgfx::destroy(fields->ibh);

        fields->ibh = bgfx::createIndexBuffer(bgfx::copy(m_pIndices, m_uTotalParticles * 6 * sizeof(GLushort)));
    }

    virtual void setTotalParticles(unsigned int tp)
    {
        bool ri = tp > m_uAllocatedParticles;

        CCParticleSystemQuad::setTotalParticles(tp);

        if (ri)
            setupIndices();
    }

    virtual void setBatchNode(CCParticleBatchNode* batchNode)
    {
        bool ri = (batchNode != m_pBatchNode) && batchNode;

        CCParticleSystemQuad::setBatchNode(batchNode);

        if (ri)
            setupIndices();
    }

    virtual bool initWithTotalParticles(unsigned int numberOfParticles, bool unk)
    {
        if (!CCParticleSystemQuad::initWithTotalParticles(numberOfParticles, unk))
            return false;

        setupIndices();
        return true;
    }

    virtual void draw()
    {
        kmMat4 mat = BGFXUtils::getMatrix();
        
        bgfx::setTransform(mat.mat);

        bgfx::TransientVertexBuffer tvb;
        bgfx::allocTransientVertexBuffer(&tvb, m_uParticleCount * 4, VertexLayoutManager::get<cocos2d::ccV3F_C4B_T2F>());
        memcpy(tvb.data, m_pQuads, m_uParticleCount * 4 * sizeof(ccV3F_C4B_T2F));

        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(m_fields->ibh, 0, m_uParticleCount * 6);
        static_cast<BGFXTexture2D*>(m_pTexture)->bind();

        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_tBlendFunc));

        bgfx::submit(0, ShaderCache::get("sprite.vs.sc", "sprite.fs.sc"));
    }
};