#include "Buffer.h"
#include <algorithm>
#include <stdexcept>
namespace Tenderer {

Buffer::Buffer(size_t _width, size_t _height)
    : size(_width * _height), width(_width), height(_height),
      data(std::make_unique<Color[]>(size)) {}

Buffer::~Buffer() {}

Color &Buffer::operator[](size_t index) const {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

void Buffer::Resize(size_t _width, size_t _height) {
  width = _width;
  height = _height;
  size_t newSize = width * height;

  std::unique_ptr<Color[]> newArray = std::make_unique<Color[]>(newSize);

  for (size_t i = 0; i < std::min(size, newSize); ++i) {
    newArray[i] = std::move(data[i]);
  }

  size = newSize;
  data = std::move(newArray);
}

size_t Buffer::Size() const { return size; }
size_t Buffer::Width() const { return width; }
size_t Buffer::Height() const { return height; }

Color &Buffer::Get(size_t x, size_t y) { return data[y * width + x]; }

} // namespace Tenderer
