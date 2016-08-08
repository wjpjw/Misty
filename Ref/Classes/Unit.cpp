#include "Unit.h"
#include "cocos2d.h"
#include "ConjurerBattle.h"
using namespace wjp;
USING_NS_CC;
wjp::UnitOnBoard::UnitOnBoard(UnitMeta unit, bool fromLeftToRight, Position position, ConjurerBattle&battle)
	:unit(unit), fromLeftToRight(fromLeftToRight), state(UnitOnBoardState::stay),enemy(nullptr),battle(battle)
{
	skeletonNode = SkeletonAnimation::createWithFile(jsonFileForUnit(), atlasFileForUnit());
	skeletonNode->setSkin(fromLeftToRight ? "goblingirl" : "goblin");  //To be removed when new models added!!
	skeletonNode->setPosition(position.x, position.y);
	skeletonNode->setName("skeleton name");
	battle.createAnimation(skeletonNode);
	skeletonNode->setScale(0.4f);
	stay();
	setDirection();
}

//x:left -> right
void wjp::UnitOnBoard::setDirection()
{
	if (fromLeftToRight)return;
	skeletonNode->setScaleX(-0.4f); 
}

void wjp::UnitOnBoard::stay()
{
	skeletonNode->setAnimation(0, "walk", true);  //First time
	state = UnitOnBoardState::stay;
	skeletonNode->setTimeScale(0);
}

void wjp::UnitOnBoard::walk()
{
	skeletonNode->setAnimation(0, "walk", true);
	state = UnitOnBoardState::walk;
	skeletonNode->setTimeScale(1);
}

void wjp::UnitOnBoard::moveInOneFrame(){
	if (fromLeftToRight) {
		skeletonNode->setPositionX(skeletonNode->getPositionX() + ((float)unit.moveSpeedPerS / 60));  //Assume it's 60HZ!
	}
	else {
		skeletonNode->setPositionX(skeletonNode->getPositionX() - ((float)unit.moveSpeedPerS / 60));  //Assume it's 60HZ!
	}
}
void wjp::UnitOnBoard::fight()
{
	state = UnitOnBoardState::fight;
	skeletonNode->setTimeScale(1000/((float)unit.attackIntervalMS+200));    //This should be modified!
	skeletonNode->setEndListener([this](int track_index){
		walk(); //Hit once and then walk!
	});
}

void wjp::UnitOnBoard::fall()
{
	skeletonNode->setAnimation(0, "walk", false);
	state = UnitOnBoardState::fall;
}



bool wjp::UnitOnBoard::findEnemyInRange(std::vector<UnitOnBoard*> units)
{
	if (enemy != nullptr) {
		if (findOneEnemyInRange(enemy)) {
			return true;
		}
	}
	for (auto i: units) {
		if (findOneEnemyInRange(i)) {
			return true;
		}
	}
	return false;
}

bool wjp::UnitOnBoard::findOneEnemyInRange(UnitOnBoard * u)
{
	if (skeletonNode == nullptr)return false;
	float x1 = this->skeletonNode->getPositionX();
	float x2 = u->skeletonNode->getPositionX();
	if (abs(x1 - x2)<this->unit.attackRange) {
		enemy = u;
		return true;
	}
	return false;
}
