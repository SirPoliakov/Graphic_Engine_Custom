#include "Texture.h"
#include "Renderer.h"
#include "stb_image.h"


Texture::Texture(const std::vector<Image>& imgs)
{
    unsigned int count = 0;
    
    for(Image image : imgs)
    {
        unsigned int temp_ID;
        GLCall(glGenTextures(1, &temp_ID));

        if (count > 0) GLCall(glActiveTexture(GL_TEXTURE0 + count));

        GLCall(glBindTexture(GL_TEXTURE_2D, temp_ID));
        renderer_IDs.push_back(temp_ID);
        if (image.format == ImageFormat::JPG)
        {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        }
        else {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        }
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        int width, height, nrChannels;
        //GLCall(stbi_set_flip_vertically_on_load(true));
        unsigned char* data = stbi_load(image.path, &width, &height, &nrChannels, 0);

        if (data)
        {
            if (image.format == ImageFormat::JPG)
            {
               GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
            }
            else
            { 
                GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
                
            }
            
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        
        count++;
    }
}

void Texture::setUniforms(Shader& myShader)
{
    unsigned int count = 1;
    std::string tex = "texture";

    myShader.use();

    for (unsigned int id : renderer_IDs)
    {
        std::string num = std::to_string(count);
        std::string final = tex + num;
        count++;
        myShader.setInt(final, id-1);
    }
}

const void Texture::bind() const
{
    unsigned int count = 0
        ;
    for (unsigned int id : renderer_IDs)
    {
        GLCall(glActiveTexture(GL_TEXTURE0+count));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));

        count++;
    }
    
}

const void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
