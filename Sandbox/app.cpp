#include "Application.h"
#include "Buffer.h"
#include "Camera.h"
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
  scene1.camera.aspect = (float)app.Width() / app.Height();
  scene1.camera.projectionType = Tenderer::Projection::PERSPECTIVE;
  scene1.camera.position.x = 9.6f;
  scene1.camera.position.z = -10.0f;
  scene1.camera.orthoZoom = 8.0f;

  std::shared_ptr<Tenderer::Object> cube =
      std::make_shared<Tenderer::Object>(Tenderer::Mesh::CreateCube());

  std::shared_ptr<Tenderer::Object> points =
      std::make_shared<Tenderer::Object>(Tenderer::Mesh::CreateCube());
  points->mesh.renderType = Tenderer::RenderType::POINTS;

  points->mesh.colors = {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0},
                         {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}};

  // scene1.AddObject(points);
  // scene1.AddObject(cube);
  //
  std::shared_ptr<Tenderer::Object> cow = std::make_shared<Tenderer::Object>(
      Tenderer::Mesh::LoadObj("../Sandbox/assets/cow.obj"));
  std::shared_ptr<Tenderer::Object> teapot = std::make_shared<Tenderer::Object>(
      Tenderer::Mesh::LoadObj("../Sandbox/assets/teapot.obj"));
  // std::shared_ptr<Tenderer::Object> pumpkin =
  //     std::make_shared<Tenderer::Object>(
  //         Tenderer::Mesh::LoadObj("../Sandbox/assets/pumpkin.obj"));
  // pumpkin->transform.scale = glm::vec3(0.2f);
  std::shared_ptr<Tenderer::Object> teddy = std::make_shared<Tenderer::Object>(
      Tenderer::Mesh::LoadObj("../Sandbox/assets/teddy.obj"));
  teddy->transform.scale = glm::vec3(0.2f);
  scene1.AddObject(cow);
  scene1.AddObject(teapot);
  // scene1.AddObject(pumpkin);
  scene1.AddObject(teddy);

  int i = 0;
  for (auto &object : scene1.objects) {
    object->transform.position = glm::vec3(i * 10.0f, 0, 0);
    i++;
  }

  app.limitFps = false;
  app.maxFps = 60;

  unsigned int it = 0;
  bool running = true;
  while (running) {
    app.PollKey();

    app.renderer->Fill({0, 0, 0});
    // scene1.camera.Input(key);
    if (app.keyMap['q']) {

      running = false;
      break;
    }
    if (app.keyMap['c']) {

      for (auto &object : scene1.objects) {
        if (object->mesh.renderType == Tenderer::RenderType::TRIANGLES)
          object->mesh.renderType = Tenderer::RenderType::POINTS;
        else
          object->mesh.renderType = Tenderer::RenderType::TRIANGLES;
      }
    }

    if (app.keyMap['+']) {
      scene1.camera.fov -= 10.0f;
    }
    if (app.keyMap['-']) {
      scene1.camera.fov += 10.0f;
    }
    scene1.camera.Input(app.keyMap);

    if (it % 20 == 0) {

      app.renderer->Text(10, 10, std::format("FPS: {:.2f}", app.fps).c_str(),
                         {100, 0, 0});
    }

    app.renderer->Text(10, 20,
                       std::format("Position: {:.2f}, {:.2f}, {:.2f}",
                                   scene1.camera.position.x,
                                   scene1.camera.position.y,
                                   scene1.camera.position.z)
                           .c_str(),
                       {20, 20, 20});
    app.renderer->Text(10, 22,
                       std::format("Orientation: {:.2f}, {:.2f}, {:.2f}",
                                   scene1.camera.forward.x,
                                   scene1.camera.forward.y,
                                   scene1.camera.forward.z)
                           .c_str(),
                       {20, 20, 20});
    int vertices = 0;
    for (auto &object : scene1.objects) {
      vertices += object->mesh.vertices.size();
    }
    app.renderer->Text(10, 24,
                       std::format("Vertices: {}", vertices

                                   )
                           .c_str(),
                       {20, 20, 20});
    for (auto &object : scene1.objects) {
      object->transform.rotation = glm::vec3(it, 0, it);
      // object->transform.scale *= 1.001;
    }

    app.RenderScene(scene1);

    it++;
  }
  return 0;
}
