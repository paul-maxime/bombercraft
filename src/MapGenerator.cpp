#include "MapGenerator.hpp"
#include "EntitiesFactory.hpp"
#include "CharToEntityConverter.hpp"
#include "Map.hpp"

Map*	MapGenerator::generate(const SceneChooseMap::AsciiMapInfo& infos,
			       const GameEngine::MapParameters& params)
{
  Map* map = new Map();
  CharToEntityConverter converter;
  EntitiesFactory* factory = EntitiesFactory::getInstance();
  std::vector<glm::vec2> spawnsCpy = infos.spawns;

  map->setParameters(params);
  map->createEmptyMap(infos.width, infos.height);
  for (std::string::const_iterator it = infos.content.begin(); it != infos.content.end(); ++it)
    {
      int x = (it - infos.content.begin()) % infos.width,
	y = (it - infos.content.begin()) / infos.width;
      if ((*it) != converter.convert(EntitiesFactory::PLAYER) &&
	  (*it) != converter.convert(EntitiesFactory::FLOOR))
	map->addEntityAt(x, y, factory->generateEntity(map, x, y, converter.convert((*it))));
    }
  for (int i = 0; i < params.nbPlayers; ++i)
    {
      int pos = std::rand() % spawnsCpy.size();
      int x = spawnsCpy[pos].x, y = spawnsCpy[pos].y;
      
      map->addPlayer(x, y, i);
      spawnsCpy.erase(spawnsCpy.begin() + pos);
    }
  for (int i = 0; i < params.nbIAPlayers; ++i)
    {
      int pos = std::rand() % spawnsCpy.size();
      int x = spawnsCpy[pos].x, y = spawnsCpy[pos].y;

      map->addIAPlayer(x, y);
      spawnsCpy.erase(spawnsCpy.begin() + pos);
    }
  return (map);
}
