#include <graphics/Gp.h>
#include <iostream>

// Shaders filepaths:
const GLchar* light_v = "Additional_Files/shaders/light_vert.txt";
const GLchar* light_f = "Additional_Files/shaders/light_frag.txt";

// Model
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";


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

    // Create camera:
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(0.0f, 0.0f, 0.0f),  // position
        glm::vec3(0.0f, 0.0f, 1.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user

    // Create GameObjects:
    std::shared_ptr<GameObject> gameobject0 = context->CreateGameObject();

    //Load in meshes:
    glm::vec3 position0 = { 2.0f, 1.0f, 0.0f };
    std::shared_ptr<Mesh> curuthers = context->CreateMesh(model_filepath, position0);
    gameobject0->AddMesh(curuthers);
    shader->AddGameObjectToRender(gameobject0);

    float angle = 0.1f;
    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    {
      
        angle += 0.1f;
        //gameobject0->Translate(glm::vec3(0.0f, 0.0f, -2.5f));
        gameobject0->Rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));

        // Input:
        context->ProcessInput(window);

        // Render:
        shader->Render(main_cam, true);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up:
    glfwTerminate();
    return 0;
}