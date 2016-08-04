//
//  NumberVisualizer.hpp
//  MathGameCpp
//
//  Created by Ole Herman S. Elgesem on 03/08/16.
//
//

#ifndef NumberVisualizer_h
#define NumberVisualizer_h

#include "functions.h"

class NumberVisualizer : public cocos2d::Node{
public:
	
	int maxH;
	
	std::string textureFile;
	int sprites_x;
	int sprites_y;
	int sprites_s;
	
	NumberVisualizer(int x,int y, int maxHeight, std::string textureFile, int sprites_x, int sprites_y, int sprites_s);
	
	void populate(int n, int rowSize, int size, int spacing, int spritenum, int faded);
	void clear();
	
	int getWidth(int n, int rowSize, int size, int spacing);
	int getHeight(int n, int rowSize, int size, int spacing);
	
private:
	
};


#endif /* NumberVisualizer_hpp */
