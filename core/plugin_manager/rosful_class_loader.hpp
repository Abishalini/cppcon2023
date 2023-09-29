#pragma once
#include <class_loader.h>

#pragma once

#include <exception>
#include <memory>

#if defined(__linux__) || defined(__APPLE__)
  using HandleType = void*;
#elif _WIN32
  using HandleType = HWMODULE;
#elif __APPLE__
  using HandleType = void*;
#endif

template<class Base>
class ROSfulClassLoader
{
public:
  std::unique_ptr<Base> createUniqueInstance(const std::string derived_class_name)
  {
    // Check if class is loaded, else call loadLibrary

    // Get Derived type using the derived class name
    // return std::make_unique<Base>();
  }

  // Input parameter - fully qualified path to the runtime library
  void loadLibrary(const std::string& library_path)
  {
    #if defined(__linux__) || defined(__APPLE__)
      handle_ = dlopen(library_path.c_str(), RTLD_LAZY);
      if (handle_) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
      }
    #elif _WIN32
      handle_ = LoadLibrary(library_path.c_str());
      if (handle_) {
        std::cerr << "Cannot load library: " << library_path << '\n';
      }
    #endif    
    
  }

  // Input parameter - fully qualified path to the runtime library
  void unloadLibrary(const std::string& library_path)
  {
    #if defined(__linux__) || defined(__APPLE__)
      if(dlclose(handle_) != 0)
      {
        std::cerr << "An error occured closing a library: " << dlerror() << '\n';
      }
    }
    #elif _WIN32
			if (FreeLibrary(handle_) == 0) 
      {
				std::cerr << "Can't close " << library_path << std::endl;
			}
    #elif __APPLE__

    #endif   
  }

  std::vector<std::string> getLibraryPath(const std::string& library_name, const std::string& package_name)
  {
    // In ROS world, the path is <path_to_workspace>/install/<package_name>/lib/<library_name>.so
  }

  template<typename Derived, typename Base>
  std::unique_ptr<MetaObject> registerPlugin(const std::string& class_name, const std::string& base_class_name)
  {
    // First Load Library

    std::unique_ptr<MetaObject<Derived, Base>> new_factor 
      = std::make_unique<MetaObject<Derived, Base>>(class_name, base_class_name);
  }

private:
  HandleType handle_;
};
