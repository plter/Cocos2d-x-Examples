//
//  Ball.cpp
//  MoveBall
//
//  Created by plter on 10/31/14.
//
//

#include "Ball.h"

bool Ball::init(){
    
    Sprite::initWithFile("ball.png");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    speedX = 3;

    return true;
}


void Ball::move(){
    setPositionX(getPositionX()+speedX);
    
    if (getPositionX()>visibleSize.width) {
        setPositionX(0);
    }
}