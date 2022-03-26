#define SDL_MAIN_HANDLED 

#include "Gp.h"
#include <wavefront/wavefront.h>
#include <SDL.h>
#include <GL/glew.h>
#include <memory>

#include <ext.hpp>
#include <iostream>
#include <vector>

const GLchar* font_filepath = "Additional_Files\\fonts\\JetBrainsMono-Light.ttf";
const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";
const GLchar* basic_v_filepath = "Additional_Files/basic_vert2.txt";
const GLchar* basic_f_filepath = "Additional_Files/basic_frag2.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/fragment_shader.txt";
const GLchar* image_filepath = "Additional_Files/images/image_test.PNG";
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";

int main()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create window with graphics context
	int window_width = 720;
	int window_height = 720;

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Window* window = SDL_CreateWindow("3DGP Assignment 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_width, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync


    // Create context for Gp:
    std::shared_ptr<GpContext> context = Gp::CreateContext(); 
	
    // Create texture:
    std::shared_ptr<Texture> texture = context->CreateTexture(image_filepath);

    // Create vertex array:
    std::shared_ptr<VertexArray> image = context->Create2DImage(image_filepath);
    

    // Main loop
    bool done = false;
    bool window_open = true;
    
	// Background color:
	glm::vec4 background_col = { 0.6f, 0.7f, 0.8f, 1.0f };

    // Create Shader:
	std::shared_ptr<Shader> shader = context->CreateShader(basic_v_filepath, basic_f_filepath);
	

    
    while (!done)
    { 
        // Input loop:
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Rendering:
        glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, window_width, window_height);
        glClearColor(background_col.x * background_col.w, background_col.y * background_col.w, background_col.z * background_col.w, background_col.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind texture:
        glBindTexture(GL_TEXTURE_2D, texture->GetId());

        // Bind VAO:
        glBindVertexArray(image->GetId());

		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(shader->GetId());
		

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Reset the state:
        glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);
        glDisable(GL_BLEND); 
        glDisable(GL_CULL_FACE); 
        glDisable(GL_DEPTH_TEST); 

        SDL_GL_SwapWindow(window);
    }

    // Cleanup:
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}