#include <glm/gtc/matrix_transform.hpp>
#include "AObject.hpp"

AObject::AObject() :
  _position(0, 0, 0),
  _rotation(0, 0, 0),
  _scale(1, 1, 1),
  _center(0, 0, 0)
{
}

AObject::~AObject()
{
}

void AObject::update(gdl::Clock const&)
{
}

void AObject::reset()
{
  _position = glm::vec3(0, 0, 0);
  _rotation = glm::vec3(0, 0, 0);
  _scale = glm::vec3(1, 1, 1);
}

void AObject::setTranslation(glm::vec3 const& v)
{
  _position = v;
}

void AObject::setRotation(glm::vec3 const& v)
{
  _rotation = v;
}

void AObject::setScale(glm::vec3 const& v)
{
  _scale = v;
}

void AObject::setCenter(glm::vec3 const& v)
{
  _center = v;
}

void AObject::translate(glm::vec3 const& v)
{
  _position += v;
}

void AObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

void AObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

void AObject::addScale(glm::vec3 const& scale)
{
  _scale += scale;
}

glm::mat4 AObject::getTransformation() const
{
  glm::mat4 transform(1);

  // Translation
  transform = glm::translate(transform, _position);

  // Scaling
  transform = glm::scale(transform, _scale);

  // Rotation
  transform = glm::translate(transform, _center);

  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

  transform = glm::translate(transform, -_center);

  return (transform);
}

const glm::vec3& AObject::getPosition() const
{
  return (_position);
};

void	AObject::serialize(std::ostream& out) const
{
  serializeVec3(_position, out);
  serializeVec3(_rotation, out);
  serializeVec3(_scale, out);
  serializeVec3(_center, out);
}

void	AObject::unserialize(std::istream& in)
{
  unserializeVec3(_position, in);
  unserializeVec3(_rotation, in);
  unserializeVec3(_scale, in);
  unserializeVec3(_center, in);
}
