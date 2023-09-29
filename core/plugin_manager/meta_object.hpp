#pragma once

template<class Derived, class Base>
class MetaObject 
{
public:
  MetaObject(const std::string & class_name, const std::string & base_class_name)
  {}

  Base * create() const
  {
    return new Derived;
  }
};
