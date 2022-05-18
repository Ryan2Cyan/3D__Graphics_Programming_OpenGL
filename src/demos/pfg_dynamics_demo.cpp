#include <graphics/Gp.h>
#include <physics/Ph.h>
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

// Models:
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";
const GLchar* cube_w = "Additional_Files/models/cube/cube.obj";
const GLchar* sphere_o = "Additional_Files/models/Sphere/orange/sphere.obj";
const GLchar* sphere_b = "Additional_Files/models/Sphere/blue/sphere.obj";
const GLchar* sphere_c = "Additional_Files/models/Sphere/cyan/sphere.obj";
const GLchar* sphere_l = "Additional_Files/models/Sphere/lime/sphere.obj";
const GLchar* sphere_p = "Additional_Files/models/Sphere/purple/sphere.obj";
const GLchar* sphere_r = "Additional_Files/models/Sphere/red/sphere.obj";
const GLchar* sphere_rs = "Additional_Files/models/Sphere/rose/sphere.obj";
const GLchar* sphere_w = "Additional_Files/models/Sphere/white/sphere.obj";

int main()
{
    srand(time(0));

    // Create window and assign OpenGL context:
    glm::ivec2 window_size{ 1000, 1000 };
    GLFWwindow* window = Gp::CreateWindow(window_size);
    glfwMakeContextCurrent(window);

    // Create context:
    std::shared_ptr<GpContext> context = Gp::CreateContext();
    std::shared_ptr<PhContext> phy_context = Ph::CreateContext();

    // Create Shader for on-screen rendering:
    std::shared_ptr<Shader> shader = context->CreateShader(light_v, light_f);
    std::shared_ptr<Shader> hud_shader = context->CreateShader(light_v, light_f);
    std::shared_ptr<Shader> theshold_shader = context->CreateShader(postproc_v, threshold_f);
    std::shared_ptr<Shader> blur_shader = context->CreateShader(postproc_v, blur_f);
    std::shared_ptr<Shader> merge_shader = context->CreateShader(postproc_v, merge_f);

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(-20.0f, 5.0f, 50.0f),  // position
        glm::vec3(0.0f, 0.0f, 0.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user


    //Load in sphere meshes:
    std::shared_ptr<Mesh> sphere0 = context->CreateMesh(sphere_o);
    sphere0->SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    std::shared_ptr<Mesh> sphere1 = context->CreateMesh(sphere_b);
    std::shared_ptr<Mesh> sphere2 = context->CreateMesh(sphere_c);
    std::shared_ptr<Mesh> sphere3 = context->CreateMesh(sphere_l);
    std::shared_ptr<Mesh> sphere4 = context->CreateMesh(sphere_p);
    std::shared_ptr<Mesh> sphere5 = context->CreateMesh(sphere_r);
    std::shared_ptr<Mesh> sphere6 = context->CreateMesh(sphere_rs);
    std::shared_ptr<Mesh> sphere7 = context->CreateMesh(sphere_w);
    std::shared_ptr<Mesh> cube0 = context->CreateMesh(cube_w);
    int sphere_color = 0;// Determine what sphere color to use:


    // Create white cube gameobject:
    std::shared_ptr<GameObject> cube = context->CreateGameObject();
    cube->AddMesh(cube0);
	cube->name = "cube";
    cube->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
    cube->Scale(glm::vec3(20.0f, 0.1f, 20.0f));
	cube->AddPlaneCollider(0.5f, glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
    cube->AddRigidbody(20.0f, false);
    shader->AddGameObject(cube);

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
   
    

    // Create physics world to apply dynamic physics:
    std::shared_ptr<PhysicsWorld> phy_world = phy_context->CreatePhysicsWorld();
	phy_world->AddGameObject(cube);

	// Game variables:
    bool spawned_sphere = false;
	float spawn_timer = 0.0f;
	float spawn_delay = 1.0f;
    double previousTime = glfwGetTime();
    int frameCount = 0;

    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    {
        // Print fps: https://gamedev.stackexchange.com/questions/133173/how-to-calculate-fps-in-glfw
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0)  // If a second has passed.
        {
            // Display the frame count here any way you want.
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            previousTime = currentTime;
        }

        // Rest of your game loop...
        

        // Resize render textures to be size of window:
        if (render_texture->GetSize().x != (int)main_cam->GetSize().x ||
            render_texture->GetSize().y != (int)main_cam->GetSize().y) {
            for (size_t i = 0; i < render_textures.size(); i++) {
                render_textures[i]->SetSize(main_cam->GetSize());
            }
        }
      
        // Calc delta time:
        float delta_time = context->CalcDeltaTime();

        // Input:
        context->ProcessInput(window, delta_time);

        // Calculate physics:
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !spawned_sphere) {

            phy_world->start = true;
            // Create GameObjects:
            std::shared_ptr<GameObject> new_gameobject = context->CreateGameObject();
			new_gameobject->name = "new-sphere";
            switch (sphere_color)
            {
            case 0:
                new_gameobject->AddMesh(sphere0);
                break;
            case 1:
                new_gameobject->AddMesh(sphere1);
                break;
            case 2:
                new_gameobject->AddMesh(sphere2);
                break;
            case 3:
                new_gameobject->AddMesh(sphere3);
                break;
            case 4:
                new_gameobject->AddMesh(sphere4);
                break;
            case 5:
                new_gameobject->AddMesh(sphere5);
                break;
            case 6:
                new_gameobject->AddMesh(sphere6);
                break;
            case 7:
                new_gameobject->AddMesh(sphere7);
                break;
            default:
                break;
            }
            sphere_color = rand() % (7 - 0 + 1);
            new_gameobject->SetPos(glm::vec3(0.0f, 50.0f, 0.0f));
            shader->AddGameObject(new_gameobject);
            new_gameobject->AddRigidbody(1.0f);
            new_gameobject->GetRigidbody()->AddForce(glm::vec3(0.0f, 0.0f, 0.0f));
			new_gameobject->AddSphereCollider(0.6f, 1.0f);
            phy_world->AddGameObject(new_gameobject);

			spawn_timer = spawn_delay;
            spawned_sphere = true;
        }
		if (spawned_sphere)
			spawn_timer -= delta_time;
		if (spawn_timer <= 0.0f)
			spawned_sphere = false;
		
        phy_world->Step(delta_time);

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