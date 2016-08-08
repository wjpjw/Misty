#include "VisibleRect.h"
#include "Conjurer.h"
#include "ConjurerBattleLayer.h"
USING_NS_CC;
using namespace wjp;
using namespace VisibleRect;

wjp::ConjurerBattleLayer::ConjurerBattleLayer(wjp::Game* g, wjp::ConjurerBattle*conjurerBattle) :
	game(*g), conjurerBattle(conjurerBattle),preparationEndItem(nullptr), lastTouchedLocation(Position(20)), 
	temp_menu(nullptr),menu(nullptr), player1(conjurerBattle->getPlayer1()),player2(conjurerBattle->getPlayer2()),
	isOnTempMenu(false){}



void wjp::ConjurerBattleLayer::showPreparationPhaseUI()
{
	preparationEndItem->setVisible(true);
}

void wjp::ConjurerBattleLayer::hidePrepatationPhaseUI()
{
	preparationEndItem->setVisible(false);
}

bool wjp::ConjurerBattleLayer::init()
{
	if (!Layer::init())  return false;
	conjurerBattle->setCurrentLayer(this);  //Bind These two classes!
	///background image
	auto bg_sprite = Sprite::create("images/desert.jpg");
	bg_sprite->setPosition(center());
	this->addChild(bg_sprite);
	///game menu
	auto close_label = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 20);
	auto close_item = MenuItemLabel::create(close_label, [&](Ref* sender) {
		game.backToStartMenu();
	});
	close_item->setPosition(pos(rightTop(), -30, -20));

	auto shop_label = Label::createWithTTF("Shop", "fonts/Marker Felt.ttf", 20);

	auto shop_item = MenuItemLabel::create(shop_label, [&](Ref* sender) {
		game.startShopping();
	});
	shop_item->setPosition(pos(rightTop(), -110, -20));

	auto pause_label = Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 20);
	auto pause_item = MenuItemLabel::create(pause_label, [&](Ref* sender) {
		game.pause();
	});
	pause_item->setPosition(pos(rightTop(), -190, -20));

	auto preparation_end_label = Label::createWithTTF("Go!", "fonts/Marker Felt.ttf", 20);
	preparationEndItem = MenuItemLabel::create(preparation_end_label, [&](Ref* sender) {
		conjurerBattle->preparationEnded();
		hidePrepatationPhaseUI();
	});
	preparationEndItem->setPosition(pos(rightTop(), -270, -20));

	menu = Menu::create(close_item, pause_item, shop_item, preparationEndItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	player2->summonUnitOnBoard(Position(900),"Goblin Worrior");
	player2->summonUnitOnBoard(Position(900,100), "Goblin Worrior");

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool{
		switch (conjurerBattle->runtimeState) {
		case ConjurerBattleRuntimeState::PreparationPhase:
			preparationTouch(touch);
			break;
		case ConjurerBattleRuntimeState::BattlePhase:
			break;
		case ConjurerBattleRuntimeState::WinOrLosePhase:
			break;
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void wjp::ConjurerBattleLayer::preparationTouch(Touch*touch)
{
	if (isOnTempMenu) {
		if (touch->getLocation().getDistance(Vec2((float)lastTouchedLocation.x, (float)lastTouchedLocation.y))<100) {
			return; 
		}
		else {
			this->removeChild(temp_menu);
		}
	}
	CCLOG("Touch Screen: something should pop up");
	lastTouchedLocation.x = touch->getLocation().x;
	lastTouchedLocation.y = touch->getLocation().y;
	int x_offset = -20;
	int y_offset = -20;
	temp_menu = Menu::create();
	temp_menu->setPosition(Vec2::ZERO);
	for (auto&i : player1->availableUnitNames) {
		auto label = Label::createWithTTF(i, "fonts/Marker Felt.ttf", 20);
		auto item = MenuItemLabel::create(label, [&](Ref*sender) {
			player1->summonUnitOnBoard(lastTouchedLocation, i);
			temp_menu->setVisible(false);  
			this->removeChild(temp_menu);
			isOnTempMenu = false;
		});
		item->setPosition(pos(touch->getLocation(), x_offset, y_offset));
		temp_menu->addChild(item);
		y_offset += 30;
	}
	temp_menu->setPosition(Vec2::ZERO);
	this->addChild(temp_menu);
	isOnTempMenu = true;
}

//display units
void wjp::ConjurerBattleLayer::update(float delta)
{
	Layer::update(delta); //Layer is the super class.
	conjurerBattle->updateEverything();
}


