#pragma once

#include <string_view>

namespace core{

enum class ErrorCode{
  load_error,
  unload_error,
  invalid_symbol,
  loader_in_use_error
};

static const std::string_view error_message(ErrorCode error_code){
  switch(error_code){
  case ErrorCode::load_error:
    return "Plugin failed to load";

  case ErrorCode::unload_error:
    return "Plugin failed to unload";

  case ErrorCode::invalid_symbol:
    return "Symbol not found";

  case ErrorCode::loader_in_use_error:
    return "Cannot load plugin. A plugin is currently in use.";

  default:
    return "Undefined Error";
  }
}
}
