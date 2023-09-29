#pragma once

#include <iostream>
#include <memory>
#include <string>

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
using HandleType = void*;
#elif _WIN32
#include <windows.h>
using HandleType = HWMODULE;
#endif

namespace {
  constexpr auto DEFAULT_CREATE_CLASS_SYMBOL{"create"};
  constexpr auto DEFAULT_DESTROY_CLASS_SYMBOL{"destroy"};
}

template<class Base>
class ClassLoader
{
public:
  // Input parameter - fully qualified path to the runtime library
  ClassLoader(const std::string& library_path)
  : library_path_{library_path}
  {}

  void loadLibrary()
  {
    #if defined(__linux__) || defined(__APPLE__)
    handle_ = dlopen(library_path_.c_str(), RTLD_LAZY);
    if (handle_) {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
    }
    #elif _WIN32
    handle_ = LoadLibrary(library_path_.c_str());
    if (handle_) {
      std::cerr << "Cannot load library: " << library_path_ << '\n';
    }
    #endif 
  }

  void unloadLibrary()
  {
    #if defined(__linux__) || defined(__APPLE__)
    if(dlclose(handle_) != 0)
    {
      std::cerr << "An error occured closing a library: " << dlerror() << '\n';
    }
    #elif _WIN32
    if (FreeLibrary(handle_) == 0) 
    {
      std::cerr << "Can't close " << library_path_ << std::endl;
    }
    #endif   
  }

  std::shared_ptr<Base> GetInstance()
  {
    // function pointer types
    using allocClass = Base *(*)();
    using deleteClass = void (*)(Base *);

    #if defined(__linux__) || defined(__APPLE__)

    auto createFunc = reinterpret_cast<allocClass>(
      dlsym(handle_, DEFAULT_CREATE_CLASS_SYMBOL));
    auto destroyFunc = reinterpret_cast<deleteClass>(
      dlsym(handle_, DEFAULT_DESTROY_CLASS_SYMBOL));
    if (!createFunc || !destroyFunc) {
      std::cerr << dlerror() << std::endl;
      unloadLibrary();
    }
    #elif _WIN32
    
    auto createFunc = reinterpret_cast<allocClass>(
      GetProcAddress(handle_, DEFAULT_ALLOC_CLASS_SYMBOL));
    auto destroyFunc = reinterpret_cast<deleteClass>(
      GetProcAddress(handle_, DEFAULT_DELETER_CLASS_SYMBOL));

    if (!createFunc || !destroyFunc) {
      std::cerr << "Can't find create or destroy symbol in " << _pathToLib << std::endl;
      unloadLibrary(); 
    }
    #endif

    return std::shared_ptr<Base>(
        createFunc(),
        [destroyFunc](Base *p){ destroyFunc(p); });
  }

private:
  HandleType handle_;
  std::string library_path_;
};
