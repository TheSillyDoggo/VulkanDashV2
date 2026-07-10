#include "CCParticleSystemQuad.hpp"
using namespace geode::prelude;

bgfx::IndexBufferHandle getIbh3()
{
    static uint16_t indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    static bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(indices)));
    return ibh;
}

float BGFXParticleSystemQuad::lerp(float from, float to, float t)
{
    return from + t * (to - from);
}

ccV2F_T2F BGFXParticleSystemQuad::createVertex(cocos2d::CCPoint point)
{
    auto pointRect = m_tTextureRect;

    CCRect rect = CCRectMake(
        pointRect.origin.x * CC_CONTENT_SCALE_FACTOR(),
        pointRect.origin.y * CC_CONTENT_SCALE_FACTOR(),
        pointRect.size.width * CC_CONTENT_SCALE_FACTOR(),
        pointRect.size.height * CC_CONTENT_SCALE_FACTOR());

    float wide = (float) pointRect.size.width;
    float high = (float) pointRect.size.height;

    if (m_pTexture)
    {
        wide = (float)m_pTexture->getPixelsWide();
        high = (float)m_pTexture->getPixelsHigh();
    }

    float left = rect.origin.x / wide;
    float bottom = rect.origin.y / high;
    float right = left + rect.size.width / wide;
    float top = bottom + rect.size.height / high;

    return ccV2F_T2F(
        {lerp(-0.75f, 0.75f, point.x), lerp(-0.75f, 0.75f, point.y)},
        {lerp(left, right, point.x), lerp(top, bottom, point.y) }
    );
}

void BGFXParticleSystemQuad::updateVertex()
{
    log::warn("update vertex called");

    auto fields = m_fields.self();

    if (bgfx::isValid(fields->vbh))
        bgfx::destroy(fields->vbh);

    ccV2F_T2F verts[4];

    verts[0] = createVertex(ccp(0, 1));
    verts[1] = createVertex(ccp(1, 1));
    verts[2] = createVertex(ccp(0, 0));
    verts[3] = createVertex(ccp(1, 0));

    fields->vbh = bgfx::createVertexBuffer(bgfx::copy(verts, sizeof(verts)), VertexLayoutManager::get<ccV2F_T2F>());
}

void BGFXParticleSystemQuad::initTexCoordsWithRect(const CCRect& rect)
{
    m_tTextureRect = rect;
    updateVertex();
}

void BGFXParticleSystemQuad::setTotalParticles(unsigned int tp)
{
    CCParticleSystemQuad::setTotalParticles(tp);

    m_fields->instances.resize(tp);
}

bool BGFXParticleSystemQuad::initWithTotalParticles(unsigned int numberOfParticles, bool unk)
{
    if (!CCParticleSystemQuad::initWithTotalParticles(numberOfParticles, unk))
        return false;

    m_fields->instances.resize(numberOfParticles);
    updateVertex();
    return true;
}

void BGFXParticleSystemQuad::updateQuadWithParticle(tCCParticle* particle, const CCPoint& newPosition)
{
    auto& instance = m_fields.self()->instances[CCParticleSystem::m_uParticleIdx];

    instance.pos.x = newPosition.x;
    instance.pos.y = newPosition.y;
    instance.rotation = particle->rotation;
    instance.size = particle->size;

    float opacity = (float)m_uOpacity;
    float alpha = opacity * particle->color.a;
    float y = particle->modeA.dir.y;
    float fadeVar = particle->modeA.radialAccel;

    if (fadeVar > y || (y = particle->timeToLive, fadeVar = particle->modeA.tangentialAccel, fadeVar > y))
    {
        if (m_bOpacityModifyRGB)
            alpha *= y / fadeVar;
        else
            opacity *= y / fadeVar;
    }

    if (m_bOpacityModifyRGB)
    {
        m_tQuadColor.r = (GLubyte)(alpha * particle->color.r);
        m_tQuadColor.g = (GLubyte)(alpha * particle->color.g);
        m_tQuadColor.b = (GLubyte)(alpha * particle->color.b);
        m_tQuadColor.a = (GLubyte)alpha;
    }
    else
    {
        m_tQuadColor.r = (GLubyte)(opacity * particle->color.r);
        m_tQuadColor.g = (GLubyte)(opacity * particle->color.g);
        m_tQuadColor.b = (GLubyte)(opacity * particle->color.b);
        m_tQuadColor.a = (GLubyte)(opacity * particle->color.a);
    }

    instance.colour = ccc4FFromccc4B(m_tQuadColor);
}

void BGFXParticleSystemQuad::draw()
{
    if (m_uParticleCount == 0)
        return;

    auto fields = m_fields.self();

    kmMat4 mat = BGFXUtils::getMatrix();
    bgfx::setTransform(mat.mat);

    
    auto ret = bgfx::getAvailInstanceDataBuffer(m_uParticleCount, sizeof(GPUParticleInstance));
    if (ret < m_uParticleCount)
    {
        log::error("instance count bigger: {} < {}", ret, m_uParticleCount);
        return; 
    }

    bgfx::InstanceDataBuffer idb;
    bgfx::allocInstanceDataBuffer(&idb, m_uParticleCount, sizeof(GPUParticleInstance));
    std::memcpy(idb.data, fields->instances.data(), m_uParticleCount * sizeof(GPUParticleInstance));

    bgfx::setVertexBuffer(0, fields->vbh);
    bgfx::setIndexBuffer(getIbh3());

    bgfx::setInstanceDataBuffer(&idb);

    static_cast<BGFXTexture2D*>(m_pTexture)->bind();

    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFXUtils::getBlendFunc(m_tBlendFunc));

    bgfx::submit(0, ShaderCache::get("particle.vs.sc", "particle.fs.sc"));
}