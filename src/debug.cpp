#include "debug.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GL/glew.h>

namespace Debug {
                         
    // Renders debug window:
    void debug_state::RenderWindow() {

        ImGui::Begin("Debug Window");                          

        BackgroundColor(&background_color);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();

    }
   
    // Changes the background color:
    void debug_state::BackgroundColor(ImVec4* col_arg) {
        ImGui::ColorEdit3("clear color", (float*)&background_color, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel);
    }
}
