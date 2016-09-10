#include "Plane.hpp"

Plane::Plane(int x, int y)
  : _width(x), _height(y)
{
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(x, 0, 0));
  _geometry.pushVertex(glm::vec3(x, 0, y));
  _geometry.pushVertex(glm::vec3(0, 0, y));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(x, 0.0f));
  _geometry.pushUv(glm::vec2(x, y));
  _geometry.pushUv(glm::vec2(0.0f, y));

  _geometry.build();
}

Plane::~Plane()
{
}

int Plane::getWidth() const
{
  return (_width);
}

int Plane::getHeight() const
{
  return (_height);
}
