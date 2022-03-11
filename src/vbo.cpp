#include "vbo.h"
#include <ext.hpp>

// Default Buffer:

/////////// CONSTRUCTOR ///////////
vbo_obj::vbo_obj(GLsizei input_num_of_buffers, std::vector<GLfloat> input_data, GLuint input_size, 
    GLenum input_binding_point, GLenum input_data_usage)
    : num_of_buffers{ input_num_of_buffers }, data {input_data}, binding_point{ input_binding_point }, 
    data_usage{ input_data_usage }, size_of_data{ input_size }
{
    id = 0;
}


/////////// UTILITY ///////////
void vbo_obj::generate() {
    glGenBuffers(num_of_buffers, &id);
    if (!id) throw std::exception();
}
void vbo_obj::bind() const {
    glBindBuffer(binding_point, id);
}
void vbo_obj::unbind() const {
    glBindBuffer(binding_point, 0);
}
void vbo_obj::buffer_data() const {
    bind();
    glBufferData(binding_point, data.size() * sizeof(data.at(0)), &data.at(0), data_usage);
    unbind();
}

/////////// GETTERS ///////////
GLenum vbo_obj::get_binding_point() const { return binding_point; }
GLuint vbo_obj::get_size() const { return size_of_data; }
GLuint vbo_obj::get_id() const { return id; }
std::vector<GLfloat> vbo_obj::get_data() const { return data; };




// Texture Buffer:

/////////// CONSTRUCTOR ///////////
texture_vbo_obj::texture_vbo_obj(GLsizei input_num_of_buffers, GLenum input_binding_point, GLuint input_level,
    GLint input_internal_format, GLenum input_format, GLenum input_type, GLint input_border,
    unsigned char* input_data, GLsizei input_width, GLsizei input_height)
    : num_of_buffers{ input_num_of_buffers }, binding_point{ input_binding_point }, level{input_level},
    internal_format{input_internal_format}, format{input_format}, type{input_type}, border{input_border},
    data{ input_data }, width{ input_width }, height{input_height}
{
    id = 0;
}
/////////// UTILITY ///////////
void texture_vbo_obj::generate() {
    glGenTextures(num_of_buffers, &id);
    if (!id) throw std::exception();
}
void texture_vbo_obj::bind() const {
    glBindTexture(binding_point, id);
}
void texture_vbo_obj::unbind() const {
    glBindTexture(binding_point, 0);
}
void texture_vbo_obj::buffer_data() const {
    bind();
    glTexImage2D(binding_point, level, internal_format, width, height, border, format, type, data);
    free(data);
    glGenerateMipmap(binding_point);
    unbind();
}


class vertex_object {
private:
    GLuint id;
    int components;
    std::vector<GLfloat> data;
    bool dirty;
    int type;

public:
    vertex_object() {
        dirty = false;
    };

    // Destructor: Unbind and delete buffer:
    ~vertex_object(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        GLuint del_id = id;
        glDeleteBuffers(1, &del_id); 
    }

    // Add vec2 GLfloat to the buffer:
    void add(glm::vec2 value){
        if (type != 0 && type != GL_FLOAT_VEC2) { 
            std::cout << "Error: mixing of types" << std::endl;
            throw std::exception();
        }
        data.push_back(value.x);
        data.push_back(value.y);
        dirty = true;
    }

    // Add vec3 GLfloat to the buffer:
    void add(glm::vec3 value){
        if (type != 0 && type != GL_FLOAT_VEC3) { 
            std::cout << "Error: mixing of types" << std::endl;
            throw std::exception();
        }
        data.push_back(value.x);
        data.push_back(value.y);
        data.push_back(value.z);
        dirty = true;
    }

    // Add vec4 GLfloat to the buffer:
    void add(glm::vec4 value){
        if (type != 0 && type != GL_FLOAT_VEC4) { 
            std::cout << "Error: mixing of types." << std::endl;
            throw std::exception();
        }
        data.push_back(value.x);
        data.push_back(value.y);
        data.push_back(value.z);
        data.push_back(value.w);
        dirty = true;
    }

    int get_components() {
        return components;
    }

    int get_data_size() {
        if (type == GL_FLOAT_VEC2) { return data.size() / 2; }
        else if (type == GL_FLOAT_VEC3) { return data.size() / 3; }
        else if (type == GL_FLOAT_VEC3) { return data.size() / 4; }
        else throw std::exception();
    }

    // Binds buffer, then buffers all the data held within it. Then resets the state:
    GLuint get_id(){
        glBindBuffer(GL_ARRAY_BUFFER, id);

        if (type == GL_FLOAT || type == GL_FLOAT_VEC2 || type == GL_FLOAT_VEC3 || type == GL_FLOAT_VEC4) {
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
        }
        else {
            std::cout << "Error: invalid buffer data type." << std::endl;
            throw std::exception();
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        dirty = false; // Data has been sent to the GPU.
    }
};


