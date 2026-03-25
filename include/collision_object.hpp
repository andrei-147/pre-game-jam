#pragma once

#include "transform_object.hpp"
namespace core {

class CollisionObject : public TransformObject {

public:
    using TransformObject::TransformObject;

    /// \brief Method that checks if this object collides with the given object
    /// \param object The object for which the collision is checked
    /// \return Returns true if collides with given object, otherwise returns false
    bool collides_with(const CollisionObject &object);
};

}
