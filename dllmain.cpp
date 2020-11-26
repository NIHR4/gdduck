// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "incl/utilities/MinHook.h"
#include "PlayLayer.h"
#include "MoreOptions.h"
#include "GameManager.h"

[[noreturn]] void duck_thread(HMODULE myModule) {
    MH_Initialize();
    PlayLayer::mem_init();
    MoreOptions::mem_init();
    GameManager::mem_init();
    MH_EnableHook(MH_ALL_HOOKS);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)duck_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

