#pragma once
#include <Windows.h>
#include <iostream>
#include <direct.h>
#include <iomanip>
#include <thread>

#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "SDK/Engine_classes.hpp"
#include "SDK/MainPlayer_classes.hpp"
#include "SDK/DaynightCycle_classes.hpp"
#include "SDK/MainGamemode_classes.hpp"
#include "SDK/Car1_classes.hpp"
#include "SDK/VictoryBPLibrary_classes.hpp"
#include "SDK/Lib_classes.hpp"
#include "SDK/LowEntryExtendedStandardLibrary_classes.hpp"
#include "SDK/VotV_classes.hpp"
#include "SDK/GameInst_classes.hpp"
//#include "SDK/Umg_spawnmenu_classes.hpp"
//#include "SDK/Umg_classes.hpp"
//#include "SDK/PropProcessor_classes.hpp"
//#include "SDK/Umg_cheatMenu_classes.hpp"
//#include "SDK/Umg_UI_classes.hpp"
//#include "SDK/Umg_cheatMenuSlot_classes.hpp"
//#include "SDK/LowEntryEncryption_classes.hpp"

#include "cheat.hpp"

#include "menu.hpp"
#include "settings.hpp"
#include "drawings.hpp"

#define _CRT_SECURE_NO_WARNINGS

inline cheat_manager* sdk;
inline menu_imgui* gui;
inline settings* cfg;
inline FILE* file;
inline drawings* draw;


typedef HRESULT(__stdcall* Resize)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

