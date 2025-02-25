#include "Texture.h"
#include "stb_image.h"


Texture::Texture(const std::vector<Image>& imgs)
{
    unsigned int count = 0;
    
    for(Image image : imgs)
    {
        unsigned int temp_ID;
        GLCall(glGenTextures(1, &temp_ID));

        if (count > 0) GLCall(glActiveTexture(GL_TEXTURE0 + count));

        int width, height, nrChannels;
        //GLCall(stbi_set_flip_vertically_on_load(true));
        unsigned char* data = stbi_load(image.path, &width, &height, &nrChannels, 0);

        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            GLCall(glBindTexture(GL_TEXTURE_2D, temp_ID));
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));

            unsigned int texFormat;

            if (image.format == ImageFormat::JPG)
            {
                texFormat = GL_CLAMP_TO_EDGE;
            }
            else {
                if (image.glParam == REPEAT)
                    texFormat = GL_REPEAT;
                if (image.glParam == MIRRORED_REPEAT)
                    texFormat = GL_MIRRORED_REPEAT;
                if (image.glParam == CLAMP_TO_BORDER)
                    texFormat = GL_CLAMP_TO_BORDER;
                if (image.glParam == CLAMP_TO_EDGE)
                    texFormat = GL_CLAMP_TO_EDGE;
            }
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texFormat));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texFormat));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            
            renderer_IDs.push_back(temp_ID);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data); 
        
        count++;
    }
}


void Texture::setUniforms(Shader& myShader, std::string name)
{
    unsigned int count = 1;
    std::string tex = name;

    myShader.use();

    for (unsigned int id : renderer_IDs)
    {
        std::string num = std::to_string(count);
        std::string final = tex + num;
        count++;
        myShader.setInt(final, id - 1);
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
