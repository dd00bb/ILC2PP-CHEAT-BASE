#pragma once
#include <vector>

namespace sdk
{
	uintptr_t Base;
	uintptr_t GameAssembly;
	uintptr_t UnityPlayer;
}

namespace offsets
{
	uintptr_t StartAuthentication = 0x0;
	uintptr_t AllAchievementsUnlocked = 0x0;
	uintptr_t get_Instance = 0x0;
	uintptr_t UnlockAchievement = 0x0;
}

namespace vars
{
	inline static UINT vps = 1;
	D3D11_VIEWPORT viewport;
	Vector2 screen_size = { 0, 0 };
	Vector2 screen_center = { 0, 0 };
	
	void* ptr = nullptr;

	bool start = false;
	bool instance = false;
	bool called = false;
	int num = 0;

	bool initil2cpp = false;
	bool show_menu = true;
	bool g_bUnloaded = false;
}