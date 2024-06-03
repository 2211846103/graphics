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
    char contents[size + 1];
    for (int i = 0; file.get(contents[i]); i++);
    contents[size] = '\0';

    return contents;
}

OpenGLShader::OpenGLShader(const char* vShaderPath, const char* fShaderPath) {
    const char* vShaderSource = readFile(vShaderPath);
    const char* fShaderSource = readFile(fShaderPath);
    
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

