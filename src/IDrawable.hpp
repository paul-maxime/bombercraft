/**
 * \file IDrawable.hh
 * Contains the Drawable interface.
 */

#ifndef I_DRAWABLE_HPP_
#define I_DRAWABLE_HPP_

namespace gdl
{
  class Clock;
  class AShader;
}

/**
 * \class IDrawable
 * Something that can be drawn on the window.
 */
class IDrawable
{
public:
  /**
   * Virtual destructor.
   */
  virtual ~IDrawable() {}

  /**
   * Updates the internal element state.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void update(gdl::Clock const &clock) = 0;

  /**
   * Draws the element on the screen.
   * \param shader The shader which should be used to draw the element.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
};

#endif
