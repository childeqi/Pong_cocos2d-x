#include "HelloWorldScene.h"
#include "GameScene.h"
#include "AIScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene( )
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
    
    // Screen real dimensions
    auto vSize = Director::getInstance()->getVisibleSize();
    auto vWidth = vSize.width;
    auto vHeight = vSize.height;

    //

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    opSprite = Sprite::create("op.jpg");
    opSprite->setPosition(Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
//    opSprite->setPosition(Vec2((visibleSize.width / 2), (visibleSize.height / 2)));
    this->addChild(opSprite);

    label = Label::createWithTTF( "Mengqi Wu", "fonts/Marker Felt.ttf", visibleSize.height * 0.1 );
    label->setPosition( origin + Vec2( visibleSize.width * 0.2, visibleSize.height * 0.1) );
    this->addChild(label);

    auto menu_start = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::Start, this));
    auto menu_AI = MenuItemFont::create("Play with AI", CC_CALLBACK_1(HelloWorld::AI, this));
    auto menu_vup = MenuItemFont::create("Volume + ", CC_CALLBACK_1(HelloWorld::volumeUp, this));
    auto menu_vdown = MenuItemFont::create("Volume -", CC_CALLBACK_1(HelloWorld::volumeDown, this));
    auto menu_ball = MenuItemImage::create("qb80.png", "qb100.png", CC_CALLBACK_1(HelloWorld::ImageButton, this));

    menu_start->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 5));
    menu_AI->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 4));
    menu_vup->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 3));
    menu_vdown->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 2));
    menu_ball->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 1));

    auto *menu = Menu::create(menu_start, menu_AI, menu_vup, menu_vdown, menu_ball, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
    vol = 0.5; 
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(vol);

    return true;
}

void HelloWorld::Start(cocos2d::Ref *pSender)
{
    CCLOG("Start");
    auto scene = Game::createScene();
    Director::getInstance()->pushScene(scene);
}

void HelloWorld::AI(cocos2d::Ref *pSender)
{
    CCLOG("AI");
    auto scene = AI::createScene();
    Director::getInstance()->pushScene(scene);
}

void HelloWorld::volumeUp(cocos2d::Ref *pSender)
{
    CCLOG("volumeUp");
    vol = vol + 0.1;
    if (vol > 1)
        vol = 1;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(vol);
}

void HelloWorld::volumeDown(cocos2d::Ref *pSender)
{
    CCLOG("volumeDown");
    vol = vol - 0.1;
    if (vol < 0)
        vol = 0;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(vol);
}

void HelloWorld::ImageButton(cocos2d::Ref *pSender)
{
    CCLOG("IMAGE Button");
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
