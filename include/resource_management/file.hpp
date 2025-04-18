#pragma once

#include <memory>
#include <resource_management/resource.hpp>
#include <string>
#include <filewatch/FileWatch.hpp>


namespace engine::resource_management {

class File : public Resource {
private:
  std::unique_ptr<filewatch::FileWatch<std::string>> _watcher;

  void load() override;
  void unload() override;

public:
  std::string path;
  bool hot_reload = false;

  File(const std::string path, std::string name = "", bool hot_reload = false);
  ~File();

  // Hot Reloading Methods
  void watch();
  void stopWatching();

  std::string read();
};

}
