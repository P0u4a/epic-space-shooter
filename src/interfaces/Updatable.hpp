#ifndef SRC_INTERFACES_UPDATEABLE_HPP
#define SRC_INTERFACES_UPDATEABLE_HPP

class Updatable {
  public:
    Updatable();
    Updatable(const Updatable &) = delete;
    Updatable(Updatable &&) = default;
    Updatable &operator=(const Updatable &) = delete;
    Updatable &operator=(Updatable &&) = default;
    virtual void update() = 0;
    virtual ~Updatable() = default;
};

#endif // SRC_INTERFACES_UPDATEABLE_HPP
