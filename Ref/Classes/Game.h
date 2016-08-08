#pragma once

#include "ConjurerBattle.h"

namespace wjp {
	class Game {
		ConjurerBattle                              conjurerBattle;
	public:
		void                                        startShopping();
		void                                        startNewGame();
		void                                        backToStartMenu();
		void										startForTheFirstTime();
		void                                        pause();
	};
}