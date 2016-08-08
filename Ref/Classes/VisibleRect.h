#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

namespace VisibleRect
{
    cocos2d::Rect getVisibleRect();
    cocos2d::Vec2 left();
    cocos2d::Vec2 right();
    cocos2d::Vec2 top();
    cocos2d::Vec2 bottom();
    cocos2d::Vec2 center();
    cocos2d::Vec2 leftTop();
    cocos2d::Vec2 rightTop();
    cocos2d::Vec2 leftBottom();
    cocos2d::Vec2 rightBottom();
	cocos2d::Vec2 pos(cocos2d::Vec2 anchor, int x, int y);
};

#endif /* __VISIBLERECT_H__ */
