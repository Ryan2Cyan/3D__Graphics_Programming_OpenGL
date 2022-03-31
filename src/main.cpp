#define SDL_MAIN_HANDLED 

#include "Gp.h"
//#include <wavefront/wavefront.h>
#include <SDL.h>
#include <glfw/glfw3.h>
#include <GL/glew.h>
#include <memory>
#include <ext.hpp>
#include <iostream>
#include <vector>
#include <fstream>

// Shaders filepaths:
const GLchar* vertex_shader_filepath = "Additional_Files/shaders/vertex_shader.txt";
const GLchar* basic_v_filepath = "Additional_Files/shaders/basic_vert.txt";
const GLchar* basic_f_filepath = "Additional_Files/shaders/basic_frag2.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/shaders/fragment_shader.txt";
const GLchar* f_basic_lighting = "Additional_Files/shaders/basic_lighting_frag.txt";
const GLchar* v_basic_lighting = "Additional_Files/shaders/basic_lighting_vert.txt";
const GLchar* f_off_screen = "Additional_Files/shaders/off_screen_frag.txt";
const GLchar* v_off_screen = "Additional_Files/shaders/off_screen_vert.txt";

// Resource filepaths:
const GLchar* image_filepath = "Additional_Files/images/wall.jpg";
const GLchar* image_filepath2 = "Additional_Files/images/image_test_flip.png";
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";
const GLchar* model_filepath2 = "Additional_Files/models/gun/mxng.obj";
const GLchar* model_filepath3 = "Additional_Files/models/graveyard/graveyard.obj";


int main()
{

    // Create window and assign OpenGL context:
    glm::ivec2 window_size{ 720, 720 };
    GLFWwindow* window = Gp::CreateWindow(window_size);
    glfwMakeContextCurrent(window);

    // Create context:
    std::shared_ptr<GpContext> context = Gp::CreateContext();


    // Create Shader for on-screen rendering:
    std::shared_ptr<Shader> shader = context->CreateShader(v_basic_lighting, f_basic_lighting);

	// Object 1:
    std::vector<glm::vec3> position = {
        { 1.0f, -1.0f, 0.0f }, 
        { 1.0f, 1.0f, 0.0f },
        { -1.0f, -1.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { -1.0f, 1.0f, 0.0f },
        { -1.0f, -1.0f, 0.0f }
    };
    std::vector<glm::vec2> tex_coords = {
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f }
    };
    std::shared_ptr<VertexArray> quad = context->Create2D(position, tex_coords);
    std::shared_ptr<Texture> texture = context->CreateTexture(image_filepath);
    glm::vec3 position0 = { 0.0f, 0.0f, -4.0f };
    std::shared_ptr<Mesh> quad_mesh = context->CreateMesh(quad, texture, position0);
    shader->AddMeshToRender(quad_mesh);

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(0.0f, 0.0f, 0.0f),  // position
        glm::vec3(0.0f, 0.0f, 1.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam);

    //Load in meshes:
    glm::vec3 position1 = { 0.0f, 0.0f, 0.0f };
    std::shared_ptr<Mesh> curuthers = context->CreateMesh(model_filepath, position1);
    shader->AddMeshToRender(curuthers);

       // Create render texture:
    std::shared_ptr<RenderTexture> render_texture = context->CreateRenderTexture(window_size);


    // Create Shader for off-screen rendering:
    std::shared_ptr<Shader> shader_off = context->CreateShader(v_off_screen, f_off_screen);


  
    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    { 

        // Input:
        context->ProcessInput(window);

        // Render:
        shader->Render(main_cam, render_texture, shader_off, quad, true);
        std::cout << "cam pos" << "x: " << main_cam->pos.x
            << "   y: " << main_cam->pos.y << "   z: " << main_cam->pos.z << std::endl;
        std::cout << "cam dir" << "x: " << main_cam->dir.x
            << "   y: " << main_cam->dir.y << "   z: " << main_cam->dir.z << std::endl;
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Clean up:
    glfwTerminate();
    return 0;
}