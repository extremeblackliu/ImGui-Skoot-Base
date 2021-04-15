#pragma once
#include "Menu.h"
#include "..\imgui\imgui.h"
#include "Config.h"

ImGuiStyle* style = &ImGui::GetStyle();

// =====================================
// - Custom controls
// =====================================

#define InsertSpacer(x1) style->Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0); ImGui::BeginChild(x1, ImVec2(210.f, 18.f), false); {} ImGui::EndChild(); style->Colors[ImGuiCol_ChildBg] = ImColor(49, 49, 49, 255);
#define InsertGroupboxSpacer(x1) style->Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0); ImGui::BeginChild(x1, ImVec2(210.f, 9.f), false); {} ImGui::EndChild(); style->Colors[ImGuiCol_ChildBg] = ImColor(49, 49, 49, 255);
#define InsertGroupboxTitle(x1) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(11.f); ImGui::GroupBoxTitle(x1);

#define InsertGroupBoxLeft(x1,x2) ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(x1, ImVec2(258.f, x2), true);
#define InsertGroupBoxRight(x1,x2) ImGui::NewLine(); ImGui::SameLine(10.f); ImGui::BeginGroupBox(x1, ImVec2(258.f, x2), true);
#define InsertEndGroupBoxLeft(x1,x2) ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(x1, x2, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();
#define InsertEndGroupBoxRight(x1,x2) ImGui::EndGroupBox(); ImGui::SameLine(10.f); ImGui::BeginGroupBoxScroll(x1, x2, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();

#define InsertGroupBoxTop(x1,x2) ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(x1, x2, true);
#define InsertEndGroupBoxTop(x1,x2,x3) ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(x1, x2, x3, true); ImGui::EndGroupBoxScroll();

// =====================================
// - Default controls
// =====================================

#define InsertCheckbox(x1,x2) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::Checkbox(x1, &x2);
#define InsertSlider(x1,x2,x3,x4,x5) ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(159.f); ImGui::SliderFloat(x1, &x2, x3, x4, x5); ImGui::PopItemWidth();
#define InsertSliderWithoutText(x1,x2,x3,x4,x5) ImGui::Spacing(); ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(159.f); ImGui::SliderFloat(x1, &x2, x3, x4, x5); ImGui::PopItemWidth();
#define InsertCombo(x1,x2,x3) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertComboWithoutText(x1,x2,x3) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertMultiCombo(x1,x2,x3,x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(x1, x2, x3, x4); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertMultiComboWithoutText(x1,x2,x3,x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(x1, x2, x3, x4); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertColorPicker(x1,x2,x3) ImGui::SameLine(219.f); Menu::ColorPicker(x1, x2, x3);