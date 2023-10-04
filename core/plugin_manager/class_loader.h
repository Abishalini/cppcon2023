#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <expected>
#include <optional>
#include <system_error>
#include "plugin_manager_errors.h"

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
  ClassLoader(const std::string& create_symbol=DEFAULT_CREATE_CLASS_SYMBOL, 
              const std::string& destroy_symbol=DEFAULT_DESTROY_CLASS_SYMBOL)
  : handle_{nullptr}
  , create_symbol_(create_symbol)
  , destroy_symbol_(destroy_symbol)
  {}

  ~ClassLoader() = default;

  std::optional<core::ErrorCode> loadLibrary(const std::string& library_path)
  {
    #if defined(__linux__) || defined(__APPLE__)
    if(handle_ != nullptr){
      return core::ErrorCode::loader_in_use_error;
    }
    handle_ = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle_) {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
      return core::ErrorCode::load_error;
    }
    #elif _WIN32
    handle_ = LoadLibrary(library_path.c_str());
    if (handle_) {
      std::cerr << "Cannot load library: " << library_path << '\n';
      return core::ErrorCode::load_error;
    }
    #endif
    return std::nullopt;
  }

  std::optional<core::ErrorCode> unloadLibrary()
  {
    #if defined(__linux__) || defined(__APPLE__)
    if(dlclose(handle_) != 0)
    {
      std::cerr << "An error occured closing a library: " << dlerror() << '\n';
      return core::ErrorCode::unload_error;
    }
    #elif _WIN32
    if (FreeLibrary(handle_) == 0) 
    {
      return core::ErrorCode::unload_error;
    }
    #endif   
  }

  std::expected<std::shared_ptr<Base>, core::ErrorCode> GetInstance()
  {
    // function pointer types
    using createFuncType = Base*(*)();
    using destroyFuncType = void(*)(Base *);

    // function pointer types
    #if defined(__linux__) || defined(__APPLE__)

    std::function<Base*()> createFunc(
      reinterpret_cast<createFuncType>(dlsym(handle_, create_symbol_.c_str())));
    if (createFunc == nullptr) {
      std::cerr << dlerror() << std::endl;
      return std::unexpected(core::ErrorCode::invalid_symbol);
    }
    std::function<void(Base*)> destroyFunc(
      reinterpret_cast<destroyFuncType>(dlsym(handle_, destroy_symbol_.c_str())));
    if (destroyFunc == nullptr) {
      std::cerr << dlerror() << std::endl;
      return std::unexpected(core::ErrorCode::invalid_symbol);
    }
    #elif _WIN32
    
    auto createFunc = reinterpret_cast<createClass>(
      GetProcAddress(handle_, DEFAULT_ALLOC_CLASS_SYMBOL));
    auto destroyFunc = reinterpret_cast<destroyClass>(
      GetProcAddress(handle_, DEFAULT_DELETER_CLASS_SYMBOL));

    if (!createFunc || !destroyFunc) {
      std::cerr << "Can't find create or destroy symbol in " << _pathToLib << std::endl;
      unloadLibrary(); 
      return std::unexpected(core::ErrorCode::invalid_symbol);
      
    }
    #endif

    return std::shared_ptr<Base>(
        createFunc(), destroyFunc);
  }

private:
  HandleType handle_;
  std::string create_symbol_;
  std::string destroy_symbol_;
};
