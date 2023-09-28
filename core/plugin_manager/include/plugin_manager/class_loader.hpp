#pragma once

#include <exception>
#include <memory>
#include <string>

namespace {
  constexpr auto DEFAULT_ALLOC_CLASS_SYMBOL{"allocator"};
  constexpr auto DEFAULT_DELETER_CLASS_SYMBOL{"deleter"};
}

namespace plugin_manager {

#if defined(__linux__) || defined(__APPLE__)
  using HandleType = void*;
#elif _WIN32
  using HandleType = HWMODULE;
#elif __APPLE__
  using HandleType = void*;
#endif

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
    handle_ = dlopen(library_path.c_str(), RTLD_LAZY);
    if (handle_) {
      cerr << "Cannot load library: " << dlerror() << '\n';
    }
    #elif _WIN32
    handle_ = LoadLibrary(library_path.c_str());
    if (handle_) {
      cerr << "Cannot load library: " << library_path_ << '\n';
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
    using allocClass = Base * (*)();
    using deleteClass = void (*)(Base *);
  
    #if defined(__linux__) || defined(__APPLE__)

    auto allocFunc = reinterpret_cast<allocClass>(
      dlsym(_handle, DEFAULT_ALLOC_CLASS_SYMBOL));
    auto deleteFunc = reinterpret_cast<deleteClass>(
      dlsym(_handle, DEFAULT_DELETER_CLASS_SYMBOL));
    if (!allocFunc || !deleteFunc) {
      std::cerr << dlerror() << std::endl;
      unloadLibrary();
    }
    #elif _WIN32
    
    auto allocFunc = reinterpret_cast<allocClass>(
      GetProcAddress(_handle, DEFAULT_ALLOC_CLASS_SYMBOL));
    auto deleteFunc = reinterpret_cast<deleteClass>(
      GetProcAddress(_handle, DEFAULT_DELETER_CLASS_SYMBOL));

    if (!allocFunc || !deleteFunc) {
      std::cerr << "Can't find allocator or deleter symbol in " << _pathToLib << std::endl;
      unloadLibrary(); 
    }
    #endif

    return std::shared_ptr<T>(
        allocFunc(),
        [deleteFunc](Base *p){ deleteFunc(p); });
  }

private:
  HandleType handle_;
  std::string library_path_;
};

}
