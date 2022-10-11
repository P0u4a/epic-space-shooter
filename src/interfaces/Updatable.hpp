#ifndef SRC_INTERFACES_UPDATABLE_HPP
#define SRC_INTERFACES_UPDATABLE_HPP

class Updatable
{
  public:
    virtual ~Updatable() = default;

    virtual void update(float delta_time) = 0;
};

#endif // SRC_INTERFACES_UPDATABLE_HPP
