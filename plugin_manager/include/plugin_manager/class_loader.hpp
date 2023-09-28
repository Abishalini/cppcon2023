#pragma once

#include <iostream>
#include <memory>
#include <string>


namespace plugin_manager {

#if defined(__linux__) || defined(__APPLE__)
  using HandleType = void*;
#elif _WIN32
  using HandleType = HWMODULE;
#endif

template<class Base>
class ClassLoader
{
public:
  // Input parameter - fully qualified path to the runtime library
  ClassLoader(const std::string& library_path);

  void loadLibrary();

  void unloadLibrary();

  std::shared_ptr<Base> GetInstance();

private:
  HandleType handle_;
  std::string library_path_;
};

}
