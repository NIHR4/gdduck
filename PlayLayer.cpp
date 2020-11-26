#include "pch.h"
#include "PlayLayer.h"

bool __fastcall PlayLayer::initHook(CCLayer* self, int edx, void* GJGameLevel) {
    auto spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (int i = 0; i < 4; i++) {
        std::string plist = stdx::format("Resources\\GJ_DuckSheet_%03d-uhd.plist", i);
        spriteCache->addSpriteFramesWithFile(plist.c_str());
    }
    return PlayLayer::init(self, GJGameLevel);
}

void __fastcall PlayLayer::togglePracticeHook(CCLayer* self, int edx, bool practice)
{
    void* gmInstance = GameManager::getSharedState();
    if (practice && GameManager::getGameVariable(gmInstance,"1337")) {
        auto sprite = CCSprite::create();//CCSprite::createWithSpriteFrameName("GJ_DuckSprite_001.png");
        auto frames = CCArray::create();
        for (int i = 1; i <= 50; i++) {
            auto spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            std::string spriteName = stdx::format("GJ_DuckSprite_%03d.png", i);
            auto nextFrame = spriteCache->spriteFrameByName(spriteName.c_str());
            if (!nextFrame) return togglePractice(self, practice);
            frames->addObject(nextFrame);
        }
        auto animation = CCAnimation::createWithSpriteFrames(frames, 1.0 / 20.0);
        sprite->setOpacity(0);
        sprite->runAction(CCFadeTo::create(5, 40));
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        auto window = CCDirector::sharedDirector()->getWinSize();
        sprite->setPosition({ window.width / 2,window.height / 2 });
        sprite->setTag(555);
        self->addChild(sprite, 5);

    }
    else self->removeChildByTag(555);
    togglePractice(self, practice);
}

void PlayLayer::mem_init()
{
    size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));
    MH_CreateHook(
        (PVOID)(base + 0x01FB780),
        PlayLayer::initHook,
        (LPVOID*)&PlayLayer::init

    );

    MH_CreateHook(
        (PVOID)(base + 0x20D0D0),
        PlayLayer::togglePracticeHook,
        (LPVOID*)&PlayLayer::togglePractice
    );
}
