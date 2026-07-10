#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"

struct GPUParticleInstance
{
    cocos2d::ccVertex2F pos;
    float rotation, size;
    cocos2d::ccColor4F colour;
};

class $modify (BGFXParticleSystemQuad, cocos2d::CCParticleSystemQuad)
{
    struct Fields
    {
        bgfx::VertexBufferHandle vbh = {bgfx::kInvalidHandle};
        std::vector<GPUParticleInstance> instances;

        ~Fields()
        {
            if (bgfx::isValid(vbh))
                bgfx::destroy(vbh);
        }
    };

    // Hooks
    bool initWithTotalParticles(unsigned int numberOfParticles, bool unk);
    void initTexCoordsWithRect(const cocos2d::CCRect& rect);
    void setTotalParticles(unsigned int tp);
    void updateQuadWithParticle(cocos2d::tCCParticle* particle, const cocos2d::CCPoint& newPosition);
    void draw();

    float lerp(float from, float to, float t);
    ccV2F_T2F createVertex(cocos2d::CCPoint point);
    void updateVertex();
};