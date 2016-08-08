#include "StartMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "WuJipeng.h"
USING_NS_CC;
using namespace wjp;
using namespace VisibleRect;

bool StartMenuLayer::init()
{
	if (!Layer::init())  return false;
	///background image
	auto bg_sprite = Sprite::create("images/tower.jpg");
	bg_sprite->setPosition(center());
	bg_sprite->setScale(2);
	this->addChild(bg_sprite);
	///title
	auto label = Label::createWithTTF("Conjurer War Alpha 1.0: Misty Realm", font5(), 64);

	label->setPosition(pos(top(), 0, -label->getContentSize().height));
	this->addChild(label);
	///game menu
	auto close_label = Label::createWithTTF("Quit", font1(), 44);
	auto closeItem = MenuItemLabel::create(close_label, [&](Ref* sender){
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	});
	closeItem->setPosition(pos(center(), 0, -120));

	auto shop_label = Label::createWithTTF("Shop", font1(), 44);

	auto shopItem = MenuItemLabel::create(shop_label, [&](Ref* sender) {
		Game::startShopping();
	});
	shopItem->setPosition(pos(center(), 0, -20));

	auto start_label = Label::createWithTTF("Start", font1(), 44);
	auto startItem = MenuItemLabel::create(start_label, [&](Ref* sender) {
		Game::startNewBattle();
	});
	startItem->setPosition(pos(center(), 0, 80));

	auto menu = Menu::create(closeItem, startItem, shopItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}
