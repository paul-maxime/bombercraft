/**
 * \file TextureManager.hpp.
 * Contains the texture manager.
 */

#ifndef TEXTURE_MANAGER_HPP_
#define TEXTURE_MANAGER_HPP_

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace gdl
{
  class Texture;
}

/**
 * This singleton contains every textures.
 * It is used to load and bind (activate) them.
 */
class TextureManager
{
public:
  /**
   * Texture's list.
   */
  enum TextureName
    {
      DEFAULT,
      BOMB,
      EXPLOSION,
      BACKGROUND,
      SCORE_BACKGROUND,
      INTRO_BACKGROUND,
      MAIN_MENU,
      MENU_INPUT,
      MENU_INPUT_FOCUSED,
      SAVEBOX,
      SAVEBOX_FOCUSED,
      CHECKBOX_NOT_CHECKED,
      CHECKBOX_CHECKED,
      STONE,
      BEDROCK,
      TNT,
      GRASS,
      DIRT,
      COBBLESTONE,
      LIVE,
      REDSTONE_BLOCK,
      BEACON,
      TITLE,
      LOADING_SCREEN,
      GAME_OVER,
      WIN,
      LOSE,
      BOMBS,
      PISTON,
      CREATED_BY,
      DUVAL_H,
      CAUDOU_J,
      DRAIN_A,
      LEDUC_P,
      MORPHE_H
    };

  /**
   * \return the texture manager instance. Creates it if it doesn't exist.
   */
  static TextureManager*	getInstance();

  /**
   * Frees the memory used by the texture manager.
   */
  static void			destroy();

  /**
   * Binds the specified texture (activate it).
   * \param texture Texture's name.
   */
  void				bind(TextureName texture, bool repeat = false) const;

  /**
   * Stores the specified texture's size into a vector.
   * \param texture Texture's name.
   * \param vec Where to store the texture's size.
   */
  void				getSize(TextureName texture, glm::vec2& vec) const;

private:
  TextureManager();
  virtual ~TextureManager();

  TextureManager&	operator=(const TextureManager&);

  static TextureManager*			_instance;
  std::map< TextureName, std::string >		_texturesName;
  std::map< TextureName, gdl::Texture* >	_textures;
};

#endif
