#pragma once

namespace wjp {
	class BattleLayer;
	class Battle {
		BattleLayer&								layer;
	public:
		Battle() = delete;
		Battle(BattleLayer*layer);
		void										endPreparation();
	};
}