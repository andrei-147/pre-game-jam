#include "collision_object.hpp"
#include "constants.hpp"
#include <algorithm>
#include <cmath>

SDL_FPoint core::CollisionObject::projection(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float t = ((c.x - a.x) * dx - (c.y - a.y) * dy) / (dx * dx + dy * dy);
	return {a.x + t * dx, a.y + t * dy};
}

bool core::CollisionObject::collides_with(const core::CollisionObject &object) {
	std::vector<SDL_FPoint> this_transformed(this->vertex_count);
	std::vector<SDL_FPoint> object_transformed(object.vertex_count);
	
	for (size_t i = 0; i < this->vertex_count; ++i) this_transformed[i] = this->transform(this->vertices[i]);
	for (size_t i = 0; i < object.vertex_count; ++i) object_transformed[i] = object.transform(object.vertices[i]);

	auto get_perpendicular = [](SDL_FPoint a, SDL_FPoint b) -> SDL_FPoint {
		SDL_FPoint edge = { b.x - a.x, b.y - a.y };
		SDL_FPoint axis = { -edge.y, edge.x };
		float len = std::sqrt(axis.x*axis.x + axis.y*axis.y);
		if (len != 0) { axis.x /= len; axis.y /= len; }
		return axis;
	};

	auto project_onto_axis = [&](const std::vector<SDL_FPoint>& verts, SDL_FPoint axis_origin, SDL_FPoint axis_end, float& min, float& max) {
		SDL_FPoint proj = projection(axis_origin, axis_end, verts[0]);
		min = max = proj.x * axis_end.x + proj.y * axis_end.y;
		for (size_t i = 1; i < verts.size(); ++i) {
			proj = projection(axis_origin, axis_end, verts[i]);
			float value = proj.x * axis_end.x + proj.y * axis_end.y;
			if (value < min) min = value;
			if (value > max) max = value;
		}
	};

	auto check_axes = [&](const std::vector<SDL_FPoint>& vertsA, const std::vector<SDL_FPoint>& vertsB) {
		size_t n = vertsA.size();
		for (size_t i = 0; i < n; ++i) {
			SDL_FPoint a = vertsA[i];
			SDL_FPoint b = vertsA[(i + 1) % n];
			SDL_FPoint axis = get_perpendicular(a, b);

			SDL_FPoint axis_end = { a.x + axis.x, a.y + axis.y };

			float minA, maxA, minB, maxB;
			project_onto_axis(vertsA, a, axis_end, minA, maxA);
			project_onto_axis(vertsB, a, axis_end, minB, maxB);

			if (maxA < minB || maxB < minA) return false;
		}
		return true;
	};

	return check_axes(this_transformed, object_transformed) &&
		   check_axes(object_transformed, this_transformed);
}
