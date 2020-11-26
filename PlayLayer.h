#pragma once
#include "cocos2d.h"
#include "format.h"
#include <iostream>
#include "incl/utilities/MinHook.h"
#include "GameManager.h"
namespace PlayLayer {
    using namespace cocos2d;
    inline bool(__thiscall* init)(CCLayer* self, void* GJGameLevel);
    bool __fastcall initHook(CCLayer* self, int edx, void* GJGameLevel);

    inline void(__thiscall* togglePractice)(CCLayer* self, bool practice);
    void __fastcall togglePracticeHook(CCLayer* self, int edx, bool practice);
    void mem_init();
}

