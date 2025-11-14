#include "Object.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

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

glm::mat4 Object::GetModel() const {
  glm::mat4 model =
      glm::translate(glm::mat4(1.0f), transform.position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x),
                  glm::vec3(1, 0, 0)) *
      glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y),
                  glm::vec3(0, 1, 0)) *
      glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z),
                  glm::vec3(0, 0, 1)) *
      glm::scale(glm::mat4(1.0f), transform.scale);

  return model;
}

} // namespace Tenderer
