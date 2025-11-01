#include "Application.h"
#include <chrono>
#include <cmath>
#include <ratio>
#include <string>
#include <thread>
#include <threads.h>

int main() {

  Tenderer::Application app;

  app.Fill({0, 255, 0});

  // update time
  double crntTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
  double prevTime = 0;
  double dt, fps;

  unsigned int it = 0;
  while (1) {
    crntTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
    dt = crntTime - prevTime;
    dt /= 1000;
    fps = 1 / dt;
    prevTime = crntTime;

    app.SetTitle(std::to_string(fps));

    // app.Fill({255, 255, 255});

    if (app.PollKey() == 'q')
      break;

    // for (uint y = 0; y < app.Height(); y++) {
    //   for (uint x = 0; x < app.Width(); x++) {
    //     app.Point(x, y,
    //               {static_cast<unsigned char>(x / (float)app.Width() *
    //               255.0f),
    //                static_cast<unsigned char>(y / (float)app.Height() *
    //                255.0f), static_cast<unsigned char>(std::abs(std::sin(it /
    //                400.0f)) *
    //                                           255.0f)});
    //   }
    // }
    //
    for (uint y = 0; y < app.Height(); y++) {
      for (uint x = 0; x < app.Width(); x++) {
        if ((x + y) % 2 == 0)
          app.Point(x, y, {1, 1, 1});
        else
          app.Point(x, y, {255, 255, 255});
      }
    }
    app.Text(10, 10, ("FPS: " + std::to_string(fps)).c_str(), {0, 0, 0});

    app.RenderScreen();

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    it++;
  }
  return 0;
}
