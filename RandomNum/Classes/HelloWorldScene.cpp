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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    srand(time(NULL));
    theRandomNum = rand()%100;
    
//    for (int i=0; i<100; i++) {
//        theRandomNum = rand()%100;
//        log("The random num is %d",theRandomNum);
//    }
    
    buildUI();
    addListeners();
    
    return true;
}


void HelloWorld::buildUI(){
    
    
    auto label = Label::create();
    label->setString("Please input a number between 0 - 100");
    addChild(label);
    label->setPosition(visibleSize.width/2, visibleSize.height-label->getContentSize().height/2-20);
    
    tf = TextFieldTTF::textFieldWithPlaceHolder("Input number here", "Courier", 16);
    tf->setPosition(visibleSize.width/2, label->getPositionY()-50);
    addChild(tf);
    
    submitBtn = Label::create();
    submitBtn->setPosition(visibleSize.width/2, tf->getPositionY()-50);
    submitBtn->setString("Submit");
    addChild(submitBtn);
    
    messageLabel = Label::create();
    addChild(messageLabel);
    messageLabel->setPosition(visibleSize.width/2, submitBtn->getPositionY()-50);
    
}


void HelloWorld::addListeners(){
    auto director = Director::getInstance();
    
    auto handler = [this](Touch* t,Event * e){
        
        auto target = e->getCurrentTarget();
        auto point = t->getLocation();
        
        if (target->getBoundingBox().containsPoint(point)) {
            if (target==tf) {
                tf->attachWithIME();
                
            }else if (target==submitBtn){
                tf->detachWithIME();
//                log("Submit");
                
                int inputValue = __String::create(tf->getString())->intValue();
                if (inputValue>theRandomNum) {
                    messageLabel->setString("Input value is bigger");
                }else if (inputValue<theRandomNum){
                    messageLabel->setString("Input value is smaller");
                }else{
                    messageLabel->setString("Input value is right");
                }
            }
        }else{
            tf->detachWithIME();
        }
        return false;
    };
    
    auto l = EventListenerTouchOneByOne::create();
    l->onTouchBegan = handler;
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(l, tf);
    
    auto submitBtnClickListener = EventListenerTouchOneByOne::create();
    submitBtnClickListener->onTouchBegan = handler;
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(submitBtnClickListener, submitBtn);
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
