#include <graphics/Gp.h>
#include <physics/Ph.h>
#include <iostream>
#include <random>

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
    std::shared_ptr<Shader> cubemap_shader = context->CreateShader(cubemap_v, cubemap_f);
	std::shared_ptr<Shader> theshold_shader = context->CreateShader(postproc_v, threshold_f);
	std::shared_ptr<Shader> blur_shader = context->CreateShader(postproc_v, blur_f);
	std::shared_ptr<Shader> merge_shader = context->CreateShader(postproc_v, merge_f);
	std::shared_ptr<Shader> gui_shader = context->CreateShader(gui_v, gui_f);

    // Create camera:
    std::shared_ptr<GameObject> player = context->CreateGameObject();
    player->AddRigidbody(0.0f, false);
    player->AddSphereCollider(0.1, 5.0f);
    std::shared_ptr<Camera> main_cam = context->CreateCamera(
        false,
        glm::vec2((float)window_size.x, (float)window_size.y),
        glm::vec3(0.0f, 0.0f, 0.0f),  // position
        glm::vec3(0.0f, 0.0f, 1.0f),  // target
        70.0f                         //fov
    );
    context->SetMainCamera(main_cam); // "Main Camera" can be controlled by the user

    // Create curuthers gameobject:
    std::shared_ptr<Mesh> curuthers_m = context->CreateMesh(model_filepath);
    curuthers_m->SetDiffuse(glm::vec3(0.0, 0.0, 0.0));
    // Generate random numbers for curuther's position:
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-250, 250); // define the range
    std::shared_ptr<GameObject> curuthers = context->CreateGameObject(curuthers_m);
    curuthers->SetPos(glm::vec3(
        distr(gen),
        distr(gen),
        distr(gen)));

    curuthers->Scale(glm::vec3(0.4f, 0.4f, 0.4f));
    curuthers->AddRigidbody(0.0f, false);
    curuthers->AddSphereCollider(0.1f, 5.0f);
    curuthers->name = "curuthers";
    shader->AddGameObject(curuthers);
   
    // Create graveyard tree gameobject:
    std::shared_ptr<Mesh> tree_m = context->CreateMesh(model_tree);
    tree_m->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    std::shared_ptr<Mesh> ground_m = context->CreateMesh(model_ground);
    ground_m->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    curuthers_m->SetSpecular(glm::vec3(0.0, 0.0, 0.0));
    std::shared_ptr<Mesh> skeleton_m = context->CreateMesh(model_skeleton);
    skeleton_m->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    std::shared_ptr<Mesh> bird_m = context->CreateMesh(model_bird);
    bird_m->SetDiffuse(glm::vec3(0.5, 0.5, 1.0));
    std::shared_ptr<GameObject> graveyard_tree = context->CreateGameObject();
    graveyard_tree->AddMesh(tree_m);
    graveyard_tree->AddMesh(ground_m);
    graveyard_tree->AddMesh(skeleton_m);
    graveyard_tree->AddMesh(bird_m);
    graveyard_tree->SetPos(glm::vec3(5.0f, 0.0f, 0.0f));
    shader->AddGameObject(graveyard_tree);

	//Load in sphere meshes:
	 //Load in sphere meshes:
	std::shared_ptr<Mesh> sphere0 = context->CreateMesh(sphere_o);
	std::shared_ptr<Mesh> sphere1 = context->CreateMesh(sphere_b);
	std::shared_ptr<Mesh> sphere2 = context->CreateMesh(sphere_c);
	std::shared_ptr<Mesh> sphere3 = context->CreateMesh(sphere_l);
	std::shared_ptr<Mesh> sphere4 = context->CreateMesh(sphere_p);
	std::shared_ptr<Mesh> sphere5 = context->CreateMesh(sphere_r);
	std::shared_ptr<Mesh> sphere6 = context->CreateMesh(sphere_rs);
	std::shared_ptr<Mesh> sphere7 = context->CreateMesh(sphere_w);
	int sphere_color = 0; // Determine what sphere color to use:

    // Create render textures:
    std::shared_ptr<RenderTexture> render_texture = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> threshold_render_texture = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> blur_render_texture0 = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> blur_render_texture1 = context->CreateRenderTexture(window_size);
    std::shared_ptr<RenderTexture> merge_render_texture = context->CreateRenderTexture(window_size);
	std::shared_ptr<RenderTexture> test_rt = context->CreateRenderTexture(window_size);
    std::vector<std::shared_ptr<RenderTexture>> render_textures{
        render_texture,
        threshold_render_texture,
        blur_render_texture0,
        blur_render_texture1,
        merge_render_texture,
		test_rt
    };

	// Make triangle object:
	std::vector<glm::vec3> triangle_pos = {
			glm::vec3(-0.5f , -0.5f, 0.0f),
			glm::vec3(0.5f , -0.5f, 0.0f),
			glm::vec3(0.0f, 0.5f, 0.0f)
	};
	std::vector<glm::vec2> triangle_texcoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f)
	};
	std::shared_ptr<VertexArray> triangle = context->Create2D(triangle_pos, triangle_texcoords);
	/*std::shared_ptr<GameObject> triangle_go = context->CreateGameObject()*/

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
    main_cam->SetCubeMapShader(cubemap_shader);
    main_cam->SetCubeMapObj(context->CreateUnitCube());

    // Create physics world to handle collisions:
    std::shared_ptr<PhysicsWorld> phy_world = phy_context->CreatePhysicsWorld();
    phy_world->AddGameObject(curuthers);
    phy_world->AddGameObject(player);

    // Game values:
    bool found = false;
    bool game_active = true;
    phy_world->start = true;
	float sphere_spawn_delay = 1.0f;
	float sphere_spawn_timer = 0.0f;

    // Render loop (called each frame):
    while (!glfwWindowShouldClose(window))
    {
        // Calc delta time:
        float delta_time = context->CalcDeltaTime();

        // Resize render textures to be size of window:
        if (render_texture->GetSize().x != (int)main_cam->GetSize().x ||
            render_texture->GetSize().y != (int)main_cam->GetSize().y){
            for (size_t i = 0; i < render_textures.size(); i++) {
                render_textures[i]->SetSize(main_cam->GetSize());
            }
        }
            
        // Input:
        context->ProcessInput(window, delta_time);

        // Game code:
        player->SetPos(main_cam->GetTransform().position);
        if (curuthers->GetRigidbody()->has_collided || player->GetRigidbody()->has_collided && !found) {
            if (game_active) {
                system("cls");
                std::cout << "Found Him!" << std::endl;
                curuthers_m->SetDiffuse(glm::vec3(1.0, 1.0, 1.0));
                found = true;
                game_active = false;
            }
        }
        if (!found) {
            // Print positions of player and curuthers:
            std::cout << 
                "Curuthers Pos:  [x] " << std::roundf(curuthers->GetTransform()->position.x) << 
                ",   [y]  " << std::roundf(curuthers->GetTransform()->position.y) <<
                ",   [z]  " << std::roundf(curuthers->GetTransform()->position.z) << std::endl;

            std::cout << "Camera Pos:     [x] " << std::roundf(main_cam->GetTransform().position.x) <<
                ",   [y]  " << std::roundf(main_cam->GetTransform().position.y) <<
                ",   [z]  " << std::roundf(main_cam->GetTransform().position.z) << std::endl;
        }
		sphere_spawn_timer -= delta_time;
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && sphere_spawn_timer <= 0.0f) {
			// Create GameObjects:
			std::cout << "Spawn Sphere" << std::endl;
			std::shared_ptr<GameObject> new_gameobject = context->CreateGameObject();
			// Add random coloured sphere mesh:
			sphere_color = rand() % (7 - 0 + 1);
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
			new_gameobject->name = "new-sphere";
			new_gameobject->SetPos(glm::vec3(
				player->GetTransform()->position.x,
				player->GetTransform()->position.y, 
				player->GetTransform()->position.z));
			new_gameobject->Scale(glm::vec3(0.3f, 0.3f, 0.3f));
			shader->AddGameObject(new_gameobject);
			sphere_spawn_timer = sphere_spawn_delay;
		}
		

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

		// Render orthographic:
		
		// shader gui
		/*gui_shader->Render()*/
		// u_proj <- ortho
		// use
		// draw 2 tris / quad
        
        // Physics (collision):
        phy_world->Step(delta_time);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up:
    glfwTerminate();
    return 0;
}
