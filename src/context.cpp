#include "Gp.h"

static float last_x = 0.0f;
static float last_y = 0.0f;
static bool firstMouse = true;

// Create 2D asset (without texture):
std::shared_ptr<VertexArray> GpContext::Create2D(std::vector<glm::vec3> pos_coords) {

	// Initialise buffer:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();

	// Add pos coords to the buffer:
	for (size_t i = 0; i < pos_coords.size(); i++)
	{
		pos_buffer->Add(pos_coords[i]);
	}
	
	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add pos buffer to the vertex array:
	vertex_array->AddBuffer(pos_buffer);

	return vertex_array;
}

// Create 2D asset (with texture):
std::shared_ptr<VertexArray> GpContext::Create2D(std::vector<glm::vec3> pos_coords,
	std::vector<glm::vec2> tex_coords) {

	// Initialise buffers:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();
	std::shared_ptr<Buffer> tex_coord_buffer = CreateBuffer();

	// Add pos coords to the buffer:
	if (pos_coords.size() != tex_coords.size())
		throw std::exception("Mismatched attribute vector sizes");
	else {
		for (size_t i = 0; i < pos_coords.size(); i++)
		{
			pos_buffer->Add(pos_coords[i]);
			tex_coord_buffer->Add(tex_coords[i]);
		}
	}

	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add buffers to the vertex array:
	vertex_array->AddBuffer(pos_buffer);
	vertex_array->AddBuffer(tex_coord_buffer);

	return vertex_array;
}



// Process user input during the input loop:
void GpContext::ProcessInput(GLFWwindow* window) {

	// Calc delta time:
	float delta_time = 0.0f;
	static float last_frame = 0.0f;
	float current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;

	// Hide cursor when using mouse in window:
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (main_cam) {
		// Camera movement [W = Forward, S = Back, A = Right, D = Left, Q = Up, E = Down]:
		static float cam_speed = 4.5f * delta_time;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			main_cam->pos += cam_speed * main_cam->dir;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			main_cam->pos -= cam_speed * main_cam->dir;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			main_cam->pos -= glm::normalize(glm::cross(main_cam->dir, main_cam->up)) * cam_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			main_cam->pos += glm::normalize(glm::cross(main_cam->dir, main_cam->up)) * cam_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			main_cam->pos += cam_speed * main_cam->up;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			main_cam->pos -= cam_speed * main_cam->up;
		}

		// Adjust movement speed [Shift = move faster]:
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			cam_speed = 10.0f * delta_time;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			cam_speed = 4.5f * delta_time;
		}

		/*std::cout << "Cam speed: " << cam_speed << std::endl;*/

		// Rotate camera based on mouse movement:
		int win_width;
		int win_height;
		glfwGetWindowSize(window, &win_width, &win_height);
		main_cam->size.x = win_width;
		main_cam->size.y = win_height;

		double mouse_x;
		double mouse_y;
		glfwGetCursorPos(window, &mouse_x, &mouse_y);

		if (last_x == 0.0f && last_y == 0.0f) {
			last_x = (float)win_width / 2.0f;
			last_y = (float)win_height / 2.0f;
		}

		// Check if the mouse first entered the window - if true, set position:
		if (firstMouse) {
			last_x = mouse_x;
			last_y = mouse_y;
			firstMouse = false;
		}

		// Calculate the offset (value we will move the camera direction):
		float x_offset = mouse_x - last_x;
		float y_offset = last_y - mouse_y;
		last_x = mouse_x;
		last_y = mouse_y;

		// Adjust by movement sensitivity:
		float sensitivity = 0.5f;
		x_offset *= sensitivity;
		y_offset *= sensitivity;

		// Adjust yaw and pitch:
		main_cam->yaw += x_offset;
		main_cam->pitch += y_offset;

		// Clamp pitch (to prevent a full 360 loop):
		if (main_cam->pitch > 89.0f) main_cam->pitch = 89.0f;
		if (main_cam->pitch < -89.0f) main_cam->pitch = -89.0f;

		main_cam->Refresh();
	}
}

// Allows the user to set a main camera that will be used for movement:
void GpContext::SetMainCamera(std::shared_ptr<Camera> arg) {
	main_cam = arg;
}

// Object functions:
// Creates a vertex buffer object and returns its ID:
std::shared_ptr<Buffer> GpContext::CreateBuffer() {

	std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
	buffer->context = self.lock();
	return buffer;
}

std::shared_ptr<VertexArray> GpContext::CreateVertexArray() {

	std::shared_ptr<VertexArray> vertex_array = std::make_shared<VertexArray>();
	vertex_array->context = self.lock();
	return vertex_array;
}

std::shared_ptr<Shader> GpContext::CreateShader(std::string vert_path, std::string frag_path) {

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert_path, frag_path);
	shader->context = self.lock();
	return shader;
}

std::shared_ptr<Texture> GpContext::CreateTexture(std::string tex_path) {
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(tex_path);
	texture->context = self.lock();
	return texture;
}

std::shared_ptr<Mesh> GpContext::CreateMesh(std::string wf_filepath, glm::vec3 pos_arg) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(wf_filepath, pos_arg);
	mesh->context = self.lock();
	return mesh;
}

std::shared_ptr<Mesh> GpContext::CreateMesh(std::shared_ptr<VertexArray> vao_arg,
	std::shared_ptr<Texture> tex_arg, glm::vec3 pos_arg) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vao_arg, tex_arg, pos_arg);
	mesh->context = self.lock();
	return mesh;
}

std::shared_ptr<Mesh> GpContext::CreateMesh(std::shared_ptr<VertexArray> vao_arg,
	std::shared_ptr<RenderTexture> rend_tex_arg, glm::vec3 pos_arg) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vao_arg, rend_tex_arg, pos_arg);
	mesh->context = self.lock();
	return mesh;
}

std::shared_ptr<Camera> GpContext::CreateCamera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(ortho, win_size, position, target, fov_arg);

	camera->context = self.lock();
	return camera;
}

std::shared_ptr<RenderTexture> GpContext::CreateRenderTexture(glm::ivec2 size_arg) {

	// Create a quad that will contain scene information:
	std::vector<glm::vec3> position = {
		{ 1.0f, -1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f }
	};
	std::shared_ptr<VertexArray> quad_vao = Create2D(position);
	std::shared_ptr<RenderTexture> render_texture = std::make_shared<RenderTexture>(size_arg, quad_vao);
	render_texture->context = self.lock();
	return render_texture;
}



