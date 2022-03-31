#pragma once

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <vector>
//#include <string>
//
//struct AssImpMesh;
//struct Shader;
//struct AItexture;
//
//
//struct Model
//{
//public:
//    Model(char* path)
//    {
//        loadModel(path);
//    }
//    void Draw(Shader& shader);
//private:
//    // model data
//    std::vector<AssImpMesh> meshes;
//    std::string directory;
//
//    void loadModel(std::string path);
//    void processNode(aiNode* node, const aiScene* scene);
//    AssImpMesh processMesh(aiMesh* mesh, const aiScene* scene);
//    std::vector<AItexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
//        std::string typeName);
//};