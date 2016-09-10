#include "CharToEntityConverter.hpp"

CharToEntityConverter::CharToEntityConverter()
{
  _convert[EntitiesFactory::UNKNOWN] = '?';
  _convert[EntitiesFactory::BOMB] = 'B';
  _convert[EntitiesFactory::PLAYER_SPEED_BONUS] = 's';
  _convert[EntitiesFactory::BOMB_QUANTITY_BONUS] = 'q';
  _convert[EntitiesFactory::BOMB_RANGE_BONUS] = 'r';
  _convert[EntitiesFactory::BOMB_PUSH_BONUS] = 'p';
  _convert[EntitiesFactory::BOX] = 'b';
  _convert[EntitiesFactory::EXPLOSION] = 'E';
  _convert[EntitiesFactory::FLOOR] = '.';
  _convert[EntitiesFactory::PLAYER] = 'P';
  _convert[EntitiesFactory::LUA_PLAYER] = 'P';
  _convert[EntitiesFactory::SOLID_WALL] = 'w';
  _convert[EntitiesFactory::WALL] = 'W';

  _colors[EntitiesFactory::UNKNOWN] = glm::vec3(0, 0, 0);
  _colors[EntitiesFactory::BOMB] = glm::vec3(0, 0, 255);
  _colors[EntitiesFactory::PLAYER_SPEED_BONUS] = glm::vec3(0, 0, 0);
  _colors[EntitiesFactory::BOMB_QUANTITY_BONUS] = glm::vec3(0, 0, 0);
  _colors[EntitiesFactory::BOMB_RANGE_BONUS] = glm::vec3(0, 0, 0);
  _colors[EntitiesFactory::BOMB_PUSH_BONUS] = glm::vec3(0, 0, 0);
  _colors[EntitiesFactory::BOX] = glm::vec3(0, 51, 127);
  _colors[EntitiesFactory::EXPLOSION] = glm::vec3(0, 0, 127);
  _colors[EntitiesFactory::FLOOR] = glm::vec3(17, 127, 0);
  _colors[EntitiesFactory::PLAYER] = glm::vec3(0, 216, 255);
  _colors[EntitiesFactory::LUA_PLAYER] = glm::vec3(0, 216, 255);
  _colors[EntitiesFactory::SOLID_WALL] = glm::vec3(20, 20, 20);
  _colors[EntitiesFactory::WALL] = glm::vec3(128, 128, 128);
}

CharToEntityConverter::~CharToEntityConverter()
{
}

char	CharToEntityConverter::convert(EntitiesFactory::FactoryType type) const
{
  if (_convert.find(type) == _convert.end())
    return '?';
  return (_convert.at(type));
}

EntitiesFactory::FactoryType	CharToEntityConverter::convert(char c) const
{
  for (std::map<EntitiesFactory::FactoryType, char>::const_iterator it = _convert.begin();
       it != _convert.end();
       ++it)
    {
      if (it->second == c)
	return it->first;
    }
  return (EntitiesFactory::UNKNOWN);
}

char	CharToEntityConverter::convert(AEntity::Type type) const
{
  return (convert(EntitiesFactory::getInstance()->convert(type)));
}

void	CharToEntityConverter::convertEntityCharToColor(char c, glm::vec3& color) const
{
  color = _colors.at(convert(c));
}
