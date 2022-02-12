#include "instance.h"
#include "GL/glew.h"


/////////// CONSTRUCTOR ///////////
application::application(sdl_window input_window, program_obj input_program, vao_obj input_vao) : 
    window{ input_window }, program{input_program}, vertex_array{input_vao}
{
    running = true;
}

/////////// UTILITY ///////////
void application::render_loop()
{
    SDL_Event event;
    while (running) {
        window.change_window_colour(1.0f, 0.0f, 0.0f, 1.0f);
        glUseProgram(program.get_id());
        glBindVertexArray(vertex_array.get_id());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        SDL_GL_SwapWindow(window.get_window());

        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
    }
}
