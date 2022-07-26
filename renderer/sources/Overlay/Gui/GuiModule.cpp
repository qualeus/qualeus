#include "../../../include/Overlay/Gui/GuiModule.hpp"

namespace ImGui {

float AnimationLinear(bool direction, float value, float min, float max, float speed) {
    float diff = (max - min) / 100.0f;
    return direction ? std::min(value + diff * speed, max) : std::max(value - diff * speed, min);
}
float AnimationEaseInOut(bool direction, float value, float min, float max, float speed) {
    float difference_border = 0.1f + std::min(std::abs(value - max), std::abs(min - value)) / 10.0f;
    return direction ? std::min(value + difference_border * speed, max) : std::max(value - difference_border * speed, min);
}

void TextCenter(std::string text) {
    float font_size = ImGui::GetFontSize() * text.size() / 2;
    ImGui::SameLine(ImGui::GetWindowSize().x / 2 - font_size + (font_size / 2));

    ImGui::Text(text.c_str());
}

bool ValidationPopup(std::string title, std::string content) {
    bool always_open = true;
    bool validated = false;

    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(title.c_str(), &always_open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(content.c_str());

        ImGui::Dummy(ImVec2(0.0f, 7.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 7.0f));

        if (ImGui::Button("Validate", ImVec2(200, 0))) {
            validated = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(200, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
        ImGui::Separator();

        // static int unused_i = 0;
        // ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    return validated;
}

/* Helper Hover */
void Help(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

/* Tri-State CheckBox */
bool TriCheckBox(const char* label, int* v_tristate) {
    bool ret;
    if (*v_tristate == -1) {
        ImGui::PushItemFlag(ImGuiItemFlags_MixedValue, true);
        bool b = false;
        ret = ImGui::Checkbox(label, &b);
        if (ret) { *v_tristate = 1; }
        ImGui::PopItemFlag();
    } else {
        bool b = (*v_tristate != 0);
        ret = ImGui::Checkbox(label, &b);
        if (ret) { *v_tristate = (int)b; }
    }
    return ret;
}

bool PushButton(const char* str_id, bool* v) {
    if (v) {}
    if (ImGui::Button(str_id)) { *v = !v; }
    if (v) {}

    return v;
}

/* Toggle Button  */
bool ToggleButton(const char* str_id, bool* v) {
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    ImGui::InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked()) { *v = !*v; }

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.08f;
    if (g.LastActiveId == g.CurrentWindow->GetID(str_id))  // && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered()) {
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
    } else {
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));
    }

    if (ImGui::IsItemHovered()) {
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * 0.5f);
    } else {
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * 0.50f);
    }

    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

    return v;
}
}  // namespace ImGui