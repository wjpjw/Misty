#pragma once

#include "cocos2d.h"
#include "Game.h"
USING_NS_CC;
namespace wjp {
	class ConjurerBattleLayer : public cocos2d::Layer
	{
		Game&										game;
		ConjurerBattle*								conjurerBattle;
		MenuItemLabel*								preparationEndItem;
		Position									lastTouchedLocation;
		Menu*										menu;
		Menu*										temp_menu;
		Conjurer*                                   player1;
		Conjurer*									player2;
		bool                                        isOnTempMenu;
	public:		
		void										preparationTouch(Touch*touch);
		void										showPreparationPhaseUI();
		void										hidePrepatationPhaseUI();
		ConjurerBattleLayer() = delete;
		ConjurerBattleLayer(Game* g, ConjurerBattle*conjurerBattle);
		virtual bool init();
		void update(float delta)override;
		static ConjurerBattleLayer* create(wjp::Game*game, ConjurerBattle*conjurerBattle)
		{
			ConjurerBattleLayer *pRet = new(std::nothrow) ConjurerBattleLayer(game, conjurerBattle);
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
