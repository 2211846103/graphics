#include <texture.hpp>

using namespace Graphics;

OpenGLTexture::OpenGLTexture() {
    glGenTextures(1, &this->_id);
}

OpenGLTexture::~OpenGLTexture() {
    glDeleteTextures(1, &this->_id);
    unbind();
    delete this;
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
    this->bind2D();
    int channels;

    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(path, width, height, &channels, 4);
    if (!data) {
        std::cerr << "Failed to load texture " << path[0] << std::endl;
        return;
    }

    glTexImage2D(this->_target, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

void OpenGLTexture::load3D(const char* path[], size_t size, int* width, int* height, int* depth) {
  this->bind3D();
  int textureSize = 0;
  unsigned char* data = NULL;
  *depth = size / sizeof(const char*);

  for (int i = 0; i < *depth; i++) {
    int iWidth, iHeight, iChannels;
    unsigned char* iData = stbi_load(path[i], &iWidth, &iHeight, &iChannels, 4);
    if (!iData) {
      std::cerr << "Failed to load texture " << path[i] << std::endl;
      return;
    }

    data = (unsigned char*)realloc(data, (textureSize + iWidth * iHeight * iChannels) * sizeof(unsigned char));
    std::memcpy(data + textureSize, iData, iWidth * iHeight * iChannels * sizeof(unsigned char));
    textureSize += iWidth * iHeight * iChannels;

    stbi_image_free(iData);
    if (i == 0) {
      *width = iWidth;
      *height = iHeight;
    }
  }

  glTexImage3D(this->_target, 0, GL_RGBA, *width, *height, *depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);\

  free(data);
}

void OpenGLTexture::loadCube(const char* path[], size_t size, int* width, int* height) {
  this->bindCube();
  GLenum cubeFaces[] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };

  for (int i = 0; i < 6; i++) {
    int iWidth, iHeight, iChannels;
    unsigned char* iData = stbi_load(path[i], &iWidth, &iHeight, &iChannels, 4);
    if (iWidth != iHeight) {
      std::cerr << "Texture specified at " << path[i] << " doesn't have equal width and height" << std::endl;
      return;
    }
    if (!iData) {
      std::cerr << "Failed to load texture " << path[i] << std::endl;
      return;
    }

    glTexImage2D(cubeFaces[i], 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, iData);

    stbi_image_free(iData);
  }
}

void OpenGLTexture::generateMipmap() {
  glGenerateMipmap(this->_target);
}

void OpenGLTexture::activate(int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
}

void OpenGLTexture::loadConfig(TextureConfig* config) {
  // Base level
  glTexParameteri(this->_target, GL_TEXTURE_BASE_LEVEL, config->base_level);

  GLenum min_filter;
  // Min Filter
  switch (config->min_filter) {
    case LINEAR:
      min_filter = GL_LINEAR;
      break;
    case NEAREST:
      min_filter = GL_NEAREST;
      break;
    case NEAREST_MIPMAP_LINEAR:
      min_filter = GL_NEAREST_MIPMAP_LINEAR;
      break;
    case NEAREST_MIPMAP_NEAREST:
      min_filter = GL_NEAREST_MIPMAP_NEAREST;
      break;
    case LINEAR_MIPMAP_LINEAR:
      min_filter = GL_LINEAR_MIPMAP_LINEAR;
      break;
    case LINEAR_MIPMAP_NEAREST:
      min_filter = GL_LINEAR_MIPMAP_NEAREST;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, min_filter);

  // Mag Filter
  GLenum mag_filter;
  switch (config->mag_filter) {
    case LINEAR:
      mag_filter = GL_LINEAR;
      break;
    case NEAREST:
      mag_filter = GL_NEAREST;
      break;
    default:
      std::cerr << "Invalid Magnification Filter" << std::endl;
      exit(1);
  }
  glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, mag_filter);

  // LOD Bias
  glTexParameterf(this->_target, GL_TEXTURE_LOD_BIAS, config->lod_bias);

  // Min LOD
  glTexParameterf(this->_target, GL_TEXTURE_MIN_LOD, config->min_lod);

  // Max LOD
  glTexParameterf(this->_target, GL_TEXTURE_MAX_LOD, config->max_lod);

  // Max Level
  glTexParameteri(this->_target, GL_TEXTURE_MAX_LEVEL, config->max_level);

  // Swizzle R
  GLenum rswizzle;
  switch (config->swizzle_r) {
    case RED:
      rswizzle = GL_RED;
      break;
    case GREEN:
      rswizzle = GL_GREEN;
      break;
    case BLUE:
      rswizzle = GL_BLUE;
      break;
    case ALPHA:
      rswizzle = GL_ALPHA;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_R, rswizzle);

  // Swizzle G
  GLenum gswizzle;
  switch (config->swizzle_g) {
    case RED:
      gswizzle = GL_RED;
      break;
    case GREEN:
      gswizzle = GL_GREEN;
      break;
    case BLUE:
      gswizzle = GL_BLUE;
      break;
    case ALPHA:
      gswizzle = GL_ALPHA;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_G, gswizzle);

  // Swizzle B
  GLenum bswizzle;
  switch (config->swizzle_b) {
    case RED:
      bswizzle = GL_RED;
      break;
    case GREEN:
      bswizzle = GL_GREEN;
      break;
    case BLUE:
      bswizzle = GL_BLUE;
      break;
    case ALPHA:
      bswizzle = GL_ALPHA;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_B, bswizzle);

  // Swizzle A
  GLenum aswizzle;
  switch (config->swizzle_a) {
    case RED:
      aswizzle = GL_RED;
      break;
    case GREEN:
      aswizzle = GL_GREEN;
      break;
    case BLUE:
      aswizzle = GL_BLUE;
      break;
    case ALPHA:
      aswizzle = GL_ALPHA;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_A, aswizzle);

  // Wrap S
  GLenum swrap;
  switch (config->wrap_x) {
    case CLAMP_TO_BORDER:
      swrap = GL_CLAMP_TO_BORDER;
      break;
    case CLAMP_TO_EDGE:
      swrap = GL_CLAMP_TO_EDGE;
      break;
    case MIRRORED_REPEAT:
      swrap = GL_MIRRORED_REPEAT;
      break;
    case REPEAT:
      swrap = GL_REPEAT;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, swrap);

  // Wrap T
  GLenum twrap;
  switch (config->wrap_y) {
    case CLAMP_TO_BORDER:
      twrap = GL_CLAMP_TO_BORDER;
      break;
    case CLAMP_TO_EDGE:
      twrap = GL_CLAMP_TO_EDGE;
      break;
    case MIRRORED_REPEAT:
      twrap = GL_MIRRORED_REPEAT;
      break;
    case REPEAT:
      twrap = GL_REPEAT;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, twrap);

  // Wrap R
  GLenum rwrap;
  switch (config->wrap_z) {
    case CLAMP_TO_BORDER:
      rwrap = GL_CLAMP_TO_BORDER;
      break;
    case CLAMP_TO_EDGE:
      rwrap = GL_CLAMP_TO_EDGE;
      break;
    case MIRRORED_REPEAT:
      rwrap = GL_MIRRORED_REPEAT;
      break;
    case REPEAT:
      rwrap = GL_REPEAT;
      break;
  }
  glTexParameteri(this->_target, GL_TEXTURE_WRAP_R, rwrap);
}

void Texture::activate(Shader* shader, const char* uniName, int unit) {
  this->bind();
  if (!this->isConfigLoaded) {
    this->_api->loadConfig(this->config);
    this->isConfigLoaded = true;
  }
  this->_api->activate(unit);
  shader->setIntUniform(uniName, unit);
}

Texture2D::Texture2D(TextureAPI* api) {
  this->_api = api;
  this->config = new TextureConfig();
}

void Texture2D::bind() {
  this->_api->bind2D();
}

void Texture2D::unbind() {
  this->_api->unbind();
}

void Texture2D::mipmap() {
  this->_api->generateMipmap();
}

void Texture2D::load(const char* path) {
  this->_api->load2D(path, &this->width, &this->height);
}

Texture3D::Texture3D(TextureAPI* api) {
  this->_api = api;
  this->config = new TextureConfig();
}

void Texture3D::bind() {
  this->_api->bind3D();
}

void Texture3D::unbind() {
  this->_api->unbind();
}

void Texture3D::load(const char* path[], size_t size) {
  this->_api->load3D(path, size, &this->width, &this->height, &this->depth);
}

TextureCube::TextureCube(TextureAPI* api) {
  this->_api = api;
  this->config = new TextureConfig();
}

void TextureCube::bind() {
  this->_api->bindCube();
}

void TextureCube::unbind() {
  this->_api->unbind();
}

void TextureCube::load(const char* path[], size_t size) {
  this->_api->loadCube(path, size, &this->width, &this->height);
}