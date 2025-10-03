#include <map>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "custom.h"




bool ImGui::Custom::FancyToggle(const char* label, bool* v) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    const float square_sz = 17;
    const float spacing = 6;
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect frame_bb(pos, pos + ImVec2(square_sz * 2, square_sz));
    const ImRect total_bb(pos, pos + ImVec2(square_sz * 2 + spacing + label_size.x, square_sz));

    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (pressed) {
        *v = !(*v);
        MarkItemEdited(id);
    }

    struct toggle_animation { float animation; };

    std::map<ImGuiID, toggle_animation> anim;
    
    auto it_anim = anim.find(id);
    if (it_anim == anim.end()) {
        anim.insert({ id, { 0.0f } });
        it_anim = anim.find(id);
    }

    it_anim->second.animation = ImLerp(it_anim->second.animation, *v ? 1.0f : 0.0f, 0.12f * (1.0f - ImGui::GetIO().DeltaTime));

    RenderNavHighlight(total_bb, id);

    ImVec2 toggle_min = frame_bb.Min;
    ImVec2 toggle_max = frame_bb.Min + ImVec2(30, 15);

    RenderFrame(toggle_min, toggle_max, ImColor(15, 15, 16), false, 9.0f);
    RenderFrame(toggle_min, toggle_max, ImColor(ImGui::GetStyle().Colors[ImGuiCol_FrameBg].x, ImGui::GetStyle().Colors[ImGuiCol_FrameBg].y, ImGui::GetStyle().Colors[ImGuiCol_FrameBg].z, it_anim->second.animation), false, 9.0f);

    window->DrawList->AddCircleFilled(ImVec2(toggle_min.x + 7 + 14 * it_anim->second.animation, toggle_min.y + 7), 5.0f, ImColor(1.0f, 1.0f, 1.0f), 30);

    if (label_size.x > 0.0f)
        RenderText(ImVec2(toggle_max.x + spacing, pos.y + 1), label);

    return pressed;
}

