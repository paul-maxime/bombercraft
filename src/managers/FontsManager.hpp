/**
 * \file FontsManager.hpp
 * Contains the fonts manager.
 */

#ifndef FONTS_MANAGER_HPP_
#define FONTS_MANAGER_HPP_

#include "BitmapFont.hpp"

namespace gdl
{
  class Geometry;
  class Texture;
}

/**
 * \class FontsManager
 * This singleton is used to draw 2D texts on the screen.
 */
class FontsManager
{
public:
  /**
   * List of available fonts.
   */
  enum FontType
    {
      DEFAULT = 0
    };

  /**
   * \return the fonts manager instance. Creates it if it doesn't exist.
   */
  static FontsManager*	getInstance();

  /**
   * Frees the memory used by the fonts manager.
   */
  static void		destroy();

  /**
   * Creates a new text geometry.
   * \param geo Geometry where the informations will be stored.
   * \param texture The used texture will be stored in this variable.
   * \param type Font type to use.
   * \param text String to draw.
   */
  void			create(gdl::Geometry& geo,
			       const gdl::Texture*& texture,
			       glm::vec2& size,
			       FontType type,
			       const std::string& text);

private:
  FontsManager();
  virtual ~FontsManager();

  void			registerFont(FontType type, const std::string& name);

  void			generateGeometry(gdl::Geometry& geo,
					 const std::string& text,
					 glm::vec2& size,
					 const BitmapFont* font,
					 const gdl::Texture* texture);

  void			generateLetter(gdl::Geometry& geo,
				       const BitmapFont::BlockChar* shape,
				       const gdl::Texture* texture);


  FontsManager&		operator=(const FontsManager&);

  static FontsManager*			m_instance;
  std::map<FontType, BitmapFont*>	m_fonts;
  std::map<FontType, gdl::Texture*>	m_textures;

  unsigned int				m_delta_x;
  unsigned int				m_delta_y;
};

#endif
