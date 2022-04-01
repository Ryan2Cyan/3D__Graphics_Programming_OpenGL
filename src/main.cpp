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
const GLchar* light_v = "Additional_Files/shaders/light_vert.txt";
const GLchar* light_f = "Additional_Files/shaders/light_frag.txt";
const GLchar* postproc_v = "Additional_Files/shaders/postprocess_vert.txt";
const GLchar* threshold_f = "Additional_Files/shaders/threshold_frag.txt";
const GLchar* blur_f = "Additional_Files/shaders/blur_frag.txt";
const GLchar* gui_f = "Additional_Files/shaders/gui_frag.txt";
const GLchar* gui_v = "Additional_Files/shaders/gui_vert.txt";
const GLchar* null_f = "Additional_Files/shaders/null_frag.txt";
const GLchar* merge_f = "Additional_Files/shaders/merge_frag.txt";

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
    std::shared_ptr<Shader> shader = context->CreateShader(light_v, light_f);
	std::shared_ptr<Shader> theshold_shader = context->CreateShader(postproc_v, threshold_f);
	std::shared_ptr<Shader> blur_shader = context->CreateShader(postproc_v, blur_f);
	std::shared_ptr<Shader> merge_shader = context->CreateShader(postproc_v, merge_f);

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
	std::shared_ptr<RenderTexture> threshold_render_texture = context->CreateRenderTexture(window_size);
	std::shared_ptr<RenderTexture> blur_render_texture0 = context->CreateRenderTexture(window_size);
	std::shared_ptr<RenderTexture> blur_render_texture1 = context->CreateRenderTexture(window_size);
	std::shared_ptr<RenderTexture> merge_render_texture = context->CreateRenderTexture(window_size);


	std::shared_ptr<Mesh> threshold_mesh = context->CreateMesh(quad, threshold_render_texture, glm::vec3(0.0f, 0.0f, 0.0f));

    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    { 

        // Input:
        context->ProcessInput(window);

        // Render:
        shader->Render(main_cam, render_texture, theshold_shader, quad, true);
		theshold_shader->Swap(render_texture, threshold_render_texture, theshold_shader, quad);
		theshold_shader->Swap(threshold_render_texture, blur_render_texture0, theshold_shader, quad);
		theshold_shader->Swap(blur_render_texture0, blur_render_texture1, blur_shader, quad);
		bool first_swap = true;
		for (size_t i = 0; i < 20; i++)
		{
			
			theshold_shader->Swap(blur_render_texture1, blur_render_texture0, blur_shader, quad);
		
			theshold_shader->Swap(blur_render_texture0, blur_render_texture1, blur_shader, quad);
	
			
		}

		theshold_shader->Swap(blur_render_texture0, merge_render_texture, merge_shader, quad);
		theshold_shader->Swap(merge_render_texture, nullptr, merge_shader, quad, render_texture->GetTexId());
	/*	theshold_shader->Swap(merge_render_texture, nullptr, merge_shader, quad);*/
	

        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    // Clean up:
    glfwTerminate();
    return 0;
}