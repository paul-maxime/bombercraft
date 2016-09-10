#include <Clock.hh>
#include "ABonus.hpp"

ABonus::ABonus(Map *map, int posX, int posY, float size,
	       GeometricManager::Name geometric,
	       TextureManager::TextureName texture)
  : AEntity(map, posX, posY, size, AEntity::BONUS),
    m_geometric(geometric), m_texture(texture), m_height(1.0f), m_speed(1)
{
  m_totalTime = 0;
  _isCollidable = false;
  _isUpdatable = true;

  m_scale = glm::vec3(0.5f, 0.5f, 0.5f);
  setScale(m_scale);
}

ABonus::~ABonus()
{
}

void	ABonus::update(gdl::Clock const &clock)
{
  m_height += clock.getElapsed() * m_speed;
  m_totalTime += clock.getElapsed();
  if (m_height < 0.0f)
    m_speed = 1;
  else if (m_height > 1.5f)
    m_speed = -1;

  setTranslation(glm::vec3(_posX, m_height, _posY));
  rotate(glm::vec3(0.0f, 1.0f, 0.0f), clock.getElapsed() * 100.0f);
  float currentScale = std::abs(0.3 * std::cos(m_totalTime));
  setScale(m_scale + glm::vec3(currentScale, currentScale, currentScale));
}

void	ABonus::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _textureManager->bind(m_texture);
  GeometricManager::getInstance()->draw(m_geometric, shader, getTransformation());
}

void		ABonus::serialize(std::ostream& out) const
{
  AEntity::serialize(out);
  SeriBonus	seri;

  seri.height = m_height;
  seri.speed = m_speed;
  seri.totalTime = m_totalTime;
  writeInFile<SeriBonus>(seri, out);
  serializeVec3(m_scale, out);
}

void		ABonus::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  SeriBonus	seri;

  readFromFile<SeriBonus>(seri, in);
  m_height = seri.height;
  m_speed = seri.speed;
  m_totalTime = seri.totalTime;
  unserializeVec3(m_scale, in);
}
