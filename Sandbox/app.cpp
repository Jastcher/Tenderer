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

    if (app.PollKey() == 'q')
      break;

    for (uint y = 0; y < app.Height(); y++) {
      for (uint x = 0; x < app.Width(); x++) {
        app.Point(x, y,
                  {static_cast<unsigned char>(x / (float)app.Width() * 255.0f),
                   static_cast<unsigned char>(y / (float)app.Height() * 255.0f),
                   static_cast<unsigned char>(std::abs(std::sin(it / 100.0f)) *
                                              255.0f)});
      }
    }
    app.RenderScreen();

    std::cout << fps;
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    it++;
  }
  return 0;
}
