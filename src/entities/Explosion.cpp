#include <SdlContext.hh>

#include "Map.hpp"
#include "TextureManager.hpp"
#include "GeometricManager.hpp"
#include "AudioManager.hpp"

#include "Explosion.hpp"

Explosion::Explosion(Map *map, int posX, int posY) : AEntity(map, posX, posY, 1, AEntity::EXPLOSION)
{
  _isCollidable = false;
  _isUpdatable = true;
  m_step = 0.0f;
  translate(glm::vec3(posX, 0, posY));
  AudioManager::getInstance()->playSound(AudioManager::EXPLOSION);
}

Explosion::~Explosion()
{
}

void	Explosion::damage() const
{
  std::list<AEntity*> tab;
  _map->getProxyEntities(tab, _posX, _posY, true);
  for (std::list<AEntity*>::iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it)->getType() == AEntity::PLAYER && collideWith((*it)))
	(*it)->destroy();
    }
}

void	Explosion::update(gdl::Clock const &clock)
{
  damage();
  m_step += clock.getElapsed() * 1000.0f;
  if (m_step >= 500.0f)
    this->kill();
}

void	Explosion::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _textureManager->bind(TextureManager::EXPLOSION);
  GeometricManager::getInstance()->draw(GeometricManager::CUBE, shader, getTransformation());
}

void	Explosion::serialize(std::ostream& out) const
{
  AEntity::serialize(out);
  writeInFile<float>(m_step, out);
}

void	Explosion::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  readFromFile<float>(m_step, in);
}
