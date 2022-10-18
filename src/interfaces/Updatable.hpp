#ifndef SRC_INTERFACES_UPDATABLE_HPP
#define SRC_INTERFACES_UPDATABLE_HPP

class Updatable
{
  public:
    virtual ~Updatable() = default;

    /**
     * @brief Pure virtual function for updating classes derived from updatable
     *
     * @param delta_time the time since the previous frame of the game loop, used for frame independent motion
     */
    virtual void update(float delta_time) = 0;
};

#endif // SRC_INTERFACES_UPDATABLE_HPP
