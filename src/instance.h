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
    GLuint model_mat_location;
    GLuint projection_mat_location;

public:
    /////////// CONSTRUCTOR ///////////
    application(sdl_window input_window, program_obj input_program, vao_obj input_vao, GLuint input_model_mat, GLuint input_proj_mat);

    /////////// UTILITY ///////////
    void render_loop();

};
