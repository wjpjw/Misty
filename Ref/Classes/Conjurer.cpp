#include "tinyxml2\tinyxml2.h"
#include "Unit.h"
#include "ConjurerBattle.h"
using namespace wjp;

wjp::Conjurer::Conjurer(ConjurerBattle*b) :currentMana(100), totalMana(300), manaRegen(100), battle(*b){
	try {
		loadInitialAvailableSkillsAndUnits();
	}
	catch (const std::exception& e) {
		e.what();
		throw e;
	}
	catch (...) {
		throw "Conjurer() failed";
	}
}

std::vector<UnitOnBoard*> wjp::Conjurer::myUnitsOnBoard()
{
	std::vector<UnitOnBoard*> sss;
	for (auto&i : unitsOnBoard) {
		sss.push_back(i.get());
	}
	return sss;
}

void wjp::Conjurer::preparationEnded()
{
	battle.runtimeState = ConjurerBattleRuntimeState::BattlePhase;
	for (auto&i : unitsOnBoard) {
		i->walk();
	}
}

void wjp::Conjurer::updateUnitsOnBoard()
{
	Conjurer& enemyConjurer = battle.opponent(this);
	std::vector<UnitOnBoard*> enemies=enemyConjurer.myUnitsOnBoard();
	for (auto&i : unitsOnBoard) {
		UnitOnBoardState s=i->state;
		switch (s) {
		case UnitOnBoardState::fall:  //do nothing!
			break;
		case UnitOnBoardState::fight: //do nothing! Just wait until the fight animation ends and then it will walk again!
			break;
		case UnitOnBoardState::stay:  //do nothing!
			break;
		case UnitOnBoardState::walk:  //find enemy and fight, ow, walk forward
			if (i->findEnemyInRange(enemies)) {
				i->fight();
			}
			else {
				i->moveInOneFrame();
			}
			break;
		}
	}
}

void wjp::Conjurer::printState() const {
	CCLOG("Conjurer printState:");
	for (auto& i : availableSkills) {
		CCLOG(i.get()->name.c_str());
	}
	for (auto& i : availableUnitNames) {
		CCLOG(i.c_str());
	}
}

void wjp::Conjurer::loadInitialAvailableSkillsAndUnits()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("data/init.xml");
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError errorId = doc.LoadFile(filePath.c_str());
	if (errorId != 0)throw FileException();
	tinyxml2::XMLElement *initUnits = doc.RootElement()->FirstChildElement("initUnits");
	for (tinyxml2::XMLElement *unitName = initUnits->FirstChildElement("unitName");
		unitName != nullptr; unitName = unitName->NextSiblingElement()) {
		availableUnitNames.push_back(unitName->GetText());
	}
	tinyxml2::XMLElement *initSkills = initUnits->NextSiblingElement();
	for (tinyxml2::XMLElement *skillName = initUnits->FirstChildElement("skillName");
		skillName != nullptr; skillName = skillName->NextSiblingElement()) {
		Skill& t = battle.getSkill(skillName->GetText());
		availableSkills.push_back(std::make_unique<Skill>(t));
	}
}



void wjp::Conjurer::summonUnitOnBoard(Position p, std::string unit_name)
{
	unitsOnBoard.push_back(std::make_unique<UnitOnBoard>(battle.getUnit(unit_name),
													 (this == battle.getPlayer1()), 
		                                                                         p, 
		                                                                    battle));
}

void wjp::Conjurer::useSkill(Skill & skill)
{
	//TBD
	if (currentMana < skill.manaCost)return;
	currentMana -= skill.manaCost;
	if ("Fire Flame" == skill.name) {
		for (auto&i : skill.targetUnits) {
			battle.createArrow(i, [](UnitOnBoard*u) {
				//TBD
			});
		}
	}

	if ("Heal" == skill.name) {
		for (auto&i : skill.targetUnits) {
			battle.createArrow(i, [](UnitOnBoard*u) {
				//TBD
			});
		}
	}
	//...
	skill.targetUnits.clear();
}





void wjp::Conjurer::randomlyUpdateUnitPool()
{
	//do it later
}

wjp::UnitOnBoard* wjp::Conjurer::findARandomLivingUnit()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, unitsOnBoard.size() - 1);
	return unitsOnBoard[dist(mt)].get();
}