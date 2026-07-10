#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>

struct GPUSpriteInstance
{
    cocos2d::ccVertex2F pos;
    cocos2d::ccVertex2F scale;
    cocos2d::ccVertex2F rotation;
    cocos2d::ccVertex2F skew;
};

class $modify (BGFXSpriteBatchNode, cocos2d::CCSpriteBatchNode)
{
    static cocos2d::CCSpriteBatchNode* getLastBatchNode();

    virtual void draw();
};