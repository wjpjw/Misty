#include "Game.h"
#include "StartMenuLayer.h"
#include "ConjurerBattleLayer.h"
USING_NS_CC;

void wjp::Game::startShopping()
{
}

void wjp::Game::startNewGame()
{
	auto scene = Scene::create();
	scene->addChild(ConjurerBattleLayer::create(this,&conjurerBattle));
	Director::getInstance()->replaceScene(scene);
}

void wjp::Game::backToStartMenu()
{
	auto scene = Scene::create();
	scene->addChild(StartMenuLayer::create(this));
	Director::getInstance()->replaceScene(scene);
}

void wjp::Game::startForTheFirstTime()
{
	auto scene = Scene::create();
	scene->addChild(StartMenuLayer::create(this));
	Director::getInstance()->runWithScene(scene);
}

void wjp::Game::pause()
{
	Director::getInstance()->pause();
}
