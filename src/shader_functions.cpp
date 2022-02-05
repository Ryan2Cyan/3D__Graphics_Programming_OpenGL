#include "shader_functions.h"

// Reads contents of a shader txt file:
const std::string read_shader_file(const GLchar* file_path) {
	std::string content;
	std::ifstream file_stream(file_path, std::ios::in);

	// Check if the file can be opened:
	if (!file_stream.is_open()) {
		std::cerr << "Could not read file " << file_path << ". File does not exist." << std::endl;
		return "";
	}
	std::string line = "";
	while (!file_stream.eof()) {    // While the stream has not reached the end of the file
		std::getline(file_stream, line);
		content.append(line + "\n");
	}
	return content;
}
