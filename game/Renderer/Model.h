#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>

#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

class Model
{
public:
    std::vector<Mesh> meshes_;
    
    Model(const std::string _path, 
        bool embedded = false, 
        bool gamma = false);

    void Draw(Shader& shader);
    void DrawInstanced(Shader& shader, std::vector<glm::mat4>& instance_mod_mats);
    void DrawInstanced(Shader& shader, std::shared_ptr<std::vector<glm::mat4>> instance_mod_mats);

private:
    std::string directory_;
    bool gamma_correction_;
    bool textures_embedded_;
    std::vector<Mesh::Texture> textures_loaded_;

    void loadModel(const std::string _path);
    void processNode(aiNode* node, const aiScene* _scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* _scene);
    std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* material, aiTextureType ai_type, 
        TEXTYPEenum tx_type, TEXFORMATenum tx_format);
    std::vector<Mesh::Texture> loadMaterialTexturesEmbedded(aiMaterial* material,
        aiTextureType ai_type, TEXFORMATenum tx_format);
};