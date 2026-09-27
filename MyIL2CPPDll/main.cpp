#include "includes.h"
#include "Menu.h"
#include <stdio.h>
#include <thread>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	const char* fontPath = "C:\\Windows\\Fonts\\msyh.ttc";
	ImFont* chineseFont = io.Fonts->AddFontFromFileTTF(
		fontPath,
		18.0f,
		nullptr,
		io.Fonts->GetGlyphRangesChineseFull()
		//io.Fonts->GetGlyphRangesChineseSimplifiedCommon()  
	);
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

//窗口消息处理函数，负责处理游戏窗口的输入事件（如鼠标点击、键盘按键等），并将这些事件传递给 ImGui 以便它能够正确响应用户的交互操作。
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

const char* achievementIds[] = {
	"AARON",
	"KILL_CHIEFOFSECURITY",
	"AFFIX_CRAFT_FIRST",
	"FLAWLESS_ELITE_ROOM",
	"KILL_POWERLOADER",
	"UNLOCKED_KATARS",
	"DAMAGE_TOTAL_COUNT",
	"KILL_CHAINERDEMON",
	"KILL_PLAGUEBEARER",
	"KILL_SORROW",
	"UNLOCKED_WARHAMMER",
	"KILL_BATCH_ABILITY",
	"UPGRADES_AIDA",
	"DANIELLE",
	"DANIELLE_FLAWLESS",
	"KILL_CURSEDTOTEM",
	"KILL_WENDIGO",
	"KILL_LIEGFRIED",
	"KILL_QUEENMEZHAD",
	"KILL_ENEMIES_COUNT",
	"ALL_ALLIES",
	"BATAIR",
	"BATAIR_FLAWLESS",
	"ARTIFACT_OBTAIN",
	"KILL_ABYSSLAMPREY",
	"THE_END_CH3",
	"KILL_HERALDSOFTHECAUSE",
	"UPGRADES_MORTIMER",
	"MAX_SHADOW",
	"ENCHANTMENT_OBTAIN",
	"COIN_SPEND_SHOP",
	"KATAR_SPECIAL_SKILL_KILL",
	"DEATH_BLOB",
	"KATANA_SPECIAL_SKILL_ACTIVATION",
	"AFFIX_CRAFT_COUNT",
	"AARON_FLAWLESS",
	"KILL_COMPANION",
	"REROLL_COUNT",
	"WEAPON_SWITCH_ATTACK_KILL",
	"ABILITY_REPLACE",
	"RESOURCE_DOOR_HP",
	"WARHAMMER_STRONG_KILL"
};

void Call() {
	//调用游戏内的函数，解锁成就
	if (vars::ptr&&vars::start)
	{
		for (int i = 0; i < 14; i++)
		{
			Functions::UnlockAchievement(vars::ptr, i, NULL);
		}
		printf("[ DEBUG ] ALL Achievement Unlocked\n");
		vars::called = true;
	}
	
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)//每帧执行
{
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!init)//只执行一次：初始化 ImGui 环境
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&vars::vps, &vars::viewport);//获取当前视口信息，存储在全局变量中，方便后续使用
	vars::screen_size = { vars::viewport.Width, vars::viewport.Height };
	vars::screen_center = { vars::viewport.Width / 2.0f, vars::viewport.Height / 2.0f };

	//ImGui 准备每帧更新和渲染
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui 要显示的内容
	if (vars::show_menu)
	{
		DrawMenu();
	}

	

	if (!vars::called)
	{
		Call();
	}

	//渲染 ImGui 内容到屏幕上
	ImGui::Render();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		vars::show_menu = !(vars::show_menu);
		ImGui::GetIO().MouseDrawCursor = vars::show_menu;
	}

	if (GetAsyncKeyState(VK_END) & 1)
	{
		if (!vars::g_bUnloaded)
		{
			MH_DisableHook(MH_ALL_HOOKS);
			MH_Uninitialize();
			vars::show_menu = false;
		}
	}

	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		if (!vars::g_bUnloaded)
		{
			// 1. 先全部取消钩子，避免卸载崩溃
			MH_DisableHook(MH_ALL_HOOKS);
			MH_Uninitialize();

			vars::g_bUnloaded = true;
			vars::show_menu = false;

			// 2. 卸载自身DLL
			HMODULE hMod = GetModuleHandleA("VampireSurvivors.dll"); // 改成你DLL文件名
			if (hMod)
			{
				FreeLibrary(hMod);
			}
		}
	}

	IL2CPP::Thread::Detach(m_pThisThread);

	//设置渲染目标为主渲染目标视图（即游戏的后备缓冲区），然后调用 ImGui 的渲染函数把 ImGui 的绘制数据渲染到屏幕上
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);// 1. 设置当前要渲染的目标（屏幕/窗口）
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());// 2. 让 ImGui 把界面画到上面设置的目标上

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void CreateConsole() {
	AllocConsole();////向系统申请一个控制台窗口
	AttachConsole(GetCurrentProcessId());//把控制台绑定到当前游戏进程
	SetConsoleTitle("EpicAchievementManager");
	//把程序的输出重定向到控制台
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

//获取模块基址，初始化 Il2Cpp 环境，并打印相关信息到控制台，方便调试和后续使用
void GetModules() {
	if (IL2CPP::Initialize(true)) {
		printf("[ DEBUG ] Il2Cpp initialized\n");
	}
	else {
		printf("[ DEBUG ] Il2Cpp initialize failed, quitting...");
		Sleep(300);
		exit(0);
	}
	sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
	printf("[ DEBUG ] Base Address: 0x%llX\n", sdk::Base);
	sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
	printf("[ DEBUG ] GameAssembly Base Address: 0x%llX\n", sdk::GameAssembly);
	sdk::UnityPlayer = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
	printf("[ DEBUG ] UnityPlayer Base Address: 0x%llX\n", sdk::UnityPlayer);
	printf("----------------------------------------------------------\n");
	printf("\n");
}

void GetOffsets() {
	Unity::il2cppClass* EpicPlatform = IL2CPP::Class::Find("EpicPlatform");

	offsets::StartAuthentication = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(EpicPlatform, "StartAuthentication");
	offsets::UnlockAchievement = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(EpicPlatform, "UnlockAchievement");

	printf("[ DEBUG ] StartAuthentication Address: 0x%llX\n", offsets::StartAuthentication - sdk::GameAssembly);
	printf("[ DEBUG ] UnlockAchievement Address: 0x%llX\n", offsets::UnlockAchievement - sdk::GameAssembly);
}

void EnableHooks() {

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(offsets::StartAuthentication), &Functions::StartAuthentication_hk, (LPVOID*)&Functions::StartAuthentication_o) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(offsets::StartAuthentication));
	}
}

#define DEBUG

void init_il2cpp()
{
	//#ifdef DEBUG
	//CreateConsole(); // if using melonloader console is already created
	//system("cls");//清空当前控制台窗口所有内容
	//#endif // DEBUG
	GetModules();
	GetOffsets();
	EnableHooks();
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			init_il2cpp();
			kiero::bind(8, (void**)& oPresent, hkPresent);//把 DX11 第 8 号函数 Present 替换成我们自己的 hkPresent
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);//优化：减少不必要的线程通知，让 DLL 更稳定、不卡
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}