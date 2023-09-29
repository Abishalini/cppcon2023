#pragma once
#include <string>

class SharedLibrary
{
public:

SharedLibrary(const std::string& library_path)
{
  library_path_ = library_path;
}

void load_library()
{
  if #unix
    handle_ = dlopen(library_path_, RTLD_LAZY);

  if #windows
    handle_ = LoadLibrary(TEXT(library_path_));
}

void unload_library()
{
  if #unix
    dlclose(library_path_);

  if #windows
    FreeLibrary((HMODULE)library_path_);
}

void* SharedLibrary::find_symbol(const std::string& symbol_name)
{
  if #unix
    return dlsym(handle_, name.c_str());

  if #windows
    return (void*)(GetProcAddress)((HMMODULE)hnadle_, symbole_name.c_str());
} 
  
private:
  std::string library_path_;
  void* handle_;
};
