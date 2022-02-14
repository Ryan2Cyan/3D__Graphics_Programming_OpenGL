#include "instance.h"
#include "GL/glew.h"
#include "mat4_uniform.h"
#include <ext.hpp>


/////////// CONSTRUCTOR ///////////
application::application(const sdl_window input_window, const program_obj input_program, const vao_obj input_vao) :
    window{ input_window }, program{input_program}, vertex_array{input_vao}
{
    running = true;
}

/////////// UTILITY ///////////
void application::render_loop()
{
    SDL_Event event;
    GLfloat angle = 0;


    while (running) {
        window.change_window_colour(0.4f, 0.7f, 0.9f, 1.0f);
        window.adjust_viewport();

        // Initialise model matrix:
        mat4_uniform model_mat("u_model", 1, GL_FALSE);
        model_mat.set_location(program.get_id());
        model_mat.set_value(glm::mat4(1.0f));

        // Initialise projection matrix:
        mat4_uniform projection_mat("u_projection", 1, GL_FALSE);
        projection_mat.set_location(program.get_id());
        projection_mat.set_value(glm::perspective(
            glm::radians(45.0f),
            (float)window.get_width() / (float)window.get_height(),
            0.1f,
            100.f
        ));

        // Modify model matrix for rotation:
        model_mat.translate(glm::vec3(0, 0, -2.5f));
        model_mat.rotate(angle, glm::vec3(0, 1, 0));

        angle += 0.5f; // Increase angle next frame to rotate the triangle

        glUseProgram(program.get_id());
        glBindVertexArray(vertex_array.get_id());
        
        // Upload matrix data:
        model_mat.upload_data();
        projection_mat.upload_data();

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
