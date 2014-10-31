//
//  Ball.h
//  MoveBall
//
//  Created by plter on 10/31/14.
//
//

#ifndef __MoveBall__Ball__
#define __MoveBall__Ball__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Ball:public Sprite {
    
public:
    virtual bool init();
    
    void move();
    
    CREATE_FUNC(Ball);
    
private:
    float speedX;
    Size visibleSize;
};

#endif /* defined(__MoveBall__Ball__) */
