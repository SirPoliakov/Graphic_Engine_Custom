#include "Mesh.h"
#include "Shader.h"
#include "VertexBufferLayout.h"


Mesh::Mesh(vector<Vertex>* _vertices, vector<unsigned int>* _indices, vector<Texture>* _textures)
: vertices(*_vertices), indices(*_indices), textures(*_textures)
{
    _vertices = 0; delete _vertices; 
    _indices = 0;  delete _indices; 
    _textures = 0;  delete _textures;
    
    setupMesh();
    VAO.unbind();
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
        GLCall(glActiveTexture(GL_TEXTURE0 + i)); // active proper texture unit before binding
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
        GLCall(glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i));
        // and finally bind the texture
        GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
    }

    //std::cout << "Drawing VAO: " << VAO.getID() << " | Indices: " << indices.size() << std::endl;
    VAO.bind();
    GLCall(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
    VAO.unbind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{  
    this->VAO.bind();
    this->VBO.populateBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
    this->EBO.populateIndex(&indices[0], indices.size());

    VertexBufferLayout vbLayout; vector<void*> offsets;

    vbLayout.push(3); offsets.push_back((void*)offsetof(Vertex,Position));
    vbLayout.push(3); offsets.push_back((void*)offsetof(Vertex, Normal));
    vbLayout.push(2); offsets.push_back((void*)offsetof(Vertex, TexCoords));
    //vbLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Tangent));
    //vbLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Bitangent));
    //vbLayout.push<unsigned int>(4); offsets.push_back((void*)offsetof(Vertex, m_BoneIDs));
    //vbLayout.push<float>(4); offsets.push_back((void*)offsetof(Vertex, m_Weights));
    
    unsigned int size = sizeof(Vertex);

    //std::cout << "  Tang -> Offset: " << (size_t)offsets[3] << std::endl;
    //std::cout << "  Bitan -> Offset: " << (size_t)offsets[4] << std::endl;
    //std::cout << "  BoneIDs -> Offset: " << (size_t)offsets[5] << std::endl;
    //std::cout << "  Weights -> Offset: " << (size_t)offsets[6] << std::endl;

    VAO.addBuffer(VBO, vbLayout, size, offsets); 
}
