#include "BattleLayer.h"
#include "Battle.h"
#include "VisibleRect.h"
#include "WuJipeng.h"
using namespace VisibleRect;
wjp::BattleLayer::BattleLayer():battle(std::make_unique<Battle>(this)),preparationEndItem(nullptr),pauseOrResumeItem(nullptr)
{
}

bool wjp::BattleLayer::init()
{
	if (!Layer::init())  return false;

	auto bg_sprite = Sprite::create("images/desert.jpg");
	bg_sprite->setPosition(center());
	bg_sprite->setScale(1.2);
	this->addChild(bg_sprite);
	///game menu
	auto close_label = Label::createWithTTF("Quit", font1(), 20);
	auto close_item = MenuItemLabel::create(close_label, [&](Ref* sender){Game::backToStartMenu();});
	close_item->setPosition(pos(rightTop(), -30, -20));

	auto shop_label = Label::createWithTTF("Shop", font1(), 20);
	auto shop_item = MenuItemLabel::create(shop_label, [&](Ref* sender){Game::startShopping();});
	shop_item->setPosition(pos(rightTop(), -110, -20));

	auto pause_label = Label::createWithTTF("Pause", font1(), 20);
	pauseOrResumeItem = MenuItemLabel::create(pause_label, [&](Ref* sender){Game::pauseOrResume();});
	pauseOrResumeItem->setPosition(pos(rightTop(), -190, -20));

	auto preparation_end_label = Label::createWithTTF("Go!", font1(), 20);
	preparationEndItem = MenuItemLabel::create(preparation_end_label, [&](Ref* sender) {
		battle->endPreparation();
		hidePrepatationPhaseUI();
	});
	preparationEndItem->setPosition(pos(rightTop(), -270, -20));

	auto menu = Menu::create(close_item, pauseOrResumeItem, shop_item, preparationEndItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void wjp::BattleLayer::update(float delta)
{
}

void wjp::BattleLayer::showPreparationPhaseUI()
{
	preparationEndItem->setVisible(true);
}

void wjp::BattleLayer::hidePrepatationPhaseUI()
{
	preparationEndItem->setVisible(false);
}