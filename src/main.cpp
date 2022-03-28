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
const GLchar* f_off_screen = "Additional_Files/shaders/off_screen_frag.txt";
const GLchar* v_off_screen = "Additional_Files/shaders/off_screen_vert.txt";

// Resource filepaths:
const GLchar* image_filepath = "Additional_Files/images/image_test.PNG";
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";
const GLchar* ground_filepath = "Additional_Files/models/PSX_tree/PSX_style_tree.obj";

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
    glm::ivec2 window_size2{ 360, 360 };

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Window* window = SDL_CreateWindow("3DGP Assignment 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        window_size.x, window_size.y, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync


    // Create context for Gp:
    std::shared_ptr<GpContext> context = Gp::CreateContext(); 
	
    // Create render texture:
    std::shared_ptr<RenderTexture> render_texture = context->CreateRenderTexture(window_size);

    // Create Shader for on-screen rendering:
    std::shared_ptr<Shader> shader = context->CreateShader(v_basic_lighting, f_basic_lighting);

    // Create Shader for off-screen rendering:
    std::shared_ptr<Shader> shader_off = context->CreateShader(v_off_screen, f_off_screen);

    // Load in meshes:
    glm::vec3 position = { 0.0f, 0.0f, 9.5f };
    std::shared_ptr<Mesh> curuthers = context->CreateMesh(model_filepath, position);

    // Vector of all meshes [heirarchy]:
    shader->AddMeshToRender(curuthers);

    // Create quad for render texture:
    std::shared_ptr<VertexArray> quad = context->Create2DImage();

    // Handle Uniforms:
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)window_size.x / (float)window_size.y, 0.1f, 100.f);

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        glm::vec3(1.0f, 1.0f, 30.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    // Main loop state:
    bool done = false;
    bool window_open = true;
    bool backface_cull = false;
    float camera_speed = 0.05f;
    float delta_time = 0;
    bool first_mouse = true;
    bool mouse_motion = false;
    float mouse_x = 0;
    float mouse_y = 0;
    float mouse_s = 0.1f;
    Uint64 last = 0;
    Uint64 now = SDL_GetPerformanceCounter();

    // Object state:
    float angle = 45.0f;
    
	// Background color:
	glm::vec4 background_col = { 0.9f, 0.9f, 0.0f, 1.0f };
	
    
    while (!done)
    { 
        // Calc deltatime:
        last = now;
        now = SDL_GetPerformanceCounter();
        delta_time = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency());

        // Input loop:
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                done = true;
                break;
            }
           
            if (event.key.repeat == 0 && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    main_cam->vel += delta_time * camera_speed * main_cam->front;
                    break;
                case SDLK_s:
                    main_cam->vel -= delta_time * camera_speed * main_cam->front;
                    break;
                case SDLK_a:
                    main_cam->vel -= glm::normalize(glm::cross(main_cam->front, main_cam->up)) * camera_speed * delta_time;
                    break;
                case SDLK_d:
                    main_cam->vel += glm::normalize(glm::cross(main_cam->front, main_cam->up)) * camera_speed * delta_time;
                    break;
                default:
                    break;
                }
            }
            if (event.key.repeat == 0 && event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    main_cam->vel -= delta_time * camera_speed * main_cam->front;
                    break;
                case SDLK_s:
                    main_cam->vel += delta_time * camera_speed * main_cam->front;
                    break;
                case SDLK_a:
                    main_cam->vel += glm::normalize(glm::cross(main_cam->front, main_cam->up)) * camera_speed * delta_time;
                    break;
                case SDLK_d:
                    main_cam->vel -= glm::normalize(glm::cross(main_cam->front, main_cam->up)) * camera_speed * delta_time;
                    break;
                default:
                    break;
                }
            }
        }

        // Clamp velocity to prevent pos changing from small values:
        if (main_cam->vel.x < 0.09f && main_cam->vel.x > -0.09f)
            main_cam->vel.x = 0.0f;
        if (main_cam->vel.y < 0.09f && main_cam->vel.y > -0.09f)
            main_cam->vel.y = 0.00f;
        if (main_cam->vel.z < 0.09f && main_cam->vel.z > -0.09f)
            main_cam->vel.z = 0.0f;

        // Update position:
        main_cam->pos += main_cam->vel;

        // Refresh camera:
        main_cam->view = glm::lookAt(main_cam->pos, main_cam->pos + main_cam->front, main_cam->up);

        // Parse matrix data:
        glUseProgram(shader->GetId());
        shader->SetUniform("u_View", main_cam->view);
        shader->SetUniform("u_Projection", projection);
        shader->SetUniform("u_ViewPos", main_cam->pos);
        glUseProgram(0);

      
        // Render:
        shader->Render(render_texture, shader_off, quad, window_size, 
            background_col, backface_cull);
        SDL_GL_SwapWindow(window);
    }

    // Cleanup:
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}