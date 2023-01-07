#pragma once
#include <imgui.h>
#include <imgui-SFML.h>

struct GUI{
    bool ai_vision{false};
    bool ship_invincible{false};
    bool asteroid_invincible{false};

    void AI_WINDOW(){
        ImGui::Begin("AI");
        ImGui::Checkbox("AI Vision", &ai_vision);
        ImGui::End();
    }

    void GAMEOBJ_WINDOW(){
        ImGui::Begin("Game Object");
        ImGui::Text("Invincibility");
        ImGui::Checkbox("Ship", &ship_invincible);
        ImGui::Checkbox("Asteroid", &asteroid_invincible);
        ImGui::End();
    }
};