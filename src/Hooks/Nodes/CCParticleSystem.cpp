#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystem.hpp>
#include <bgfx/bgfx.h>
#include "../Utils/VertexLayoutManager.hpp"
#include "../Utils/ShaderCache.hpp"
#include <BGFX.hpp>
#include "../CCTexture2D.hpp"

using namespace geode::prelude;

class $modify (BGFXParticleSystem, CCParticleSystem)
{
    void update(float dt)
    {
        if (CCKeyboardDispatcher::get()->getShiftKeyPressed())
            CCParticleSystem::update(dt);
    }
};