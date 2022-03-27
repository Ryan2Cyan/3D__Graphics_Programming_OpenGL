#define SDL_MAIN_HANDLED 

#include "Gp.h"
//#include <wavefront/wavefront.h>
#include <SDL.h>
#include <GL/glew.h>
#include <memory>

#include <ext.hpp>
#include <iostream>
#include <vector>
#include <fstream>

// Shaders filepaths:
const GLchar* vertex_shader_filepath = "Additional_Files/shaders/vertex_shader.txt";
const GLchar* basic_v_filepath = "Additional_Files/shaders/basic_vert2.txt";
const GLchar* basic_f_filepath = "Additional_Files/shaders/basic_frag2.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/shaders/fragment_shader.txt";
const GLchar* f_basic_lighting = "Additional_Files/shaders/basic_lighting_frag.txt";
const GLchar* v_basic_lighting = "Additional_Files/shaders/basic_lighting_vert.txt";

// Resource filepaths:
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
    glm::ivec2 window_size{ 720, 720 };

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Window* window = SDL_CreateWindow("3DGP Assignment 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        window_size.x, window_size.y, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync


    // Create context for Gp:
    std::shared_ptr<GpContext> context = Gp::CreateContext(); 
	
    // Create Shader:
    std::shared_ptr<Shader> shader = context->CreateShader(v_basic_lighting, f_basic_lighting);

    // Load in model:
    glm::vec3 position = { 0.0f, 0.0f, -10.5f };
    std::shared_ptr<Mesh> curuthers = context->CreateMesh(model_filepath, position);

    // Load in model 2:
    glm::vec3 position2 = { 0.0f, 6.0f, -10.5f };
    std::shared_ptr<Mesh> curuthers2 = context->CreateMesh(model_filepath, position2);

    // Load in model 2:
    glm::vec3 position3 = { 0.0f, -6.0f, -10.5f };
    std::shared_ptr<Mesh> curuthers3 = context->CreateMesh(model_filepath, position3);

    // Vector of all models to load:
    shader->AddMeshToRender(curuthers);
    shader->AddMeshToRender(curuthers2);
    shader->AddMeshToRender(curuthers3);

    // Main loop state:
    bool done = false;
    bool window_open = true;
    bool backface_cull = false;

    // Object state:
    float angle = 45.0f;
    
	// Background color:
	glm::vec4 background_col = { 0.6f, 0.7f, 0.8f, 1.0f };
	
    
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
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) {
                    glm::vec3 mod{ 0.5f, 0.0f, 0.0f };
                    curuthers->SetPos(curuthers->GetPos() - mod);
                }
                if (event.key.keysym.sym == SDLK_d) {
                    glm::vec3 mod{ -0.5f, 0.0f, 0.0f };
                    curuthers->SetPos(curuthers->GetPos() - mod);
                }
                if (event.key.keysym.sym == SDLK_s) {
                    glm::vec3 mod{ 0.0f, 0.5f, 0.0f };
                    curuthers->SetPos(curuthers->GetPos() - mod);
                }
                if (event.key.keysym.sym == SDLK_w) {
                    glm::vec3 mod{ 0.0f, -0.5f, 0.0f };
                    curuthers->SetPos(curuthers->GetPos() - mod);
                }
            }
        }

        // Render:
        shader->Render(window_size, background_col, backface_cull, angle);
        SDL_GL_SwapWindow(window);
    }

    // Cleanup:
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}