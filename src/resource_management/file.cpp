#include "filewatch/FileWatch.hpp"
#include <memory>
#include <resource_management/file.hpp>
#include <stdio.h>


using namespace engine::resource_management;

File::File(const std::string path, std::string name, bool hot_reload, bool lazy) :
Resource(ResourceType::File, name, lazy) {
  this->path = path;
  this->hot_reload = hot_reload;

  if (hot_reload) this->watch();
  if (lazy) this->load();
}
File::~File() {
  this->unload();
}

void File::load() {
  if (this->loaded) return;
  this->loaded = true;
}

void File::unload() {
  if (!this->loaded) return;
  this->loaded = false;
}

void File::watch() {
  this->load();

  if (_watcher) return;
  _watcher = std::make_unique<filewatch::FileWatch<std::string>>(this->path, [this](const std::string& path, const filewatch::Event change_type) {
    if (change_type == filewatch::Event::modified) this->reload();
    this->version++;
  });
}
void File::stopWatching() {
  this->load();

  _watcher.reset();
}

std::string File::read() {
  this->load();

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
