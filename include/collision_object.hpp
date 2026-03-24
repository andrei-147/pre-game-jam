#pragma once

#include "transform_object.hpp"
namespace core {

class CollisionObject : TransformObject {

public:
    using TransformObject::TransformObject;

    /// \brief Method that checks if this object collides with the given object
    /// \param object The object for which the collision is checked
    void collides_with(const CollisionObject &object);
};

}
