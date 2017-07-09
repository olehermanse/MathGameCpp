// Copyright Ole Herman Schumacher Elgesem
// github.com/olehermanse

#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

static cocos2d::Size designResolution = cocos2d::Size(1280, 720);
static cocos2d::Size smallResolution = cocos2d::Size(480, 270);
static cocos2d::Size mediumResolution = cocos2d::Size(1280, 720);
static cocos2d::Size largeResolution = cocos2d::Size(2560, 1440);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MathGameCpp", cocos2d::Rect(0, 0, designResolution.width, designResolution.height));
#else
        glview = GLViewImpl::create("MathGameCpp");
#endif
        director->setOpenGLView(glview);
    }

	director->setDisplayStats(false); // Stats, Framerate(FPS) etc.

	director->setAnimationInterval(1.0f / 60); // Set frame interval, default is 1/60, (60FPS)

    // Set the design resolution
    glview->setDesignResolutionSize(designResolution.width, designResolution.height, ResolutionPolicy::NO_BORDER);

	// Set content scale factor based on device resolution
	// This will scale content to high resolution phone displays
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > mediumResolution.height)
    {
        director->setContentScaleFactor(MIN(largeResolution.height/designResolution.height, largeResolution.width/designResolution.width));
    }
    else if (frameSize.height > smallResolution.height)
    {
        director->setContentScaleFactor(MIN(mediumResolution.height/designResolution.height, mediumResolution.width/designResolution.width));
    }
    else
    {
        director->setContentScaleFactor(MIN(smallResolution.height/designResolution.height, smallResolution.width/designResolution.width));
    }

    register_all_packages();

    // Create and run the main game scene:
    auto scene = GameScene::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
