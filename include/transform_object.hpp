#pragma once

#include "object.hpp"

namespace core {

class TransformObject : Object {

protected:
    SDL_FPoint offset = {0.0f, 0.0f};
    SDL_FPoint scaling = {0.0f, 0.0f};
    float theta = 0.0f;

public:
    using Object::Object;

    /// \brief Sets the offset of the object
    /// \param off The distance to offset the object from the center of the screen
    void setOffset(SDL_FPoint offset);
    /// \brief Gets the offset of the object
    /// \return An SDL_FPoint representing the offset on the x and y axis of the object
    [[nodiscard]] SDL_FPoint getOffset() const;

    /// \brief Sets the rotation of the object
    /// \param theta The angle in radians at which the object is rotated
    void setRotation(float theta);
    /// \brief Gets the rotation of the object
    /// \return The angle in radians at which the object is rotated
    [[nodiscard]] float getRotation() const;

    /// \brief Sets the scaling of the object
    /// \param theta An SDL_FPoint representing the scaling on the x and y axis of the object
    void setScaling(SDL_FPoint scaling);
    /// \brief Gets the scaling of the object
    /// \return An SDL_FPoint representing the scaling on the x and y axis of the object
    [[nodiscard]] SDL_FPoint getScaling() const;
};

}
