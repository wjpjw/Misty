#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>
#include "Conjurer.h"
#include "cocos2d.h"
#include "Unit.h"
USING_NS_CC;
namespace wjp {
	class ConjurerBattleLayer;
	struct UnitMeta;
	class UnitOnBoard;
	class ConjurerBattle;
	//projectiles
	struct Arrow {
		Arrow(std::function<void(UnitOnBoard*)> func, UnitOnBoard* targetUnit) :
			onHitFunction(func), targetUnit(targetUnit) {}
		std::function<void(UnitOnBoard*)>			onHitFunction;
		UnitOnBoard*								targetUnit;
	};

	//to be done!
	struct Skill{
		int											manaCost;
		int											coolDownMS;			   //1 cycle of 60HZ is about 17MS.
		std::string									name;
		std::string									description;
		std::vector<UnitOnBoard*>                   targetUnits;           //runtime value, it could be none, one unit or many.
	};
	enum class ConjurerBattleRuntimeState {
		PreparationPhase,  // 
		BattlePhase,       // 
		WinOrLosePhase,    //Show Win/Lose Screen
	};
	class ConjurerBattle
	{
		Conjurer									player1;
		Conjurer									player2;
		std::unordered_map<std::string, UnitMeta>   metaUnits;				//meta objects hold in memory unit data.  
		std::unordered_map<std::string, Skill>		metaSkills;
		void										loadMetaUnits();
		void										loadMetaSkills();
		std::vector<std::unique_ptr<Arrow>>         arrows;
		ConjurerBattleLayer*						currentLayer;
	public:
		ConjurerBattleRuntimeState                  runtimeState;
		ConjurerBattle();
		bool                                        isBoardClear()const{
			return player1.isBoardClear() && player2.isBoardClear();
		}
		void										preparationEnded() {
			runtimeState = ConjurerBattleRuntimeState::BattlePhase;
			player1.preparationEnded();
			player2.preparationEnded(); //player2 is AI.
		}
		void                                        createArrow(UnitOnBoard* targetUnit,
																std::function<void(UnitOnBoard*)> onHitFunction){
			arrows.push_back(std::make_unique<Arrow>(onHitFunction, targetUnit));
		}
		void										setCurrentLayer(ConjurerBattleLayer*c) { currentLayer = c; }
		void										updateEverything();
		ConjurerBattleLayer*						getCurrentLayer() { return currentLayer; }
		Conjurer*                                   getPlayer1() { return &player1; }
		Conjurer*									getPlayer2() { return &player2; }
		Conjurer&									opponent(Conjurer*me) { return me == &player1 ? player2 : player1; }
		UnitMeta&									getUnit(const std::string& name) { 
			return metaUnits[name]; 
		}
		Skill&										getSkill(const std::string& name){ return metaSkills[name]; }
		UnitOnBoard*								findARandomLivingUnitOfMyEnemy(Conjurer*me);
		void										updateArrows();//TBD
		void										printState()const;
		void                                        createAnimation(SkeletonAnimation*animation);
	};

}
