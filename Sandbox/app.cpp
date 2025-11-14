#include "Application.h"
#include "Buffer.h"
#include "Mesh.h"
#include "Object.h"
#include "Scene.h"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <format>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <string>
#include <threads.h>

int main() {

  Tenderer::Application app;

  // Object cube = Object(Mesh::CreateCube()); ??

  Tenderer::Scene scene1;

  std::shared_ptr<Tenderer::Object> cube =
      std::make_shared<Tenderer::Object>(Tenderer::Mesh::CreateCube());

  std::shared_ptr<Tenderer::Object> points =
      std::make_shared<Tenderer::Object>(Tenderer::Mesh::CreateCube());
  points->mesh.renderType = Tenderer::RenderType::POINTS;

  points->mesh.colors = {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0},
                         {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}};

  scene1.AddObject(points);
  scene1.AddObject(cube);

  // Object monkey = Object(Mesh::LoadObj("monkey.obj")) ;
  //
  // scene1.camera.projection = Camera::Projection::Perspective
  // scene1.camera.fov = 90.0f
  //
  //
  //
  app.limitFps = true;
  app.maxFps = 30;
  app.wRenderer->wireframeMode = true;

  unsigned int it = 0;
  bool running = true;
  while (running) {

    app.renderer->Fill({0, 0, 0});

    switch (app.PollKey()) {
    case 'q':
      running = false;
      break;
    case 'w':
      app.wRenderer->wireframeMode = !app.wRenderer->wireframeMode;
      break;
    }

    if (it % 20 == 0) {

      app.renderer->Text(10, 10, std::format("FPS: {:.4f}", app.fps).c_str(),
                         {255, 0, 0});
    }

    for (auto &object : scene1.objects) {
      object->transform.rotation = glm::vec3(it, 0, it);
    }

    app.RenderScene(scene1);

    it++;
  }
  return 0;
}
