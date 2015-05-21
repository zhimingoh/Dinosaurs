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

GameScene::GameScene(void)
{

}
bool GameScene::init()
{
	if ( !CCLayerColor::init()) 
	{
		return false;
	}
	_successCount=0;

	CCParticleSystem *particle=CCParticleSnow::create();

	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//初始化
	_projs=new cocos2d::CCArray;
	_targets=new cocos2d::CCArray;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav",true);
	//Class::create不需要手动释放
	//new的对象需要手动释放


	//创建记分板
	pLabel = CCLabelTTF::create("0", "Arial", 24);
	pLabel->setColor(ccWHITE);
	pLabel->retain();
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height - pLabel->getContentSize().height));
	this->addChild(pLabel, 1);
	//设置背景
	CCSprite* pSprite = CCSprite::create("pk.png");
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0);
	//设置主角
	#if 0
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* player=CCSprite::create("2.png");
	player->setPosition(ccp(0+30,screenSize.height/2));
	this->addChild(player);
	#endif
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* hero=CCSprite::create("2.png");
	hero->setPosition(ccp(30,240));
	this->addChild(hero);
	//menu
	this->schedule(schedule_selector(GameScene::gameLogic),2);
	this->schedule(schedule_selector(GameScene::update));
	this->setTouchEnabled(true);

	return true;
}


GameScene::~GameScene(void)
{
	if (_projs!=NULL)
	{
		_projs->release();
	}
	if (_targets!=NULL)
	{
		_targets->release();
	}
}

cocos2d::CCScene* GameScene::scene1()
{
	CCScene* sc=CCScene::create();
	GameScene* layer=GameScene::create();

	sc->addChild(layer);
	return sc;

}
void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch=(CCTouch*)pTouches->anyObject();
	CCPoint loccInView=touch->getLocationInView();
	CCPoint loc=CCDirector::sharedDirector()->convertToGL(loccInView);//转换坐标系
	CCLOG("%f",loc.x);
	CCLOG("%f",loc.y);
	if (loc.x<=10)
	{
		return;
	}
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* proj=CCSprite::create("firePng3.png");
	proj->setPosition(ccp(75,(screenSize.height/2.0)+5));
	this->addChild(proj);
	//技能声效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("fire.wav");
	_projs->addObject(proj);
	proj->setTag(2);
	
	double dx=loc.x-20;
	double dy=loc.y-screenSize.height/2.0;
	double d=sqrt(dx* dx+dy);
	double D=sqrt(screenSize.width*screenSize.width+screenSize.height*screenSize.height);
	double ratio=D/d;
	double endx=ratio*dx+20;
	double endy=ratio*dy+screenSize.height/2.0;
	CCMoveTo* move=CCMoveTo::create(D/320,ccp(endx,endy));
	CCCallFuncN* moveFinish=CCCallFuncN::create(this,callfuncN_selector(GameScene::myDefine));
	CCSequence* actions=CCSequence::create(move,moveFinish,NULL);
	proj->runAction(actions);
	
	

}
void GameScene::gameLogic(float dt)
{
	this->creatSprite();
}
void GameScene::responseFunc(CCObject* obj)
{
	//CCLOG("hello");
	
}
void GameScene::creatSprite()
{
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	//添加精灵
	CCSprite* mytarget=CCSprite::create("aoteman1.png");
	int y=rand()%(int)(screenSize.height);
	mytarget->setPosition(ccp(screenSize.width-20,y));
	this->addChild(mytarget);
	_targets->addObject(mytarget);
	mytarget->setTag(1);
	CCMoveTo* move=CCMoveTo::create(2,ccp(0,40));
	CCCallFuncN* disappear=CCCallFuncN::create(this,callfuncN_selector(GameScene::myDefine));
	CCSequence* actions=CCSequence::create(move,disappear,NULL);
	mytarget->runAction(actions);
}
void GameScene::creatBigGay()
{
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	//添加BOSS
	CCSprite* mytarget1=CCSprite::create("aoteman2.png");
	int y=rand()%(int)(screenSize.height);
	mytarget1->setPosition(ccp(screenSize.width-20,y));
	this->addChild(mytarget1);
	_targets->addObject(mytarget1);
	mytarget1->setTag(1);
	CCMoveTo* move=CCMoveTo::create(1,ccp(0,40));
	CCJumpTo* jump=CCJumpTo::create(1,ccp(0,50),50,5);
	CCCallFuncN* disappear=CCCallFuncN::create(this,callfuncN_selector(GameScene::myDefine));
	CCSequence* actions=CCSequence::create(move,disappear,NULL);
	mytarget1->runAction(actions);
};
void GameScene::update(float delta)//delta=1.0/fps
{
	//击中怪物
	CCArray* targetToDelete=new CCArray;
	CCArray* projToDelete=new CCArray;
	CCObject* itarget;
	CCObject* iproj;
	
	CCARRAY_FOREACH(_targets,itarget){
		CCSprite *target=(CCSprite*)itarget;
		//获取矩形区域
		CCRect targetZone=CCRectMake(target->getPositionX(),
			target->getPositionY(),
			target->getContentSize().width,
			target->getContentSize().height);

		CCARRAY_FOREACH(_projs,iproj){
			CCSprite* proj=(CCSprite*)iproj;
			CCRect projZone=CCRectMake(proj->getPositionX(),
				proj->getPositionY(),
				proj->getContentSize().width,
				proj->getContentSize().height);

		if (projZone.intersectsRect(targetZone))
		{

			_successCount++; // 
			char str[100] = {'0'};
			sprintf(str, "%d", _successCount);
			pLabel->setString(str);
			pLabel->setVisible(true);


			projToDelete->addObject(iproj);
			targetToDelete->addObject(itarget);
		}
		}//end of iterate projectile

	}//end of iter  target




	CCARRAY_FOREACH(projToDelete,iproj)
	{
		_projs->removeObject(iproj);
		CCSprite* proj=(CCSprite*)iproj;
		proj->removeFromParentAndCleanup(true);

	}
	CCARRAY_FOREACH(targetToDelete,itarget){
		_targets->removeObject(itarget);
		CCSprite* target=(CCSprite*)itarget;
		target->removeFromParentAndCleanup(true);
	}
	targetToDelete->release();
	projToDelete->release();
}
void GameScene::myDefine(CCNode* who)
{
	
	who->removeFromParentAndCleanup(true);
	int tag=who->getTag();
	if(1==tag)
	{
		_targets->removeObject(who);
		CCScene* overScene=GameOverLayer::scene();//

		//场景传值
		GameOverLayer * layer = (GameOverLayer*)(overScene->getChildren()->objectAtIndex(0));
		CCString* ns=CCString::createWithFormat("%d",_successCount);
		layer->value =*ns;
		GameOverLayer* overLayer=(GameOverLayer*)overScene->getChildByTag(100);
		overLayer->_label->setString("GameOver");
		CCDirector::sharedDirector()->replaceScene(overScene);

	}
	else if(2==tag)
	{
		_projs->removeObject(who);

	}

}

void GameScene::PushScene(int *ref)
{
	 
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
