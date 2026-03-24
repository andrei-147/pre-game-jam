#pragma once

#include "collision_object.hpp"
namespace core {

class PhysicsObject : CollisionObject {

protected:
    SDL_FPoint velocity = {0.0f, 0.0f};
    SDL_FPoint acceleration = {0.0f, 0.0f};

public:

    /// \brief Sets the velocity of the object
    /// \param velocity The velocity on the x and y axis to set for the object
    void setVelocity(SDL_FPoint velocity);
    /// \brief Gets the velocity of the object
    /// \return Returns the velocity on the x and y axis of the object
    [[nodiscard]] SDL_FPoint getVelocity() const;

    /// \brief Sets the acceleration of the object
    /// \param accel The acceleration on the x and y axis to set for the object
    void setAcceleration(SDL_FPoint accel);
    /// \brief Gets the acceleration of the object
    /// \return Returns the acceleration on the x and y axis of the object
    [[nodiscard]] SDL_FPoint getAcceleration() const;

    /// \brief Updates the state of the physing object during one game tick
    void update();

};

}
