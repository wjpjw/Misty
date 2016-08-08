#pragma once
#include "cocos2d.h"
USING_NS_CC;
namespace wjp {
	class Game {
		static void									startALayer(Layer*layer);
	public:
		static void									startNewBattle();   
		static void									startShopping();
		static void                                 backToStartMenu();
		static void									startForTheFirstTime();
		static void			                        pauseOrResume();
	};
}