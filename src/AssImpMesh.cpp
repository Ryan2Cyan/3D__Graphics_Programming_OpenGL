#include "AssImpMesh.h"
#include <GL/glew.h>
#include "Shader.h"

AssImpMesh::AssImpMesh(std::vector<AIvertex> vert_arg, std::vector<GLuint> indi_arg,
	std::vector<AItexture> tex_arg) {

	vertices = vert_arg;
	indices = indi_arg;
	textures = tex_arg;

	SetUpMesh();
}

void AssImpMesh::SetUpMesh() {

    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);
    glGenBuffers(1, &ebo_id);

    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(AIvertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AIvertex), (void*)0);

    // AIvertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AIvertex), (void*)offsetof(AIvertex, norm));

    // AIvertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AIvertex), (void*)offsetof(AIvertex, tex_coord));

    glBindVertexArray(0);
}

void AssImpMesh::Draw(std::shared_ptr<Shader> shader) {

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_Diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_Specular")
            number = std::to_string(specularNr++);

        glUseProgram(shader->GetId());
        shader->SetUniform((name + number), textures[i].id);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(vao_id);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}