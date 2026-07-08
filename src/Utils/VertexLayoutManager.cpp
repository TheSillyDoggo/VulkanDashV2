#include "VertexLayoutManager.hpp"

#define VERTEX_TYPE_CPP($type) \
template <> \
bgfx::VertexLayout VertexLayoutManager::get<$type>()

template <typename T>
bgfx::VertexLayout VertexLayoutManager::get()
{
    return {};
}

VERTEX_TYPE_CPP(cocos2d::ccV3F_C4B_T2F)
{
    static bgfx::VertexLayout layout = []{
        bgfx::VertexLayout layout;
            layout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();

        return layout;
    }();

    return layout;
}