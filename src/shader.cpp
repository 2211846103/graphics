#include <shader.hpp>

using namespace Graphics;

static char* readFile(const char* path) {
    // Opens file
    std::ifstream file(path);
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
    for (int i = 0; file.get(contents[i]); i++);
    contents[size] = '\0';

    return contents;
}

/* 
    OpenGLShader constracter that takes 
    vertex & fragment shaders file paths
    to compile then attach them to a shader program.
*/
OpenGLShader::OpenGLShader(const char* vShaderPath, const char* fShaderPath) {
    char* vShaderSource = readFile(vShaderPath);
    char* fShaderSource = readFile(fShaderPath);
    int  success;
    char infoLog[512];
    
    _vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex, 1, &vShaderSource, NULL);
    glCompileShader(_vertex);

    glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    _fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment, 1, &fShaderSource, NULL);
    glCompileShader(_fragment);

    glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    free(vShaderSource);
    free(fShaderSource);

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertex);
    glAttachShader(_shaderProgram, _fragment);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

OpenGLShader::~OpenGLShader() {
    glDeleteShader(_vertex);
    glDeleteShader(_fragment);
    glDeleteProgram(_shaderProgram);
}

void OpenGLShader::useShader() {
    glUseProgram(_shaderProgram);
}

void OpenGLShader::setUniform(const char* uniName) {
    OpenGLShader::useShader();

    float timeValue = glfwGetTime();
    float redValue = sin(timeValue) / 2.0f + 0.5f;
    float greenValue = 0.5f;
    float blueValue = sin(timeValue) / 3.1f + 0.3;
    float opacity = 1.0f;
    int vertexColorLocation = glGetUniformLocation(this->_shaderProgram, uniName);

    glUseProgram(this->_shaderProgram);
    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, opacity);

}