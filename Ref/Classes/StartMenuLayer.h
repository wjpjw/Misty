#pragma once

#include "cocos2d.h"
#include "Game.h"
namespace wjp {
	class StartMenuLayer : public cocos2d::Layer
	{
		wjp::Game& game;
	public:
		StartMenuLayer() = delete;
		StartMenuLayer(wjp::Game* ctrl) :game(*ctrl) {}
		virtual bool init();
		static StartMenuLayer* create(wjp::Game*game)
		{
			StartMenuLayer *pRet = new(std::nothrow) StartMenuLayer(game);
			if (pRet && pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			else
			{
				delete pRet;
				pRet = nullptr;
				return nullptr;
			}
		}
	};
}
