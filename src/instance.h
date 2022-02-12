#pragma once
#include <SDL.h>
#include "window.h"
#include "program.h"
#include "vao.h"

class application {
private:
    sdl_window window;
    bool running;
    program_obj program;
    vao_obj vertex_array;

public:
    /////////// CONSTRUCTOR ///////////
    application(sdl_window input_window, program_obj input_program, vao_obj input_vao);

    /////////// UTILITY ///////////
    void render_loop();

};
