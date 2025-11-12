#include "Object.h"

namespace Tenderer {

Object::Object() {};
Object::Object(const Mesh &mesh)
    : transform({0, 0, 0},
                {
                    1,
                    1,
                    1,
                },
                {0, 0, 0}),
      mesh(mesh) {}

Object::~Object() {};

} // namespace Tenderer
