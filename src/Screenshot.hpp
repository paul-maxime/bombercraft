/**
 * \file Screenshop.hpp
 * Contains the Screenshot class.
 */

#ifndef SCREENSHOT_HPP_
#define SCREENSHOT_HPP_

#include <string>

/**
 * \class Screenshot
 * Saves the current OpenGL window into a TGA image.
 */
class Screenshot
{
public:
  /**
   * Creates a new Screenshot object.
   */
  Screenshot();

  /**
   * Frees the memory used by the Screenshot object.
   */
  virtual ~Screenshot();

  /**
   * Saves the current OpenGL context into a buffer.
   * \param w Screen's width.
   * \param h Screen's height.
   */
  void	saveScreenBuffer(unsigned int w, unsigned int h);

  /**
   * Saves the current OpenGL context into a TGA file.
   * \param name File's name (without the final .tga).
   * \param w Screen's width.
   * \param h Screen's height.
   */
  void	screenshotTGA(const std::string& name, unsigned int w, unsigned int h);

  /**
   * Saves the saved buffer into a TGA file.
   * \param name File's name (without the final .tga).
   */
  void	saveBufferTGA(const std::string& name);

  /**
   * Save an ascii map to a TGA file
   * \param nam File's name (without the final .tga).
   * \param map The map to save.
   * \param w Map's width.
   * \param h Map's height.
   * \param fw Ideal size.
   * \param fh Ideal size.
   */
  void	asciiMapToTGA(const std::string& name, const std::string& map,
		      unsigned int w, unsigned int h,
		      unsigned int fw, unsigned int fh);

private:
  Screenshot(const Screenshot&);
  Screenshot&	operator=(const Screenshot&);

  void	writeTGAData(const std::string& file, unsigned int w,
		     unsigned int h, const unsigned char *data);

  unsigned char	_tgaHeader[18];
  unsigned int	_w;
  unsigned int	_h;
  unsigned char	*_data;
};

#endif
