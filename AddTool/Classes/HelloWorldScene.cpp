#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buildUI();
    addListeners();
    
    return true;
}


void HelloWorld::buildUI(){
    aTf = TextFieldTTF::textFieldWithPlaceHolder("Value", "Courier", 16);
    aTf->setPosition(100, 300);
    addChild(aTf);
    
    auto addLabel = Label::create();
    addLabel->setString("+");
    addChild(addLabel);
    addLabel->setPosition(aTf->getPositionX()+50, aTf->getPositionY());
    
    bTf = TextFieldTTF::textFieldWithPlaceHolder("Value", "Courier", 16);
    bTf->setPosition(addLabel->getPositionX()+50, aTf->getPositionY());
    addChild(bTf);
    
    auto equalLabel = Label::create();
    equalLabel->setString("=");
    addChild(equalLabel);
    equalLabel->setPosition(bTf->getPositionX()+50, aTf->getPositionY());
    
    resultLabel = Label::create();
    addChild(resultLabel);
    resultLabel->setPosition(equalLabel->getPositionX()+50, aTf->getPositionY());
    
    addBtn = Label::create();
    addBtn->setString("Add");
    addBtn->setSystemFontSize(16);
    addChild(addBtn);
    addBtn->setPosition(aTf->getPositionX(), aTf->getPositionY()-50);
}


void HelloWorld::addListeners(){
    
    auto director = Director::getInstance();
    
    auto handler = [=](Touch * t,Event * e){
        
        auto target = e->getCurrentTarget();
        
        if (target->getBoundingBox().containsPoint(t->getLocation())) {
            if (aTf==target) {
                aTf->attachWithIME();
            }else if (bTf==target){
                bTf->attachWithIME();
            }else if(target==addBtn){
                
                int a = __String::create(aTf->getString())->intValue();
                int b = __String::create(bTf->getString())->intValue();
                
                resultLabel->setString(StringUtils::format("%d",a+b));
            }
        }
        
        return false;
    };
    
    auto addListenerToTarget = [director,handler](Node* target){
        auto l = EventListenerTouchOneByOne::create();
        l->onTouchBegan = handler;
        director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(l, target);
    };
    
    addListenerToTarget(addBtn);
    addListenerToTarget(aTf);
    addListenerToTarget(bTf);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
