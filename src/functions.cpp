//
//  functions.cpp
//  MathGameCpp
//
//  Created by Ole Herman S. Elgesem on 03/08/16.
//
//

#include "functions.h"

// Super simple random function from min to max, inclusive
int random(int min, int max){
	int delta = max+1-min;
	return rand()%delta + min;
}

// Rescales a cocos2d sprite to specified
cocos2d::Sprite* permanentScale(cocos2d::Sprite* inp, int w, int h){
	cocos2d::Texture2D::TexParams params;
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_NEAREST;
	params.wrapS = GL_CLAMP_TO_EDGE;
	params.wrapT = GL_CLAMP_TO_EDGE;
	inp->getTexture()->setTexParameters(params);
	
	int old_w = inp->getContentSize().width;
	int old_h = inp->getContentSize().height;
	float scale_w = (float)(w)/(float)(old_w);
	float scale_h = (float)(h)/(float)(old_h);
	inp->setFlippedY(true);
	inp->setScale(scale_w, scale_h);
	inp->setPosition(cocos2d::Vec2(0.0,0.0));
	inp->setAnchorPoint(cocos2d::Vec2(0.0,0.0));
	auto renderTexture = cocos2d::RenderTexture::create( w, h, cocos2d::Texture2D::PixelFormat::RGBA8888 );
	renderTexture->begin();
	inp->visit();
	renderTexture->end();
	return cocos2d::Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
}