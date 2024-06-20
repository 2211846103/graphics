#include <texture.hpp>

using namespace Graphics;

OpenGLTexture::OpenGLTexture() {
    glGenTextures(1, &this->_id);
}

OpenGLTexture::~OpenGLTexture() {
    glDeleteTextures(1, &this->_id);
    unbind();
}

void OpenGLTexture::bind2D() {
    this->_target = GL_TEXTURE_2D;
    glBindTexture(this->_target, this->_id);
}

void OpenGLTexture::bind3D() {
    this->_target = GL_TEXTURE_3D;
    glEnable(this->_target);
    glBindTexture(this->_target, this->_id);
}

void OpenGLTexture::bindCube() {
    this->_target = GL_TEXTURE_CUBE_MAP;
    glBindTexture(this->_target, this->_id);
}

void OpenGLTexture::unbind() {
    glBindTexture(this->_target, 0);
    this->_target = 0;
}

void OpenGLTexture::load2D(const char* path, int* width, int* height) {
    unsigned char* data = stbi_load(path, width, height, nullptr, 4);
    if (!data) {
        std::cerr << "Failed to load texture " << path << std::endl;
    }

    glTexImage2D(this->_target, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

void OpenGLTexture::load3D(const char* dir, int* width, int* height, int layers) {
    DIR* folder = opendir(dir);
    if (!folder) {
        std::cerr << "Failed to open " << folder << std::endl;
        return;
    }

    unsigned char* data = NULL;
    size_t currentSize = 0;
    dirent* entry;
    while (entry = readdir(folder)) {
        std::string filename = entry->d_name;
        if (filename == "." || filename == "..") {
            continue;
        }
        std::string path = std::string(dir) + "/" + filename;

        unsigned char* temp = stbi_load(path.c_str(), width, height, nullptr, 4);
        int elementsCount = *width * *height * 4;
        currentSize += sizeof(unsigned char) * (elementsCount - 1);

        data = (unsigned char*)realloc(data, currentSize + sizeof(unsigned char) * elementsCount);
        std::copy<unsigned char, unsigned char>(temp, temp+currentSize, data)
    }
}