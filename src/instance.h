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
    GLuint texture;

public:
    /////////// CONSTRUCTOR ///////////
    application(const sdl_window input_window, const program_obj input_program, const vao_obj input_vao,
        GLuint input_texture );

    /////////// UTILITY ///////////
    void render_loop();

};
