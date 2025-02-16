#include <file.hpp>

using namespace Utils;

char* File::readFile(const char* path) {
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