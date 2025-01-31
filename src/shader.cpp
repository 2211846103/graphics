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

void OpenGLShader::useShader() {
    glUseProgram(_shaderProgram);
}

void OpenGLShader::setIntUniform(const char* uniName, int value) {
    // Specify Shader used
    OpenGLShader::useShader();

    // Get Uniform Location and Assign Value to it
    int vertexColorLocation = glGetUniformLocation(this->_shaderProgram, uniName);
    glUniform1i(vertexColorLocation, value);
}