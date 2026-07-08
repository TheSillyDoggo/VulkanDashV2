#pragma once

#include <Geode/Geode.hpp>
#include <bgfx/bgfx.h>

#define VERTEX_TYPE($type) \
template <> \
bgfx::VertexLayout get<$type>();

class VertexLayoutManager
{
    public:
        template <typename T>
        static bgfx::VertexLayout get();

        VERTEX_TYPE(cocos2d::ccV3F_C4B_T2F);
};