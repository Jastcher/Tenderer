#include "Application.h"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <format>
#include <glm/gtx/transform.hpp>
#include <string>
#include <threads.h>

int main() {

  Tenderer::Application app;

  // Object cube = Object(Mesh::CreateCube());
  // Object monkey = Object(Mesh::LoadObj("monkey.obj")) ;
  //
  // Scene scene1;
  // scene1.camera.projection = Camera::Projection::perspective
  // scene1.camera.fov = 90.0f
  //
  // scene1.Add(cube);
  // cube.position.x += 1;
  //
  // scene1.Render();
  //
  app.limitFps = true;
  app.maxFps = 30;

  unsigned int it = 0;
  float aspect = (float)app.Width() / (float)app.Height();
  while (1) {

    if (app.PollKey() == 'q')
      break;

    app.renderer->Fill({0, 0, 0});

#if 0
    for (uint y = 0; y < app.Height(); y++) {
      for (uint x = 0; x < app.Width(); x++) {
        app.renderer->Point(
            x, y,
            {static_cast<unsigned char>(x / (float)app.Width() * 255.0f),
             static_cast<unsigned char>(y / (float)app.Height() * 255.0f),
             static_cast<unsigned char>(std::abs(std::sin(it / 50.0f)) *
                                        255.0f)});
      }
    }
#endif

#if 0
    for (uint y = 0; y < app.Height(); y++) {
      for (uint x = 0; x < app.Width(); x++) {
        if ((x + y) % 2 == 0)
          app.renderer->Point(x, y, {1, 1, 1});
        else
          app.renderer->Point(x, y, {255, 255, 255});
      }
    }
#endif

    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians((float)it),
                                glm::vec3(1, 0, 1));

    // app.wRenderer->Line(rot, glm::vec2(-0.2, -0.2), glm::vec2(0.2, 0.2),
    //{255, 0, 0}, {0, 0, 255});

    // app.wRenderer->Triangle(rot, {-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5},
    //                         {255, 0, 0}, {0, 255, 0}, {0, 0, 255});

    app.wRenderer->Square(rot, {-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0.5, 0.5, 0},
                          {-0.5, 0.5, 0}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255},
                          {255, 255, 0});
    // app.renderer->Line(15, 15, 60, 34, {255, 1, 128}, {0, 255, 255});
    // app.renderer->Line(60, 34, 30, 30, {255, 255, 1}, {0, 0, 255});
    // app.renderer->Line(30, 30, 15, 15, {255, 1, 255}, {0, 255, 0});

    // app.renderer->Triangle(15, 15, 60, 34, 30, 30, {255, 0, 0}, {0, 255, 0},
    //{0, 0, 255});

    // app.renderer->Text(15, 15, "15;15", {0, 0, 0});
    // app.renderer->Text(60, 34, "60;34", {0, 0, 0});
    // app.renderer->Text(30, 30, "30;30", {0, 0, 0});

    if (it % 20 == 0)
      app.renderer->Text(10, 10, std::format("FPS: {:.2f}", app.fps).c_str(),
                         {255, 0, 0});

    app.RenderScreen();

    it++;
  }
  return 0;
}
