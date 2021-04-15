#include "Menu.h"
#include "MenuControls.h"
#include "Config.h"

#include "..\Hooks.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../Utils/GlobalVars.h"

Menu g_Menu;

static int tab = 0;

void Menu::ColorPicker(const char* name, float* color, bool alpha) {

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiStyle* style = &ImGui::GetStyle();

	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;

	ImGui::SameLine(219.f);
	ImGui::ColorEdit4(std::string{ "##" }.append(name).append("Picker").c_str(), color, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
}

void Menu::Render()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(6, 6);
	style->WindowRounding = 0;
	style->ScrollbarSize = 3.f;
	style->ScrollbarRounding = 2.f;

	ImGui::PushFont(g::menuFont);

	ImGui::SetNextWindowSize(ImVec2(660.f, 560.f));
	ImGui::BeginMenuBackground("ThighHighs & Tranny hake", &g_Menu.bMenuOpened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar); {

		ImGui::BeginChild("Complete Border", ImVec2(648.f, 548.f), false); {

			ImGui::Image(g::menuBg, ImVec2(648.f, 548.f));

		} ImGui::EndChild();

		ImGui::SameLine(6.f);

		style->Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0);

		ImGui::BeginChild("Menu Contents", ImVec2(648.f, 548.f), false); {

			ImGui::ColorBar("unicorn", ImVec2(648.f, 2.f));

			style->ItemSpacing = ImVec2(0.f, -1.f);
			
			ImGui::BeginTabs("Tabs", ImVec2(75.f, 542.f), false); {

				style->ItemSpacing = ImVec2(0.f, 0.f);

				style->ButtonTextAlign = ImVec2(0.5f, 0.47f);

				ImGui::PopFont();
				ImGui::PushFont(g::tabFont);

				switch (tab) {
				case 0:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::SelectedTab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;		
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 1:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::SelectedTab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 2:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::SelectedTab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 3:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::SelectedTab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 4:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::SelectedTab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 5:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));		

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::SelectedTab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::Tab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				case 6:
					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));

					if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
					if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
					if (ImGui::Tab("H", ImVec2(75.f, 75.f))) tab = 2;
					if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 3;
					if (ImGui::Tab("G", ImVec2(75.f, 75.f))) tab = 4;
					if (ImGui::Tab("I", ImVec2(75.f, 75.f))) tab = 5;
					if (ImGui::SelectedTab("E", ImVec2(75.f, 75.f))) tab = 6;

					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					break;
				}

				ImGui::PopFont();
				ImGui::PushFont(g::menuFont);

				style->ButtonTextAlign = ImVec2(0.5f, 0.5f);

			} ImGui::EndTabs();		

			ImGui::SameLine(75.f);

			ImGui::BeginChild("Tab Contents", ImVec2(572.f, 542.f), false); {

				style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);

				switch (tab) {

				case 0:
					Aimbot();
					break;
				case 1:
					Antiaim();
					break;
				case 2:
					Legit();
					break;
				case 3:
					Visuals();
					break;
				case 4:
					Misc();
					break;
				case 5:
					Skins();
					break;
				case 6:
					Players();
					break;
				}

				style->Colors[ImGuiCol_Border] = ImColor(10, 10, 10, 255);

			} ImGui::EndChild();

			style->ItemSpacing = ImVec2(4.f, 4.f);
			style->Colors[ImGuiCol_ChildBg] = ImColor(17, 17, 17, 255);

		} ImGui::EndChild();

		ImGui::PopFont();
		
	} ImGui::End();
}

void Menu::Shutdown() {

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

void Menu::Aimbot() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Aimbot", 506.f); {


		} InsertEndGroupBoxLeft("Aimbot Cover", "Aimbot");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Other", 506.f); {


		} InsertEndGroupBoxRight("Other Cover", "Other");
	}
}

void Menu::Antiaim() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Anti-aimbot angles", 506.f); {


		} InsertEndGroupBoxLeft("Anti-aimbot angles Cover", "Anti-aimbot angles");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Fake lag", 331.f); {


		} InsertEndGroupBoxRight("Fake lag Cover", "Fake lag");

		InsertSpacer("Fake lag - Other Spacer");

		InsertGroupBoxRight("Other", 157.f); {


		} InsertEndGroupBoxRight("Other Cover", "Other");
	}
}

void Menu::Legit() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	InsertGroupBoxTop("Weapon Selection", ImVec2(535.f, 61.f)); {


	} InsertEndGroupBoxTop("Weapon Selection Cover", "Weapon Selection", ImVec2(536.f, 11.f));

	InsertSpacer("Weapon Selection - Main Group boxes Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Aimbot", 427.f); {


		} InsertEndGroupBoxLeft("Aimbot Cover", "Aimbot");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Triggerbot", 277.f); {


		} InsertEndGroupBoxRight("Triggerbot Cover", "Triggerbot");

		InsertSpacer("Triggerbot - Other Spacer");

		InsertGroupBoxRight("Other", 132.f); {


		} InsertEndGroupBoxRight("Other Cover", "Other");
	}
}

void Menu::Visuals() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Player ESP", 331.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);




			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Player ESP Cover", "Player ESP");

		InsertSpacer("Player ESP - Colored models Spacer");

		InsertGroupBoxLeft("Colored models", 157.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);	



			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Colored models Cover", "Colored models");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Other ESP", 199.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);



			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Other ESP Cover", "Other ESP");

		InsertSpacer("Other ESP - Effects Spacer");

		InsertGroupBoxRight("Effects", 289.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);




			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Effects Cover", "Effects");
	}
}

void Menu::Misc() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Miscellaneous", 506.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);



			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Miscellaneous Cover", "Miscellaneous");

	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Settings", 156.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Settings Cover", "Settings");

		InsertSpacer("Settings - Other Spacer");

		InsertGroupBoxRight("Other", 332.f); {


		} InsertEndGroupBoxRight("Other Cover", "Other");
	}
}

void Menu::Skins() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Knife options", 112.f); {



		} InsertEndGroupBoxLeft("Knife options Cover", "Knife options");

		InsertSpacer("Fake lag - Other Spacer");

		InsertGroupBoxLeft("Glove options", 376.f); {



		} InsertEndGroupBoxLeft("Glove options Cover", "Glove options");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Weapon skin", 506.f); {


		} InsertEndGroupBoxRight("Weapon skin Cover", "Weapon skin");
	}
}

void Menu::Players() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Players", 506.f); {


		} InsertEndGroupBoxLeft("Players Cover", "Players");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Adjustments", 506.f); {


		} InsertEndGroupBoxRight("Adjustments Cover", "Adjustments");
	}
}