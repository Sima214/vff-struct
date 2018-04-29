#ifndef DUMMY_STRUCT_HPP
#define DUMMY_STRUCT_HPP

#include <dispatch/icommandable.hpp>

namespace structures {
class Dummy: public dispatch::ICommandable{
  public:
    ~Dummy() {};
};
}
#endif /*DUMMY_STRUCT_HPP*/