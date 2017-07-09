//
//  NumberVisualizer.cpp
//  MathGameCpp
//
//  Created by Ole Herman S. Elgesem on 03/08/16.
//
//

#include "NumberVisualizer.h"

NumberVisualizer::NumberVisualizer(int x,int y, int maxHeight, std::string textureFile, int sprites_x, int sprites_y, int sprites_s){
	this->setPosition(cocos2d::Vec2(x,y));
	this->maxH = maxHeight;
	
	this->textureFile=textureFile;
	this->sprites_x=sprites_x;
	this->sprites_y=sprites_y;
	this->sprites_s=sprites_s;
}

void NumberVisualizer::populate(int n, int rowSize, int size, int spacing, int spritenum, int faded){
	this->removeAllChildren();
	if( n <= 0 || size <= 0){
		return;
	}
	if(rowSize <= 0){
		rowSize = 1;
	}
	this->setAnchorPoint(cocos2d::Vec2(0.0,0.0));
	
	if(getHeight(n, rowSize, size, spacing) > maxH){
		float factor = (float)(getHeight(n, rowSize, size, spacing))/(float)(maxH);
		float spaceRatio = (float)(spacing)/(float)(size);
		size = (int)((float)(size)/factor);
		spacing = (int)(spaceRatio*(float)(size));
	}
	
	int csf = (int)(cocos2d::Director::getInstance()->getContentScaleFactor());
	int sx = (spritenum % sprites_x) * sprites_s/csf;
	int sy = (spritenum / sprites_x) * sprites_s/csf;
	
	
	auto original = cocos2d::Sprite::create(textureFile.c_str(), cocos2d::Rect(sx,sy,16/csf,16/csf));
	auto sprite = permanentScale(original, size, size);
	sprite->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	sprite->setPosition(cocos2d::Vec2(0,0));
	
	int curX = 0;
	int curY = 0;
	int width = getWidth(n, rowSize, size, spacing);
	int height = getHeight(n, rowSize, size, spacing);
	for(int i=0;i<n;++i){
		auto newSprite = cocos2d::Sprite::createWithTexture(sprite->getTexture());
		newSprite->setAnchorPoint(cocos2d::Vec2(0.0,0.0));
		newSprite->setPosition(cocos2d::Vec2(curX,height-size-curY));
		
		if(n-i <= faded){
			auto fadeTo = cocos2d::FadeTo::create(1.2f, 0.15*255.0f);
			newSprite->runAction(fadeTo);
		}
		
		this->addChild(newSprite);
		
		
		if((i+1) % rowSize == 0){
			curX = 0;
			curY += size+spacing;
		}else{
			curX += size+spacing;
		}
	}
	this->setContentSize(cocos2d::Size(width,height));
	this->setAnchorPoint(cocos2d::Vec2(0.5,1.0));
}

void NumberVisualizer::clear(){
	this->removeAllChildren();
}

int NumberVisualizer::getWidth(int n, int rowSize, int size, int spacing){
	int cols = rowSize;
	if(n < rowSize){
		cols = n;
	}
	return cols*size + (cols-1)*spacing;
}

int NumberVisualizer::getHeight(int n, int rowSize, int size, int spacing){
	int rows = n/rowSize;
	if(n%rowSize > 0)
		++rows;
	return rows*size + (rows-1)*spacing;
}
