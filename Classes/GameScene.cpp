// Copyright Ole Herman Schumacher Elgesem
// github.com/olehermanse

#include "GameScene.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setSpeed(5.0);
	
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	srand (time(NULL));
	
	auto bg = cocos2d::LayerColor::create(cocos2d::Color4B(255,255,255,255));
	addChild(bg);
	
	level = 1;
	difficulty = 4;
	
	// add "Helloworld" splash screen"
	cluster = new NumberVisualizer(1280/2,710, 350, "res/rpgitems.png", 4, 4, 16);
	clusterA = new NumberVisualizer(1280/2-200,710, 350, "res/rpgitems.png", 4, 4, 16);
	clusterB = new NumberVisualizer(1280/2+200,710, 350, "res/rpgitems.png", 4, 4, 16);
	
	this->addChild(cluster);
	this->addChild(clusterA);
	this->addChild(clusterB);
	
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto body = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(cocos2d::Vec2(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	
	newTask();
	
	btnSize = 90;
	int margins = 20.0f;
	int gap = 1280 - margins - btnSize*12;
	btnHeight = btnSize+margins;
	for(int i = 1; i < 13; i++){
		auto btn = cocos2d::ui::Button::create();
		btn->setActionTag(i);
		std::stringstream ss;
		if(i == 10){
			ss << 0;
			btn->setActionTag(0);
		}else if(i == 11)
			ss << '<';
		else if(i == 12)
			ss << '>';
		else
			ss << i;
		btn->setTitleText(ss.str().c_str());
		btn->setTitleFontSize(64);
		btn->setColor(cocos2d::Color3B(0,0,0));
		btn->ignoreContentAdaptWithSize(false);
		btn->setContentSize(cocos2d::Size(btnSize,btnSize));
		int x = (i-1.0)*btnSize + margins;
		int y = margins;
		if(i > 6){
			x += gap;
		}
		btn->setPosition(Vec2(x,y));
		btn->setTitleColor(Color3B(255,255,255));
		btn->setTouchEnabled(true);
		//btn->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
		btn->setAnchorPoint(Vec2(0.0,0.0));
		
		btn->addTouchEventListener( CC_CALLBACK_2(GameScene::clickEvent, this) );
		addChild(btn);
	}
	
	mainLabel = cocos2d::Label::createWithSystemFont("","Arial",100);
	mainLabel->setPosition(this->getBoundingBox().getMidX(),this->getBoundingBox().getMinY()+btnHeight);
	mainLabel->setAnchorPoint(cocos2d::Vec2(0.5,0.0));
	mainLabel->setTextColor(cocos2d::Color4B(0,0,0,255));
	addChild(mainLabel);
	levelLabel = cocos2d::Label::createWithSystemFont("","Arial",64);
	levelLabel->setPosition(this->getBoundingBox().getMaxX(),this->getBoundingBox().getMaxY());
	levelLabel->setAnchorPoint(cocos2d::Vec2(1.0,1.0));
	levelLabel->setTextColor(cocos2d::Color4B(0,0,0,255));
	addChild(levelLabel);
	
	//Director::getInstance()->getOpenGLView().setIMEKeyboardState(true);
	
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(false);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		int num = int(keyCode) - int(EventKeyboard::KeyCode::KEY_0);
		if(num >= 0 && num <= 9){
			pressNumber(num);
		}else if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE){
			pressBackspace();
		}else if(keyCode == EventKeyboard::KeyCode::KEY_ENTER){
			pressEnter();
		}else if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
			exit(0);
		}
	};
	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
	
	// Let cocos know we have an update function to be called.
	// No worries, ill cover this in more detail later on
	this->scheduleUpdate();
	return true;
}

void GameScene::clickEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eventType){
	if (cocos2d::ui::Widget::TouchEventType::ENDED == eventType) {
		int tag = ((cocos2d::ui::Button*) pSender)->getActionTag();
		if(tag < 10){
			pressNumber(tag);
		}else if(tag == 11){
			pressBackspace();
		}else if(tag == 12){
			pressEnter();
		}
	}
}

int GameScene::correctAnswer(){
	switch (op) {
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
	}
	return 0;
}

int GameScene::userAnswer(){
	return std::atoi(userInput.c_str());
}

void GameScene::pressBackspace(){
	if(userInput.length() > 0){
		userInput.pop_back();
	}
}

void GameScene::addHistory(){
	auto tmpLabel = cocos2d::Label::createWithSystemFont(currentString().c_str(),"Arial",100);
	tmpLabel->setPosition(this->getBoundingBox().getMidX(),this->getBoundingBox().getMinY()+btnHeight);
	tmpLabel->setAnchorPoint(cocos2d::Vec2(0.5,0.0));
	tmpLabel->setTextColor(cocos2d::Color4B(0,0,0,255));
	addChild(tmpLabel);
	history.push_back(tmpLabel);
	
	while(history.size() > 10){
		removeChild(history[0]);
		history.erase(history.begin());
	}
	
	float delta = 100.0f;
	float scale = 0.5f;
	float fade = 0.7f;
	
	for(int i = (int)history.size()-1; i >= 0; --i){
		auto moveBy = MoveBy::create(0.2, Vec2(0,delta));
		history[i]->runAction(moveBy);
		delta *= scale;
		auto scaleBy = ScaleBy::create(0.2f, scale);
		history[i]->runAction(scaleBy);
		auto fadeTo = FadeTo::create(0.2f, fade*255.0f);
		history[i]->runAction(fadeTo);
		fade -= 0.1f;
	}
}

void GameScene::pressEnter(){
	if(userInput.length() == 0 || userInput.length() > 6){
		userInput = "";
		return;
	}
	if(userAnswer() == correctAnswer()){
		addHistory();
		++level;
		difficulty += 0.5;
		userInput = "";
		std::string prev = currentString();
		int prevAnswer = correctAnswer();
		newTask();
		while(currentString() == prev || correctAnswer() == prevAnswer){
			newTask();
		}
	}
	userInput = "";
}

void GameScene::pressNumber(int num){
	std::stringstream ss;
	ss << userInput << num;
	userInput = ss.str();
}


void GameScene::newTask(){
	int diff = int(difficulty);
	
	char ops[4] = "+-*";
	op = ops[random(0,2)];
	if(op == '*'){
		diff = diff / 2;
	}
	
	a = random(diff/6,diff);
	b = random(diff/6,diff);
	if(a < b){
		int tmp = a;
		a = b;
		b = tmp;
	}
	cluster->clear();
	clusterA->clear();
	clusterB->clear();
	int spritenum = random(0,4*4-1);
	if(op == '*'){
		cluster->populate(a*b, b, 128, 32, spritenum, 0);
	}else if(op == '+'){
		clusterA->populate(a, 5, 48, 16, spritenum, 0);
		clusterB->populate(b, 5, 48, 16, spritenum, 0);
	}else if(op == '-'){
		cluster->populate(a, 10, 64, 16, spritenum, b);
	}
}

std::string GameScene::currentString(){
	std::stringstream ss;
	ss << a << op << b << "=" << userInput;
	return ss.str();
}

void GameScene::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	mainLabel->setString(currentString().c_str());
	std::stringstream ss;
	ss << level;
	levelLabel->setString(ss.str().c_str());
}