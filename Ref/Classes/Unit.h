#pragma once
#include "wjp.h"
#include <string>
#include <spine/spine-cocos2dx.h>
using namespace spine;
namespace wjp {
	class ConjurerBattle;
	//static data
	struct UnitMeta {
		std::string									name;
		std::string									description;
		int                                         hp;
		int											attackDamage;
		int                                         attackIntervalMS;
		int                                         moveSpeedPerS;
		int                                         attackRange;            //melee = range <100, requires no arrow
		std::string                                 model;
	};
	enum class UnitOnBoardState {
		stay,         //preparation
		walk,         //battle begins
		fight,        //enemy close
		fall,         //dead
	};
	//The spine animation must implement stay, walk, fight and fall!
	class UnitOnBoard {
		spine::SkeletonAnimation*					skeletonNode;
		bool										isAlive()const { return currentHp <= 0; }
		int                                         currentHp;              //runtime value, inited only after summoned on board
		UnitMeta									unit;
		UnitOnBoard*                                enemy;
		ConjurerBattle&                             battle;
		bool										fromLeftToRight;
		std::string									jsonFileForUnit() { return "models/" + unit.model + ".json"; }
		std::string									atlasFileForUnit() { return "models/" + unit.model + ".atlas"; }
	public:
		UnitOnBoardState							state;
		UnitOnBoard() = delete;
		UnitOnBoard(UnitMeta unit, bool fromLeftToRight, Position position, ConjurerBattle& battle);
		SkeletonAnimation*							getAnimation() { return skeletonNode; }
		void                                        setDirection();
		void 	                                    stay();
		void										walk();
		void										fight();
		void										fall();
		void										moveInOneFrame();
		bool										findEnemyInRange(std::vector<UnitOnBoard*> units);
		bool										findOneEnemyInRange(UnitOnBoard*unit);
	};

}