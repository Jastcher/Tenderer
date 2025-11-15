#include "Scene.h"
#include "render/WRenderer.h"
#include <memory>

namespace Tenderer {

Scene::Scene() : camera() {}
Scene::~Scene() {}

void Scene::AddObject(std::shared_ptr<Object> object) {
  objects.push_back(object);
}

} // namespace Tenderer
