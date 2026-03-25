#include "physics_object.hpp"


void core::PhysicsObject::setVelocity(SDL_FPoint velocity) { this->velocity = velocity; }
[[nodiscard]] SDL_FPoint core::PhysicsObject::getVelocity() const { return velocity; }

void core::PhysicsObject::setAcceleration(SDL_FPoint accel) { this->acceleration = accel; }
[[nodiscard]] SDL_FPoint core::PhysicsObject::getAcceleration() const { return acceleration; }

void core::PhysicsObject::update() {
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    offset.x += velocity.x;
    offset.y += velocity.y;
}
