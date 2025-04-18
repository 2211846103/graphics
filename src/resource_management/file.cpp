#include "filewatch/FileWatch.hpp"
#include <iostream>
#include <memory>
#include <resource_management/file.hpp>
#include <stdio.h>


using namespace engine::resource_management;

File::File(const std::string path, std::string name, bool hot_reload) :
Resource(ResourceType::File, name) {
  this->path = path;
  this->hot_reload = hot_reload;

  if (hot_reload) this->watch();
  this->load();
}
File::~File() {
  this->unload();
}

void File::load() {
  std::cout << "Loading File" << std::endl;
}

void File::unload() {
  std::cout << "Unloading File" << std::endl;
}

void File::watch() {
  if (_watcher) return;
  _watcher = std::make_unique<filewatch::FileWatch<std::string>>(this->path, [this](const std::string& path, const filewatch::Event change_type) {
    if (change_type == filewatch::Event::modified) this->reload();
  });
}
void File::stopWatching() {
  _watcher.reset();
}

std::string File::read() {
  char * buffer = 0;
  long length;
  FILE * f = fopen(this->path.c_str(), "rb");

  if (f) {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = (char*) malloc (length);
    if (buffer) {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }

  return std::string(buffer);
}
