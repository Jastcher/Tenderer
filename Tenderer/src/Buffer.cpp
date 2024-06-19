#include "Buffer.h"
#include <algorithm>
#include <stdexcept>
namespace Tenderer
{

template<typename T> Buffer<T>::Buffer(size_t _width, size_t _height)
    : size(_width * _height), width(_width), height(_height), data(std::make_unique<T[]>(size))
{
}

template<class T> Buffer<T>::~Buffer()
{
}

template<class T> T& Buffer<T>::operator[](size_t index) const
{
	if(index >= size) { throw std::out_of_range("Index out of range"); }
	return data[index];
}

template<typename T> void Buffer<T>::Resize(size_t _width, size_t _height)
{
	width = _width;
	height = _height;
	size_t newSize = width * height;

	std::unique_ptr<T[]> newArray = std::make_unique<T[]>(newSize);

	for(size_t i = 0; i < std::min(size, newSize); ++i) { newArray[i] = std::move(data[i]); }

	size = newSize;
	data = std::move(newArray);
}

template<class T> size_t Buffer<T>::Size() const
{
	return size;
}
template<class T> size_t Buffer<T>::Width() const
{
	return width;
}
template<class T> size_t Buffer<T>::Height() const
{
	return height;
}

template<class T> T& Buffer<T>::Get(size_t x, size_t y)
{
	return data[y * width + x];
}

} // namespace Tenderer
