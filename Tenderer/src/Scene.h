#pragma once
#include "Camera.h"
#include "Object.h"

#include <memory>
#include <vector>
namespace Tenderer {

class Scene {
public:
  Scene();
  ~Scene();

  void AddObject(std::shared_ptr<Object> object);

  std::vector<std::shared_ptr<Object>> objects;
  Camera camera;
};

} // namespace Tenderer
