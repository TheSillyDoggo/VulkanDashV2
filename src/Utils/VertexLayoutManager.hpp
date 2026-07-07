#pragma once

#include <Geode/Geode.hpp>
#include <bgfx/bgfx.h>

class VertexLayoutManager
{
    public:
        template <typename T>
        static bgfx::VertexLayout get();
        template <>
        bgfx::VertexLayout get<cocos2d::ccV3F_C4B_T2F>();
};