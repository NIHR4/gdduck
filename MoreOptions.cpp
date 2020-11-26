#include "pch.h"
#include "MoreOptions.h"

bool __fastcall MoreOptions::initHook(void* self)
{
    bool result = MoreOptions::init(self);
    MoreOptions::addToggle(
        self, 
        "Enable Duck", 
        "1337",
        "Adds a spinning duck; overlayed on top of your screen whenever you go into practice mode");
    return result;
}

void MoreOptions::mem_init(){
    size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));
    MH_CreateHook(
        (PVOID)(base+0x1DE8F0),
        MoreOptions::initHook,
        (PVOID*)&MoreOptions::init);
    
    MoreOptions::addToggle = reinterpret_cast<decltype(MoreOptions::addToggle)>(base + 0x1DF6B0);
}
