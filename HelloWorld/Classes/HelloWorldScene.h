#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::Sprite *mySprite;
    cocos2d::Sprite *opSprite;
    cocos2d::Label *label;

    void Start(Ref *pSender);
    void AI(cocos2d::Ref *pSender);
    void volumeUp(Ref *pSender);
    void volumeDown(Ref *pSender);
    void ImageButton(Ref *pSender);
    float vol;

};

#endif // __HELLOWORLD_SCENE_H__
