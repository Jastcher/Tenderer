#pragma once

#include <cstddef>
#include <memory>
#include <sys/types.h>

namespace Tenderer
{

template<typename T> class Buffer
{
  public:
	Buffer(size_t width, size_t height);
	~Buffer();

	void Resize(size_t width, size_t height);

	size_t Size() const;
	size_t Width() const;
	size_t Height() const;

	T& Get(size_t x, size_t y);
	T& operator[](size_t index) const;
 
  void operator=(const Buffer& other) {
    for (size_t i = 0; i < size; i++) {
      data[i] = other[i];
    }
  }

  private:
	size_t size;
	size_t width;
	size_t height;
	std::unique_ptr<T> data;
};
} // namespace Tenderer
