#pragma once
#include "imgui/imgui.h"

namespace Debug {
    struct debug_state {
        ImVec4 background_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);  // Background color
        bool show_debug_window = true;
        bool show_bg_color_change = true;
        bool show_fps_counter = true;

        void RenderWindow();

        void BackgroundColor(ImVec4* col_arg);
    };
}