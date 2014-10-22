#include "HelloWorldScene.h"

USING_NS_CC;


#define RED_BIT_MASK    0b0100
#define GREEN_BIT_MASK  0b0010
#define BLUE_BIT_MASK   0b0001
#define EDGE_BIT_MASK   0b1000

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
    
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
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch * t,Event * e){
        this->addBox(t->getLocation());
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact & contact){
        switch (contact.getShapeA()->getBody()->getContactTestBitmask()|contact.getShapeB()->getBody()->getContactTestBitmask()) {
            case RED_BIT_MASK|BLUE_BIT_MASK:
                log("red rect contact blue rect");
                break;
            case RED_BIT_MASK|GREEN_BIT_MASK:
                log("red rect contact green rect");
                break;
            case BLUE_BIT_MASK|GREEN_BIT_MASK:
                log("blue rect contact green rect");
                break;
            case RED_BIT_MASK|EDGE_BIT_MASK:
                log("red rect hit edge");
                break;
            case GREEN_BIT_MASK|EDGE_BIT_MASK:
                log("green rect hit edge");
                break;
            case BLUE_BIT_MASK|EDGE_BIT_MASK:
                log("blue rect hit edge");
                break;
            case GREEN_BIT_MASK:
                log("two green rect contact");
                break;
            case RED_BIT_MASK:
                log("two red rect contact");
                break;
            case BLUE_BIT_MASK:
                log("two blue rect contact");
                break;
            default:
                break;
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}


void HelloWorld::onEnter(){
    
    Layer::onEnter();
    
    auto bounds = Node::create();
    bounds->setContentSize(visibleSize);
    bounds->setPhysicsBody(PhysicsBody::createEdgeBox(bounds->getContentSize()));
    bounds->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
    bounds->setPosition(visibleSize/2);
    addChild(bounds);
    
    addBox(Vec2(visibleSize.width/2, visibleSize.height/2));
    
}


void HelloWorld::addBox(cocos2d::Vec2 position){
    
    // 0b010 | 0b001 = 0b011
    
    auto r = Sprite::create();
    r->setTextureRect(Rect(0, 0, 50, 50));
    r->setPhysicsBody(PhysicsBody::createBox(r->getContentSize()));
    addChild(r);
    r->setPosition(position);
    
    switch (rand()%3) {
        case 0:
            r->setColor(Color3B(255, 0, 0));
            r->getPhysicsBody()->setContactTestBitmask(RED_BIT_MASK);
            break;
        case 1:
            r->setColor(Color3B(0, 255, 0));
            r->getPhysicsBody()->setContactTestBitmask(GREEN_BIT_MASK);
            break;
        case 2:
            r->setColor(Color3B(0, 0, 255));
            r->getPhysicsBody()->setContactTestBitmask(BLUE_BIT_MASK);
            break;
        default:
            break;
    }
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
