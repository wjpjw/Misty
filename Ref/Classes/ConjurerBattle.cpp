#include "ConjurerBattle.h"
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include <random>
#include <functional>
#include "wjp.h"
#include "spine/spine.h"
#include "ConjurerBattleLayer.h"
#include "Unit.h"

USING_NS_CC;
using namespace wjp;
wjp::ConjurerBattle::ConjurerBattle() : player1(this),player2(this),
						runtimeState(ConjurerBattleRuntimeState::PreparationPhase), currentLayer(nullptr)
{
	try
	{
		loadMetaUnits();
		loadMetaSkills();
	}
	catch (const std::exception& e)
	{
		e.what();
		throw e;
	}
	catch (...) {
		throw "ConjurerBattle() failed.";
	}
#ifdef WJP_DEBUG_ON
	printState();
#endif
}

void wjp::ConjurerBattle::updateEverything()
{
	player1.updateUnitsOnBoard();
	player2.updateUnitsOnBoard();
	updateArrows();
}

UnitOnBoard* wjp::ConjurerBattle::findARandomLivingUnitOfMyEnemy(Conjurer* me)
{
	return this->opponent(me).findARandomLivingUnit();
}

void wjp::ConjurerBattle::updateArrows()
{


}

void wjp::ConjurerBattle::printState()const
{
	CCLOG("ConjurerBattle printState");
	for (auto&i : metaUnits) {
		CCLOG("%s:%s  HP:%d", i.first.c_str(),i.second.description.c_str(),i.second.hp);
	}
	for (auto&i : metaSkills) {
		CCLOG("%s:%s  CD:%d(ms)", i.first.c_str(), i.second.description.c_str(), i.second.coolDownMS);
	}
	player1.printState();
}

void wjp::ConjurerBattle::createAnimation(SkeletonAnimation * animation)
{
	currentLayer->addChild(animation);
	currentLayer->scheduleUpdate();
}

void wjp::ConjurerBattle::loadMetaSkills()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("data/skills.xml");
	CCLOG("fullpath:%s",filePath.c_str());
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError errorId = doc.LoadFile(filePath.c_str());
	if (errorId != 0)throw FileException();
	auto creeate_skill_from_xml_element = [&](tinyxml2::XMLElement* element) {
		Skill t;
		element = element->FirstChildElement("name");
		t.name = element->GetText();
		element = element->NextSiblingElement();
		t.description = element->GetText();
		element = element->NextSiblingElement();
		t.manaCost = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.coolDownMS = std::stoi(element->GetText());
		metaSkills.insert({ t.name, t });
	};
	for (tinyxml2::XMLElement *skill = doc.RootElement()->FirstChildElement("skill");
		skill != nullptr; skill = skill->NextSiblingElement()) {
		creeate_skill_from_xml_element(skill);
	}
}

void wjp::ConjurerBattle::loadMetaUnits()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("data/units.xml");
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError errorId = doc.LoadFile(filePath.c_str());
	if (errorId != 0) throw FileException();
	auto creeate_unit_from_xml_element = [&](tinyxml2::XMLElement* element) {
		UnitMeta t;
		element = element->FirstChildElement("name");
		t.name = element->GetText();
		element = element->NextSiblingElement();
		t.description= element->GetText();
		element = element->NextSiblingElement();
		t.hp = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.attackDamage = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.attackIntervalMS = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.moveSpeedPerS = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.attackRange = std::stoi(element->GetText());
		element = element->NextSiblingElement();
		t.model = element->GetText();
		metaUnits.insert({ t.name, t });
	};
	for (tinyxml2::XMLElement *unit = doc.RootElement()->FirstChildElement("unit");
		unit != nullptr; unit = unit->NextSiblingElement()) {
		creeate_unit_from_xml_element(unit);
	}
}



