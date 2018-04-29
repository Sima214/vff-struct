#ifndef DISPATCH_ICMD_HPP
#define DISPATCH_ICMD_HPP

namespace dispatch {
/*
 * Interface which accepts the commands.
 */
class ICommandable {
  public:
    virtual ~ICommandable() {};
};
}
#endif /*DISPATCH_ICMD_HPP*/