#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);

    cocos2d::Sprite *mySprite;
    cocos2d::Sprite *opSprite;
    cocos2d::Sprite *paddleLSprite;
    cocos2d::Sprite *paddleRSprite;
    cocos2d::Sprite *wallSprite;
    cocos2d::Sprite *ballSprite;

    cocos2d::Vec2 paddleSize;

	cocos2d::Label *label1;
    cocos2d::Label *label2;
    cocos2d::Vec2 velocity;
	cocos2d::Vec2 acceleration;

    float paddlelength;
    float paddlewidth;
    float x_min;
    float x_max;
    float x_left;
    float x_right;
    float y_min;
    float y_max;

	unsigned int score1;
    unsigned int score2;
    unsigned int level;


    void GoBack(Ref *pSender);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
 //   bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
 //   bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    void leftUp(cocos2d::Ref *pSender);
    void leftDown(cocos2d::Ref *pSender);
    void rightUp(cocos2d::Ref *pSender);
    void rightDown(cocos2d::Ref *pSender);

	


};

#endif // __GAME_SCENE_H__
