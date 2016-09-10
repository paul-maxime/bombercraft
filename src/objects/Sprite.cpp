#include "Sprite.hpp"

Sprite::Sprite() :
  m_repeat(false)
{
}

Sprite::Sprite(TextureManager::TextureName texture)
{
  init(texture);
}

Sprite::Sprite(TextureManager::TextureName texture,
	       const glm::vec2& size)
{
  init(texture, size);
}

Sprite::Sprite(TextureManager::TextureName texture,
	       const glm::vec2& size,
	       const glm::vec4& from)
{
  init(texture, size, from);
}

Sprite::~Sprite()
{
}

void Sprite::init(TextureManager::TextureName texture)
{
  glm::vec2 size;
  TextureManager::getInstance()->getSize(texture, size);
  init(texture, size, glm::vec4(0, 0, 1, 1));
}

void Sprite::init(TextureManager::TextureName texture,
		  const glm::vec2& size)
{
  glm::vec2 texsize;
  TextureManager::getInstance()->getSize(texture, texsize);
  glm::vec4 from(0, 0, size.x / texsize.x, size.y / texsize.y);
  init(texture, size, from);
  m_repeat = true;
}

void Sprite::init(TextureManager::TextureName texture,
		  const glm::vec2& size,
		  const glm::vec4& from)
{
  m_texture = texture;

  m_geometry.pushVertex(glm::vec3(0, 0, 0));
  m_geometry.pushVertex(glm::vec3(0, size.y, 0));
  m_geometry.pushVertex(glm::vec3(size.x, size.y, 0));
  m_geometry.pushVertex(glm::vec3(size.x, 0, 0));

  m_geometry.pushUv(glm::vec2(from[0], from[3]));
  m_geometry.pushUv(glm::vec2(from[0], from[1]));
  m_geometry.pushUv(glm::vec2(from[2], from[1]));
  m_geometry.pushUv(glm::vec2(from[2], from[3]));

  m_geometry.build();

  setCenter(glm::vec3(static_cast<float>(size.x) / 2.0f,
		      static_cast<float>(size.y) / 2.0f, 0));
}

void Sprite::resize(const glm::vec2& size)
{
  setScale(glm::vec3(1, 1, 1));

  glm::vec2 texsize;
  TextureManager::getInstance()->getSize(m_texture, texsize);
  scale(glm::vec3(size.x / texsize.x, size.y / texsize.y, 1));
}

void Sprite::resize(const glm::vec2& size, const glm::vec2& from)
{
  setScale(glm::vec3(1, 1, 1));

  scale(glm::vec3(size.x / from.x, size.y / from.y, 1));
}

void Sprite::draw(gdl::AShader& shader, gdl::Clock const&)
{
  TextureManager::getInstance()->bind(m_texture, m_repeat);
  m_geometry.draw(shader, getTransformation(), GL_QUADS);
}

void Sprite::drawCustom(gdl::AShader& shader, gdl::Clock const&)
{
  m_geometry.draw(shader, getTransformation(), GL_QUADS);
}

void Sprite::setRepeat(bool repeat)
{
  m_repeat = repeat;
}

void Sprite::setTexture(TextureManager::TextureName texture)
{
  m_texture = texture;
}
