#pragma once

#include "GLCalls.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <string>

using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];

    //Vertex(Vertex&&) = default;
    //Vertex& operator=(Vertex&&) = default;
};

struct Texture {
    unsigned int id;
    string type;
    string path;

    //Texture(Texture&&) = default;
    //Texture& operator=(Texture&&) = default;
};

class Shader;


class Mesh {

public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;

    VertexArray VAO;

    // constructor
    Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);
    

    //Move Operation
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    //DeletedCopy
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void draw(const Shader& shader);

private:
    // render data 
    VertexBuffer VBO;
    IndexBuffer EBO;

    void setupMesh();
};