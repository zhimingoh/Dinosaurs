#pragma once
#include "cocos2d.h"
USING_NS_CC;
//USING_NS_CC_EXT;
class GameOverLayer:public cocos2d::CCLayerColor
{
public:
	bool init();
	CREATE_FUNC(GameOverLayer);
	static cocos2d::CCScene* scene();
	CCString value;
	virtual void onEnter();

	CCLabelTTF* pLabel;
	cocos2d::CCLabelTTF* _label;
	GameOverLayer(void);
	int _successCount;
	~GameOverLayer(void);
	void returnToGame(cocos2d::CCNode*);
	void gotomenu(CCObject* obj);
};

