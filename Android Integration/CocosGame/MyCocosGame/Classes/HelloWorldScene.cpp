#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    string path = CCFileUtils::getInstance()->getWritablePath() + "game_data.txt";
    FILE *fp = fopen(path.c_str(), "r");
    char buf[200] = {0};

    if (! fp)
    {
        CCLOG("can not open file %s", path.c_str());
    } else {
        fgets(buf, 200, fp);
        CCLOG("read content %s", buf);
    }

    stringstream ss;
    string text;
    ss << buf;
    ss >> text;

    auto label = LabelTTF::create( text, "Arial", 40);
    
    label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 0);
    
    return true;
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
