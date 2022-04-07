#define SDL_MAIN_HANDLED 

#include "Gp.h"
#include <iostream>

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
const GLchar* cubemap_v = "Additional_Files/shaders/cubemap_vert.txt";
const GLchar* cubemap_f = "Additional_Files/shaders/cubemap_frag.txt";

// Texture filepaths:
const GLchar* image_filepath = "Additional_Files/images/skybox_1.png";
const GLchar* image_filepath2 = "Additional_Files/images/image_test_flip.png";
const GLchar* front = "Additional_Files/images/skybox/back.jpg";
const GLchar* bottom = "Additional_Files/images/skybox/bottom.jpg";
const GLchar* back = "Additional_Files/images/skybox/front.jpg";
const GLchar* left = "Additional_Files/images/skybox/left.jpg";
const GLchar* right = "Additional_Files/images/skybox/right.jpg";
const GLchar* top = "Additional_Files/images/skybox/top.jpg";

// Model
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";
const GLchar* model_filepath2 = "Additional_Files/models/gun/mxng.obj";
const GLchar* model_filepath3 = "Additional_Files/models/graveyard/graveyard.obj";
const GLchar* model_filepath4 = "Additional_Files/models/cube/cube.obj";
const GLchar* model_tree = "Additional_Files/models/tree/tree.obj";
const GLchar* model_ground = "Additional_Files/models/tree/ground.obj";
const GLchar* model_skeleton = "Additional_Files/models/tree/skeleton.obj";
const GLchar* model_bird = "Additional_Files/models/tree/bird.obj";


int main()
{

    // Create window and assign OpenGL context:
    glm::ivec2 window_size{ 1000, 1000 };
    GLFWwindow* window = Gp::CreateWindow(window_size);
    glfwMakeContextCurrent(window);

    // Create context:
    std::shared_ptr<GpContext> context = Gp::CreateContext();

    // Create Shader for on-screen rendering:
    std::shared_ptr<Shader> shader = context->CreateShader(light_v, light_f);
    std::shared_ptr<Shader> cubemap_shader = context->CreateShader(cubemap_v, cubemap_f);
	std::shared_ptr<Shader> theshold_shader = context->CreateShader(postproc_v, threshold_f);
	std::shared_ptr<Shader> blur_shader = context->CreateShader(postproc_v, blur_f);
	std::shared_ptr<Shader> merge_shader = context->CreateShader(postproc_v, merge_f);

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(0.0f, 0.0f, 0.0f),  // position
        glm::vec3(0.0f, 0.0f, 1.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user

    //Load in meshes:
    glm::vec3 position0 = { 2.0f, 1.0f, 0.0f };
    std::shared_ptr<Mesh> curuthers = context->CreateMesh(model_filepath, position0);
    curuthers->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    curuthers->SetModelMat(glm::scale(curuthers->GetModelMat(), glm::vec3(0.5f, 0.5f, 0.5f)));
    shader->AddMeshToRender(curuthers);
   

    glm::vec3 position1 = { 5.0f, 0.0f, 0.0f };
    std::shared_ptr<Mesh> tree = context->CreateMesh(model_tree, position1);
    tree->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    shader->AddMeshToRender(tree);
    std::shared_ptr<Mesh> ground = context->CreateMesh(model_ground, position1);
    ground->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    shader->AddMeshToRender(ground);
    std::shared_ptr<Mesh> skeleton = context->CreateMesh(model_skeleton, position1);
    skeleton->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    shader->AddMeshToRender(skeleton);
    std::shared_ptr<Mesh> bird = context->CreateMesh(model_bird, position1);
    bird->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    shader->AddMeshToRender(bird);

    // Create render textures:
    std::shared_ptr<RenderTexture> render_texture = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> threshold_render_texture = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> blur_render_texture0 = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> blur_render_texture1 = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> merge_render_texture = context->CreateRenderTexture(window_size);
    std::vector<std::shared_ptr<RenderTexture>> render_textures{
        render_texture,
        threshold_render_texture,
        blur_render_texture0,
        blur_render_texture1,
        merge_render_texture
    };

    // Cubemap demo:
    std::vector<std::string> faces = {
        right,
        left,
        top,
        bottom,
        back,
        front
    };
    main_cam->SetCubeMap(context->CreateCubemap(faces));
    main_cam->cubemap_shader = cubemap_shader;
    main_cam->SetCubeMapObj(context->CreateUnitCube());

    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    {
        // Resize render textures to be size of window:
        if (render_texture->GetSize().x != (int)main_cam->GetSize().x ||
            render_texture->GetSize().y != (int)main_cam->GetSize().y){
            for (size_t i = 0; i < render_textures.size(); i++) {
                render_textures[i]->SetSize(main_cam->GetSize());
            }
        }
            
        
        // Input:
        context->ProcessInput(window);

        // Render:
        shader->Render(main_cam, render_texture, true);

		theshold_shader->Swap(render_texture, threshold_render_texture, NULL);
		theshold_shader->Swap(threshold_render_texture, blur_render_texture0, NULL);
        blur_shader->Swap(blur_render_texture0, blur_render_texture1, NULL);
		for (size_t i = 0; i < 10; i++)
		{
            blur_shader->Swap(blur_render_texture1, blur_render_texture0, NULL);
            blur_shader->Swap(blur_render_texture0, blur_render_texture1, NULL);
		}
        merge_shader->Swap(blur_render_texture0, merge_render_texture, NULL);
        merge_shader->Swap(merge_render_texture, nullptr, render_texture->GetTexId());
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up:
    glfwTerminate();
    return 0;
}