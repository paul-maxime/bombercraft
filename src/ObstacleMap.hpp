/**
 * \file ObstacleMap.hpp
 * Defines the ObstacleMap class.
 */

#ifndef OBSTACLE_MAP_HPP_
#define OBSTACLE_MAP_HPP_

#include <vector>

class Map;
class AEntity;
class Bomb;

/**
 * \class ObstacleMap
 * This class is only used by the AI.
 * It generates a little mini-map based on the real map.
 */
class ObstacleMap
{
public:
  /**
   * List of the mini-map elements.
   */
  enum Type
    {
      NONE = 0,		/**< Nothing. */
      SOLID = 1,	/**< A solid (non-walkable) block. */
      EXPLOSION = 2,	/**< An explosion still burning. */
      FUTURE = 4	/**< Some explosion will spawn here soon. */
    };

  /**
   * Main constructor. Creates a new mini-map around a location.
   * \param map Original and complete map.
   * \param centerX Location X point.
   * \param centerY Location Y point.
   * \param depth Squared-radius of the mini-map.
   */
  ObstacleMap(const Map* map, int centerX, int centerY, int depth);

  /**
   * Releases the ressources used by the map.
   */
  virtual ~ObstacleMap();

  /**
   * Returns an int indicating every objects at a position.
   * \return A composite of the Type enumeration.
   */
  int			get(int x, int y) const;

  /**
   * Checks the specified position for a future explosion.
   * \return true in case of danger.
   */
  bool			isDangerAt(int x, int y) const;

  /**
   * \return true if the location is within the generated minimap.
   */
  bool			isInMinimap(int x, int y) const;

private:
  void			set(int x, int y, int type);

  void			generate();
  void			generateAt(int x, int y);
  void			generateEntityAt(int x, int y, const AEntity* entity);

  void			generateSolidAt(int x, int y, const AEntity* entity);
  void			generateExplosionAt(int x, int y, const AEntity* entity);
  void			generateBombAt(int x, int y, const AEntity* entity);

  const Map*		m_map;
  std::vector<int>	m_obstacles;
  int			m_centerX;
  int			m_centerY;
  int			m_width;
  int			m_height;
  int			m_depth;
};

#endif
