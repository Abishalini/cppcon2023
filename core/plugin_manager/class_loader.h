#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <expected>
#include <optional>

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

enum struct ClassLoaderError{
  load_error,
  unload_error,
  invalid_symbol,
  handle_in_use_error, // This error only exists because I don't want to implement logic to load multiple plugins at once.
};

template<class Base>
class ClassLoader
{
public:
  // Input parameter - fully qualified path to the runtime library
  ClassLoader(const std::string& create_symbol=DEFAULT_CREATE_CLASS_SYMBOL, 
              const std::string& destroy_symbol=DEFAULT_DESTROY_CLASS_SYMBOL)
  : create_symbol_(create_symbol)
  , destroy_symbol_(destroy_symbol)
  {}

  ~ClassLoader() = default;

  std::optional<ClassLoaderError> loadLibrary(const std::string& library_path)
  {
    #if defined(__linux__) || defined(__APPLE__)
    if(handle_){
      return ClassLoaderError::handle_in_use_error;
    }
    handle_ = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle_) {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
      return ClassLoaderError::load_error;
    }
    #elif _WIN32
    handle_ = LoadLibrary(library_path_.c_str());
    if (handle_) {
      std::cerr << "Cannot load library: " << library_path_ << '\n';
    }
    #endif 
  }

  std::optional<ClassLoaderError> unloadLibrary()
  {
    #if defined(__linux__) || defined(__APPLE__)
    if(dlclose(handle_) != 0)
    {
      std::cerr << "An error occured closing a library: " << dlerror() << '\n';
      return ClassLoaderError::unload_error;
    }
    #elif _WIN32
    if (FreeLibrary(handle_) == 0) 
    {
      std::cerr << "Can't close " << library_path_ << std::endl;
    }
    #endif   
  }

  std::expected<std::unique_ptr<Base>, ClassLoaderError> GetInstance()
  {
    // function pointer types
    #if defined(__linux__) || defined(__APPLE__)

    std::function<Base *()> createFunc = dlsym(handle_, create_symbol_.c_str());
    if (createFunc == nullptr) {
      std::cerr << dlerror() << std::endl;
      return ClassLoaderError::invalid_symbol;
    }
    std::function<void(Base *)> destroyFunc = dlsym(handle_, destroy_symbol_.c_str());
    if (destroyFunc == nullptr) {
      std::cerr << dlerror() << std::endl;
      return ClassLoaderError::invalid_symbol;
    }
    #elif _WIN32
    
    auto createFunc = reinterpret_cast<createClass>(
      GetProcAddress(handle_, DEFAULT_ALLOC_CLASS_SYMBOL));
    auto destroyFunc = reinterpret_cast<destroyClass>(
      GetProcAddress(handle_, DEFAULT_DELETER_CLASS_SYMBOL));

    if (!createFunc || !destroyFunc) {
      std::cerr << "Can't find create or destroy symbol in " << _pathToLib << std::endl;
      unloadLibrary(); 
    }
    #endif

    return std::unique_ptr<Base>(
        createFunc(),
        [destroyFunc](Base *p){ destroyFunc(p); });
  }

private:
  HandleType handle_;
  std::string library_path_;
  std::string create_symbol_;
  std::string destroy_symbol_;
};
