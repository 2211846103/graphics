#pragma once

#include <fstream>
#include <iostream>

namespace Utils {
    class File {
        public:
            static char* readFile(const char* path);
    };
}