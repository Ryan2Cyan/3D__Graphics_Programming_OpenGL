#include <graphics/Gp.h>
#include <physics/Ph.h>
#include <iostream>

// Shaders filepaths:
const GLchar* light_v = "Additional_Files/shaders/light_vert.txt";
const GLchar* light_f = "Additional_Files/shaders/light_frag.txt";

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

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(-20.0f, 5.0f, 100.0f),  // position
        glm::vec3(0.0f, 0.0f, 0.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user

    //Load in sphere meshes:
    std::shared_ptr<Mesh> sphere0 = context->CreateMesh(sphere_o);
    std::shared_ptr<Mesh> sphere1 = context->CreateMesh(sphere_b);
    std::shared_ptr<Mesh> sphere2 = context->CreateMesh(sphere_c);
    std::shared_ptr<Mesh> sphere3 = context->CreateMesh(sphere_l);
    std::shared_ptr<Mesh> sphere4 = context->CreateMesh(sphere_p);
    std::shared_ptr<Mesh> sphere5 = context->CreateMesh(sphere_r);
    std::shared_ptr<Mesh> sphere6 = context->CreateMesh(sphere_rs);
    std::shared_ptr<Mesh> sphere7 = context->CreateMesh(sphere_w);
    std::shared_ptr<Mesh> cube0 = context->CreateMesh(cube_w);
    cube0->SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    int sphere_color = 0;// Determine what sphere color to use:

    // Create white cube gameobject:
    std::shared_ptr<GameObject> cube = context->CreateGameObject();
    cube->AddMesh(cube0);
    cube->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
    cube->Scale(glm::vec3(20.0f, 0.1f, 20.0f));
    shader->AddGameObject(cube);
   
    

    // Create physics world to apply dynamic physics:
    std::shared_ptr<PhysicsWorld> phy_world = phy_context->CreatePhysicsWorld();


    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    {
      
        // Calc delta time:
        float delta_time = context->CalcDeltaTime();

        // Input:
        context->ProcessInput(window, delta_time);
        

        // Calculate physics:
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            phy_world->start = true;
            // Create GameObjects:
            std::shared_ptr<GameObject> new_gameobject = context->CreateGameObject();
            switch (sphere_color)
            {
            case 0:
                new_gameobject->AddMesh(sphere0);
                std::cout << "Sphere Color:  Orange" << std::endl;
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
            new_gameobject->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
            shader->AddGameObject(new_gameobject);
            new_gameobject->AddRigidbody(70.0f);
            new_gameobject->GetRigidbody()->AddForce(glm::vec3(5000.0f, 30000.0f, 0.0f));
            phy_world->AddGameObject(new_gameobject);
        }

        phy_world->Step(delta_time);

        // Render:
        shader->Render(main_cam, true);
        glfwSwapBuffers(window);
        glfwPollEvents();

        for (std::shared_ptr<GameObject> gameobject : shader->gameobjects) {
            if (gameobject->GetTransform()->position.y <= -20.0f) {
                phy_world->RemoveGameObject(gameobject);
            }
        }
    }

    // Clean up:
    glfwTerminate();
    return 0;
}