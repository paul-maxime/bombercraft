#include <stdexcept>
#include <map>
#include "ObstacleMap.hpp"
#include "Map.hpp"
#include "Bomb.hpp"

ObstacleMap::ObstacleMap(const Map* map, int centerX, int centerY, int depth)
  : m_map(map),
    m_centerX(centerX),
    m_centerY(centerY),
    m_width(map->getWidth()),
    m_height(map->getHeight()),
    m_depth(depth)
{
  m_obstacles.resize(depth * depth * 4);
  generate();
}

ObstacleMap::~ObstacleMap()
{
}

void ObstacleMap::set(int x, int y, int type)
{
  if (x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
      int lx = x - m_centerX + m_depth;
      int ly = y - m_centerY + m_depth;
      if (lx >= 0 && ly >= 0 && lx < m_depth * 2 && ly < m_depth * 2)
	m_obstacles[lx + ly * m_depth * 2] |= type;
    }
}

int ObstacleMap::get(int x, int y) const
{
  if (x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
      int lx = x - m_centerX + m_depth;
      int ly = y - m_centerY + m_depth;
      if (lx >= 0 && ly >= 0 && lx < m_depth * 2 && ly < m_depth * 2)
	return m_obstacles[lx + ly * m_depth * 2];
    }
  return 0;
}

bool ObstacleMap::isDangerAt(int x, int y) const
{
  for (int ix = x - 2; ix <= x + 2; ++ix)
    for (int iy = y - 2; iy <= y + 2; ++iy)
      if (get(ix, iy) & FUTURE)
	return true;
  return false;
}

bool ObstacleMap::isInMinimap(int x, int y) const
{
  int lx = x - m_centerX + m_depth;
  int ly = y - m_centerY + m_depth;
  if (x >= 0 && y >= 0 && x < m_width && y < m_height &&
      lx >= 0 && ly >= 0 && lx < m_depth * 2 && ly < m_depth * 2)
    return true;
  return false;
}

void ObstacleMap::generate()
{
  for (int x = m_centerX - m_depth; x < m_centerX + m_depth; ++x)
    for (int y = m_centerY - m_depth; y < m_centerY + m_depth; ++y)
      if (x >= 0 && y >= 0 && x < m_width && y < m_height)
	generateAt(x, y);
}

void ObstacleMap::generateAt(int x, int y)
{
  const std::list<AEntity *>* cell = m_map->getEntitysAt(x, y);
  std::list<AEntity *>::const_iterator it;
  for (it = cell->begin(); it != cell->end(); ++it)
    generateEntityAt(x, y, *it);
}

void ObstacleMap::generateEntityAt(int x, int y, const AEntity* entity)
{
  std::map<AEntity::Type, void (ObstacleMap::*)(int, int, const AEntity*)> fcts;
  std::map<AEntity::Type, void (ObstacleMap::*)(int, int, const AEntity*)>::iterator it;

  fcts[AEntity::BOX] = &ObstacleMap::generateSolidAt;
  fcts[AEntity::WALL] = &ObstacleMap::generateSolidAt;
  fcts[AEntity::SOLID_WALL] = &ObstacleMap::generateSolidAt;
  fcts[AEntity::EXPLOSION] = &ObstacleMap::generateExplosionAt;
  fcts[AEntity::BOMB] = &ObstacleMap::generateBombAt;

  it = fcts.find(entity->getType());
  if (it != fcts.end())
    (this->*(it->second))(x, y, entity);
}

void ObstacleMap::generateSolidAt(int x, int y, const AEntity*)
{
  set(x, y, SOLID);
}

void ObstacleMap::generateExplosionAt(int x, int y, const AEntity*)
{
  set(x, y, EXPLOSION);
}

void ObstacleMap::generateBombAt(int x, int y, const AEntity* entity)
{
  const Bomb* bomb = dynamic_cast<const Bomb*>(entity);
  if (!bomb)
    throw std::runtime_error("A bomb is not a bomb, wtf?");
  set(x, y, SOLID);
  int size = bomb->getExplodeSize();
  for (int x2 = x - size; x2 <= x + size; ++x2)
    if (x2 >= 0 && x2 < m_width)
      set(x2, y, FUTURE);
  for (int y2 = y - size; y2 <= y + size; ++y2)
    if (y2 >= 0 && y2 < m_height)
      set(x, y2, FUTURE);
}
