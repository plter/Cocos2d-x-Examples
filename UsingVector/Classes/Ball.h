//
//  Ball.h
//  UsingVector
//
//  Created by plter on 10/21/14.
//
//

#ifndef UsingVector_Ball_h
#define UsingVector_Ball_h

#include <cocos2d.h>

class Ball:public cocos2d::Sprite {
    
private:
    float speedX,speedY;
    
public:
    
    virtual bool init(){
        speedX = CCRANDOM_0_1()*20-10;
        speedY = CCRANDOM_0_1()*20-10;
        
        Sprite::initWithFile("ball.png");
        
        return true;
    };
    
    void move(){
        setPositionX(getPositionX()+speedX);
        setPositionY(getPositionY()+speedY);
    }
    
    CREATE_FUNC(Ball);
};

#endif
