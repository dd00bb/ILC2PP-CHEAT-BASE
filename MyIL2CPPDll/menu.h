#pragma once
#include "imgui/imgui.h"
#include "vars.h"
using namespace ImGui;

void ImGuiTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	// ===================== 核心配色：#222222 背景 + #BFFF00 主色 =====================
	// 窗口背景
	colors[ImGuiCol_WindowBg] = ImVec4(0.133f, 0.133f, 0.133f, 1.00f);   // #222222
	// 子窗口/面板背景
	colors[ImGuiCol_ChildBg] = ImVec4(0.133f, 0.133f, 0.133f, 1.00f);     // #222222
	// 弹窗背景
	colors[ImGuiCol_PopupBg] = ImVec4(0.133f, 0.133f, 0.133f, 1.00f);     // #222222

	// 边框（主色半透明）
	colors[ImGuiCol_Border] = ImVec4(0.749f, 1.00f, 0.00f, 0.40f);       // #BFFF00 40%透明度
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);   // 无阴影

	// 输入框/按钮背景
	colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);        // 浅一点的深灰
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.749f, 1.00f, 0.00f, 0.20f); //  hover 主色遮罩
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.749f, 1.00f, 0.00f, 0.40f);  // 点击 主色遮罩

	// 标题栏
	colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);        // 更深的标题背景
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.749f, 1.00f, 0.00f, 1.00f);  // 激活标题 #BFFF00
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

	// 文字颜色
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);           // 纯白文字
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);   // 灰色禁用文字

	// 分割线
	colors[ImGuiCol_Separator] = ImVec4(0.749f, 1.00f, 0.00f, 0.60f);     // #BFFF00
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.749f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.749f, 1.00f, 0.00f, 1.00f);

	// 滑块/拖动条
	//colors[ImGuiCol_Grab] = ImVec4(0.749f, 1.00f, 0.00f, 0.80f);
	//colors[ImGuiCol_GrabHovered] = ImVec4(0.749f, 1.00f, 0.00f, 1.00f);
	//colors[ImGuiCol_GrabActive] = ImVec4(0.749f, 1.00f, 0.00f, 1.00f);

	// 按钮
	colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.749f, 1.00f, 0.00f, 0.50f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.749f, 1.00f, 0.00f, 0.80f);

	// 标签页
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.749f, 1.00f, 0.00f, 0.30f);
	colors[ImGuiCol_TabActive] = ImVec4(0.749f, 1.00f, 0.00f, 0.80f);

	// ===================== 样式圆角、间距 =====================
	style.WindowRounding = 10.0f;    // 窗口圆角
	style.FrameRounding = 6.0f;     // 组件圆角
	style.PopupRounding = 8.0f;     // 弹窗圆角
	style.GrabRounding = 4.0f;     // 滑块圆角
	style.TabRounding = 6.0f;      // 标签页圆角

	style.FrameBorderSize = 1.0f;   // 组件边框宽度
	style.WindowBorderSize = 1.0f;  // 窗口边框宽度

	style.ItemSpacing = ImVec2(8, 8);       // 组件间距
	style.ItemInnerSpacing = ImVec2(6, 6);  // 内部间距
}

void DrawMenu()
{
	ImGuiTheme();
	static int page = 0;
	if (ImGui::Begin("                            ",
		nullptr,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetWindowPos(ImVec2(500, 200), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(450, 450), ImGuiCond_Once);

		ImGui::Separator();

		ImGui::BeginChild("InfoArea", ImVec2(0, 150), true);
		{

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("!!!    IPhoneP40Pro 制作  !!!").x) / 2);
			ImGui::TextColored(ImVec4(0.7f, 0.8f, 1.0f, 1.0f), "!!!   IPhoneP40Pro 制作   !!!");

			ImGui::Spacing();

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("!!!   哔哩哔哩--IPhoneP40Pro   !!!").x) / 2);
			ImGui::TextColored(ImVec4(0.8f, 0.7f, 1.0f, 1.0f), "!!!   哔哩哔哩--IPhoneP40Pro   !!!");

			ImGui::Spacing();

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("!!!   需要Epic版本   !!!").x) / 2);
			ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.7f, 1.0f), "!!!   需要Epic版本   !!!");
			ImGui::Spacing();

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Version: 1.0.0").x) / 2);
			ImGui::TextDisabled("Version: 1.0.0");
		}
		ImGui::EndChild();

		ImGui::Separator();

		ImGui::BeginChild("ButtonArea", ImVec2(0, 200), true);
		{

			float buttonWidth = ImGui::GetWindowWidth() * 0.7f;
			float buttonHeight = 40.0f;
			float buttonX = (ImGui::GetWindowWidth() - buttonWidth) / 2;

			ImGui::Spacing();

			ImGui::SetCursorPosX(buttonX);

			if (ImGui::Button("更多Epic游戏成就解锁器", ImVec2(buttonWidth, buttonHeight)))
			{

			}

			ImGui::Spacing();
			//ImGui::Checkbox("立即胜利", &vars::win);
			//ImGui::Spacing();

			ImGui::SetCursorPosX(buttonX);
			if (ImGui::Button("B站搜索IPhoneP40Pro", ImVec2(buttonWidth, buttonHeight)))
			{
				//vars::num++;
				//vars::called = false;
				vars::start = true;
			}

			ImGui::Spacing();

			ImGui::SetCursorPosX(buttonX);
			if (ImGui::Button("我的B站主页", ImVec2(buttonWidth, buttonHeight)))
			{
				ShellExecuteA(nullptr, "open", "https://space.bilibili.com/1338487878", nullptr, nullptr, SW_SHOWNORMAL);
			}
		}
		ImGui::EndChild();


		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("© 2026 IPhoneP40Pro All Rights Reserved").x) / 2);
		ImGui::TextDisabled("© 2026 IPhoneP40Pro All Rights Reserved");
	}
	ImGui::End();

}

