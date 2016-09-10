#ifndef MAP_GENERATOR_HPP_
#define MAP_GENERATOR_HPP_

#include "GameEngine.hpp"
#include "SceneChooseMap.hpp"

class Map;

class MapGenerator
{
public:
  static Map*	generate(const SceneChooseMap::AsciiMapInfo& infos,
			 const GameEngine::MapParameters& params);
};

#endif
