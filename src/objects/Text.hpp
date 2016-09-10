/**
 * \file Text.hpp
 * Defines the Text object.
 */

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <Geometry.hh>
#include "FontsManager.hpp"
#include "AObject.hpp"

/**
 * This object represents a rendered text.
 * Inherits from AObject.
 */
class Text : public AObject
{
public:
  /**
   * Creates an empty Text instance.
   * You shall call init if you use this constructor.
   */
  Text();

  /**
   * Creates a new Text instance. Internally calls init.
   * \param font The font used to render the text.
   * \param text The text to render.
   */
  Text(FontsManager::FontType font, const std::string& text);

  /**
   * Destroys this Text instance.
   */
  virtual ~Text();

  /**
   * Initializes this Text instance.
   * \param font The font used to render the text.
   * \param text The text to render.
   */
  void			init(FontsManager::FontType font, const std::string& text);

  /**
   * Draws the text geometry on the screen.
   * Inherited from AObject.
   * \param shader The shader which should be used to draw the text.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * \return Geometry's width.
   */
  int			getWidth() const;

  /**
   * \return Geometry's height.
   */
  int			getHeight() const;

private:
  Text(const Text&);
  Text& operator=(const Text&);

  FontsManager::FontType	m_font;
  std::string			m_text;
  gdl::Geometry			m_geometry;
  const gdl::Texture*		m_texture;
  int				m_width;
  int				m_height;
};

#endif
