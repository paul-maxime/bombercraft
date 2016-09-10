/*
 * \file Map.hpp
 * Defines the Map class.
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <list>
#include <string>

#include "GameEngine.hpp"
#include "ASerializable.hpp"
#include "Player.hpp"

namespace gdl
{
  class AShader;
}

namespace math
{
  const double	PI = 3.14159265359;
}

class AEntity;

/**
 * \class Map
 * A container for all the entities to draw and update
 * Inherits from ASerializable
 */
class Map : public ASerializable
{
public:
  /**
   * \class Pos
   * Containing positions in int
   */
  class Pos
  {
  public:
    int		x;
    int		y;
  };

private:
  class SeriMap
  {
  public:
    unsigned int nbEntities;
    unsigned int nbAvailablePlayerPos;
    unsigned int nbToUpdate;
    unsigned int nbPlayers;
    unsigned int nbIAplayers;
    int solidWallPairPercent;
    Map::Pos mapSize;
  };

private:
  std::vector<Map::Pos *>				_availablePlayerPos;
  std::vector<AEntity *>				_entityTrash;
  std::vector<std::vector<std::list<AEntity *> *> *>	_mapData;
  std::vector<AEntity*>					_toUpdate;
  std::vector<AEntity*>					_addToUpdate;
  std::vector<Player*>					_players;
  std::list<Player*>					_IAplayers;
  Map::Pos						_mapSize;
  GameEngine::MapParameters				_params;
  int							_solidWallPairPercent;

public:
  /**
   * Empty constructor
   */
  Map();

  /**
   * The virtual destructor
   */
  virtual ~Map();

  /**
   * \return The map width
   */
  int					getWidth() const;

  /**
   * \return The map height
   */
  int					getHeight() const;

  /**
   * Add a playable character
   * \param idPlayerKeys The id of the keys used to move the player
   * \return A pointer to the new player
   */
  Player				*addPlayer(int idPlayerKeys);

  /**
   * Add a playable character with coordinates
   * \param x The x coordinate
   * \param y The y coordinate
   * \param idPlayerKeys The id of the keys used to move the player
   * \return A pointer to the new player
   */
  Player				*addPlayer(int x, int y, int idPlayerKeys);

  /**
   * Add an IA with coordinates
   * \param x The x coordinate
   * \param y The y coordinate
   * \return A pointer to the new player
   */
  Player				*addIAPlayer(int x, int y);

  /**
   * Add an IA
   * \return A pointer to the new player
   */
  Player				*addPlayer();

  /**
   * \return The number of IA alive
   */
  int					nbIAplayersAlive() const;

  /**
   * \return A reference to the vector of players
   */
  const std::vector<Player*> &		getPlayers() const;

  /**
   * Fill a vector with the players ordered by id
   * \param players The vector to fill
   */
  void					getOrderedRealPlayers(std::vector<Player*>& players) const;

  /**
   * Set the parameters of the map
   * \param parameters The parameters to set
   */
  void					setParameters(const GameEngine::MapParameters& parameters);

  /**
   * Generate a new map from scratch with the passed parameters
   * \param MapParameters The parameters to use in order to create the map
   */
  void					generate(const GameEngine::MapParameters &MapParameters);

  /**
   * Print the ASCII representation of the map
   */
  void					print() const;

  /**
   * Remove all entities at the specified location
   * \param posX The x coordinate
   * \param posY The y coordinate
   */
  void					clearEntitysAt(const int posX, const int posY);

  /**
   * Remove a specific entity at the specified location
   * \param posX The x coordinate
   * \param posY The y coordinate
   * \param entity The entity to remove
   */
  bool					delEntityLikeAt(const int posX, const int posY,
							const AEntity *entity);

  /**
   * Move an entity in the map
   * \param entity The entity to move
   * \param x The current x coordinate
   * \param y The current y coordinate
   * \param x2 The new x coordinate
   * \param y2 The new y coordinate
   */
  void					moveEntityFromTo(AEntity* entity, int x, int y, int x2, int y2);

  /**
   * Draw all the entities on a specified scope
   * \param shader The shader used to draw
   * \param clock The game's clock
   * \param x The x coordinate
   * \param y The y coordinate
   * \param nbCase The range of cases to draw
   */
  void					draw(gdl::AShader &shader, gdl::Clock const &clock,
					     int x, int y, int nbCase);

  /**
   * Update all the updatable entities on the map
   * \param clock The game's clock
   */
  void					update(gdl::Clock const &clock);

  /**
   * Get all the entities close to the specified location
   * \param tab The entities found
   * \param posX The x coordinate
   * \param posY The y coordinate
   * \param collidable If true only collidable entities will be reported
   */
  void					getProxyEntities(std::list<AEntity*>& tab, const int posX,
							 const int posY, bool collidable) const;

  /**
   * Get all the entities at the specified position
   * \param posX The x coordinate
   * \param posY The y coordinate
   * \return The constant list of entities (cannot be modified)
   */
  const std::list<AEntity *>		*getEntitysAt(const int posX, const int posY) const;

  /**
   * Get all the entities at the specified position
   * \param posX The x coordinate
   * \param posY The y coordinate
   * \return The list of entities
   */
  std::list<AEntity *>			*getEntitysAt(const int posX, const int posY);

  /**
   * Add an entity at the specified location
   * \param posX The x coordinate
   * \param posY The y coordinate
   * \param entity The entity to add
   * \return A boolean true if the entity has been added
   */
  bool					addEntityAt(const int posX, const int posY, AEntity * entity);

  /**
   * Add an entity to be destroy after the update loop
   * \param entity The entity to delete
   */
  void					addEntityToTrash(AEntity *entity);

  /**
   * Create an empty map with the asked dimensions
   * \param width The width of the map
   * \param height The height of the map
   */
  void					createEmptyMap(int width, int height);

  /**
   * Get all the entities on the map
   * \param entities The entities found
   */
  void					getAllEntities(std::list<AEntity*>& entities) const;

  /**
   * \return A const reference of the actual map parameters
   */
  const GameEngine::MapParameters&	getParams() const;

  /**
   * The serialisation of the map
   * \param out The stream to write
   */
  virtual void				serialize(std::ostream& out) const;

  /**
   * The unserialization of the map
   * \param in The stream to read
   */
  virtual void				unserialize(std::istream& in);

private:
  void					insertPlayersOnCircle(const GameEngine::MapParameters &MapParameters);
  void					insertPlayersOnRectangle(const GameEngine::MapParameters &MapParameters,
								 const bool rectangleOnX);
  void					insertPlayers(const GameEngine::MapParameters &MapParameters);
  void					clearSpawnArea(const int posX, const int posY);
  void					clearArea(const int posX, const int posY, const int size);
  void					checkPosition(Map::Pos *position) const;
  void					checkRange(const int posX, const int posY) const;
  std::vector<std::list<AEntity *> *>	*createLine(const GameEngine::MapParameters &MapParameters, const int posY);
  template <typename T>
  void					addRandomCircleArea(const GameEngine::MapParameters &MapParameters);
  template <typename T>
  void					addCircleArea(const int posX, const int posY, const int size, const int density);
  bool					isEntityInList(const std::list<AEntity *> &list, const AEntity * entity) const;
  bool					isInteractive(const std::list<AEntity *> &list) const;

private:
  Map(const Map &);
  Map &operator=(const Map &);
};

#endif /* !MAP_HPP_ */
