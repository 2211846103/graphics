#include <shader.hpp>

using namespace Graphics;

static char* readFile(const char* path) {
    // Opens file
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Couldn't read " << path << std::endl;
        return nullptr;
    }

    // Gets the size of the file
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Get contents of the file
    char* contents = (char*)malloc(sizeof(char) * (size + 1));
    file.read(contents, size);
    contents[size] = '\0';

    return contents;
}

/* 
    OpenGLShader constracter that takes 
    vertex & fragment shaders file paths
    to compile then attach them to a shader program.
*/
OpenGLShader::OpenGLShader(const char* vShaderPath, const char* fShaderPath) {
    // Read Shader Files
    char* vShaderSource = readFile(vShaderPath);
    char* fShaderSource = readFile(fShaderPath);
    int  success;
    char infoLog[512];
    
    // Create a Vertex Shader
    _vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex, 1, &vShaderSource, NULL);
    glCompileShader(_vertex);

    // Check for Compilation Error
    glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create a Fragment Shader
    _fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment, 1, &fShaderSource, NULL);
    glCompileShader(_fragment);

    // Check for Compilation Error
    glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Deallocate Shader Files Content
    free(vShaderSource);
    free(fShaderSource);

    // Create a Shader Program
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertex);
    glAttachShader(_shaderProgram, _fragment);
    glLinkProgram(_shaderProgram);

    // Check for Linking Issues
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

OpenGLShader::~OpenGLShader() {
    // Delete Vertex, Fragment, and Shader Program
    glDeleteShader(_vertex);
    glDeleteShader(_fragment);
    glDeleteProgram(_shaderProgram);
}

void OpenGLShader::use() {
    glUseProgram(_shaderProgram);
}

void OpenGLShader::setUniform(const char* name, int value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform1i(loc, value);
}

void OpenGLShader::setUniform(const char* name, float value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform1f(loc, value);
}

void OpenGLShader::setUniform(const char* name, bool value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform1i(loc, static_cast<int>(value)); // OpenGL uses int for bools
}

void OpenGLShader::setUniform(const char* name, Math::Vec2& value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform2fv(loc, 1, value.toFloat());
}

void OpenGLShader::setUniform(const char* name, Math::Vec3& value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform3fv(loc, 1, value.toFloat());
}

void OpenGLShader::setUniform(const char* name, Math::Vec4& value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniform4fv(loc, 1, value.toFloat());
}

void OpenGLShader::setUniform(const char* name, Math::Mat4& value) {
    GLint loc = glGetUniformLocation(_shaderProgram, name);
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, value.toFloat());
}