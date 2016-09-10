/**
 * \file Sprite.hpp
 * Contains the Sprite object.
 */

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <Geometry.hh>
#include "TextureManager.hpp"
#include "AObject.hpp"

/**
 * This object represents a rendered sprite (2d image).
 * Inherits from AObject.
 */
class Sprite : public AObject
{
public:
  /**
   * Creates an empty Sprite instance.
   * You shall call init if you use this constructor.
   */
  Sprite();

  /**
   * Creates a new Sprite instance. Internally calls init.
   * \param texture The sprite's texture.
   */
  Sprite(TextureManager::TextureName texture);

  /**
   * Creates a new Sprite instance. Internally calls init.
   * \param texture The sprite's texture.
   * \param size The sprite size.
   */
  Sprite(TextureManager::TextureName texture,
	 const glm::vec2& size);

  /**
   * Creates a new Sprite instance. Internally calls init.
   * \param texture The sprite's texture.
   * \param size The sprite size.
   * \param from The origin rectangle (from the texture).
   */
  Sprite(TextureManager::TextureName texture,
	 const glm::vec2& size,
	 const glm::vec4& from);

  /**
   * Destroys this Sprite instance.
   */
  virtual ~Sprite();

  /**
   * Initializes this Sprite instance using the specified texture.
   * \param texture The sprite's texture.
   */
  void			init(TextureManager::TextureName texture);

  /**
   * Initializes this Sprite instance using the specified texture and size.
   * Automatically sets the repeat flag.
   * \param texture The sprite's texture.
   * \param size The sprite size.
   */
  void			init(TextureManager::TextureName texture,
			     const glm::vec2& size);

  /**
   * Initializes this Sprite instance using the specified texture, size and origin.
   * \param texture The sprite's texture.
   * \param size The sprite size.
   * \param from The origin rectangle (from the texture).
   */
  void			init(TextureManager::TextureName texture,
			     const glm::vec2& size,
			     const glm::vec4& from);

  /**
   * Draws the sprite on the screen.
   * Inherited from AObject.
   * \param shader The shader which should be used to draw the sprite.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * Draws the sprite on the screen without binding the texture
   * \param shader The shader which should be used to draw the sprite.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  void			drawCustom(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * Sets the OpenGL repeat flag.
   * \param repeat Does the texture repeat?
   */
  void			setRepeat(bool repeat);

  /**
   * Sets the sprite texture.
   */
  void			setTexture(TextureManager::TextureName texture);

  /**
   * Resize the sprite with its texture
   * \param size the new size of the sprite
   */
  void			resize(const glm::vec2& size);

  /**
   * Resize the sprite with its texture
   * \param size the new size of the sprite
   * \param from the previous size of the sprite
   */
  void			resize(const glm::vec2& size, const glm::vec2& from);

private:
  Sprite(const Sprite&);
  Sprite& operator=(const Sprite&);

  gdl::Geometry			m_geometry;
  TextureManager::TextureName	m_texture;
  bool				m_repeat;
};

#endif
