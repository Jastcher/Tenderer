#pragma once
#include "Object.h"

#include <memory>
#include <vector>
namespace Tenderer {

class Scene {
public:
  Scene();
  ~Scene();

  void AddObject(std::shared_ptr<Object> object);
  void Render();

  std::vector<std::shared_ptr<Object>> objects;
  // Camera camera;
};

} // namespace Tenderer
