#pragma once

#include <stdint.h>
#include <Geode/cocos/include/ccTypes.h>
#include <Geode/cocos/textures/CCTexture2D.h>

struct kmMat4;

namespace BGFXUtils
{
    void initBGFX(void* nativeHandle, int width, int height);
    kmMat4 getMatrix();
    uint64_t getBlendFunc();
    uint64_t getBlendFunc(cocos2d::ccBlendFunc);
    uint64_t glToBGFXBlend(int gl);
    cocos2d::CCTexture2D* getBlankTex();
};