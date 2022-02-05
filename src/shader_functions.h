#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <glew.h>

// Reads contents of a shader txt file:
const std::string read_shader_file(const char* file_path);