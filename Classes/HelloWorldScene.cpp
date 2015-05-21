#include "HelloWorldScene.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
#include "GameScene.h"
#include "Gif/GIFMovie.h"
#include "Gif/CacheGif.h"
#include "Gif/InstantGif.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
	
    return scene;
}


bool HelloWorld::init()
{

 if ( !CCLayerColor::initWithColor(ccc4(125,155,207,255))) 
    {
        return false;
    }
	CCParticleSystem *particle=CCParticleSnow::create();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCSprite* pSprite = CCSprite::create("fengmian.png");
	pSprite->setPosition(ccp(400,200));
	this->addChild(pSprite, 0);

	
	CCSprite* hero=CCSprite::create("2.png");
	hero->setPosition(ccp(30,240));
	this->addChild(hero);
	CCMoveTo* heroMove=CCMoveTo::create(1,ccp(350,250));
	hero->runAction(heroMove);
	
	CCSprite* logo=CCSprite::create("logo.png");
	logo->setPosition(ccp(400,370));
	this->addChild(logo);
	
	CCSprite* aotomen=CCSprite::create("aoteman1.png");
	aotomen->setPosition(ccp(799,0));
	this->addChild(aotomen);
	CCMoveTo* aotomenMove=CCMoveTo::create(1,ccp(450,250));
	aotomen->runAction(aotomenMove);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "play2.png",
                                        "playonTouch.png",
                                        this,
                                        menu_selector(HelloWorld::BeginGame));
		//CC_BREAK_IF(! pCloseItem);  
    	pCloseItem->setPosition(ccp(0,-100));
		
		CCMenu* pMenu = CCMenu::create(pCloseItem ,NULL); 
 
    this->addChild(pMenu, 1);

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav",true);

	

    return true;
}

void HelloWorld::BeginGame(CCObject* obj)
{
	CCScene* game1=GameScene::scene1();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,game1)); 
	
}
HelloWorld::~HelloWorld()
{

}

