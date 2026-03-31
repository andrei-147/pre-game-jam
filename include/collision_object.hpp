#pragma once

#include "transform_object.hpp"
namespace core {

class CollisionObject : public TransformObject {
private:
	SDL_FPoint projection(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c);

public:
	using TransformObject::TransformObject;

	/// \brief Method that checks if this object collides with the given object
	/// \param object The object for which the collision is checked
	/// \return Returns true if collides with given object, otherwise returns false
	bool collides_with(const CollisionObject &object);
};

}
