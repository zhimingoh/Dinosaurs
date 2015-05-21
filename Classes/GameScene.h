#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameScene:public cocos2d::CCLayerColor
{
public:
	//CCLabelTTF* pLabel;
	static cocos2d::CCScene* scene1();
	CREATE_FUNC(GameScene);
	CCLabelTTF* pLabel;
	cocos2d::CCSprite* target;
	virtual bool init();  

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	void responseFunc(CCObject* obj);
	void myDefine(CCNode* who);
	void creatSprite();
	void gameLogic(float dt);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	
	void update(float delta);
	void creatBigGay();
	void menuFun(CCObject * node);
//	void BeginGame(CCObject* obj);
	//arry插入效率低 查找效率高
	//list 反之

	CCMenuItemImage *pCloseItem;
	cocos2d::CCArray* _targets;
	cocos2d::CCArray* _targets2;
	cocos2d::CCArray* _projs;
	int _successCount;

	GameScene(void);
	~GameScene(void);
	void PushScene(int *ref);
};

#endif