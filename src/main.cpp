#define SDL_MAIN_HANDLED 
#include "instance.h"
#include "window.h"
#include "vbo.h"
#include "vao.h"
#include "shader.h"
#include "program.h" 
#include "mat4_uniform.h"

#include <SDL.h>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <ext.hpp>
#include <iostream>
#include <vector>

const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/fragment_shader.txt";

int main(int argc, char* argv[]) {

	// Initialisation (init glew after valid rendering context):
	sdl_window window("Triangle OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	// Init GLEW:
	if (glewInit() != GLEW_OK) throw std::exception();



	/////////// POSITIONS [VBO] ///////////
	std::vector<GLfloat> positions{
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	vbo_obj buffer_obj(1, positions, 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	buffer_obj.generate();
	buffer_obj.bind();
	buffer_obj.buffer_data();
	buffer_obj.unbind();



	/////////// COLORS [VBO] ///////////
	std::vector<GLfloat> colors{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	vbo_obj color_buffer_obj(1, colors, 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	color_buffer_obj.generate();
	color_buffer_obj.buffer_data();



	/////////// INDICES [VBO] ///////////
	std::vector<GLuint> indices{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};
	GLuint element_buffer_id;
	glGenBuffers(1, &element_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), &indices.at(0), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	/////////// TEXTURE [VBO] ///////////
  // Define texture coordinates:
	std::vector<GLfloat> texture_coordinates{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
	};
	vbo_obj texture_coords_buffer(1, texture_coordinates, 2, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	texture_coords_buffer.generate();
	texture_coords_buffer.bind();
	texture_coords_buffer.buffer_data();
	texture_coords_buffer.unbind();



	///////////// VERTEX ARRAY OBJECT ///////////
	   // Create a VAO and store layout of VBO:
	vao_obj vertex_array(1, GL_FALSE);
	vertex_array.generate();
	vertex_array.insert_data(buffer_obj, 0, GL_FLOAT);  // Insert position data
	vertex_array.insert_data(color_buffer_obj, 1, GL_FLOAT);  // Insert color data
	vertex_array.insert_data(texture_coords_buffer, 2, GL_FLOAT);  // Insert texture coord data



	///////////// TEXTURE ///////////
	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image:
	int w, h, channels;
	unsigned char* data = stbi_load("Additional_Files/images/image_test.PNG", &w, &h, &channels, 4);
	if (!data) throw std::exception();

	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	if (!texture_id) throw std::exception();
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);



	///////////// VERTEX SHADER ///////////
	// Vertex Shader: Read source file, then generate and compile shader object:
	std::string vertex_shader_src_str = read_shader_file(vertex_shader_filepath);
	const GLchar* vertex_shader_src_char = vertex_shader_src_str.c_str();  // convert from string to const GLchar*
	GLuint vertex_shader_id = create_shader_object(GL_VERTEX_SHADER, 1, vertex_shader_src_char);



	///////////// FRAGMENT SHADER ///////////
	// Fragment Shader: Read source file, then generate and compile shader object:
	std::string fragment_shader_src_str = read_shader_file(fragment_shader_filepath);
	const GLchar* fragment_shader_src_char = fragment_shader_src_str.c_str();  // convert from string to const GLchar*
	GLuint fragment_shader_id = create_shader_object(GL_FRAGMENT_SHADER, 1, fragment_shader_src_char);



	///////////// SHADER PROGRAM ///////////
	program_obj program = program_obj();
	program.generate();
	program.attach_shaders(vertex_shader_id, fragment_shader_id);
	program.bind_vertex_attribute("a_position");
	program.bind_fragment_attribute("a_color");
	program.link();
	program.delete_shaders(vertex_shader_id, fragment_shader_id);



	///////////// INPUT/RENDER LOOP ///////////
	SDL_Event event;
	GLfloat angle = 0;
	bool running = true;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (running) {
		window.change_window_colour(0.4f, 0.7f, 0.9f, 1.0f);

		// Initialise model matrix:
		mat4_uniform model_mat("u_model", 1, GL_FALSE);
		model_mat.set_location(program.get_id());
		model_mat.set_value(glm::mat4(1.0f));

		// Initialise projection matrix:
		mat4_uniform projection_mat("u_projection", 1, GL_FALSE);
		projection_mat.set_location(program.get_id());
		projection_mat.set_value(glm::perspective(
			glm::radians(45.0f),
			(float)window.get_width() / (float)window.get_height(),
			0.1f,
			100.f
		));

		// Modify model matrix for rotation:
		model_mat.translate(glm::vec3(0, 0, -2.5f));
		model_mat.rotate(angle, glm::vec3(0, 1, 0));

		angle += 0.5f; // Increase angle next frame to rotate the triangle

		glBindVertexArray(vertex_array.get_id());
		glUseProgram(program.get_id());

		// Upload matrix data:
		model_mat.upload_data();
		projection_mat.upload_data();

		// Bind texture:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		// Draw Call!
		glEnable(GL_CULL_FACE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window.get_window());
		glDisable(GL_CULL_FACE);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				vertex_array.delete_vao();
				program.delete_program();
				window.delete_window();
				break;
			case SDL_WINDOWEVENT:
				// Adjust OpenGL viewport on window resize
				window.adjust_viewport();
				break;
			default:
				break;
			}
		}
	}
}