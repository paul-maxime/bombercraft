#include "Cube.hpp"

Cube::Cube(float size) : _size(size / 2)
{
  _geometry.pushVertex(glm::vec3(-_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(_size, _size, _size));
  _geometry.pushVertex(glm::vec3(-_size, _size, _size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-_size, -_size, -_size));
  _geometry.pushVertex(glm::vec3(_size, -_size, -_size));
  _geometry.pushVertex(glm::vec3(_size, _size, -_size));
  _geometry.pushVertex(glm::vec3(-_size, _size, -_size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_size, -_size, -_size));
  _geometry.pushVertex(glm::vec3(_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(_size, _size, _size));
  _geometry.pushVertex(glm::vec3(_size, _size, -_size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-_size, -_size, -_size));
  _geometry.pushVertex(glm::vec3(-_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(-_size, _size, _size));
  _geometry.pushVertex(glm::vec3(-_size, _size, -_size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-_size, _size, _size));
  _geometry.pushVertex(glm::vec3(_size, _size, _size));
  _geometry.pushVertex(glm::vec3(_size, _size, -_size));
  _geometry.pushVertex(glm::vec3(-_size, _size, -_size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(_size, -_size, _size));
  _geometry.pushVertex(glm::vec3(_size, -_size, -_size));
  _geometry.pushVertex(glm::vec3(-_size, -_size, -_size));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
}

Cube::~Cube()
{
}

float Cube::getSize() const
{
  return (_size);
}
