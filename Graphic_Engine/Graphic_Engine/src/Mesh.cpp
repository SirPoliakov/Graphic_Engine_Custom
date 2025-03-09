#include "Mesh.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures) : 
	VAO(VertexArray()),
    vertices(_vertices), 
	indices(_indices), 
	textures(_textures),
	EBO(IndexBuffer(&indices[0], indices.size())), 
	VBO(VertexBuffer(&vertices[0], vertices.size()))
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
    GLCall(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
    VAO.unbind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	VertexBufferLayout vLayout; vector<void*> offsets;

	vLayout.push<float>(3); offsets.push_back((void*)0);
	vLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Normal));
	vLayout.push<float>(2); offsets.push_back((void*)offsetof(Vertex, TexCoords));
	vLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Tangent));
	vLayout.push<float>(3); offsets.push_back((void*)offsetof(Vertex, Bitangent));
	vLayout.push<float>(4); offsets.push_back((void*)offsetof(Vertex, m_BoneIDs));
	vLayout.push<float>(4); offsets.push_back((void*)offsetof(Vertex, m_Weights));

	unsigned int size = sizeof(Vertex);

	VAO.addBuffer(VBO, vLayout, size, offsets);
}
