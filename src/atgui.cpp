#include "atgui.h"

bool UI::isVisible = false;

ImColor Settings::UI::mainColor = ImColor(54, 54, 54, 255);
ImColor Settings::UI::bodyColor = ImColor(24, 24, 24, 240);
ImColor Settings::UI::fontColor = ImColor(255, 255, 255, 255);
bool showMainWindow = true;
bool showSkinChangerWindow = false;
bool showConfigWindow = false;
bool showColorsWindow = false;
float gunWearAmount = 0.005f;
float knifeWearAmount = 0.005f;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
					 static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
					   static_cast<void*>(&values), values.size());
	}
}

void UI::SetVisible(bool visible)
{
	UI::isVisible = visible;
	cvar->FindVar("cl_mouseenable")->SetValue(!UI::isVisible);
}

void UI::SetupColors()
{

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered = ImVec4(Settings::UI::mainColor.Value.x + 0.1f, Settings::UI::mainColor.Value.y + 0.1f, Settings::UI::mainColor.Value.z + 0.1f, Settings::UI::mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.Value.x + 0.2f, Settings::UI::mainColor.Value.y + 0.2f, Settings::UI::mainColor.Value.z + 0.2f, Settings::UI::mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w + .1f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 1);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	style.Colors[ImGuiCol_Text] = Settings::UI::fontColor;
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = Settings::UI::bodyColor;
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]= frameBgColor;
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg]= Settings::UI::mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = frameBgColor;
	style.Colors[ImGuiCol_CheckMark] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_Header] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
	style.Colors[ImGuiCol_Column] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGrip] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_PlotHistogramHovered] =  mainColorHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void SetupMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &showMainWindow, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Skin Changer Window", &showSkinChangerWindow, 0, ImVec2(ImGui::CalcTextSize("Skin Changer Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Config Window", &showConfigWindow, 0, ImVec2(ImGui::CalcTextSize("Config Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Spectators Window", &Settings::ShowSpectators::enabled, 0, ImVec2(ImGui::CalcTextSize("Spectators Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Colors Window", &showColorsWindow, 0, ImVec2(ImGui::CalcTextSize("Colors Window", NULL, true).x, 0.0f));

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void ColorsWindow()
{
	if (!showColorsWindow)
		return;

	const char* colorSelection[] =
			{
					"UI Main",
					"UI Body",
					"UI Font",
					"FOV Circle",
					"ESP - Team",
					"ESP - Enemy",
					"ESP - Enemy Visible",
					"ESP - Bones",
					"ESP - Bomb",
					"ESP - Team Text",
					"ESP - Enemy Text",
					"ESP - Enemy Visible Text",
					"Chams - Team",
					"Chams - Team Visible",
					"Chams - Enemy",
					"Chams - Enemy Visible",
					"Glow - Team",
					"Glow - Enemy",
					"Glow - Enemy Visible",
					"Glow - Weapon",
					"Glow - Grenade",
					"Glow - Defuser",
					"Glow - Defuser",
					"Dlights - Team",
					"Dlights - Enemy",
			};
	ImColor* colors[] =
			{
					&Settings::UI::mainColor,
					&Settings::UI::bodyColor,
					&Settings::UI::fontColor,
					&Settings::ESP::FOVCrosshair::color,
					&Settings::ESP::ally_color,
					&Settings::ESP::enemy_color,
					&Settings::ESP::enemy_visible_color,
					&Settings::ESP::bones_color,
					&Settings::ESP::bomb_color,
					&Settings::ESP::Info::ally_color,
					&Settings::ESP::Info::enemy_color,
					&Settings::ESP::Info::enemy_visible_color,
					&Settings::ESP::Chams::players_ally_color,
					&Settings::ESP::Chams::players_ally_visible_color,
					&Settings::ESP::Chams::players_enemy_color,
					&Settings::ESP::Chams::players_enemy_visible_color,
					&Settings::ESP::Glow::ally_color,
					&Settings::ESP::Glow::enemy_color,
					&Settings::ESP::Glow::enemy_visible_color,
					&Settings::ESP::Glow::weapon_color,
					&Settings::ESP::Glow::grenade_color,
					&Settings::ESP::Glow::defuser_color,
					&Settings::Dlights::ally_color,
					&Settings::Dlights::enemy_color,
			};
	static int colorSelected = 0;

	ImGui::SetNextWindowSize(ImVec2(540, 260), ImGuiSetCond_Always);
	if (ImGui::Begin("Colors", &showColorsWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, NULL, true);
		{
			ImGui::PushItemWidth(-1);
				ImGui::ListBox("##COLORSELECTION", &colorSelected, colorSelection, IM_ARRAYSIZE(colorSelection), 10);
			ImGui::PopItemWidth();
		}
		ImGui::NextColumn();
		{
			UI::ColorPicker4((float *)colors[colorSelected]);
		}
		ImGui::End();
	}
}

void AimbotTab()
{
	UI::ReverseCheckbox("Enabled", &Settings::Aimbot::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Silent Aim", &Settings::Aimbot::silent);

		UI::ReverseCheckbox("Aimkey Only", &Settings::Aimbot::aimkey_only);
		ImGui::SameLine();

		UI::KeyBindButton(&Settings::Aimbot::aimkey);

		UI::ReverseCheckbox("Recoil Control", &Settings::Aimbot::RCS::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##RCS", &Settings::Aimbot::RCS::value, 0, 2);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Aim", &Settings::Aimbot::AutoAim::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##AA", &Settings::Aimbot::fov, 0, 180);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Smoothing", &Settings::Aimbot::Smooth::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##SMOOTH", &Settings::Aimbot::Smooth::value, 0, 1);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Smooth Salting", &Settings::Aimbot::Smooth::Salting::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##SALT", &Settings::Aimbot::Smooth::Salting::percentage, 0, 100);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Aim Step", &Settings::Aimbot::AimStep::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##STEP", &Settings::Aimbot::AimStep::value, 0, 100);
			ImGui::SliderFloat("##ERROR", &Settings::Aimbot::errorMargin, 0, 2, "Error Margin 0%f");
		ImGui::PopItemWidth();
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("Friendly", &Settings::Aimbot::friendly);
		ImGui::SameLine();
		const char* targets[] = { "PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };
		ImGui::PushItemWidth(175);
			ImGui::Combo("##AIMTARGET", &Settings::Aimbot::bone, targets, IM_ARRAYSIZE(targets));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Pistol", &Settings::Aimbot::AutoPistol::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("No Shoot", &Settings::Aimbot::no_shoot);

		UI::ReverseCheckbox("Auto Shoot", &Settings::Aimbot::AutoShoot::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Auto Scope", &Settings::Aimbot::AutoShoot::autoscope);
	}

}

void TriggerbotTab()
{
	ImGui::Columns(2, NULL, false);
	UI::ReverseCheckbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::SameLine();

	UI::KeyBindButton(&Settings::Triggerbot::key);

	ImGui::Separator();

	UI::ReverseCheckbox("Delay", &Settings::Triggerbot::Delay::enabled);
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
		ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
	ImGui::PopItemWidth();

	ImGui::Separator();
	ImGui::PushItemWidth(150);
		ImGui::ListBoxHeader("##TRIGGERFILTER", 6);
			ImGui::Selectable("Friendly", &Settings::Triggerbot::Filter::friendly);
			ImGui::Selectable("Head", &Settings::Triggerbot::Filter::head);
			ImGui::Selectable("Chest", &Settings::Triggerbot::Filter::chest);
			ImGui::Selectable("Stomach", &Settings::Triggerbot::Filter::stomach);
			ImGui::Selectable("Arms", &Settings::Triggerbot::Filter::arms);
			ImGui::Selectable("Legs", &Settings::Triggerbot::Filter::legs);
		ImGui::ListBoxFooter();
	ImGui::PopItemWidth();
}

void VisualsTab()
{
	const char* WallTypes[] = { "Flat 2D", "Box 3D" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* ChamsTypes[] = { "Normal", "Flat" };
	const char* ArmsTypes[] = { "Default", "Rainbow", "Wireframe", "None" };

	ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		if (ImGui::BeginChild("ESP", ImVec2(0, 0), true))
		{
			ImGui::Text("Player ESP");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Walls", &Settings::ESP::Walls::enabled);
				ImGui::Checkbox("Tracers", &Settings::ESP::Tracer::enabled);
				ImGui::Checkbox("Show Bones", &Settings::ESP::Bones::enabled);
				ImGui::Checkbox("Show Friendly", &Settings::ESP::friendly);
				ImGui::Checkbox("Visibility Check", &Settings::ESP::visibility_check);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##WALLTYPE", &Settings::ESP::Walls::type, WallTypes, IM_ARRAYSIZE(WallTypes));
					ImGui::Combo("##TRACERTYPE", &Settings::ESP::Tracer::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Player Information");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Name", &Settings::ESP::Info::showName);
				ImGui::Checkbox("Health", &Settings::ESP::Info::showHealth);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Weapon", &Settings::ESP::Info::showWeapon);
				ImGui::Checkbox("Colored", &Settings::ESP::Info::colorCode);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("World ESP");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Dropped Weapon Names", &Settings::ESP::Weapons::enabled);
				ImGui::Checkbox("Dropped Weapon Glow", &Settings::ESP::Glow::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Bomb ESP", &Settings::ESP::Bomb::enabled);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		if (ImGui::BeginChild("Chams", ImVec2(0, 0), true))
		{
			ImGui::Text("Chams");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Players", &Settings::ESP::Chams::players);
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				ImGui::PushID(1);
					ImGui::Checkbox("Visibility Check", &Settings::ESP::Chams::visibility_check);
				ImGui::PopID();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##CHAMSTYPE", &Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
					ImGui::Combo("##ARMSTYPE", &Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Crosshair");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				ImGui::Checkbox("No View Punch", &Settings::View::NoPunch::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000);
				ImGui::PopItemWidth();
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}

void HvHTab()
{
	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Y Axis", &Settings::AntiAim::enabled_Y);
		const char* YFakeTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		const char* YActualTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		const char* XTypes[] = { "UP", "DOWN", "DANCE" };

		if (ImGui::BeginChild("YAWTYPE", ImVec2(0, 60), true))
		{
			ImGui::Columns(2, NULL, false);
			{
				ImGui::SetColumnOffset(1, 150);
				ImGui::Text("Fake");
				ImGui::Text("Actual");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(150);
					ImGui::Combo("##YFAKETYPE", &Settings::AntiAim::type_fake_Y, YFakeTypes, IM_ARRAYSIZE(YFakeTypes));
					ImGui::Combo("##YACTUALTYPE", &Settings::AntiAim::type_Y, YActualTypes, IM_ARRAYSIZE(YActualTypes));
				ImGui::PopItemWidth();
			}
			ImGui::EndChild();
		}

		UI::ReverseCheckbox("X Axis", &Settings::AntiAim::enabled_X);

		ImGui::SameLine();
		ImGui::PushItemWidth(174);
			ImGui::Combo("##XTYPE", &Settings::AntiAim::type_X, XTypes, IM_ARRAYSIZE(XTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Edge", &Settings::AntiAim::HeadEdge::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##EDGEDISTANCE", &Settings::AntiAim::HeadEdge::distance, 10, 30);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Crouch", &Settings::Aimbot::AutoCrouch::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Auto Stop", &Settings::Aimbot::AutoStop::enabled);

		UI::ReverseCheckbox("Resolver", &Settings::Resolver::enabled);
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("Auto Wall", &Settings::Aimbot::AutoWall::enabled);
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##AUTOWALLDMG", &Settings::Aimbot::AutoWall::value, 0, 100, "Min Damage %f");
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(150);
			ImGui::ListBoxHeader("##AUTOWALLBODYPART", 6);
				ImGui::Selectable("Head", &Settings::Aimbot::AutoWall::bones[HITBOX_HEAD]);
				ImGui::Selectable("Neck", &Settings::Aimbot::AutoWall::bones[HITBOX_NECK]);
				ImGui::Selectable("Pelvis", &Settings::Aimbot::AutoWall::bones[HITBOX_PELVIS]);
				ImGui::Selectable("Spine", &Settings::Aimbot::AutoWall::bones[HITBOX_SPINE]);
				ImGui::Selectable("Legs", &Settings::Aimbot::AutoWall::bones[HITBOX_LEGS]);
				ImGui::Selectable("Arms", &Settings::Aimbot::AutoWall::bones[HITBOX_ARMS]);
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	}
}

void MiscTab()
{
	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Bunny Hop", &Settings::BHop::enabled);

		UI::ReverseCheckbox("Auto Strafe", &Settings::AutoStrafe::enabled);
		ImGui::SameLine();

		const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right" };
		ImGui::PushItemWidth(-1);
			ImGui::Combo("##STRAFETYPE", &Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("AirStuck", &Settings::Airstuck::enabled);
		ImGui::SameLine();

		UI::KeyBindButton(&Settings::Airstuck::key);

		UI::ReverseCheckbox("Position Spammer", &Settings::Spammer::PositionSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::PositionSpammer::say_team);

		UI::ReverseCheckbox("Kill Spammer", &Settings::Spammer::KillSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::KillSpammer::say_team);

		UI::ReverseCheckbox("Chat Spammer", &Settings::Spammer::NormalSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::NormalSpammer::say_team);

		UI::ReverseCheckbox("Custom Clantag", &Settings::ClanTagChanger::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##CLANTAGTEXT", Settings::ClanTagChanger::value, 15);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Animate Clantag", &Settings::ClanTagChanger::animation);
		ImGui::SameLine();
		const char* AnimationTypes[] = { "Marquee", "Words", "Letters" };
		ImGui::PushItemWidth(150);
			ImGui::Combo("##ANIMATIONTYPE", &Settings::ClanTagChanger::type, AnimationTypes, IM_ARRAYSIZE(AnimationTypes));
		ImGui::PopItemWidth();
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("No Flash", &Settings::Noflash::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("View FOV", &Settings::FOVChanger::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Viewmodel FOV", &Settings::FOVChanger::viewmodel_enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodel_value, 0, 360);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Fake Lag", &Settings::FakeLag::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Accept", &Settings::AutoAccept::enabled);

		UI::ReverseCheckbox("Show Ranks", &Settings::ShowRanks::enabled);

		static char nickname[127] = "nickname";

		if (ImGui::Button("No Name"))
		{
			Settings::NameChanger::enabled = true;
			Settings::NameChanger::last_blank = true;
		}
		ImGui::SameLine();

		if (ImGui::Button("Set Nickname"))
			NameChanger::SetName(nickname);
		ImGui::SameLine();

		ImGui::PushItemWidth(-1);
			ImGui::InputText("##NICKNAMETEXT", nickname, 127);
		ImGui::PopItemWidth();
	}
}

void MainWindow()
{
	if (!showMainWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(1000, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("AimTux", &showMainWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] =
				{
						"Aimbot",
						"Triggerbot",
						"Visuals",
						"HvH",
						"Misc",
				};
		int tabs_size = sizeof(tabs) / sizeof(tabs[0]);

		for (int i = 0; i < tabs_size; i++)
		{
			ImVec2 windowSize = ImGui::GetWindowSize();
			int width = windowSize.x / tabs_size - 9;
			int height = 25;

			if (ImGui::Button(tabs[i], ImVec2(width, height)))
				page = i;

			if (i < tabs_size - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch (page)
		{
			case 0:
				AimbotTab();
				break;
			case 1:
				TriggerbotTab();
				break;
			case 2:
				VisualsTab();
				break;
			case 3:
				HvHTab();
				break;
			case 4:
				MiscTab();
				break;
		}

		ImGui::End();
	}
}

void SkinChangerWindow()
{
	if (!showSkinChangerWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin Changer", &showSkinChangerWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* guns[] = { "AK-47", "M4A1-S", "AWP", "USP", "P2000", "Glock", "Deagle", "Famas", "Galil-AR", "Negev", "SCAR-20", "G3SG1" };
		static int current_gun = 0;
		const char* ak47_skins[] = { "Candy apple", "potato", "donut", "Candy apple", "potato", "donut", "Candy apple", "potato", "donut", "Candy apple", "potato", "donut", "Candy apple", "potato", "donut", };
		static int current_ak47_skin = 0;
		const char* m4a1_skins[] = { "pizza", "cheese", "tomato", "12 year olds", "Candy apple", "potato", "donut", "Candy apple", };
		static int current_m4a1_skin = 0;
		static char gunSkinSeed[5];
		static char gunStatTrak[9];
		static char gunName[18];
		static char knifeSkinSeed[4];
		static char knifeStatTrak[9];
		static char knifeName[18];

		ImGui::Text("Guns");
		if (ImGui::BeginChild("GunsSection", ImVec2(0, 325), true))
		{
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
					ImGui::ListBox("##GUNS", &current_gun, guns, IM_ARRAYSIZE(guns), 10);
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					switch (current_gun)
					{
						case 0:
							ImGui::ListBox("##AK47_SKINS", &current_ak47_skin, ak47_skins, IM_ARRAYSIZE(ak47_skins), 10);
							break;
						case 1:
							ImGui::ListBox("##M4A1_SKINS", &current_m4a1_skin, m4a1_skins, IM_ARRAYSIZE(m4a1_skins), 10);
							break;
					}
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##GUNWEAR", &gunWearAmount, 0.005f, 1.f, "Wear amount: %f");
				ImGui::PopItemWidth();

				ImGui::Text("Seed");
				ImGui::SameLine();
				ImGui::PushItemWidth(-1);
					ImGui::InputText("##GUNSEED", gunSkinSeed, IM_ARRAYSIZE(gunSkinSeed));
				ImGui::PopItemWidth();

				ImGui::Text("StatTrak");
				ImGui::SameLine();
				ImGui::PushItemWidth(-1);
					ImGui::InputText("##GUNSTATRAK", gunStatTrak, IM_ARRAYSIZE(gunStatTrak));
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Column 4");
				ImGui::Button("Load", ImVec2(-1, 0));
				ImGui::Button("Apply", ImVec2(-1, 0));
				ImGui::Button("Save", ImVec2(-1, 0));
			}
			ImGui::EndChild();
		}

		ImGui::Text("Knife");
		if (ImGui::BeginChild("KnifeSection", ImVec2(0, 200), true))
		{
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Text("Column 5");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Column 6");
			}
			ImGui::Columns(1);
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Text("Column 7");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Column 8");
			}

			ImGui::EndChild();
		}

		ImGui::End();
	}
}

void ConfigWindow()
{
	if (!showConfigWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Configs", &showConfigWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		static std::vector<std::string> configItems = GetConfigs();
		static int configItemCurrent = -1;

		if (ImGui::Button("Refresh"))
			configItems = GetConfigs();

		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent] << "/config.json";

			Settings::LoadDefaultsOrSave(path);
		}

		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent];

			Settings::DeleteConfig(path);

			configItems = GetConfigs();
			configItemCurrent = -1;
		}

		static char buf[128] = "";
		ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

		ImGui::SameLine();
		if (ImGui::Button("Add"))
		{
			printf("%s\n", buf);
			if (strlen(buf) == 0)
				return;

			pstring path = GetConfigDirectory();
			path << buf;

			printf("path: %s\n", path.c_str());

			if (DoesFileExist(path.c_str()))
				return;

			mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			Settings::LoadDefaultsOrSave(path << "/config.json");

			configItems = GetConfigs();
		}

		if (ImGui::ListBox("", &configItemCurrent, configItems))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent] << "/config.json";

			Settings::LoadConfig(path);
		}

		ImGui::End();
	}
}

void SpectatorsWindow()
{
	if (!Settings::ShowSpectators::enabled)
		return;

	if (!UI::isVisible && !engine->IsInGame())
		return;

	ImGui::SetNextWindowSize(ImVec2(50, 100), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Spectators", &Settings::ShowSpectators::enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		ImGui::Columns(2);
		ImGui::Separator();

		ImGui::Text("Name");
		ImGui::NextColumn();

		ImGui::Text("Mode");
		ImGui::NextColumn();

		C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
		std::list<int> observators = ShowSpectators::GetObservervators(localplayer);

		for (int entityId : observators)
		{
			C_BaseEntity* entity = entitylist->GetClientEntity(entityId);

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(entityId, &entityInformation);

			if (strcmp(entityInformation.guid, "BOT") == 0)
				continue;

			ImGui::Separator();

			ImGui::Text(entityInformation.name);
			ImGui::NextColumn();

			switch (*entity->GetObserverMode())
			{
				case ObserverMode_t::OBS_MODE_IN_EYE:
					ImGui::Text("Perspective");
					break;
				case ObserverMode_t::OBS_MODE_CHASE:
					ImGui::Text("3rd person");
					break;
				case ObserverMode_t::OBS_MODE_ROAMING:
					ImGui::Text("Free look");
					break;
				case ObserverMode_t::OBS_MODE_DEATHCAM:
					ImGui::Text("Deathcam");
					break;
				case ObserverMode_t::OBS_MODE_FREEZECAM:
					ImGui::Text("Freezecam");
					break;
				case ObserverMode_t::OBS_MODE_FIXED:
					ImGui::Text("Fixed");
					break;
			}
			ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::End();
	}
}

void UI::SwapWindow()
{
	if (UI::isVisible)
		return;

	if (engine->IsInGame())
		return;

	Draw::ImDrawText(ImVec2(4.f, 4.f), ImColor(255, 255, 255, 255), "AimTux", NULL, 0.0f, NULL, ImFontFlags_Shadow);
}

void UI::SetupWindows()
{
	if (UI::isVisible)
	{
		SetupMainMenuBar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(960, 520));
			MainWindow();
		ImGui::PopStyleVar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(500, 600));
			SkinChangerWindow();
		ImGui::PopStyleVar();

		ConfigWindow();
		ColorsWindow();
	}

	SpectatorsWindow();
}
