#include "Mesh.h"
#include "Shader.h"
#include "VertexBufferLayout.h"


Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures)
{
    this->vertices = _vertices;
    this->indices = _indices;
    this->textures = _textures;

    setupMesh();
    VAO.unbind();
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other) {
        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
        textures = std::move(other.textures);
        VAO = std::move(other.VAO);
        VBO = std::move(other.VBO);
        EBO = std::move(other.EBO);
    }
    return *this;
}

Mesh::Mesh(Mesh&& other) noexcept
    : vertices(std::move(other.vertices)),
    indices(std::move(other.indices)),
    textures(std::move(other.textures)),
    VAO(std::move(other.VAO)),
    VBO(std::move(other.VBO)),
    EBO(std::move(other.EBO)) 
    {
        setupMesh();
    }

void Mesh::draw(const Shader& shader)
{
    
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    VAO.bind();
    GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
    VAO.unbind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{  
    this->VAO.bind();

    this->VBO.populateBuffer(&vertices[0], vertices.size());

    this->EBO.populateIndex(&indices[0], indices.size());

    VertexBufferLayout vbLayout; vector<void*> offsets;

    vbLayout.push<float>(3); offsets.push_back((void*)0);
    vbLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Normal));
    vbLayout.push<float>(2); offsets.push_back((void*)offsetof(Vertex, TexCoords));
    vbLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Tangent));
    vbLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Bitangent));
    vbLayout.push<unsigned int>(4); offsets.push_back((void*)offsetof(Vertex, m_BoneIDs));
    vbLayout.push<float>(4); offsets.push_back((void*)offsetof(Vertex, m_Weights));
    
    unsigned int size = sizeof(Vertex);
    VAO.addBuffer(VBO, vbLayout, size, offsets); 
}
