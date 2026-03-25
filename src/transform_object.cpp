#include "transform_object.hpp"
#include "utils.hpp"


void core::TransformObject::setOffset(SDL_FPoint offset) { this->offset = offset; }
[[nodiscard]] SDL_FPoint core::TransformObject::getOffset() const { return offset; }

void core::TransformObject::setRotation(float theta) { this->theta = theta; }
[[nodiscard]] float core::TransformObject::getRotation() const { return theta; }

void core::TransformObject::setScaling(SDL_FPoint scaling) {this->scaling = scaling; }
[[nodiscard]] SDL_FPoint core::TransformObject::getScaling() const { return scaling; }

[[nodiscard]] SDL_FPoint core::TransformObject::transform(SDL_FPoint p) {
    return utils::translate(utils::rotate(utils::scale(p, scaling), theta), offset);
}
