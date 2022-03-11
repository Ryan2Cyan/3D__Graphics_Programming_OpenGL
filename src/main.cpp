#define SDL_MAIN_HANDLED 
#include "instance.h"
#include "window.h"
#include "buffer.h"
#include "vao.h"
#include "shader.h"
#include "program.h" 
#include "mat4_uniform.h"
#include <wavefront/wavefront.h>
#include <SDL.h>
#include <GL/glew.h>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <ext.hpp>
#include <iostream>
#include <vector>

const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/fragment_shader.txt";
const GLchar* model_filepath = "Additional_Files/models/curuthers/curuthers.obj";

int main(int argc, char* argv[]) {

	// Initialisation (init glew after valid rendering context):
	sdl_window window("Triangle OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	// Init GLEW:
	if (glewInit() != GLEW_OK) throw std::exception();


	///////////// LOAD MODEL ///////////
	WfModel curuthers = { 0 };
	if (WfModelLoad(model_filepath, &curuthers) != 0) throw std::exception();
	


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
	program.link();
	program.delete_shaders(vertex_shader_id, fragment_shader_id);



	///////////// INPUT/RENDER LOOP ///////////
	SDL_Event event;
	GLfloat angle = 0;
	bool running = true;
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	while (running) {
		window.change_window_colour(0.7f, 0.7f, 0.8f, 1.0f);

		// Initialise model matrix:
		mat4_uniform model_mat("u_model", 1, GL_FALSE);
		model_mat.set_location(program.get_id());
		model_mat.set_value(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10)));

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

		glBindVertexArray(curuthers.vaoId);
		glUseProgram(program.get_id());

		// Upload matrix data:
		model_mat.upload_data();
		projection_mat.upload_data();

		// Bind texture:
		glBindTexture(GL_TEXTURE_2D, curuthers.textureId);

		// Draw Call!
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, curuthers.vertexCount);
		SDL_GL_SwapWindow(window.get_window());
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glBindVertexArray(0);

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				/*vertex_array.delete_vao();*/
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