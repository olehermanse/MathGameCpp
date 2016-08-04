// Copyright Ole Herman Schumacher Elgesem
// github.com/olehermanse

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberVisualizer.h"
#include <map>
#include <iostream>

class GameScene : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameScene);
	
private:
	int counter;
	std::string userInput;
	int a;
	char op;
	int b;
	int level;
	int btnSize;
	int btnHeight;
	float difficulty;
	NumberVisualizer* cluster;
	NumberVisualizer* clusterA;
	NumberVisualizer* clusterB;
	cocos2d::Label * levelLabel;
	cocos2d::Label * mainLabel;
	std::vector<cocos2d::Label *> history;
	
	void clickEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eventType);
	void pressBackspace();
	void pressEnter();
	void pressNumber(int num);
	int correctAnswer();
	int userAnswer();
	void newTask();
	void addHistory();
	std::string currentString();
	
public:
	virtual void update(float delta) override;
};