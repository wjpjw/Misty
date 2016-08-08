#pragma once
#include <vector>
#include <memory>
#include "wjp.h"

namespace wjp {
	class Skill;
	class UnitOnBoard;
	class ConjurerBattle;
	class Conjurer {
		std::vector<std::unique_ptr<UnitOnBoard>>	unitsOnBoard;           //actual unit objects
		int                                         currentMana;
		int											totalMana;
		int                                         manaRegen;
		ConjurerBattle&                             battle;
	public:
		std::vector<std::unique_ptr<Skill>>			availableSkills;        //will be inited
		std::vector<std::string>				    availableUnitNames;     //will be inited
		Conjurer() = delete;
		Conjurer(ConjurerBattle*b);
		std::vector<UnitOnBoard*>					myUnitsOnBoard();
		void										preparationEnded();
		void										updateUnitsOnBoard();
		bool										isBoardClear()const { return unitsOnBoard.empty(); }
		void                                        loadInitialAvailableSkillsAndUnits();   //load from init.xml
		void                                        summonUnitOnBoard(Position p, std::string unit_name);
		void										useSkill(Skill&skill);
		void										randomlyUpdateUnitPool(); //availableUnitNames is reassigned randomly
		UnitOnBoard*								findARandomLivingUnit();
		void										printState()const;
	};
}
