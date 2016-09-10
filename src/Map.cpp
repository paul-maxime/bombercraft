#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <Clock.hh>
#include <AShader.hh>

#include "EntitiesFactory.hpp"
#include "Map.hpp"
#include "Utils.hpp"
#include "SolidWall.hpp"
#include "Box.hpp"
#include "Bomb.hpp"
#include "MapErrors.hpp"
#include "CorruptedFileError.hpp"
#include "InvalidFileError.hpp"
#include "Wall.hpp"
#include "AEntity.hpp"
#include "GameEngine.hpp"
#include "LuaPlayer.hpp"

/*
** Map
*/
void	Map::print() const
{
  std::vector<std::vector<std::list<AEntity *> *> *>::const_iterator	ItY;
  std::vector<std::list<AEntity *> *>::const_iterator			ItX;

  std::cout << "Map overview :" << std::endl;
  for (ItY = this->_mapData.begin() ; ItY != this->_mapData.end(); ++ItY)
    {
      for (ItX = (*ItY)->begin() ; ItX != (*ItY)->end(); ++ItX)
	{
	  if ((*ItX)->size() == 0)
	    std::cout << ".";
	  else
	    for (std::list<AEntity *>::const_iterator listIt = (*ItX)->begin();
		 listIt != (*ItX)->end(); ++listIt)
	      {
		std::cout << (*listIt)->inChar();
	      }
	  std::cout << " ";
	}
      std::cout << std::endl;
    }
}

bool		Map::isInteractive(const std::list<AEntity *> &list) const
{
  std::list<AEntity *>::const_iterator	it;

  for (it = list.begin(); it != list.end(); it++)
    {
      if ((*it)->inChar() == 'w' || (*it)->inChar() == 'W')
  	return true;
    }
  return false;
}

void	Map::clearArea(const int posX, const int posY, const int size)
{
  Map::Pos	cursor;

  for (int x = 0; x < size; ++x)
    {
      for (int y = 0; y < size; ++y)
	{
	  cursor.y = posY + y;
	  cursor.x = posX + x;
	  if (cursor.x > 0 && cursor.y > 0 &&
	      cursor.x < this->_mapSize.x - 1 && cursor.y < this->_mapSize.y - 1)
	    this->clearEntitysAt(cursor.x, cursor.y);
	}
    }
}

/*
** the center of the circle is at posX posY.
** size : diametre
** density : from 0 to 100
*/
template <typename T>
void	Map::addCircleArea(const int posX, const int posY, const int size,
			   const int density)
{
  Map::Pos	cursor;
  Map::Pos	dest;
  int		distance;
  int		prob;

  cursor.y = posY - size / 2;
  dest.y = posY + size / 2;
  dest.x = posX + size / 2;
  if (dest.y > this->_mapSize.y)
    dest.y = this->_mapSize.y;
  if (dest.x > this->_mapSize.x)
    dest.x = this->_mapSize.x;
  while (cursor.y < dest.y)
    {
      cursor.x = posX - size / 2;
      while (cursor.x < dest.x)
	{
	  if (cursor.x >= 0 && cursor.y >= 0 && cursor.x != 0 && cursor.x != this->_mapSize.x - 1 &&
	      cursor.y != 0 && cursor.y != this->_mapSize.y - 1)
	    {
	      distance = sqrt((posX - cursor.x) * (posX - cursor.x) +
			      (posY - cursor.y) * (posY - cursor.y));
	      if (!this->isInteractive(*(*this->_mapData[cursor.y])[cursor.x]))
		{
		  prob = rand() % 100;
		  if ((distance < size / 2 && prob < density)
		      || ((distance >= size / 2 && prob < density / 2)))
		    {
		      this->clearEntitysAt(cursor.x, cursor.y);
		      this->addEntityAt(cursor.x, cursor.y, new T(this, cursor.x, cursor.y));
		    }
		}
	    }
	  ++cursor.x;
	}
      ++cursor.y;
    }
}

std::vector<std::list<AEntity *> *>	*Map::createLine(const GameEngine::MapParameters &MapParameters, const int posY)
{
  std::vector<std::list<AEntity *> *>	*newLine;
  std::list<AEntity *>			*entityList;
  int					solidWallRoll;
  int					isPair;

  newLine = new std::vector<std::list<AEntity *> *>;
  isPair = 0;
  for (int i = 0; i < this->_mapSize.x; i++)
    {
      solidWallRoll = rand() % 100;
      entityList = new std::list<AEntity *>;
      if (i == 0 || i == this->_mapSize.x - 1 || posY == 0 || posY == this->_mapSize.y - 1)
      	entityList->push_back(new SolidWall(this, i, posY));
      else if (MapParameters.wallGrid == true &&
      	       (isPair % 3 == 0 && posY % 3 == 0 && (solidWallRoll < this->_solidWallPairPercent)))
      	entityList->push_back(new SolidWall(this, i, posY));
      else if (solidWallRoll < MapParameters.wallDensity)
      	entityList->push_back(new Wall(this, i, posY));
      newLine->push_back(entityList);
      ++isPair;
    }
  return newLine;
}

template <typename T>
void	Map::addRandomCircleArea(const GameEngine::MapParameters &MapParameters)
{
  int	posX = rand() % this->_mapSize.x;
  int	posY = rand() % this->_mapSize.y;
  int	size = (Utils::min(this->_mapSize.x, this->_mapSize.y) / 2 + rand()) %
    Utils::max(this->_mapSize.x, this->_mapSize.y);
  int	density = MapParameters.objectsDensity + ((rand() % 25) - 10);

  if (MapParameters.objectsDensity == 0 || density < 0)
    density = 0;
  this->addCircleArea<T>(posX, posY, size, density);
}

void	Map::clearSpawnArea(const int posX, const int posY)
{
  int	minSize = (this->_mapSize.x < this->_mapSize.y) ? this->_mapSize.x : this->_mapSize.y;
  int	maxSpawnAreaSize = 7;
  int	minSpawnAreaSize = 3;
  int	spawnAreaSize = minSize / 8;

  if (spawnAreaSize < minSpawnAreaSize)
    spawnAreaSize = minSpawnAreaSize;
  if (spawnAreaSize > maxSpawnAreaSize)
    spawnAreaSize = maxSpawnAreaSize;
  if (spawnAreaSize % 2 == 0)
    ++spawnAreaSize;
  this->clearArea(posX - spawnAreaSize / 2, posY - spawnAreaSize / 2, spawnAreaSize);
}

Player	*Map::addPlayer(int idPlayerKeys)
{
  int					cursPlayersPos = _availablePlayerPos.size();
  Map::Pos				*playerPos;
  Player				*player;
  std::vector<Map::Pos *>::iterator	elem;

  if (cursPlayersPos == 0)
    return NULL;
  cursPlayersPos = rand() % cursPlayersPos;
  playerPos = _availablePlayerPos[cursPlayersPos];

  elem = std::find(_availablePlayerPos.begin(), _availablePlayerPos.end(), playerPos);
  if (elem != _availablePlayerPos.end())
    _availablePlayerPos.erase(elem);

  this->clearSpawnArea(playerPos->x, playerPos->y);
  player = addPlayer(playerPos->x, playerPos->y, idPlayerKeys);
  delete playerPos;

  return player;
}

Player*	Map::addPlayer(int x, int y, int idPlayerKeys)
{
  Player *player;

  this->checkRange(x, y);

  player = new Player(this, x, y, idPlayerKeys);
  this->addEntityAt(x, y, player);
  this->_players.push_back(player);

  return player;
}

Player	*Map::addIAPlayer(int x, int y)
{
  Player *player;

  this->checkRange(x, y);

  player = new LuaPlayer(this, x, y);
  this->addEntityAt(x, y, player);
  this->_players.push_back(player);
  this->_IAplayers.push_back(player);

  return player;
}

Player	*Map::addPlayer()
{
  int					cursPlayersPos = _availablePlayerPos.size();
  Map::Pos				*playerPos;
  Player				*player;
  std::vector<Map::Pos *>::iterator	elem;

  if (cursPlayersPos == 0)
    return NULL;
  cursPlayersPos = rand() % cursPlayersPos;
  playerPos = _availablePlayerPos[cursPlayersPos];

  elem = std::find(_availablePlayerPos.begin(), _availablePlayerPos.end(), playerPos);
  if (elem != _availablePlayerPos.end())
    _availablePlayerPos.erase(elem);

  player = new LuaPlayer(this, playerPos->x, playerPos->y);

  this->clearSpawnArea(playerPos->x, playerPos->y);
  this->addEntityAt(playerPos->x, playerPos->y, player);
  this->_players.push_back(player);
  delete playerPos;

  return player;
}

const std::vector<Player*> &		Map::getPlayers() const
{
  return _players;
}

void	Map::getOrderedRealPlayers(std::vector<Player*>& players) const
{
  unsigned int i = 0;
  Player* p;

  for (std::vector<Player*>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    {
      if (!(*it)->isIA())
	players.push_back((*it));
    }
  while (i + 1 < players.size())
    {
      if (players[i]->getPlayerNum() > players[i + 1]->getPlayerNum())
	{
	  p = players[i];
	  players[i] = players[i + 1];
	  players[i + 1] = p;
	  i = 0;
	}
      else
	++i;
    }
}

Map::Map()
  : _solidWallPairPercent(100)
{
}

void	Map::checkPosition(Map::Pos *position) const
{
  if (position->x == 0)
    ++position->x;
  if (position->y == 0)
    ++position->y;

  if (position->x == this->_mapSize.x - 1)
    position->x = this->_mapSize.x - 2;
  if (position->y == this->_mapSize.y - 1)
    position->y = this->_mapSize.y - 2;
}

void	Map::insertPlayersOnCircle(const GameEngine::MapParameters &MapParameters)
{
  Map::Pos	mapCenter;
  Map::Pos	*playerPos;
  int		totalPlayers = MapParameters.nbIAPlayers + MapParameters.nbPlayers;
  int		radius = (this->_mapSize.x < this->_mapSize.y) ? this->_mapSize.x : this->_mapSize.y;
  float		distBetweenPlayers = (2 * math::PI) / totalPlayers;

  radius -= 2; // two SolidWall border
  radius = radius / 2 - static_cast<int>(radius * 0.07); // radius * 0.07 for the padding
  mapCenter.x = MapParameters.sizeX / 2;
  mapCenter.y = MapParameters.sizeY / 2;
  for (int i = 0; i < totalPlayers; ++i)
    {
      playerPos = new Map::Pos;
      playerPos->x = mapCenter.x + static_cast<int>(cos(distBetweenPlayers * i) * radius);
      playerPos->y = mapCenter.y + static_cast<int>(sin(distBetweenPlayers * i) * radius);
      this->checkPosition(playerPos);
      _availablePlayerPos.push_back(playerPos);
    }
}

void		Map::insertPlayersOnRectangle(const GameEngine::MapParameters &MapParameters,
					      const bool rectangleOnX)
{
  int		totalPlayers = MapParameters.nbIAPlayers + MapParameters.nbPlayers;
  int		distBetweenPlayers;
  Map::Pos	*playerPos;
  int		startPadding;

  distBetweenPlayers = ((this->_mapSize.x > this->_mapSize.y) ? this->_mapSize.x : this->_mapSize.y)
    / totalPlayers;
  startPadding = distBetweenPlayers / 2;
  for (int i = 0; i < totalPlayers; ++i)
    {
      playerPos = new Map::Pos;
      if (rectangleOnX)
	{
	  playerPos->y = rand () % this->_mapSize.y;
	  playerPos->x = startPadding + i * distBetweenPlayers;
	}
      else
	{
	  playerPos->x = rand () % this->_mapSize.x / 2;
	  playerPos->y = startPadding + i * distBetweenPlayers;
	}
      this->checkPosition(playerPos);
      _availablePlayerPos.push_back(playerPos);
    }
}

void	Map::insertPlayers(const GameEngine::MapParameters &MapParameters)
{
  bool rectangleOnX = this->_mapSize.y < this->_mapSize.x / 1.5;
  Player	*IAplayer;

  if (rectangleOnX || this->_mapSize.x < this->_mapSize.y / 1.5)
    this->insertPlayersOnRectangle(MapParameters, rectangleOnX);
  else
    this->insertPlayersOnCircle(MapParameters);
  for (int i = 0; i < MapParameters.nbIAPlayers; ++i)
    {
      if ((IAplayer = this->addPlayer()) == NULL)
	throw MapException("IAplayer is NULL : there is a serious problem somewhere ...");
      _IAplayers.push_back(IAplayer);
    }
}

void	Map::setParameters(const GameEngine::MapParameters& parameters)
{
  _params = parameters;
}

void	Map::generate(const GameEngine::MapParameters &MapParameters)
{
  this->_params = MapParameters;
  this->_mapSize.y = MapParameters.sizeY;
  this->_mapSize.x = MapParameters.sizeX;
  srand(time(NULL));
  for (int i = 0; i < this->_mapSize.y; i++)
    {
      this->_mapData.push_back(this->createLine(MapParameters, i));
    }
  for (int i = 5; i >= 0; --i)
    this->addRandomCircleArea<Box>(MapParameters);
  this->insertPlayers(MapParameters);
}

int	Map::nbIAplayersAlive() const
{
  int	IAplayersAlive = 0;

  for (std::list<Player *>::const_iterator it = _IAplayers.begin(); it != _IAplayers.end(); ++it)
    if ((*it)->isAlive())
      ++IAplayersAlive;
  return IAplayersAlive;
}

void	Map::getProxyEntities(std::list<AEntity*>& tab, const int posX, const int posY, bool collidable) const
{
  for (int i = posX - 1; i <= posX + 1; ++i)
    {
      for (int j = posY - 1; j <= posY + 1; ++j)
	{
	  if (i >= 0 && i < _mapSize.x && j >= 0 && j < _mapSize.y)
	    {
	      std::list<AEntity*>* ref = (*_mapData[j])[i];
	      for (std::list<AEntity*>::iterator it = ref->begin(); it != ref->end(); ++it)
		{
		  if (!collidable || (*it)->isCollidable())
		    tab.push_back((*it));
		}
	    }
	}
    }
}

const std::list<AEntity *>   *Map::getEntitysAt(const int posX, const int posY) const
{
  this->checkRange(posX, posY);
  return ((*this->_mapData[posY])[posX]);
}

void			Map::checkRange(const int posX, const int posY) const
{
  if (posX < 0 || posY < 0)
    throw MapException("position X or Y < 0");
  if (posY >= this->_mapSize.y)
    throw MapException("position Y out of range : max Y size is " + Utils::toString(this->_mapData.size()) + ", got " + Utils::toString(posY));
  if (posX >= this->_mapSize.x)
    throw MapException("position X out of range : max X size is " + Utils::toString(this->_mapData[posY]->size()) + ", got " + Utils::toString(posX));
}

std::list<AEntity *>   *Map::getEntitysAt(const int posX, const int posY)
{
  this->checkRange(posX, posY);
  return ((*this->_mapData[posY])[posX]);
}

bool			Map::isEntityInList(const std::list<AEntity *> &list,
					    const AEntity * entity) const
{
  std::list<AEntity *>::const_iterator	it;

  for (it = list.begin(); it != list.end(); it++)
    {
      if ((*it) == entity)
	return true;
    }
  return false;
}

bool		Map::addEntityAt(const int posX, const int posY, AEntity * entity)
{
  this->checkRange(posX, posY);
  if (!this->isEntityInList(*(*this->_mapData[posY])[posX], entity) == false)
    {
      std::cerr << "Entity already in list !" << std::endl;
      return false;
    }
  (*this->_mapData[posY])[posX]->push_back(entity);
  if (entity->isUpdatable())
    this->_addToUpdate.push_back(entity);
  return true;
}

void	Map::clearEntitysAt(const int posX, const int posY)
{
  this->checkRange(posX, posY);
  for (std::list<AEntity *>::iterator it = (*this->_mapData[posY])[posX]->begin(); it != (*this->_mapData[posY])[posX]->end(); ++it)
    {
      if ((*it)->isUpdatable())
	{
	  std::vector<AEntity *>::iterator elem;

	  elem = std::find(_toUpdate.begin(), _toUpdate.end(), *it);
	  if (elem != _toUpdate.end())
	    _toUpdate.erase(elem);
	}
    }
  (*this->_mapData[posY])[posX]->clear();
}

void	Map::addEntityToTrash(AEntity *entity)
{
  this->_entityTrash.push_back(entity);
}

bool	Map::delEntityLikeAt(const int posX, const int posY, const AEntity *entity)
{
  std::list<AEntity *>::iterator	it;
  std::vector<AEntity *>::iterator	elem;

  this->checkRange(posX, posY);
  for (it = (*this->_mapData[posY])[posX]->begin(); it != (*this->_mapData[posY])[posX]->end(); it++)
    {
      if ((*it) == entity)
	{
	  (*this->_mapData[posY])[posX]->erase(it);
	  elem = std::find(_toUpdate.begin(), _toUpdate.end(), entity);
	  if (elem != _toUpdate.end())
	    _toUpdate.erase(elem);

	  elem = std::find(_addToUpdate.begin(), _addToUpdate.end(), entity);
	  if (elem != _addToUpdate.end())
	    _addToUpdate.erase(elem);
	  return true;
	}
    }
  return false;
}

void	Map::moveEntityFromTo(AEntity* entity, int x, int y, int x2, int y2)
{
  std::list<AEntity *>::iterator it;

  if (x == x2 && y == y2)
    return ;
  if (x >= 0 && x < _mapSize.x &&
      y >= 0 && y < _mapSize.y &&
      (it = std::find((*_mapData[y])[x]->begin(), (*_mapData[y])[x]->end(), entity)) != (*_mapData[y])[x]->end())
    (*_mapData[y])[x]->erase(it);
  if (x2 >= 0 && x2 < _mapSize.x &&
      y2 >= 0 && y2 < _mapSize.y)
    (*_mapData[y2])[x2]->push_back(entity);
}

void	Map::draw(gdl::AShader &shader, gdl::Clock const &clock, int x, int y, int nbCase)
{
  int	minX = (x - nbCase < 0 ? 0 : x - nbCase);
  int	minY = (y - nbCase < 0 ? 0 : y - nbCase);
  int	maxX = (x + nbCase >= this->_mapSize.x ? this->_mapSize.x - 1 : x + nbCase);
  int	maxY = (y + nbCase >= this->_mapSize.y ? this->_mapSize.y - 1 : y + nbCase);

  for (int i = minY; i <= maxY; ++i)
    {
      for (int j = minX; j <= maxX; ++j)
	{
	  for (std::list<AEntity *>::iterator it = (*this->_mapData[i])[j]->begin();
	       it != (*this->_mapData[i])[j]->end();
	       ++it)
	    {
	      (*it)->draw(shader, clock);
	    }
	}
    }
}

void	Map::update(gdl::Clock const &clock)
{
  std::vector<AEntity *>::iterator it;

  for (it = _toUpdate.begin(); it != _toUpdate.end(); ++it)
    {
      (*it)->update(clock);
    }

  for (it = _entityTrash.begin(); it != _entityTrash.end(); ++it)
    this->delEntityLikeAt((*it)->getPosX(), (*it)->getPosY(), (*it));
  _entityTrash.clear();

  if (_addToUpdate.size())
    {
      _toUpdate.insert(_toUpdate.end(), _addToUpdate.begin(), _addToUpdate.end());
      _addToUpdate.clear();
    }
}

int	Map::getWidth() const
{
  return _mapSize.x;
}

int	Map::getHeight() const
{
  return _mapSize.y;
}

void		Map::createEmptyMap(int width, int height)
{
  std::vector<std::list<AEntity *> *>	*newLine;

  _mapSize.x = width;
  _mapSize.y = height;
  for (int i = 0; i < height; ++i)
    {
      newLine = new std::vector<std::list<AEntity *> *>;
      for (int j = 0; j < width; ++j)
	newLine->push_back(new std::list<AEntity *>);
      _mapData.push_back(newLine);
    }
}

void		Map::getAllEntities(std::list<AEntity*>& entities) const
{
  for (std::vector< std::vector< std::list<AEntity*>* >* >::const_iterator it = _mapData.begin();
       it != _mapData.end();
       ++it)
    {
      for (std::vector< std::list<AEntity*>* >::const_iterator it2 = (*it)->begin();
	   it2 != (*it)->end();
	   ++it2)
	{
	  for (std::list<AEntity*>::const_iterator ent = (*it2)->begin(); ent != (*it2)->end(); ++ent)
	    entities.push_back((*ent));
	}
    }
}

void		Map::serialize(std::ostream& out) const
{
  std::list<AEntity*>	entities;
  getAllEntities(entities);
  SeriMap	seri;

  seri.nbEntities = entities.size();
  for (std::vector<Player*>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    if (!(*it)->isAlive())
      ++seri.nbEntities;
  seri.nbAvailablePlayerPos = _availablePlayerPos.size();
  seri.nbToUpdate = _toUpdate.size();
  seri.nbPlayers = _players.size();
  seri.nbIAplayers = _IAplayers.size();
  seri.solidWallPairPercent = _solidWallPairPercent;
  seri.mapSize = _mapSize;
  writeInFile<SeriMap>(seri, out);
  for (std::vector<Map::Pos *>::const_iterator it = _availablePlayerPos.begin();
       it != _availablePlayerPos.end();
       ++it)
    writeInFile<Map::Pos>(*(*it), out);
  for (std::list<AEntity*>::const_iterator it = entities.begin(); it != entities.end(); ++it)
    (*it)->serialize(out);
  for (std::vector<Player*>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    if (!(*it)->isAlive())
      (*it)->serialize(out);
}

void	Map::unserialize(std::istream& in)
{
  SeriMap seri;
  EntitiesFactory::FactoryType	type;
  EntitiesFactory* factory = EntitiesFactory::getInstance();
  AEntity* entity;
  Player* p;
  Bomb* b;
  std::vector<Bomb*> bombs;
  unsigned int nb = 0,
    nbPlayersKeys = PlayersKeysManager::getInstance()->playersKeysSize();

  readFromFile<SeriMap>(seri, in);
  if (seri.mapSize.x <= 0 || seri.mapSize.y <= 0)
    throw CorruptedFileError("Map size is less than zero.");
  else if (seri.mapSize.x > 1002 || seri.mapSize.y > 1002)
    throw CorruptedFileError("Expected maximum map size of 1002, got " +
			     Utils::toString(seri.mapSize.x) + ";" +
			     Utils::toString(seri.mapSize.y));
  _solidWallPairPercent = seri.solidWallPairPercent;
  if (seri.nbAvailablePlayerPos > nbPlayersKeys)
    throw CorruptedFileError("Excepted maximum player position of " +
			     Utils::toString(nbPlayersKeys) + ", got " +
			     Utils::toString(seri.nbAvailablePlayerPos));
  else if (seri.nbEntities > 2000000)
    throw CorruptedFileError("Excepted maximum entities of 2000000, got " +
			     Utils::toString(seri.nbEntities));
  createEmptyMap(seri.mapSize.x, seri.mapSize.y);
  for (unsigned int i = 0; i < seri.nbAvailablePlayerPos; ++i)
    {
      Map::Pos*	po = new Map::Pos;
      readFromFile<Map::Pos>(*po, in);
    }
  for (unsigned int i = 0; i < seri.nbEntities; ++i)
    {
      readFromFile<EntitiesFactory::FactoryType>(type, in);
      if ((entity = factory->generateEntity(this, 0, 0, type)))
	{
	  entity->unserialize(in);
	  if (entity->isAlive())
	    {
	      try
		{
		  addEntityAt(entity->getPosX(), entity->getPosY(), entity);
		}
	      catch (const MapException&)
		{
		  throw CorruptedFileError("Entity outside the map.");
		}
	    }
	  if (entity->getType() == AEntity::PLAYER && (p = dynamic_cast<Player*>(entity)))
	    {
	      if (p->isIA())
		{
		  _IAplayers.push_back(p);
		}
	      _players.push_back(p);
	    }
	  else if (entity->getType() == AEntity::BOMB && (b = dynamic_cast<Bomb*>(entity)))
	    bombs.push_back(b);
	  ++nb;
	}
      else
	throw CorruptedFileError("Unknown entity");
    }
  for (std::vector<Bomb*>::iterator it = bombs.begin(); it != bombs.end(); ++it)
    (*it)->restoreOwner(_players);
  if (_addToUpdate.size())
    {
      _toUpdate.insert(_toUpdate.end(), _addToUpdate.begin(), _addToUpdate.end());
      _addToUpdate.clear();
    }
  if (nb != seri.nbEntities ||
      _toUpdate.size() != seri.nbToUpdate ||
      _IAplayers.size() != seri.nbIAplayers ||
      _players.size() != seri.nbPlayers)
    throw CorruptedFileError("Number of entities doesn't match");
}

const GameEngine::MapParameters& Map::getParams() const
{
  return _params;
}

Map::~Map()
{
}
