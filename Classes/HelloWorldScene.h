#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class HelloWorld : public cocos2d::CCLayerColor
{
public:
	CCLabelTTF* pLabel;
	cocos2d::CCSprite* target;
    virtual bool init();  
    static cocos2d::CCScene* scene();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();
	
	void BeginGame(CCObject* obj);

	//arry闂佸湱绮敮鎺楀矗閸℃稑鏋侀柛顐犲灩閼哄啿霉?闂佸搫琚崕鍙夌珶濮椻偓瀵偊宕奸姀鐘哄У�?
	//list 闂佸憡鐟ョ粔宕囩�?
	


};

#endif // __HELLOWORLD_SCENE_H__
