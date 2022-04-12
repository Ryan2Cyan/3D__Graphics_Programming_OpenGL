#include <graphics/Gp.h>
#include <physics/Ph.h>
#include <iostream>

// Shaders filepaths:
const GLchar* light_v = "Additional_Files/shaders/light_vert.txt";
const GLchar* light_f = "Additional_Files/shaders/light_frag.txt";

// Model
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";
const GLchar* sphere_mfp = "Additional_Files/models/Sphere/sphere.obj";

int main()
{

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
        glm::vec3(0.0f, 0.0f, 40.0f),  // position
        glm::vec3(0.0f, 0.0f, 1.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user

    // Create GameObjects:
    std::shared_ptr<GameObject> gameobject0 = context->CreateGameObject();

    //Load in meshes:
    std::shared_ptr<Mesh> sphere = context->CreateMesh(sphere_mfp);
    gameobject0->AddMesh(sphere);
    gameobject0->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
    shader->AddGameObjectToRender(gameobject0);
    gameobject0->AddRigidbody(70.0f);

    // Create physics world to apply dynamic physics:
    std::shared_ptr<PhysicsWorld> phy_world = phy_context->CreatePhysicsWorld();
    phy_world->AddGameObject(gameobject0);


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
        }
        phy_world->Step(delta_time);
        

        // Render:
        shader->Render(main_cam, true);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up:
    glfwTerminate();
    return 0;
}