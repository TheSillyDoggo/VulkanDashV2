#pragma once

#include <Geode/Geode.hpp>
#include <bgfx/bgfx.h>

#define VERTEX_TYPE($type) \
template <> \
bgfx::VertexLayout get<$type>();

typedef struct _ccV2F_T2F
{
    ccVertex2F        vertices;            // 8 bytes
    ccTex2F            texCoords;            // 8 bytes
} ccV2F_T2F;

class VertexLayoutManager
{
    public:
        template <typename T>
        static bgfx::VertexLayout get();

        VERTEX_TYPE(cocos2d::ccV2F_C4B_T2F);
        VERTEX_TYPE(cocos2d::ccV3F_C4B_T2F);        
        VERTEX_TYPE(ccV2F_T2F);        
};