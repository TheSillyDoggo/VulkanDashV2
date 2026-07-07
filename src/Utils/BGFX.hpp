#pragma once

struct kmMat4;

namespace BGFXUtils
{
    void initBGFX(void* nativeHandle, int width, int height);
    kmMat4 getMatrix();
};