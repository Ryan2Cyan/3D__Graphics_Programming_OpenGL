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
	std::shared_ptr<Mesh> cube0 = context->CreateMesh(cube_w);

	// Create white cube gameobject:
	std::shared_ptr<GameObject> cube = context->CreateGameObject();
	cube->AddMesh(cube0);
	cube->SetPos(glm::vec3(0.0f, -20.0f, 0.0f));
	cube->Scale(glm::vec3(20.0f, 0.1f, 20.0f));
	cube->AddPlaneCollider(0.4f, glm::vec3(0.0f, 1.0f, 0.0f), 100.0f);
	shader->AddGameObject(cube);

	// Create orange sphere gameobject:
	std::shared_ptr<GameObject> sphere = context->CreateGameObject();
	sphere->name = "test-sphere";
	sphere->AddMesh(sphere0);
	sphere->SetPos(glm::vec3(0.0f, 20.0f, 0.0f));
	sphere->Scale(glm::vec3(1.0f, 1.0f, 1.0f));
	sphere->AddRigidbody(20.0f);
	sphere->AddSphereCollider(0.5f, 5.0f);
	shader->AddGameObject(sphere);

	// Create physics world to apply dynamic physics:
	std::shared_ptr<PhysicsWorld> phy_world = phy_context->CreatePhysicsWorld();
	phy_world->AddGameObject(sphere);

	// Render loop (called each frame):
	while (!glfwWindowShouldClose(window))
	{
		// Calc delta time:
		float delta_time = context->CalcDeltaTime();

		// Input:
		context->ProcessInput(window, delta_time);
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { // Start simulation if press P.
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