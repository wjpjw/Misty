#pragma once

#include "cocos2d.h"
#include "Game.h"
#include <memory>

USING_NS_CC;
namespace wjp {
	class Battle;
	class BattleLayer : public cocos2d::Layer
	{
		std::unique_ptr<Battle>						battle;
		MenuItemLabel*								preparationEndItem;
		MenuItemLabel*								pauseOrResumeItem;
	public:
		void										showPreparationPhaseUI();
		void										hidePrepatationPhaseUI();
		BattleLayer();
		virtual bool init();
		void update(float delta)override;
		CREATE_FUNC(BattleLayer);
	};
}
