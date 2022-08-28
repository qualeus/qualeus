#include "../../../include/Overlay/Gui/GuiTheme.hpp"

namespace ovl {

GuiTheme::GuiTheme() { }

void GuiTheme::DarkTheme() {
    ImGui::StyleColorsDark();
}
void GuiTheme::VioletTheme() {
    ImGui::StyleColorsClassic();
}
void GuiTheme::LightTheme() {
    ImGui::StyleColorsLight();
}
void GuiTheme::ClassicTheme() {
    ImVec4 TRANSPARENT_0 = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
    ImVec4 TRANSPARENT_1 = ImVec4(0.00f, 0.00f, 0.00f, 0.15f);
    ImVec4 TRANSPARENT_2 = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    ImVec4 TRANSPARENT_3 = ImVec4(0.00f, 0.00f, 0.00f, 0.25f);
    ImVec4 TRANSPARENT_4 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);

    ImVec4 BACKGROUND_1 = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    ImVec4 BACKGROUND_2 = ImVec4(0.14f, 0.16f, 0.18f, 1.00f);
    ImVec4 BACKGROUND_3 = ImVec4(0.16f, 0.18f, 0.20f, 1.00f);
    ImVec4 BACKGROUND_4 = ImVec4(0.18f, 0.20f, 0.22f, 1.00f);

    ImVec4 CONTENT_1 = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    ImVec4 CONTENT_2 = ImVec4(0.80f, 0.80f, 0.80f, 0.80f);
    ImVec4 CONTENT_3 = ImVec4(0.80f, 0.80f, 0.80f, 0.60f);

    ImVec4 CONTENT_B = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    ImVec4 CONTENT_O = ImVec4(1.00f, 0.70f, 0.00f, 1.00f);

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = CONTENT_1;
    colors[ImGuiCol_TextDisabled] = CONTENT_2;
    colors[ImGuiCol_TextSelectedBg] = CONTENT_3;

    colors[ImGuiCol_WindowBg] = BACKGROUND_2;
    colors[ImGuiCol_ChildBg] = BACKGROUND_2;
    colors[ImGuiCol_PopupBg] = BACKGROUND_2;

    colors[ImGuiCol_Border] = TRANSPARENT_2;
    colors[ImGuiCol_BorderShadow] = TRANSPARENT_3;

    colors[ImGuiCol_FrameBg] = BACKGROUND_1;
    colors[ImGuiCol_FrameBgHovered] = BACKGROUND_3;
    colors[ImGuiCol_FrameBgActive] = BACKGROUND_1;

    colors[ImGuiCol_TitleBg] = BACKGROUND_1;
    colors[ImGuiCol_TitleBgActive] = BACKGROUND_1;
    colors[ImGuiCol_TitleBgCollapsed] = BACKGROUND_1;
    colors[ImGuiCol_MenuBarBg] = BACKGROUND_1;

    colors[ImGuiCol_ScrollbarBg] = TRANSPARENT_0;
    colors[ImGuiCol_ScrollbarGrab] = TRANSPARENT_1;
    colors[ImGuiCol_ScrollbarGrabHovered] = TRANSPARENT_2;
    colors[ImGuiCol_ScrollbarGrabActive] = TRANSPARENT_3;

    colors[ImGuiCol_CheckMark] = CONTENT_B;
    colors[ImGuiCol_SliderGrab] = TRANSPARENT_1;
    colors[ImGuiCol_SliderGrabActive] = TRANSPARENT_3;

    colors[ImGuiCol_Button] = TRANSPARENT_1;
    colors[ImGuiCol_ButtonHovered] = TRANSPARENT_2;
    colors[ImGuiCol_ButtonActive] = TRANSPARENT_3;

    colors[ImGuiCol_Header] = TRANSPARENT_1;
    colors[ImGuiCol_HeaderHovered] = TRANSPARENT_2;
    colors[ImGuiCol_HeaderActive] = TRANSPARENT_3;

    colors[ImGuiCol_Separator] = TRANSPARENT_2;
    colors[ImGuiCol_SeparatorHovered] = TRANSPARENT_3;
    colors[ImGuiCol_SeparatorActive] = TRANSPARENT_4;

    colors[ImGuiCol_ResizeGrip] = TRANSPARENT_1;
    colors[ImGuiCol_ResizeGripHovered] = TRANSPARENT_2;
    colors[ImGuiCol_ResizeGripActive] = TRANSPARENT_3;

    colors[ImGuiCol_Tab] = TRANSPARENT_1;
    colors[ImGuiCol_TabHovered] = TRANSPARENT_2;
    colors[ImGuiCol_TabActive] = TRANSPARENT_3;
    colors[ImGuiCol_TabUnfocused] = TRANSPARENT_1;
    colors[ImGuiCol_TabUnfocusedActive] = TRANSPARENT_3;

    colors[ImGuiCol_DockingPreview] = TRANSPARENT_2;
    colors[ImGuiCol_DockingEmptyBg] = TRANSPARENT_2;

    colors[ImGuiCol_PlotLines] = CONTENT_O;
    colors[ImGuiCol_PlotLinesHovered] = CONTENT_O;
    colors[ImGuiCol_PlotHistogram] = CONTENT_O;
    colors[ImGuiCol_PlotHistogramHovered] = CONTENT_O;

    colors[ImGuiCol_TableHeaderBg] = TRANSPARENT_2;
    colors[ImGuiCol_TableBorderStrong] = TRANSPARENT_2;
    colors[ImGuiCol_TableBorderLight] = TRANSPARENT_1;
    colors[ImGuiCol_TableRowBg] = TRANSPARENT_0;
    colors[ImGuiCol_TableRowBgAlt] = TRANSPARENT_3;

    colors[ImGuiCol_DragDropTarget] = TRANSPARENT_3;

    colors[ImGuiCol_NavHighlight] = TRANSPARENT_3;
    colors[ImGuiCol_NavWindowingHighlight] = TRANSPARENT_3;
    colors[ImGuiCol_NavWindowingDimBg] = TRANSPARENT_3;
    colors[ImGuiCol_ModalWindowDimBg] = TRANSPARENT_3;

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6;
    style.WindowBorderSize = 1;

    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(8.00f, 6.00f);

    style.ItemSpacing = ImVec2(4.00f, 0.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);

    style.ScrollbarSize = 15;
    style.ScrollbarRounding = 1;
    style.GrabMinSize = 10;

    style.ChildRounding = 1;
    style.ChildBorderSize = 0;
    style.FrameRounding = 1;
    style.FrameBorderSize = 0;
    style.PopupRounding = 4;
    style.PopupBorderSize = 0;
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 20;
    // style.ColumnsMinSpacing = 0; // (float)

    style.GrabRounding = 1;
    style.TabRounding = 4;
    style.TabBorderSize = 0;

    // style.Alpha = 0; // (float)
    // style.WindowMinSize = 0; // (ImVec2)

    style.WindowTitleAlign = ImVec2(0.00f, 0.50f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ColorButtonPosition = ImGuiDir_Left;
    style.ButtonTextAlign = ImVec2(0.50f, 0.50f);

    style.SelectableTextAlign = ImVec2(0.00f, 0.00f);
    style.DisplayWindowPadding = ImVec2(0.00f, 0.00f);
    style.DisplaySafeAreaPadding = ImVec2(0.00f, 0.00f);

    // style.MouseCursorScale = 0; // (float)
    // style.AntiAliasedLines = 0; // (bool)
    // style.AntiAliasedFill = 0; // (bool)
    // style.CurveTessellationTol = 0; // (float)
    // style.CircleSegmentMaxError = 0; // (float)
}

}  // namespace ovl