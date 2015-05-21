#include "GameOverLayer.h"
#include "HelloWorldScene.h"
//#include "G2UTool.h"
//#include "CCLabelBMFont.h"
USING_NS_CC;

GameOverLayer::GameOverLayer(void)
{
}


GameOverLayer::~GameOverLayer(void)
{
	if (_label)
	{
		_label->release();
	}
}

bool GameOverLayer::init()
{
	if (CCLayerColor::initWithColor(ccc4(125,155,207,255)))
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCSprite* over=CCSprite::create("gameover.png");
		over->setPosition(ccp(400,200));
		this->addChild(over);
		_label=CCLabelTTF::create("word","Artial",40);
		CCSize size=CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		_label->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(_label);
		_label->retain();//保证_label跟类对象有同样的生命周期
		//CCDelayTime* delay=CCDelayTime::create(5);
		CCCallFuncN* returnToGame=CCCallFuncN::create(this,callfuncN_selector(GameOverLayer::returnToGame));
//		this->runAction(CCSequence::create(delay,returnToGame,NULL));
		
		//最终得分
		pLabel = CCLabelTTF::create("0", "Arial", 24);
		pLabel->setColor(ccWHITE);
		pLabel->retain();
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height - pLabel->getContentSize().height));
		this->addChild(pLabel, 1);


		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"replay.png",
			"replay.png",
			this,
			menu_selector(HelloWorld::BeginGame));
		//CC_BREAK_IF(! pCloseItem);  
		pCloseItem->setPosition(ccp(60,-100));

		CCMenu* pMenu = CCMenu::create(pCloseItem ,NULL); 

		CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
			"menu.png",
			"menu.png",
			this,
			menu_selector(GameOverLayer::gotomenu));
		//CC_BREAK_IF(! pCloseItem);  
		pCloseItem2->setPosition(ccp(-60,-100));

		CCMenu* pMenu2 = CCMenu::create(pCloseItem2 ,NULL); 
		this->addChild(pMenu,1);
		this->addChild(pMenu2, 1);

		
	}
	return true;

}

void GameOverLayer::returnToGame(CCNode*)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());


}
cocos2d::CCScene* GameOverLayer::scene()
{
	CCScene* sc=CCScene::create();
	GameOverLayer* layer=GameOverLayer::create();
	layer->setTag(100);
	sc->addChild(layer);
	

	return sc;

}
void GameOverLayer::onEnter()
{
	CCLayer::onEnter();
	CCLog(value.getCString());
	_successCount=value.intValue();
	if (_successCount<=0)
	{
		char str[100] = {'0'};
		sprintf(str, "noob!");
		pLabel->setString(str);
		pLabel->setVisible(true);


	}else
	{

		char str[100] = {'0'};
		sprintf(str, "You have to kill %d gay",_successCount);
		pLabel->setString(str);
		pLabel->setVisible(true);

	}
	
}
void GameOverLayer::gotomenu(CCObject* obj)
{
	CCScene* meunscene=HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(meunscene);
}