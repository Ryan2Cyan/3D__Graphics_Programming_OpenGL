#include "instance.h"
#include "GL/glew.h"
#include <glm.hpp>
#include <ext.hpp>


/////////// CONSTRUCTOR ///////////
application::application(sdl_window input_window, program_obj input_program, vao_obj input_vao, GLuint input_model_mat, GLuint input_proj_mat) :
    window{ input_window }, program{input_program}, vertex_array{input_vao}, model_mat_location{input_model_mat}, projection_mat_location{input_proj_mat}
{
    running = true;
}

/////////// UTILITY ///////////
void application::render_loop()
{
    SDL_Event event;
    float angle = 0;

    while (running) {
        window.change_window_colour(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 projection = glm::perspective(  // Prepare perspective projection matrix
                glm::radians(45.0f),
                (float)window.get_width() / (float)window.get_height(),
                0.1f,
                100.f
            );
        glm::mat4 model(1.0f);  // Prepare model matrix
        model = glm::translate(model, glm::vec3(0, 0, -2.5f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
        angle += 0.5f; // Increase angle next frame to rotate the triangle
        glUseProgram(program.get_id());
        glBindVertexArray(vertex_array.get_id());
        glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, glm::value_ptr(model));  // Upload model matrix
        glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, glm::value_ptr(projection));  // Upload projection matrix
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
