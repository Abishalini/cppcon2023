#pragma once

#include <memory>

class ClassLoader
{
public:
  template<class Base>
  std::unique_ptr<Base> createUniqueInstance(const std::string derived_class_name)
  {
    // Check if class is loaded, else call loadLibrary

    // Get Derived type using the derived class name
    return std::make_unique<Derived>();
  }

  // Input parameter - fully qualified path to the runtime library
  void loadLibrary(const std::string& library_path)
  {
    if #unix
    void* handle = dlopen(library_path);

    if #windows
    

  }

  // Input parameter - fully qualified path to the runtime library
  void unloadLibrary(const std::string& library_path)
  {

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

}
