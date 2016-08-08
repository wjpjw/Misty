#include "Game.h"
#include "cocos2d.h"
#include "StartMenuLayer.h"
#include "BattleLayer.h"
USING_NS_CC;

void wjp::Game::startALayer(Layer * layer)
{
	auto scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

void wjp::Game::startNewBattle()
{
	startALayer(BattleLayer::create());
}

void wjp::Game::startShopping() {
	startALayer(BattleLayer::create());
}

void wjp::Game::backToStartMenu()
{
	startALayer(StartMenuLayer::create());
}

void wjp::Game::startForTheFirstTime()
{
	auto scene = Scene::create();
	scene->addChild(StartMenuLayer::create());
	Director::getInstance()->runWithScene(scene);
}

void wjp::Game::pauseOrResume()
{
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
	}
	else {
		Director::getInstance()->pause();
	}
}
