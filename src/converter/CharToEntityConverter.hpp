/**
 * \file CharToEntityConverter.hpp
 * Contains the CharToEntity converter.
 */

#ifndef CHAR_TO_ENTITY_CONVERTER_HPP_
#define CHAR_TO_ENTITY_CONVERTER_HPP_

#include <map>

#include "EntitiesFactory.hpp"
#include "AEntity.hpp"

/**
 * \class CharToEntityConverter
 * Used to convert various entities into ascii characters.
 * Useful if you want to display the map on a terminal.
 */
class CharToEntityConverter
{
public:
  /**
   * Public construtor, initializes the various conversions.
   */
  CharToEntityConverter();

  /**
   * Virtual destructor.
   */
  virtual ~CharToEntityConverter();

  /**
   * Converts the specified entity type into an ascii character.
   * \param type Entity type.
   * \return an ascii character.
   */
  char				convert(EntitiesFactory::FactoryType type) const;

  /**
   * Converts the specified entity type into an ascii character.
   * \param type Entity type.
   * \return an ascii character.
   */
  char				convert(AEntity::Type type) const;

  /**
   * Converts the specified ascii character into an entity type.
   * \param c Ascii-code.
   * \return the entity's factory type.
   */
  EntitiesFactory::FactoryType	convert(char c) const;

  /**
   * Convert the specified ascii character into a color
   * \param c Ascii-code
   * \param color The color container
   */
  void				convertEntityCharToColor(char c, glm::vec3& color) const;

private:
  CharToEntityConverter(const CharToEntityConverter&);
  CharToEntityConverter	operator=(const CharToEntityConverter&);

  std::map<EntitiesFactory::FactoryType, char>		_convert;
  std::map<EntitiesFactory::FactoryType, glm::vec3>	_colors;
};

#endif
