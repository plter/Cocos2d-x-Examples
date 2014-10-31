//
//  MoveBalls.cpp
//  MoveBall
//
//  Created by plter on 10/31/14.
//
//

#include "MoveBalls.h"


Scene * MoveBalls::createScene(){
    
    auto s = Scene::create();
    
    auto l = MoveBalls::create();
    s->addChild(l);
    
    return s;
    
}

bool MoveBalls::init(){
    LayerColor::initWithColor(Color4B(255,255,255,255));
    
    addBall(100, 100);
    addBall(100, 200);
    addBall(100, 300);
    addBall(100, 400);
    
    scheduleUpdate();
    
    return true;
}


void MoveBalls::update(float dt){
//    ball->move();
    
    for (auto it=balls.begin(); it!=balls.end(); it++) {
        (*it)->move();
    }
}

void MoveBalls::addBall(float x, float y){
    auto ball = Ball::create();
    ball->setPosition(x, y);
    addChild(ball);
    
    balls.pushBack(ball);
}


