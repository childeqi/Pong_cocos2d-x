#include "GameScene.h"
#include "AIScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace ui;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("Screensize x = %f, y = %f", visibleSize.width, visibleSize.height);
    CCLOG("originsize x = %f, y = %f", origin.x, origin.y);

    auto areaRSprite = Sprite::create("area.png");
    Vec2 areasize = areaRSprite->boundingBox().size;

    //back
    auto back = MenuItemFont::create("Go Back", CC_CALLBACK_1(Game::GoBack, this));
    back->setPosition(origin + Vec2(visibleSize.width / 2, (visibleSize.height * 0.1)));
    // 4 soft buttons for UP and DOWN

    auto leftUp = MenuItemImage::create("square2.png", "square1.png", CC_CALLBACK_1(Game::leftUp, this));
    auto leftDown = MenuItemImage::create("square2.png", "square1.png", CC_CALLBACK_1(Game::leftDown, this));
    auto rightUp = MenuItemImage::create("square2.png", "square1.png", CC_CALLBACK_1(Game::rightUp, this));
    auto rightDown = MenuItemImage::create("square2.png", "square1.png", CC_CALLBACK_1(Game::rightDown, this));
    leftUp->setPosition(origin + Vec2(areasize.x /2 , (visibleSize.height / 2 + areasize.y / 4)));
    leftDown->setPosition(origin + Vec2(areasize.x /2 , (visibleSize.height / 2 - areasize.y / 4)));
    rightUp->setPosition(origin + Vec2((visibleSize.width - areasize.x /2), (visibleSize.height / 2 + areasize.y / 4)));
    rightDown->setPosition(origin + Vec2((visibleSize.width - areasize.x / 2), (visibleSize.height / 2 - areasize.y / 4)));
    auto *menu = Menu::create(leftUp, leftDown, rightUp, rightDown, back, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    // 2 PADDLEs
    paddleLSprite = Sprite::create("square.png");
    paddleRSprite = Sprite::create("square.png");
    paddleSize = paddleRSprite->boundingBox().size;
    paddlelength = paddleSize.y / 400 * 320;
    paddlewidth = paddleSize.x;
    CCLOG("paddleSize x = %f, y = %f", paddlewidth, paddlelength);
    paddleLSprite->setAnchorPoint(Vec2(0.5, 0.5));
    paddleRSprite->setAnchorPoint(Vec2(0.5, 0.5));
    paddleLSprite->setPosition(origin + Vec2(areasize.x / 2, visibleSize.height / 2));
    paddleRSprite->setPosition(origin + Vec2(visibleSize.width - areasize.x / 2, visibleSize.height / 2));
    this->addChild(paddleLSprite);   
    this->addChild(paddleRSprite);

    // wall
    wallSprite = Sprite::create("wall.png");
    wallSprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(wallSprite);

    // score
    score1 = 0;
    score2 = 0;
    
    __String *tempScore1 = __String::createWithFormat( "%i", score1 );
    __String *tempScore2 = __String::createWithFormat( "%i", score2 );
   
    label1 = Label::createWithTTF( tempScore1->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * 0.1 );
    label2 = Label::createWithTTF( tempScore2->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * 0.1 );
    label1->setColor( Color3B::WHITE );
    label2->setColor( Color3B::WHITE );
    label1->setPosition( origin + Vec2( visibleSize.width / 2 - 20, visibleSize.height * 0.9) );
    label2->setPosition( origin + Vec2( visibleSize.width / 2 + 20, visibleSize.height * 0.9) );
    this->addChild( label1, 10000 );
    this->addChild( label2, 10000 );

    // ball
    ballSprite = Sprite::create("qb160.png");
    ballSprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(ballSprite);


    Vec2 ballSize = ballSprite->boundingBox().size;
    x_min = origin.x + areasize.x / 2 + paddleSize.x / 2 + ballSize.x / 2;
    x_max = origin.x + visibleSize.width - areasize.x / 2 - paddleSize.x / 2 - ballSize.x / 2;
    x_left = origin.x + ballSize.x / 2;
    x_right = origin.x + visibleSize.width - ballSize.x / 2;
    y_min = origin.y + ballSize.y / 2;
    y_max = origin.y + visibleSize.height - ballSize.y / 2;

    velocity = Vec2(1, 1);

    this->scheduleUpdate();
    return true;
}

void Game::update(float delta)
{

//    ballSprite->setPosition(Vec2(ballSprite->getPosition().x + velocity.x, ballSprite->getPosition().y + velocity.y));
//    CCLOG("ballposition x = %f, y = %f", ballSprite->getPosition().x, ballSprite->getPosition().y);
    Vec2 ball_future = ballSprite->getPosition() + velocity;
    Vec2 paddle_l = paddleLSprite->getPosition();
    Vec2 paddle_r = paddleRSprite->getPosition();

    if (ball_future.x <= x_left && velocity.x < 0)
    {
        velocity.x = -velocity.x;
        CCLOG("Player Lost!!");

        score2++;
        __String *tempScore = __String::createWithFormat( "%i", score2 );       
        label2->setString( tempScore->getCString( ) );
        
    }

    if (ball_future.x >= x_right && velocity.x > 0)
    {
        velocity.x = -velocity.x;
        CCLOG("Player Won!!");

        score1++;
        __String *tempScore = __String::createWithFormat( "%i", score1 );       
        label1->setString( tempScore->getCString( ) );
        if (score1 % 5 == 0)
        {
            if (velocity.x > 0)
                velocity.x = velocity.x + 0.5;
            else
                velocity.x = velocity.x - 0.5;
            if (velocity.y > 0)
                velocity.y = velocity.y + 0.5;
            else
                velocity.y = velocity.y - 0.5;
        }   
    }

    if (ball_future.y >= y_max || ball_future.y <= y_min)
    {
        velocity.y = -velocity.y;
    }

    if (ball_future.x <= x_min && velocity.x < 0)
    {
        if( ((paddle_l.y + paddlelength/2) >= ball_future.y) && ((paddle_l.y - paddlelength/2) <= ball_future.y) )
        {
            velocity.x = -velocity.x;
        }
        
    }
    if (ball_future.x >= x_max && velocity.x > 0)
    {
        if( ((paddle_r.y + paddlelength/2) >= ball_future.y) && ((paddle_r.y - paddlelength/2) <= ball_future.y) )
        {
            velocity.x = -velocity.x;
        }
    }

    ballSprite->setPosition(Vec2(ballSprite->getPosition().x + velocity.x, ballSprite->getPosition().y + velocity.y));

}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
}
void Game::leftUp(cocos2d::Ref *pSender)
{
    CCLOG("leftUp");
    auto action = MoveBy::create(0.2, Point(0, 10));
    paddleLSprite->runAction(action);
}
void Game::leftDown(cocos2d::Ref *pSender)
{
    CCLOG("leftDown");
    auto action = MoveBy::create(0.2, Point(0, -10));
    paddleLSprite->runAction(action);
}
void Game::rightUp(cocos2d::Ref *pSender)
{
    CCLOG("rightUp");
    auto action = MoveBy::create(0.2, Point(0, 10));
    paddleRSprite->runAction(action);
}
void Game::rightDown(cocos2d::Ref *pSender)
{
    CCLOG("rightDown");
    auto action = MoveBy::create(0.2, Point(0, -10));
    paddleRSprite->runAction(action);
}

void Game::GoBack(cocos2d::Ref *pSender)
{
//    auto scene_back = HelloWorld::createScene();
//    Director::getInstance()->pushScene(scene_back);
    Director::getInstance()->popScene();
}



void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

