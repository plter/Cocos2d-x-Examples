//
//  Ball.cpp
//  RandomBalls
//
//  Created by plter on 10/31/14.
//
//

#include "Ball.h"

bool Ball::init(){
    
    Sprite::initWithFile("ball.png");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    speedX = CCRANDOM_0_1()*10-5;
    speedY = CCRANDOM_0_1()*10-5;
    
    scheduleUpdate();
    return true;
}

void Ball::update(float dt){
    
    setPosition(getPositionX()+speedX, getPositionY()+speedY);

    if (getPositionX()<getContentSize().width/2) {
        speedX=fabsf(speedX);
    }
    if (getPositionX()>visibleSize.width-getContentSize().width/2) {
        speedX=-fabs(speedX);
    }
    if (getPositionY()<getContentSize().height/2) {
        speedY=fabs(speedY);
    }
    if (getPositionY()>visibleSize.height - getContentSize().height/2) {
        speedY = -fabs(speedY);
    }
}