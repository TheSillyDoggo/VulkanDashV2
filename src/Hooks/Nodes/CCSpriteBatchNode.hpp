#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>

class $modify (BGFXSpriteBatchNode, cocos2d::CCSpriteBatchNode)
{
    static cocos2d::CCSpriteBatchNode* getLastBatchNode();

    virtual void draw();
};