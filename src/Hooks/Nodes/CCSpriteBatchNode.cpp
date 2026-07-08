#include "CCSpriteBatchNode.hpp"

using namespace geode::prelude;

static CCSpriteBatchNode* lastDrawn = nullptr;

CCSpriteBatchNode* BGFXSpriteBatchNode::getLastBatchNode()
{
    auto l = lastDrawn;
    lastDrawn = nullptr;

    return l;
}

void BGFXSpriteBatchNode::draw()
{
    lastDrawn = this;
    CCSpriteBatchNode::draw();
}