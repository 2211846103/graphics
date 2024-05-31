#include <shader.hpp>

using namespace Graphics;

OpenGLShader::OpenGLShader(const char* vShaderPath, const char* fShaderPath) {
    std::string vSource;
    std::string fSource;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vShaderPath);
        fShaderFile.open(fShaderPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vSource = vShaderStream.str();
        fSource = fShaderStream.str();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR::SHADER::FAILED_READING_FILE" << std::endl;
    }
    
    const char* vShaderSource = vSource.c_str();
    const char* fShaderSource = fSource.c_str();
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, NULL);
    glCompileShader(fragment);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
}

OpenGLShader::~OpenGLShader() {
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void OpenGLShader::useShader() {
    glUseProgram(shaderProgram);
}

